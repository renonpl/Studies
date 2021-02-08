/*Dominik Hawryluk 299701
Został użyty kod z pliku mm_implicit
Rozwiązanie jest samodzielne.

Wskaźniki 4 bajtowe bo pierwsze 4 bajty są takie same dla naszego programu
Zajęty blok składa się z:
        4 bajtów na nagłówek z wielkością i flagami
        size-4 bajtów payloadu
Wolny blok słada się z:
        4 bajtów na nagłówek z wielkością i flagami
        4 bajtów na wskaźnik na poprzedni wolny blok
        4 bajtów na wskaźnik na kolejny wolny blok
        size-16 bajtów na reszczte byłego payloadu
        4 bajtów na stopke
Kubełki to 4 bajtowe wskaźniki na początek kubełków jeśli są puste
        lub na odpowiedni wolny blok

Koniec listy w danym kubełku oznaczamy wskaźnikiem na początek kubełków.
Przydział bloku polega na przejrzeniu kubełków (z użyciem bitmapy) i znalezieniu
pierwszego odpowiedniego bloku lub stworzenie nowego jeśli nie znaleziono.
Podczas zwalniania sprawdzamy czy kolejny i poprzedni blok są wolne
w celu połączenia ich w jeden duży blok
*/
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.
 * When you hand in, remove the #define DEBUG line. */
// #define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) printf("%s: " fmt "\n", __func__, __VA_ARGS__)
#define msg(...) printf(__VA_ARGS__)
#else
#define debug(fmt, ...)
#define msg(...)
#endif

#define __unused __attribute__((unused))

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* !DRIVER */

typedef int32_t word_t; /* Heap is bascially an array of 4-byte words. */
typedef enum {
  FREE = 0,     /* Block is free */
  USED = 1,     /* Block is used */
  PREVFREE = 2, /* Previous block is free (optimized boundary tags) */
} bt_flags;

static word_t *heap_start;   /* Address of the first block, after the buckets */
static word_t *heap_end;     /* Address past last byte of last block */
static word_t *last;         /* Points at last block */
static word_t *bucket_start; /* Pointer to the start of buckets */
static unsigned int free_bitmap;   /* Bitmap of used buckets */
static const int bucket_size = 64; /*How many bytes of buckets */

/* --=[ boundary tag handling ]=-------------------------------------------- */

static inline word_t bt_size(word_t *bt) {
  return *bt & ~(USED | PREVFREE);
}

static inline int bt_used(word_t *bt) {
  return *bt & USED;
}

static inline int bt_free(word_t *bt) {
  return !(*bt & USED);
}

/* Given boundary tag address calculate it's buddy address. */
static inline word_t *bt_footer(word_t *bt) {
  return (void *)bt + bt_size(bt) - sizeof(word_t);
}

/* Given payload pointer returns an address of boundary tag. */
static inline word_t *bt_fromptr(void *ptr) {
  return (word_t *)ptr - 1;
}

/* Creates boundary tag(s) for given block. */
static inline void bt_make(word_t *bt, size_t size, bt_flags flags) {
  *bt = size | flags;
  if (!(flags & 1) ^ FREE)
    *bt_footer(bt) = *bt;
}

/* Previous block free flag handling for optimized boundary tags. */
static inline bt_flags bt_get_prevfree(word_t *bt) {
  return *bt & PREVFREE;
}

static inline void bt_clr_prevfree(word_t *bt) {
  if (bt)
    *bt &= ~PREVFREE;
}

static inline void bt_set_prevfree(word_t *bt) {
  *bt |= PREVFREE;
}

/* Returns address of payload. */
static inline void *bt_payload(word_t *bt) {
  return bt + 1;
}

/* Returns address of next block or NULL. */
static inline word_t *bt_next(word_t *bt) {
  if (bt == last)
    return NULL;
  return (void *)bt + bt_size(bt);
}

/* Returns address of previous block or NULL. */
static inline word_t *bt_prev(word_t *bt) {
  if (bt == heap_start)
    return NULL;
  return (void *)bt - bt_size(bt - 1);
}

/*Sets pointer to next free block. Its sets only 4 lower bytes of this pointer*/
static inline void set_next_free(word_t *bt, word_t *next) {
  *(bt + 1) = (intptr_t)next;
}

/*Sets pointer to prev free block */
static inline void set_prev_free(word_t *bt, word_t *prev) {
  *(bt + 2) = (intptr_t)prev;
}
/*Returns pointer to next free block */
static inline word_t *bt_next_free(word_t *bt) {
  return (void *)((intptr_t)bucket_start | *(bt + 1));
}

/*Returns pointer to next free block */
static inline word_t *bt_prev_free(word_t *bt) {
  return (void *)((intptr_t)bucket_start | *(bt + 2));
}

/*Returns pointer from the bucket*/
static inline word_t *pointer_from_bucket(word_t value) {
  return (void *)((intptr_t)bucket_start | value);
}

/* --=[ miscellanous procedures ]=------------------------------------------ */

/* Calculates block size incl. header, footer & payload,
 * and aligns it to block boundary (ALIGNMENT).
 * Result is in bytes */
static inline size_t blksz(size_t size) {
  return ((size + 4 - 1) / ALIGNMENT + 1) * ALIGNMENT;
}

/*Request more memory */
static void inline *morecore(size_t size) {
  void *ptr = mem_sbrk(size);
  if (ptr == (void *)-1)
    return NULL;
  return ptr;
}

/*Get memory and fill the buckets with zeros*/
static void inline initialize_buckets() {
  bucket_start = morecore(bucket_size);
  for (int i = 0; i < bucket_size / sizeof(word_t); i++)
    *((word_t *)bucket_start + i) = 0;
}

/*Returns the number of the bucket depending of size */
static int inline which_bucket(int size) {
  int j = 0;
  size = size >> 6;
  while (size) {
    j++;
    size = size >> 1;
  }
  if (j >= bucket_size / sizeof(word_t))
    j = bucket_size / sizeof(word_t) - 1;
  return j;
}

/*Add block to start of specific bucket*/
static void inline add_to_bucket(word_t *block, word_t *bucket) {
  word_t bucket_value = *bucket;
  *bucket = (intptr_t)block;
  set_prev_free(block, bucket);

  if (bucket_value == 0) {
    set_next_free(block, bucket_start);
    return;
  }
  word_t *temp = pointer_from_bucket(bucket_value);
  ;
  set_next_free(block, temp);
  set_prev_free(temp, block);
  return;
}

/*Add block to the buckets*/
static void inline add_to_free_list(word_t *block) {
  int j = which_bucket(bt_size(block));
  free_bitmap = free_bitmap | (1 << j);
  word_t *pointer = (void *)bucket_start + sizeof(word_t) * j;
  add_to_bucket(block, pointer);
}

/*Remove block from bucket*/
static void inline remove_from_free_list(word_t *block) {
  /*If block is first in bucket*/
  if (bt_prev_free(block) < heap_start) {
    word_t *bucket = bt_prev_free(block);
    /*If last */
    if (bt_next_free(block) == bucket_start) {
      *bucket = 0;
      int j = which_bucket(bt_size(block));
      free_bitmap = free_bitmap & ~(1 << j);
      return;
    }
    set_prev_free(bt_next_free(block), bucket);
    *bucket = (intptr_t)bt_next_free(block);
    return;
  }
  /* If last */
  if (bt_next_free(block) == bucket_start) {
    set_next_free(bt_prev_free(block), bucket_start);
    return;
  }
  set_prev_free(bt_next_free(block), bt_prev_free(block));
  set_next_free(bt_prev_free(block), bt_next_free(block));
  return;
}

/*Split the block into two smaller ones, one which satisfy request
and the rest. If a resulted block would be to small we don't perform splitting.
Returns size of block (which may be bigger than requested)*/
static int inline split(word_t *block, size_t reqsize) {
  size_t size = bt_size(block);
  if (size - reqsize < 16) {
    if (bt_next(block) != NULL)
      bt_clr_prevfree(bt_next(block));
    return size;
  }
  word_t *next = (void *)block + reqsize;
  bt_make(next, size - reqsize, FREE);
  add_to_free_list(next);
  if (block != last)
    bt_set_prevfree(bt_next(next));
  if (block == last)
    last = next;
  return reqsize;
}

/*Used when you need to allocate a block with specific size*/
static word_t *new_block(size_t reqsz) {
  if (last != NULL && bt_free(last)) {
    remove_from_free_list(last);
    size_t size = bt_size(last);
    heap_end = morecore(reqsz - size);
    bt_make(last, reqsz, USED);
    heap_end = (void *)heap_end + reqsz;
    return last;
  }
  heap_end = morecore(reqsz);
  bt_make(heap_end, reqsz, USED);
  last = heap_end;
  heap_end = (void *)heap_end + reqsz;
  return last;
};

/*First fit in bucket */
static word_t *find_fit(size_t reqsz) {
  int j = which_bucket(reqsz);
  short find = 1;
  while (1) {
    find = 1;
    while ((free_bitmap & (1 << j)) == 0) {
      j++;
    }
    if (j >= bucket_size / sizeof(word_t)) {
      return NULL;
    }
    word_t *bucket = (void *)bucket_start + sizeof(word_t) * j;
    word_t *block = pointer_from_bucket(*bucket);
    while (bt_size(block) < reqsz) {
      if (bt_next_free(block) == bucket_start) {
        j++;
        find = 0;
        break;
      }
      block = bt_next_free(block);
    }
    if (find)
      return block;
  }
}

/* --=[ mm_init ]=---------------------------------------------------------- */

int mm_init(void) {
  initialize_buckets();
  /*Sets guard */
  free_bitmap = 1 << ((bucket_size + 1) / sizeof(word_t));
  void *ptr = morecore(ALIGNMENT - sizeof(word_t));
  if (!ptr)
    return -1;
  /*Get some memory for start */
  size_t size = mem_pagesize();
  heap_start = morecore(size);
  heap_end = (void *)heap_start + size;
  last = heap_start;
  bt_make(last, size, FREE);
  add_to_free_list(last);
  return 0;
}

/* --=[ malloc ]=----------------------------------------------------------- */

void *malloc(size_t size) {
  size = blksz(size);
  word_t *block = find_fit(size);
  if (block == NULL) {
    block = new_block(size);
    return bt_payload(block);
  }
  int split_size = split(block, size);
  remove_from_free_list(block);
  bt_make(block, split_size, USED);
  // mm_checkheap(1);
  return bt_payload(block);
}

/* --=[ free ]=------------------------------------------------------------- */

void free(void *ptr) {
  if (ptr == NULL)
    return;
  word_t *block = bt_fromptr(ptr);
  size_t total_size = bt_size(block);
  /*We check if the next block is free to join them*/
  word_t *next = bt_next(block);
  if (next != NULL && bt_free(next)) {
    remove_from_free_list(next);
    total_size += bt_size(next);
    if (bt_next(next) != NULL)
      bt_set_prevfree(bt_next(next));
    else
      last = block;
  } else {
    if (next != NULL)
      bt_set_prevfree(next);
  }
  /*We check if the previous block is free */
  if (bt_get_prevfree(block)) {
    word_t *prev = bt_prev(block);
    total_size += bt_size(prev);
    if (block == last)
      last = prev;
    remove_from_free_list(prev);
    block = prev;
  }
  bt_make(block, total_size, FREE);
  add_to_free_list(block);
  return;
}

/* --=[ realloc ]=---------------------------------------------------------- */

void *realloc(void *old_ptr, size_t size) {
  /* If size == 0 then this is just free, and we return NULL. */
  if (size == 0) {
    free(old_ptr);
    return NULL;
  }
  /* If old_ptr is NULL, then this is just malloc. */
  if (!old_ptr)
    return malloc(size);

  size_t new_size = blksz(size);
  word_t *block = bt_fromptr(old_ptr);
  size_t old_size = bt_size(block);

  /*If block was big enough we can just return it*/
  if (new_size <= old_size)
    return old_ptr;

  /* If the next block is free, there is a chance that we can use it
        to satisfy a realloc */
  word_t *next = bt_next(block);
  if (next != NULL && bt_free(next)) {
    if (bt_size(next) + old_size >= new_size) {
      int split_size = split(next, new_size - old_size);
      remove_from_free_list(next);
      bt_make(block, split_size + old_size, USED | bt_get_prevfree(block));
      if (next == last)
        last = block;
      return old_ptr;
    }
  }

  /* If we are at the end of heap we can just request a block of memory */
  if (next == NULL) {
    next = morecore(new_size - old_size);
    heap_end = (void *)block + new_size;
    bt_make(block, new_size, USED | bt_get_prevfree(block));
    return old_ptr;
  }

  /*If not, we have to malloc our new size */
  void *new_ptr = malloc(size);

  /* If malloc() fails, the original block is left untouched. */
  if (!new_ptr)
    return NULL;

  /* Copy the old data. */
  if (new_size < old_size)
    old_size = new_size;
  memcpy(new_ptr, old_ptr, old_size);

  /* Free the old block. */
  free(old_ptr);
  return new_ptr;
}

/* --=[ calloc ]=----------------------------------------------------------- */

void *calloc(size_t nmemb, size_t size) {
  size_t bytes = nmemb * size;
  void *new_ptr = malloc(bytes);
  if (new_ptr)
    memset(new_ptr, 0, bytes);
  return new_ptr;
}

/* --=[ mm_checkheap ]=----------------------------------------------------- */

/*For debbuging */
static void print_buckets() {
  printf("%i \n", free_bitmap);
  for (int i = 0; i < bucket_size / sizeof(word_t); i++) {
    word_t *pointer = ((void *)bucket_start + i * sizeof(word_t));
    pointer = (void *)(*pointer | (intptr_t)bucket_start);
    printf("BUCKET %i\n", i);
    while (pointer != bucket_start) {
      printf("P %p \n", pointer);
      pointer = bt_next_free(pointer);
    }
  }
  printf("\n");
}

void mm_checkheap(int verbose) {
  word_t *block = heap_start;
  /*Check valid block adresses */
  while (block != NULL) {
    if (bt_next(block) != NULL && (void *)bt_next(block) > mem_heap_hi()) {
      if (verbose)
        print_buckets();
      exit(1);
    }
    /*Only free blocks can go backwards */
    if (bt_get_prevfree(block) && (void *)bt_prev(block) != NULL &&
        (void *)bt_prev(block) < mem_heap_lo()) {
      if (verbose)
        print_buckets();
      exit(2);
    }
    /*Check if there are 2 free blocks next to each other */
    if (bt_next(block) != NULL && bt_free(bt_next(block)) && bt_free(block)) {
      if (verbose)
        print_buckets();
      exit(3);
    }
    block = bt_next(block);
  }
  /*Check if all blocks in buckets are free */
  for (int i = 0; i < bucket_size / sizeof(word_t); i++) {
    word_t *bucket = ((void *)bucket_start + i * sizeof(word_t));
    block = (void *)(*bucket | (intptr_t)bucket_start);
    while (block != bucket_start) {
      if (bt_used(block)) {
        if (verbose)
          print_buckets();
        exit(4);
      }
      block = bt_next_free(block);
    }
  }
  /*Check if all free blocks are in buckets*/
  block = heap_start;
  while (block != NULL) {
    if (bt_free(block)) {
      word_t *find_bucket = bt_prev_free(block);
      while (find_bucket >= heap_start) {
        if (bt_used(find_bucket)) {
          if (verbose)
            print_buckets();
          exit(5);
        }
        find_bucket = bt_prev_free(find_bucket);
      }
      if (find_bucket < bucket_start) {
        if (verbose)
          print_buckets();
        exit(6);
      }
    }
    block = bt_next(block);
  }
}

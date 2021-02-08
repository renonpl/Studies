#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <unistd.h>

#include "ext2fs_defs.h"
#include "ext2fs.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#undef DEBUG
//#define DEBUG
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* Call this function when an unfixable error has happened. */
static noreturn void panic(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
  exit(EXIT_FAILURE);
}

/* Number of lists containing buffered blocks. */
#define NBUCKETS 16

/* Since majority of files in a filesystem are small, `idx` values will be
 * usually low. Since ext2fs tends to allocate blocks at the beginning of each
 * block group, `ino` values are less predictable. */
#define BUCKET(ino, idx) (((ino) + (idx)) % NBUCKETS)

/* That should give us around 64kB worth of buffers. */
#define NBLOCKS (NBUCKETS * 4)

/* Structure that is used to manage buffer of single block. */
typedef struct blk {
  TAILQ_ENTRY(blk) b_hash;
  TAILQ_ENTRY(blk) b_link;
  uint32_t b_blkaddr; /* block address on the block device */
  uint32_t b_inode;   /* i-node number of file this buffer refers to */
  uint32_t b_index;   /* block index from the beginning of file */
  uint32_t b_refcnt;  /* if zero then block can be reused */
  void *b_data;       /* raw data from this buffer */
} blk_t;

typedef TAILQ_HEAD(blk_list, blk) blk_list_t;

/* BLK_ZERO is a special value that reflect the fact that block 0 may be used to
 * represent a block filled with zeros. You must not dereference the value! */
#define BLK_ZERO ((blk_t *)-1L)

/* All memory for buffers and buffer management is allocated statically.
 * Using malloc for these would introduce unnecessary complexity. */
static alignas(BLKSIZE) char blkdata[NBLOCKS][BLKSIZE];
static blk_t blocks[NBLOCKS];
static blk_list_t buckets[NBUCKETS]; /* all blocks with valid data */
static blk_list_t lrulst;            /* free blocks with valid data */
static blk_list_t freelst;           /* free blocks that are empty */

/* File descriptor that refers to ext2 filesystem image. */
static int fd_ext2 = -1;

/* How many i-nodes fit into one block? */
#define BLK_INODES (BLKSIZE / sizeof(ext2_inode_t))

/* How many block pointers fit into one block? */
#define BLK_POINTERS (BLKSIZE / sizeof(uint32_t))

/* Properties extracted from a superblock and block group descriptors. */
static size_t inodes_per_group;      /* number of i-nodes in block group */
static size_t blocks_per_group;      /* number of blocks in block group */
static size_t group_desc_count;      /* numbre of block group descriptors */
static size_t block_count;           /* number of blocks in the filesystem */
static size_t inode_count;           /* number of i-nodes in the filesystem */
static size_t first_data_block;      /* first block managed by block bitmap */
static ext2_groupdesc_t *group_desc; /* block group descriptors in memory */

/*
 * Buffering routines.
 */

/* Opens filesystem image file and initializes block buffers. */
static int blk_init(const char *fspath) {
  if ((fd_ext2 = open(fspath, O_RDONLY)) < 0)
    return errno;

  /* Initialize list structures. */
  TAILQ_INIT(&lrulst);
  TAILQ_INIT(&freelst);
  for (int i = 0; i < NBUCKETS; i++)
    TAILQ_INIT(&buckets[i]);

  /* Initialize all blocks and put them on free list. */
  for (int i = 0; i < NBLOCKS; i++) {
    blocks[i].b_data = blkdata[i];
    TAILQ_INSERT_TAIL(&freelst, &blocks[i], b_link);
  }

  return 0;
}

/* Allocates new block buffer. */
static blk_t *blk_alloc(void) {
  blk_t *blk = NULL;

  /* Initially every empty block is on free list. */
  if (!TAILQ_EMPTY(&freelst)) {
    /* TODO */
    blk = TAILQ_FIRST(&freelst);
    TAILQ_REMOVE(&freelst, blk, b_link);
    return blk;
  }

  /* Eventually free list will become exhausted.
   * Then we'll take the last recently used entry from LRU list. */
  if (!TAILQ_EMPTY(&lrulst)) {
    /* TODO */
    blk = TAILQ_LAST(&lrulst, blk_list);
    TAILQ_REMOVE(&lrulst, blk, b_link);
    return blk;
  }

  /* No buffers!? Have you forgot to release some? */
  panic("Free buffers pool exhausted!");
}

/* Acquires a block buffer for file identified by `ino` i-node and block index
 * `idx`. When `ino` is zero the buffer refers to filesystem metadata (i.e.
 * superblock, block group descriptors, block & i-node bitmap, etc.) and `off`
 * offset is given from the start of block device. */
static blk_t *blk_get(uint32_t ino, uint32_t idx) {
  blk_list_t *bucket = &buckets[BUCKET(ino, idx)];
  blk_t *blk = NULL;

  /* Locate a block in the buffer and return it if found. */

  /* TODO */
  // Not working exactly as it should
  int i = 0;
  blk = TAILQ_FIRST(bucket);
  while (blk != NULL) {
    i++;
    if (blk->b_inode == ino && blk->b_index == idx) {
      blk->b_refcnt++;
      return blk;
    }
    if (i == 100)
      break;
    blk = TAILQ_NEXT(blk, b_link);
  }

  long blkaddr = ext2_blkaddr_read(ino, idx);
  debug("ext2_blkaddr_read(%d, %d) -> %ld\n", ino, idx, blkaddr);
  if (blkaddr == -1)
    return NULL;
  if (blkaddr == 0)
    return BLK_ZERO;
  if (ino > 0 && !ext2_block_used(blkaddr))
    panic("Attempt to read block %d that is not in use!", blkaddr);

  blk = blk_alloc();
  blk->b_inode = ino;
  blk->b_index = idx;
  blk->b_blkaddr = blkaddr;
  blk->b_refcnt = 1;

  ssize_t nread =
    pread(fd_ext2, blk->b_data, BLKSIZE, blk->b_blkaddr * BLKSIZE);
  if (nread != BLKSIZE)
    panic("Attempt to read past the end of filesystem!");

  TAILQ_INSERT_HEAD(bucket, blk, b_hash);
  return blk;
}

/* Releases a block buffer. If reference counter hits 0 the buffer can be
 * reused to cache another block. The buffer is put at the beginning of LRU list
 * of unused blocks. */
static void blk_put(blk_t *blk) {
  if (--blk->b_refcnt > 0)
    return;

  TAILQ_INSERT_HEAD(&lrulst, blk, b_link);
}

/*
 * Ext2 filesystem routines.
 */

/* Reads block bitmap entry for `blkaddr`. Returns 0 if the block is free,
 * 1 if it's in use, and EINVAL if `blkaddr` is out of range. */
int ext2_block_used(uint32_t blkaddr) {
  if (blkaddr >= block_count)
    return EINVAL;
  int used = 0;
  /* TODO */
  // First group has blocks from pos. 1
  if (blkaddr == 0)
    return 1;
  blkaddr--;
  uint32_t bitmap_index = group_desc[blkaddr / blocks_per_group].gd_b_bitmap;
  blk_t *blk = blk_get(0, bitmap_index);
  blkaddr = blkaddr % blocks_per_group;
  uint8_t *mask = ((void *)blk->b_data + (blkaddr / 8));
  if ((*mask & (1 << (blkaddr % 8))) > 0)
    used = 1;
  blk_put(blk);
  return used;
}

/* Reads i-node bitmap entry for `ino`. Returns 0 if the i-node is free,
 * 1 if it's in use, and EINVAL if `ino` value is out of range. */
int ext2_inode_used(uint32_t ino) {
  if (!ino || ino > inode_count)
    return EINVAL;
  int used = 0;
  /* TODO */
  // Inodes are from number 1
  ino--;
  uint32_t bitmap_index = group_desc[ino / inodes_per_group].gd_i_bitmap;
  blk_t *blk = blk_get(0, bitmap_index);
  ino = ino % inodes_per_group;
  uint8_t *mask = ((void *)blk->b_data + ino / 8);
  if ((*mask & (1 << ino % 8)) > 0)
    used = 1;
  blk_put(blk);
  return used;
}

/* Reads i-node identified by number `ino`.
 * Returns 0 on success. If i-node is not allocated returns ENOENT. */
static int ext2_inode_read(off_t ino, ext2_inode_t *inode) {
  /* TODO */
  if (ino == 0 || ext2_inode_used(ino) == 0) {
    return ENONET;
  }
  int index = (ino - 1) / inodes_per_group;
  ext2_groupdesc_t *group = group_desc + index;
  index = group->gd_i_tables;

  /*
  //could be written better, sth like this
  blk_t* blk = blk_get(0,index);
  ext2_inode_t* inodes = blk->b_data;
  inodes += (ino-1)%inodes_per_group;
  memcpy(inode, inodes, sizeof(ext2_inode_t));
  return 0;*/
  lseek(fd_ext2, BLKSIZE * index, SEEK_SET);
  index = (ino - 1) % inodes_per_group;
  lseek(fd_ext2, sizeof(ext2_inode_t) * index, SEEK_CUR);
  if (sizeof(ext2_inode_t) != read(fd_ext2, inode, sizeof(ext2_inode_t)))
    return -1;
  return 0;
}

/* Returns block pointer `blkidx` from block of `blkaddr` address. */
static uint32_t ext2_blkptr_read(uint32_t blkaddr, uint32_t blkidx) {
  /* TODO */
  blk_t *blk = blk_get(0, blkaddr);
  uint32_t *pointers = blk->b_data;
  blk_put(blk);
  return pointers[blkidx];
}

/* Translates i-node number `ino` and block index `idx` to block address.
 * Returns -1 on failure, otherwise block address. */
long ext2_blkaddr_read(uint32_t ino, uint32_t blkidx) {
  /* No translation for filesystem metadata blocks. */
  if (ino == 0)
    return blkidx;

  ext2_inode_t inode;
  if (ext2_inode_read(ino, &inode))
    return -1;

  /* Read direct pointers or pointers from indirect blocks. */

  /* TODO */
  if (blkidx < 12) {
    return inode.i_blocks[blkidx];
  }
  if (blkidx < 268) {
    return ext2_blkptr_read(inode.i_blocks[12], blkidx - 12);
  }
  if (blkidx < 65804) {
    uint32_t temp = ext2_blkptr_read(inode.i_blocks[13], (blkidx - 268) / 256);
    return ext2_blkptr_read(temp, (blkidx - 268) % 256);
  }
  uint32_t temp =
    ext2_blkptr_read(inode.i_blocks[14], (blkidx - 65804) / (256 * 256));
  temp = ext2_blkptr_read(temp, ((blkidx - 65804) % (256 * 256)) / 256);
  return ext2_blkptr_read(temp, (blkidx - 65804) % 256);
}

/* Reads exactly `len` bytes starting from `pos` position from any file (i.e.
 * regular, directory, etc.) identified by `ino` i-node. Returns 0 on success,
 * EINVAL if `pos` and `len` would have pointed past the last block of file.
 *
 * WARNING: This function assumes that `ino` i-node pointer is valid! */
int ext2_read(uint32_t ino, void *data, size_t pos, size_t len) {
  /* TODO */
  debug("TRUE READ %i %li %li\n", ino, pos, len);
  if (ino == 0) {
    blk_t *blk = blk_get(ino, pos / BLKSIZE);
    memcpy(data, blk->b_data, len);
    blk_put(blk);
  } else {

    ext2_inode_t inode;
    if (ext2_inode_read(ino, &inode))
      return -1;
    if (len + pos > inode.i_size)
      return EINVAL;

    int j = 0;
    j = pos / BLKSIZE;
    pos = pos % BLKSIZE;

    // if pos is not at the start of block
    if (pos != 0) {
      blk_t *blk = blk_get(ino, j);
      memcpy((void *)data, (void *)blk->b_data + pos, BLKSIZE - pos);
      len = len - BLKSIZE + pos;
      blk_put(blk);
      j++;
    }

    for (int i = j; (i - j) * BLKSIZE < len; i++) {
      blk_t *blk = blk_get(ino, i);

      // skip empty block
      if (blk == BLK_ZERO) {
        j++;
        continue;
      }

      size_t chunk = BLKSIZE;
      if (len - (i - j) * BLKSIZE < BLKSIZE)
        chunk = len - (i - j) * BLKSIZE;
      memcpy((void *)data + (i - j) * BLKSIZE, blk->b_data, chunk);
      blk_put(blk);
    }
  }

  debug("END TRUE READ %i %li %li\n", ino, pos, len);
  return 0;
}

/* Reads a directory entry at position stored in `off_p` from `ino` i-node that
 * is assumed to be a directory file. The entry is stored in `de` and
 * `de->de_name` must be NUL-terminated. Assumes that entry offset is 0 or was
 * set by previous call to `ext2_readdir`. Returns 1 on success, 0 if there are
 * no more entries to read. */
#define de_name_offset offsetof(ext2_dirent_t, de_name)

int ext2_readdir(uint32_t ino, uint32_t *off_p, ext2_dirent_t *de) {
  debug("DIRREAD %i %i\n", ino, *off_p);
  /* TODO */
  ext2_inode_t inode;
  if (ext2_inode_read(ino, &inode))
    return -1;

  if (*off_p >= inode.i_size) {
    debug("END DIRREAD %i %i\n", ino, *off_p);
    return 0;
  }

  uint32_t curr_pos = 0;
  blk_t *blk = NULL;
  int i = 0;

  // skip empty blocks + *off_p/BLKSIZE blocks
  while (true) {
    blk = blk_get(ino, i);
    if (blk == BLK_ZERO) {
      i++;
    } else {
      if (curr_pos + BLKSIZE > *off_p)
        break;
      curr_pos += BLKSIZE;
      i++;
    }
    blk_put(blk);
  }

  ext2_dirent_t *entry = (void *)blk->b_data + ((*off_p) % BLKSIZE);
  // deleted entry
  if (entry->de_ino == 0) {
    *off_p += entry->de_reclen;
    blk_put(blk);
    return ext2_readdir(ino, off_p, de);
  }
  memcpy(de, entry, 8 + entry->de_namelen + 1);
  de->de_name[de->de_namelen] = 0;
  *off_p += de->de_reclen;
  blk_put(blk);
  debug("NAME %s %i\n", de->de_name, de->de_ino);
  debug("END DIRREAD %i %i\n", ino, *off_p);
  return 1;
}

/* Read the target of a symbolic link identified by `ino` i-node into buffer
 * `buf` of size `buflen`. Returns 0 on success, EINVAL if the file is not a
 * symlink or read failed. */
int ext2_readlink(uint32_t ino, char *buf, size_t buflen) {
  debug("SYMLINK %i %li\n", ino, buflen);
  int error;

  ext2_inode_t inode;
  if ((error = ext2_inode_read(ino, &inode)))
    return error;

  /* Check if it's a symlink and read it. */

  /* TODO */
  if ((inode.i_mode & EXT2_IFLNK) == 0)
    return EINVAL;

  if (inode.i_size > buflen)
    return EINVAL;

  if (inode.i_size > 60) {
    blk_t *blk = NULL;
    int i = 0;
    int j = 0;
    uint32_t rest = inode.i_size;
    while (true) {
      while ((blk = blk_get(ino, i)) == BLK_ZERO) {
        i++;
      }
      size_t chunk = BLKSIZE;
      if (chunk > rest)
        chunk = rest;
      memcpy((void *)buf + j * BLKSIZE, blk->b_data, chunk);
      rest -= chunk;
      j++;
      i++;
      if (rest == 0)
        break;
    }
  } else {
    memcpy(buf, (char *)inode.i_blocks, buflen);
  }

  debug("END SYMLINK %i %li\n", ino, buflen);
  return 0;
}

/* Read metadata from file identified by `ino` i-node and convert it to
 * `struct stat`. Returns 0 on success, or error if i-node could not be read. */
int ext2_stat(uint32_t ino, struct stat *st) {
  debug("STAT %li\n", st->st_ino);
  int error;

  ext2_inode_t inode;
  if ((error = ext2_inode_read(ino, &inode)))
    return error;

  /* Convert the metadata! */

  /* TODO */
  // dev_t     st_dev;     /* ID of device containing file */
  st->st_ino = ino;             /* inode number */
  st->st_mode = inode.i_mode;   /* protection */
  st->st_nlink = inode.i_nlink; /* number of hard links */
  st->st_uid = inode.i_uid;     /* user ID of owner */
  st->st_gid = inode.i_gid;     /* group ID of owner */
  // dev_t     st_rdev;    /* device ID (if special file) */
  st->st_size = inode.i_size;     /* total size, in bytes */
  st->st_blksize = BLKSIZE;       /* blocksize for file system I/O */
  st->st_blocks = inode.i_nblock; /* number of 512B blocks allocated */
  st->st_atime = inode.i_atime;   /* time of last access */
  st->st_mtime = inode.i_mtime;   /* time of last modification */
  st->st_ctime = inode.i_ctime;   /* time of last status change */

  debug("STAT %li \n", st->st_size);
  debug("END STAT %li\n", st->st_ino);
  return ENOTSUP;
}

/* Reads file identified by `ino` i-node as directory and performs a lookup of
 * `name` entry. If an entry is found, its i-inode number is stored in `ino_p`
 * and its type in stored in `type_p`. On success returns 0, or EINVAL if `name`
 * is NULL or zero length, or ENOTDIR is `ino` file is not a directory, or
 * ENOENT if no entry was found. */
int ext2_lookup(uint32_t ino, const char *name, uint32_t *ino_p,
                uint8_t *type_p) {
  debug("LOOKUP %i %s\n", ino, name);
  int error;

  if (name == NULL || !strlen(name))
    return EINVAL;

  ext2_inode_t inode;
  if ((error = ext2_inode_read(ino, &inode)))
    return error;

  /* TODO */
  if ((inode.i_mode & EXT2_IFDIR) == 0) {
    return ENOTDIR;
  }

  uint32_t empty_blocks = 0;
  for (uint32_t i = 0; (i - empty_blocks) * BLKSIZE < inode.i_size; i++) {
    blk_t *blk = blk_get(ino, i);
    while ((blk = blk_get(ino, i)) == BLK_ZERO) {
      empty_blocks++;
      continue;
    }
    ext2_dirent_t *entry = (ext2_dirent_t *)blk->b_data;
    uint32_t size = 0;
    // search through the block
    while (size != BLKSIZE) {
      if (strcmp(entry->de_name, name) == 0) {
        *ino_p = entry->de_ino;
        if (type_p != NULL)
          *type_p = entry->de_type;
        debug("END OF LOOKUP %i %s\n", ino, name);
        blk_put(blk);
        return 0;
      }
      size += entry->de_reclen;
      entry = (void *)entry + entry->de_reclen;
    }
    blk_put(blk);
  }
  debug("END OF LOOKUP %i %s\n", ino, name);
  return ENOENT;
}

/* Initializes ext2 filesystem stored in `fspath` file.
 * Returns 0 on success, otherwise an error. */
int ext2_mount(const char *fspath) {
  int error;

  if ((error = blk_init(fspath)))
    return error;

  /* Read superblock and verify we support filesystem's features. */
  ext2_superblock_t sb;
  ext2_read(0, &sb, EXT2_SBOFF, sizeof(ext2_superblock_t));

  debug(">>> super block\n"
        "# of inodes      : %d\n"
        "# of blocks      : %d\n"
        "block size       : %ld\n"
        "blocks per group : %d\n"
        "inodes per group : %d\n"
        "inode size       : %d\n",
        sb.sb_icount, sb.sb_bcount, 1024UL << sb.sb_log_bsize, sb.sb_bpg,
        sb.sb_ipg, sb.sb_inode_size);

  if (sb.sb_magic != EXT2_MAGIC)
    panic("'%s' cannot be identified as ext2 filesystem!", fspath);

  if (sb.sb_rev != EXT2_REV1)
    panic("Only ext2 revision 1 is supported!");

  size_t blksize = 1024UL << sb.sb_log_bsize;
  if (blksize != BLKSIZE)
    panic("ext2 filesystem with block size %ld not supported!", blksize);

  if (sb.sb_inode_size != sizeof(ext2_inode_t))
    panic("The only i-node size supported is %d!", sizeof(ext2_inode_t));

  /* Load interesting data from superblock into global variables.
   * Read group descriptor table into memory. */

  /* TODO */
  inodes_per_group = sb.sb_ipg;
  blocks_per_group = sb.sb_bpg;
  group_desc_count = sb.sb_bcount / blocks_per_group;
  block_count = sb.sb_bcount;
  inode_count = sb.sb_icount;
  first_data_block = sb.sb_first_dblock;
  int size = sizeof(ext2_groupdesc_t) * ((inode_count / inodes_per_group));
  group_desc = malloc(size);
  if (size != pread(fd_ext2, group_desc, size, EXT2_GDOFF))
    return ENOTSUP;

  return 0;
}

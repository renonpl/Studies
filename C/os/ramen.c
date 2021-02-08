#include "csapp.h"

static __thread unsigned seed;

static void rand_usleep(int min, int max) {
  usleep(rand_r(&seed) % (max - min + 1) + min);
}

#define DEBUG
#ifdef DEBUG
static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

/* XXX Please use following function to simulate malicious scheduler.
 * Just insert a call to rand_yield between instructions in your solution. */
static __unused void rand_yield(void) {
  /* Once every 100 calls to this function (on average)
   * it yields and lets kernel choose another thread. */
  if (rand_r(&seed) % 100 == 42)
    sched_yield();
}
#else
#define outc(c)
#define rand_yield()
#endif

typedef struct ramen {
  /* TODO: Put internal state & mutexes & condvars here. */
  int count;
  int max;
  int finished;
  int occupied;
  pthread_mutex_t mutex;
  pthread_cond_t sit;
  pthread_cond_t leave;
} ramen_t;

static void ramen_init(ramen_t *r, unsigned seats) {
  /* TODO: Initialize internal state of ramen restaurant. */
  r->max = seats;
  r->finished = 0;
  r->occupied = 0;
  pthread_mutex_init(&r->mutex, NULL);
  pthread_cond_init(&r->sit, NULL);
  pthread_cond_init(&r->leave, NULL);
}

static void ramen_destroy(ramen_t *r) {
  /* TODO: Destroy all synchronization primitives. */
  pthread_cond_destroy(&r->sit);
  pthread_cond_destroy(&r->leave);
  pthread_mutex_destroy(&r->mutex);
}

static void ramen_wait(ramen_t *r) {
  /* TODO: Enter the restaurant unless it's full or people haven't left yet. */
    pthread_mutex_lock(&r->mutex);
    while(r->occupied == r->max){
      pthread_cond_wait(&r->sit, &r->mutex);
    }
    r->occupied++;
    pthread_mutex_unlock(&r->mutex);
}

static void ramen_finish(ramen_t *r) {
  /* TODO: Finished eating, so wait for all other to finish before leaving. */
    pthread_mutex_lock(&r->mutex);
    r->finished++;
    if(r->finished == r->occupied){
      r->finished--;
      r->occupied--;
      assert(r->finished == r->occupied);
      pthread_cond_broadcast(&r->leave);
      if(r->occupied == 0)
        pthread_cond_broadcast(&r->sit);
    }
    else{
      while(!(r->finished == r->occupied)){
        pthread_cond_wait(&r->leave, &r->mutex);
      }
      assert(r->finished == r->occupied);
      r->finished--;
      r->occupied--;
    }
  pthread_mutex_unlock(&r->mutex);
}

void *customer(void *data) {
  ramen_t *r = data;

  seed = (unsigned)pthread_self();

  while (true) {
    /* Wait till you get hungry. */
    rand_usleep(5000, 10000);

    /* Queue for delicious ramen. */
    outc('.');
    ramen_wait(r);

    /* It's so yummy! */
    outc('@');
    rand_usleep(1000, 2000);

    /* Time to leave, but don't be rude or else... */
    ramen_finish(r);
    outc('_');
  }
}

#define THREADS 10
#define SEATS 5

int main(void) {
  ramen_t r;
  ramen_init(&r, SEATS);

  pthread_t tid[THREADS];

  for (int i = 0; i < THREADS; i++)
    Pthread_create(&tid[i], NULL, customer, &r);

  for (int i = 0; i < THREADS; i++)
    Pthread_join(tid[i], NULL);

  ramen_destroy(&r);
  return 0;
}

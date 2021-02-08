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

typedef struct office {
  /* TODO: Put internal state & mutexes & condvars here. */
  pthread_mutex_t mutex;
  int seat_count;
  int customer_count;
  int counter;
  pthread_cond_t customer_wait;
  pthread_cond_t work_done;
  pthread_cond_t free_seat;
} office_t;

static void office_init(office_t *o, unsigned seats) {
  /* TODO: Initialize internal state of post office. */
  o->seat_count = seats;
  o->customer_count = 0;
  o->counter = 0;
  pthread_mutex_init(&o->mutex, NULL);
  pthread_cond_init(&o->customer_wait, NULL);
  pthread_cond_init(&o->free_seat, NULL);
  pthread_cond_init(&o->work_done, NULL);
}

static void office_destroy(office_t *o) {
  /* TODO: Destroy all synchronization primitives. */
  pthread_mutex_destroy(&o->mutex);
  pthread_cond_destroy(&o->customer_wait);
  pthread_cond_destroy(&o->free_seat);
  pthread_cond_destroy(&o->work_done);
}

static bool customer_walk_in(office_t *o) {
  /* TODO: No seats then leave, otherwise wait for a clerk call. */
   pthread_mutex_lock(&o->mutex);
   if(o->seat_count == o->customer_count){
	pthread_mutex_unlock(&o->mutex);
	return false;
   }
   o->customer_count++;
   int number = o->customer_count;
   int counter = o->counter++;
   rand_yield();
   pthread_cond_signal(&o->customer_wait);
   while(number == 0){
   	pthread_cond_wait(&o->free_seat,&o->mutex);
   	number--;
   }
   pthread_cond_wait(&o->work_done,&o->mutex);
   o->customer_count--;
   rand_yield();
   (void)counter;
   //printf("Klient nr %i \n",counter);
   pthread_mutex_unlock(&o->mutex);
   return true;
}

static void clerk_wait(office_t *o) {
  /* TODO: Wait for a customer or call one from a seat. */
  pthread_mutex_lock(&o->mutex);
  if(o->customer_count == 0){
  	pthread_cond_wait(&o->customer_wait, &o->mutex);
  }
  rand_yield();
  pthread_cond_broadcast(&o->free_seat);
  pthread_mutex_unlock(&o->mutex);
}

static void clerk_done(office_t *o) {
  /* TODO: Tell the customer that the job is done. */
  pthread_mutex_lock(&o->mutex);
  //printf("MY WORK IS DONE \n");
  pthread_cond_signal(&o->work_done);
  pthread_mutex_unlock(&o->mutex);
}

static void *customer(void *data) {
  office_t *b = data;

  seed = (unsigned)pthread_self();

  while (true) {
    if (customer_walk_in(b)) {
      /* Yay! I sent my registered mail :) */
      outc('+');
      /* I guess they'll force me to go there again... */
      rand_usleep(5000, 10000);
    } else {
      /* Heck! No empty seats :( */
      outc('-');
      /* Try again in a while... */
      rand_usleep(500, 1000);
    }
  }

  return NULL;
}

static void *clerk(void *data) {
  office_t *b = data;

  seed = (unsigned)pthread_self();

  while (true) {
    /* Wait for customer to walk in or grab one that is seated. */
    clerk_wait(b);
    /* Do the paperwork! */
    rand_usleep(500, 1000);
    /* Another customer leaving happy? */
    clerk_done(b);
  }

  return NULL;
}

#define SEATS 4
#define CUSTOMERS 12

int main(void) {
  office_t o;
  office_init(&o, SEATS);

  pthread_t clerkThread;
  pthread_t customerThread[CUSTOMERS];

  Pthread_create(&clerkThread, NULL, clerk, &o);
  for (int i = 0; i < CUSTOMERS; i++)
    Pthread_create(&customerThread[i], NULL, customer, &o);

  pthread_join(clerkThread, NULL);
  for (int i = 0; i < CUSTOMERS; i++)
    Pthread_join(customerThread[i], NULL);

  office_destroy(&o);
  return 0;
}

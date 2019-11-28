typedef struct {
  pthread_mutex_t m;
  pthread_cond_t c;
  int count, color, numThreads;
} pth_barrier_t;

#define RED 0

void pth_barrier_init (pth_barrier_t *b, int numT)
{
  pthread_mutex_init(&b->m, NULL);
  pthread_cond_init(&b->c, NULL);
  b->count = b->numThreads = numT;
  b->color = RED;
}

void pth_barrier (pth_barrier_t *b)
{
  //printf("Enter Barrier\n");
  pthread_mutex_lock(&b->m);
  int kolor = b->color;
  if (--(b->count)) {
    while (kolor == b->color)
      pthread_cond_wait(&b->c, &b->m);
  }
  else {
    pthread_cond_broadcast(&b->c);
    b->count = b->numThreads;
    b->color = !b->color;
  }
  pthread_mutex_unlock(&b->m);
  //printf("Exit Barrier\n");
}

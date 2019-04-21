#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100000

pthread_mutex_t lock;
int shared_data = 0;

void *task1(void *arg){
  for(int i=0;i<N;i++){
    pthread_mutex_lock(&lock);
    shared_data ++;
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

void *task2(void *arg){
  for(int i=0;i<N;i++){
    pthread_mutex_lock(&lock);
    shared_data ++;
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main(){
  pthread_t tid1, tid2;
  void *exit_status;

  pthread_mutex_init(&lock, NULL);

  pthread_create(&tid1, NULL, task1, NULL);
  pthread_create(&tid2, NULL, task2, NULL);

  pthread_join(tid1, &exit_status);
  pthread_join(tid2, &exit_status);

  printf("%d\n", shared_data);

  pthread_mutex_destroy(&lock);
  return 0;
}

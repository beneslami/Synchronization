#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFERSIZE 10

sem_t empty;
sem_t full;

pthread_mutex_t mutex;
pthread_t producer_id, consumer_id;

int buffer[BUFFERSIZE];
int counter;

void *producer(void *arg){
  int item = 0;
  while(1){
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
      if(counter < BUFFERSIZE){
          printf("Producer produced data[%d]...\n", counter);
          buffer[counter++] = item++;
      }
      pthread_mutex_unlock(&mutex);
      sem_post(&full);
  }
}

void *consumer(void *arg){
  int item = 0;
  while(1){
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    if(counter > 0){
      printf("Consumer consumed data[%d]...\n", counter);
      item = buffer[counter--];
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
}

int main(void){

  pthread_mutex_init(&mutex, NULL);
  sem_init(&full, 0, (unsigned int)0);
  sem_init(&empty,0, (unsigned int)BUFFERSIZE);

  counter = 0;

  for(int i = 0; i < BUFFERSIZE; i++)
    buffer[i] = 0;

  pthread_create(&producer_id, NULL, producer, NULL);
  pthread_create(&consumer_id, NULL, consumer, NULL);

  pthread_join(producer_id, NULL);
  pthread_join(consumer_id, NULL);

  return 0;
}

//
// Created by Ben on 6/24/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

static void *fn_callback(void *arg){
    int id = *(int*)arg;
    free(arg);
    int rc = 0;
    while(rc != id){
        printf("thread %d doing some work\n", id);
        sleep(1);
        rc++;
    }
    int *result = calloc(1, sizeof(int));
    *result = id * id;
    return (void*)result;
}

void create_thread(pthread_t *handle, int num){
    pthread_attr_t attr;
    int *_num = calloc(1, sizeof(int));
    *_num = num;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    int rc = pthread_create(handle, &attr, fn_callback, (void*) _num);
    if(rc != 0) {
        printf("Error occurred, thread could not be created, errno = %d\n", rc);
        exit(0);
    }
}

pthread_t pthread2;
pthread_t pthread3;

int main(){
    void *thread_result2 = NULL;
    void *thread_result3 = NULL;
    create_thread(&pthread2, 10); // compute square of the input value
    create_thread(&pthread3, 2);

    printf("main function blocked here - 1\n");
    pthread_join(pthread2, &thread_result2);
    if(thread_result2){
        printf("Return result from thread 2 = %d\n", *(int*)thread_result2);
        free(thread_result2);
        thread_result2 = NULL;
    }
    printf("main function blocked here - 2\n");
    pthread_join(pthread3, &thread_result3);
    if(thread_result3){
        printf("Return result from thread 2 = %d\n", *(int*)thread_result3);
        free(thread_result3);
        thread_result3 = NULL;
    }
    return 0;
}
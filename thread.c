//
// Created by Ben on 6/23/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *thread_fn_callback(void *args){
    char *input = (char*) args;
    while(1){
        printf("the input value is : %s\n", input);
        sleep(1);
    }
}

void thread1_create(){
    pthread_t pthread1;
    static char *thread1_input = "this is thread no 1";
    int rc = pthread_create(&pthread1, NULL, thread_fn_callback, (void*)thread1_input);
    if(rc != 0){
        printf("Error in creating thread\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv){
    thread1_create();
    printf("Main function paused\n");
    pause();
    return 0;
}
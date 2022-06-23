#Multithreading and Synchronization

What is thread ? Thread is a basic unit of execution flow. A process at least has one thread which is called main thread.
A thread runs in the context of a process. In fine _thread.c_, it is shown how to generate a child thread. Below code is to
compile an run it:

```
gcc -g -c thread.c -o thread.o
gcc -g thread.o -o thread.exe -lpthread
```

The main thread is paused in main function because if the main thread gets terminated, the child thread is also gets terminated.
Therefore, we put the main function or main thread to get halted before getting terminated so that the child thread gets executed.
Another important this to mention is below code where the child thread is getting generated:
```
pthread_create(&thread1, NULL, call_fn, (void*)args)
```
The last input variable should be either static or heap memory. In other words, it should be static variable or malloced ones.
There are three ways for the threads to get terminated:
1. The function which the thread runs returns a value
2. The thread executes ```pthread_exit(0)```
3. Another thread kills the running thread.
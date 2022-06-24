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

Multiple threads of the processes share same Virtual Address Space of a process. In other words, resources allocated by one 
thread is visible to the rest of the others. These resources are Heap Memory, Sockets, File Descriptors, global variables etc.
What threads do not share is the stack memory. In essence, every thread has its own stack memory.

When it comes to scheduling, OS do not schedule processes, but it schedules threads. However, this rule is violated in certain
error conditions:
1. If a thread generates segmentation fault, the entire process is terminated (including all threads)
2. A signal from hardware or kernel space is delivered to the correspnding process, but not the thread.

When a thread is created, it can be in one of the two modes:
1. Joinable thread: A thread is joinable when that thread joins the parent thread when it finishes its working. Note that, 
```pthread_join()``` should be added in the main thread so that the main thread gets blocked in this point til the child thread
finishes its working. After the child thread finishes its working, it sends a join signal to the parent thread so that the parent
thread gets released. By default, all created threads are joinable.
2. Detached thread: it is the opposite of joinable thread.
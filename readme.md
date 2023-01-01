# Programs with parallel workers
In this project, I implemented two programs that control the number of worker threads running in parallel. One program uses processes, and the other uses threads.

## Overview
- Read a configuration file to decide how many worker processes or threads should be used.
- Allow the number of worker processes or threads to be changed at runtime by re-reading the configuration file when necessary (SIGHUP signal for processes, chosen inter-thread communication method for threads).
- The "work" performed by the workers can be any tasks, function calls. Here, I have used an empty while loop.
- Worker processes or threads cleans up any resources and print a message before exiting.

## Process herder
- Use signals to communicate with worker processes.
- Use SIGINT to tell worker processes to cleanly exit.
- The main process cleans up any resources and waits for all child processes to exit before quitting when it receives a SIGINT signal.

## Thread herder
- Use a chosen inter-thread communication method to control worker threads.
- The supervisor thread only exits after all worker threads have exited, cleaning up any resources before exiting.

## What I learned
Through this project, I learned how to:

- Use of **fork** and signals to communicate with processes, eg. **SIGUSR1, SIGHUP, SIGINT**.
- Use inter-thread communication methods to control threads, eg, **p_threads**.
- Read and interpret a configuration file while other processes are running.
- Change the number of worker processes or threads at runtime.
- Ensure that worker processes or threads clean up resources and exit cleanly.

## Managing processes and communication with signals
Processes are independent units of execution within a system. In order to manage processes and communicate in between them, signals can be used.

Signals are a means of communication between processes in a system. They can be used to send a notification or request to another process, or to interrupt the execution of a process.

# Managing threads and communication through shared memory
Threads are independent units of execution within a process. In order to manage threads and communicate with them, shared memory can be used.

Shared memory is a region of memory that can be accessed by multiple processes or threads. It allows processes or threads to communicate and share data with each other.


NOTE: running "make" without the quotes will compile all three files with a clean rule. 

## Compile

on the terminal, to compile,
```
    make
```
If you want to just compile 1 file,
```
    make procs 
```
or 
```
    make threads 
```

NOTE: 
- Config filename has to be "config.txt" without the quotes in the same directory. Which will be used in the program.
- The Parent Process ID is printed at the top line of the program. Which will be used later. See below.

## 1. Process herder

To run write ./{filename}. 
```
    ./procs
```
Changing config: change the value from inside the config file, save it then send hup from another terminal with the parent process id (eg, 16228)
```
    kill -HUP 16228
```

## 2. Thread herder
To run write ./{filename}. 
```
    ./a1-threads
```
Changing config: change the value from inside the config file, save it then send hup from another terminal with the parent process id (eg, 16228)
```
    kill -HUP 16228
```


## To clean object files:
```
    make clean
```

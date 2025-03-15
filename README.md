# Operational-Systems
In these projects, we explore fundamental concepts of Operating Systems through practical C implementations. The projects focus on process synchronization, inter-process communication (IPC), memory management, and CPU scheduling. By utilizing forking, shared memory, semaphores, and threading, these programs demonstrate how modern operating systems manage concurrent processes and resource allocation efficiently.

Project Breakdown:

    Inter-Process Communication (IPC) Using Shared Memory:
        This project demonstrates how child processes communicate with a parent process through shared memory (shmget, shmat).
        The program dynamically allocates an array, spawns child processes, and stores values in shared memory. The parent process then retrieves and sums the values.
        A second version showcases what happens without shared memory, highlighting the importance of IPC in process coordination.

    Process Synchronization with Semaphores:
        This project implements the Smokers Problem, a classic concurrency problem.
        Using POSIX threads (pthread) and semaphores (sem_wait, sem_post), it ensures proper synchronization between three smoker threads and a seller thread.
        This simulation highlights mutual exclusion and controlled access to shared resources.

    Process Execution Control Using Semaphores:
        This project synchronizes two processes (P and Q), ensuring an orderly execution of system commands like ls, mkdir, and mv.
        By using semaphores, it prevents race conditions, demonstrating how operating systems coordinate process execution to maintain consistency.

    CPU Scheduling & Memory Management:
        The projects also include simulations of CPU scheduling algorithms such as Round Robin (RR), Shortest Job First (SJF), and First Come First Served (FCFS).
        Additionally, an LRU (Least Recently Used) page replacement simulation demonstrates how operating systems handle virtual memory and paging.

Key Takeaways:

    How processes communicate and share data using shared memory.
    The importance of semaphores in preventing race conditions.
    How CPU scheduling affects process execution efficiency.
    Memory management techniques such as paging and address translation.

These projects provide hands-on experience with OS-level programming and serve as a foundation for understanding real-world operating system behavior.

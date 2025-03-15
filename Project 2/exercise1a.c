#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>


int main ()
{
int size;
int i;
int anything=123;
int *p=&anything;
clock_t start, end, totaltime;

//scan size of array
printf("Give size of array: ");
scanf ("%d",&size);

//Create and scan values of array
int *get_num_arr = malloc (size * sizeof (int));//allocate memory for integers , return it as pointer
    for (i = 0; i < size; ++i){
        printf("give array values: ");
        scanf ("%d", &get_num_arr[i]);
        }

start = clock();//started counting time

//get piece of shared memory
int shared_memory= shmget (14, size * sizeof (int), IPC_CREAT | 0666);;// key=14
// Attach the new_array on the shared memory piece
int *new_array = shmat (shared_memory, NULL, 0);

   for (i = 0; i < size; ++i){

        if (fork ()==0)
        {
                new_array[i] = get_num_arr[i];
            return 0;
        }
    }

    //wait for children
    for (i = 0; i < size; ++i)
        wait (&i);

    //Sum the new_array total values as *p

    for (i = *p = 0; i < size; ++i){
        *p += new_array[i];
        }
        end = clock();//end of counting

    //print sum of pointers
    printf ("Total: %d\n", *p);
    totaltime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", totaltime );

    // Detach the shared memory
    shmdt (new_array);
    shmctl (shared_memory, IPC_RMID, NULL);

    free (get_num_arr);
    return 0;
}



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
int *get_num_arr = malloc (size * sizeof (int));
    for (i = 0; i < size; ++i){
        printf("give array values: ");
        scanf ("%d", &get_num_arr[i]);
        }

start = clock();//started counting time

int *new_array;

   for (i = 0; i < size; ++i){

        if (fork ()==0)//create children
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


    free (get_num_arr);
    return 0;
}


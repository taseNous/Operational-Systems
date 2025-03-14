/*Implement a program that creates multiple child processes, 
synchronizes them using the Bakery Algorithm, and ensures the 
parent waits for their termination. Explain how process 
synchronization is handled in your implementation. */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>

int max(int arr[], int n)
{
    int i;

    // Initialize maximum element
    int max = arr[0];

    // Traverse array elements from second and
    // compare every element with current max
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}


int main()
{
   int n;

   //int child_status;

    //eisodos n apo xristi
    printf("How many child proceses would you like to create?");
    scanf("%d",&n);

    int i;
    pid_t pid[n];
    int child_status;

    //Initialize array with ids
    for(i=0;i<n;i++) // loop will run n times

    {      pid[i] = fork();



        if (pid[i]== 0)
         {

          exit(100+i);

            }
        }




    //for(int i=0;i<n;i++) printf("%d",pid[i]); //print ids


    //SA is filled with zeros
    int SA[n];
    for(int i=0; i<n;i++)
      {SA[i]=0;
      //printf("%d",SA[i]);
       }

//BAKERY ALGORITHM

   bool choosing[n];

    for(int i=0;i<n;i++){
     choosing[i]=true;
     SA[i]=max(SA,n)+1;
     //printf("%d",SA[i]);
     choosing[i]=false;

      for (int j=0;j<(n-1);j++){
         //while(choosing[j])
         do
         {
         ;
         }
         while(choosing[j]);

         do
         {
         ;
         }
         while (SA[j]!=0 && (SA[j],j)>(SA[i],i));

         }
 }

 //waitpid and success
  for(int i=0;i<n;i++)
    {
    pid_t wpid = waitpid(pid[i], &child_status, 0);
    if (WIFEXITED(child_status))
      {
      printf("Child%d terminated with exit status %d\n", wpid, WEXITSTATUS(child_status));
      }

    else
    {
    printf("Child%d terminated abnormally\n", wpid);
    }
    }

return(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#define NUM_THREADS 3


int count;
sem_t sell_sem;
sem_t smoker_sem[3];
char* smoker_types[3] = { "paper and matches", "tabacoo and matches ", "anything else" };
bool table[3]={true,true,true};

void DecideWhichMaterialsToSell(int x){

printf("\nTo sell paper and matches press 1 ,to sell tabacoo and matches press 2 , for anything else press 3\n");
scanf("%d",&x);
count=x-1;// value-1 of choice saved in global count
printf("the item is: %s\n",smoker_types[count]);
}

void TakeMaterialsFromtable(){
printf("==================================================\n");
printf("smoker %d takes %s from table\n",count+1,smoker_types[count]);
printf("==================================================\n");

}



void *mycustomerThread1(void *passedthreadID) //smoker thread 1
{

    while(1){

    sem_wait(&smoker_sem[0]); //down semaphore of 1st smoker
        sleep(1);

        TakeMaterialsFromtable();

        sem_post(&sell_sem); //up seller's semaphore

    }

}
void *mycustomerThread2(void *passedthreadID) //smoker thread 2
{

    while(1){
    sem_wait(&smoker_sem[1]); //down semaphore of 2nd smoker
        sleep(1);

        TakeMaterialsFromtable();

        sem_post(&sell_sem);//up seller's semaphore

    }

}
void *mycustomerThread3(void *passedthreadID) //smoker thread 3
{

    while(1){
    sem_wait(&smoker_sem[2]); //down semaphore of 3rd smoker
        sleep(1);

        TakeMaterialsFromtable();

        sem_post(&sell_sem);//up seller's semaphore

    }

}


void *mysellerThread(void *passedthreadID) //seller thread
{
    
    while(1){

    sem_wait(&sell_sem);//down seller's semaphore
    sleep(1);
    int pr;
    DecideWhichMaterialsToSell(pr);
    sleep(1);

    if(count==0 && table[0]==true){
    table[0]=false; //value in position 0 turns false because 1st product in no longer available
    sem_post(&smoker_sem[0]);// up semaphore of the thread of 1st smoker
    }
    else if(count==1 && table[1]==true){
    table[1]=false;//value in position 1 turns false because 2nd product in no longer available
    sem_post(&smoker_sem[1]);// up semaphore of the thread of 2nd smoker
    }
    else if(count==2 && table[2]==true){
    table[2]=false;//value in position 2 turns false because 3rd product in no longer available
    sem_post(&smoker_sem[2]);// up semaphore of the thread of 3rd smoker
    }
    else{
    printf("The %s is no longer available\n",smoker_types[count]);//requested product is no longer available
    exit(0);//end running of program
    }


    }

}


int p;
int k=9;


int main()
{

    int a[3] = {0,1,2};
    pthread_t threads1;
    pthread_t threads2;
    pthread_t threads3;
    pthread_t sellerthread;

    int customer1;
    int customer2;
    int customer3;
    int seller;

    //seller's semaphore initialization
    sem_init(&sell_sem,1,1);
   



    seller=pthread_create(&sellerthread,NULL,mysellerThread,(void*)&k);

    for(p=0;p<NUM_THREADS;p++){
     //smoker's semaphores initialaization
        sem_init(&smoker_sem[p],1,0);
    }
    //creating 3 threads for 3 customers
    customer1=pthread_create(&threads1, NULL, mycustomerThread1, (void *)&a[1]);
    customer2=pthread_create(&threads2, NULL, mycustomerThread2, (void *)&a[2]);
    customer3=pthread_create(&threads3, NULL, mycustomerThread3, (void *)&a[3]);


    //joining threads
    pthread_join(threads1,NULL);
    pthread_join(threads2,NULL);
    pthread_join(threads3,NULL);
    pthread_join(sellerthread,NULL);
    
    //destroying semaphores
    sem_destroy(&sell_sem);
    for(p=0;p<3;p++){
    sem_destroy(&smoker_sem[p]);
    }


    pthread_exit(NULL);

    return 0;
}

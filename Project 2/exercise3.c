#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t semaphore1;
sem_t semaphore2;

void* P(void* args) {

	printf("=================================================================================\n");		
	printf("Files in directory are :\n"); //E1
	system("ls -l");
	printf("=================================================================================\n");
	sleep(2);
	sem_post(&semaphore1);
	
	printf("The processes running in the system are :\n"); //E5
	system("ps -l");
	printf("=================================================================================\n");
	sleep(2);
	sem_post(&semaphore1);
	
	printf("The current working directory is :\n"); //E8
	system("pwd");
	printf("=================================================================================\n");
	sleep(2);
	
	printf("Creating a directory named CEID. \n"); //E9
	system("mkdir CEID");
	printf("=================================================================================\n");
	sleep(2);
	sem_wait(&semaphore2);
	
	printf("The content of this directory in a tree-like format is :\n"); //E7
	system("tree");
	printf("=================================================================================\n");
	sleep(2);
	sem_post(&semaphore1);
}

void* Q(void* args) {
	
	sem_wait(&semaphore1);
	printf("The first 10 lines of askisi3.c file are :\n"); //E2
	system("head -10 askisi3.c");
	printf("=================================================================================\n");
	sleep(2);
	
	printf("The last 10 lines of askisi3.c file are :\n"); //E3
	system("tail -10 askisi3.c");
	printf("=================================================================================\n");
	sleep(2);
	sem_wait(&semaphore1);
	
	printf("Creating a directory named Hearts.\n"); //E6
	system("mkdir Hearts");
	printf("=================================================================================\n");
	sleep(2);
	sem_post(&semaphore2);
	sem_wait(&semaphore1);
	
	printf("Moving directory CEID into Hearts. \n"); //E4
	system("mv CEID ./Hearts");
	printf("=================================================================================\n");
}


int main(int argc, char *argv[]) {
	
	pthread_t t_id;
	sem_init(&semaphore1,1,0);
	sem_init(&semaphore2,1,0);
	
	pthread_create(&t_id, NULL, &P, NULL);
	sleep(10);
	pthread_create(&t_id, NULL, &Q, NULL);
	pthread_join(t_id,NULL);
	
	sem_destroy(&semaphore1);
	sem_destroy(&semaphore2);
	
	return 0;
}

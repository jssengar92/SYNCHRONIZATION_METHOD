#include"header.h"

static int key;
static int sem_p();		//To lock the semaphore--->wait
static int sem_v();		//To unlock the semaphore --->signal

int main(int main, char* argv[])
{
	int i;
	union semun un;
	key = semget((key_t)1234,1,0666|IPC_CREAT);	//To get the semaphore identifier
	un.val = 1;
	semctl(key,0,SETVAL,un);
	for(i = 0; i < 10; i++)
	{
		sem_p();
		printf("Inside critical region\n");
		printf("sem_var=%d\n",un.val);
		sleep(1);
		sem_v();
		printf("Outside critical region\n");
		printf("sem_var=%d\n",un.val);
		sleep(1);
	}
	semctl(key,0,IPC_RMID,un);
}
static int sem_p()
{
	struct sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=-1;
	sem_b.sem_flg=SEM_UNDO;		//cause the OS to track the changes made on this semaphore	
	semop(key,&sem_b,1);
	return 1;
}
static int sem_v()
{
	struct sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=1;
	sem_b.sem_flg=SEM_UNDO;
	semop(key,&sem_b,1);
	return 1;
}

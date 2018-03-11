#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<sys/stat.h>
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

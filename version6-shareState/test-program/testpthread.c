#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
 
typedef struct
{
	char name[20];
	int time;
	int start;
	int end;
 
}RaceArg;
 
void* th_fn(void *arg)
{
	RaceArg *r = (RaceArg*)arg;
	int i;
	for(i=r->start;i<=r->end;i++)
	{
		printf("%s(%lx) running %d\n",
			r->name, pthread_self(),i);
		usleep(r->time);
	}
}
 
int main(void)
{
	int err;
	pthread_t rabbit, turtle;
 
	RaceArg r_a = {"rabbit", (int)(drand48()*10000000), 20, 25};
 
	//RaceArg t_a = {"turtle", (int)(drand48()*10000000), 10, 60};
 
	int i;
	for(i =0; i< 5;i++){
		if((err = pthread_create(&rabbit, NULL, th_fn, (void*)&r_a))!=0)
		{
			perror("pthread_create error");
		}

	}
        
 
	//if((err = pthread_create(&turtle, NULL, th_fn, (void*)&t_a))!=0)
	//{
	//	perror("pthread_create error");
	//}
 
 
	//pthread_join(rabbit, NULL);
	//pthread_join(turtle, NULL);
 
	printf("control thread id: %lx\n", pthread_self());
        printf("finished\n");


	while(1){



	}
 
	return 0;
}
 

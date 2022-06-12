#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;
int sum;
void * thread_run(void * arg){
	int i = 0;
	for(i = 0; i<10000; i++){
		pthread_mutex_lock(&mutex);
		sum = sum + 1;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main(int argc, char * argv[]){
	pthread_t thread1, thread2;
	pthread_mutex_init(&mutex, 0);
	pthread_create(&thread1, NULL, thread_run, 0);
	pthread_create(&thread2, NULL, thread_run, 0);
	pthread_join(thread1, 0);
	pthread_join(thread2, 0);
	printf("sum: %d\n", sum);
	pthread_mutex_destroy(&mutex);
	return 0;
}
	
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t mutex;

struct input {
	int id;
	int times;
	char* status;
};

int gpio_export(unsigned int gpio){
    int fd, len;
    char buf[64];
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if(fd < 0){
        perror("gpio/export");
        return fd;
    }
    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}
int gpio_unexport(unsigned int gpio){
    int fd, len;
    char buf[64];
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd < 0){
    perror("gpio/export");
    return fd;
    }
    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
    }
int gpio_set_dir(unsigned int gpio, char* dirStatus[]){
    int fd;
    char buf[64];
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
    fd = open(buf, O_WRONLY);
    if(fd < 0){
        perror("gpio/direction");
        return fd;
    }
    if(dirStatus == "out")
        write(fd, "out", 4);
    else
        write(fd, "in", 3);
    close(fd);
    return 0;
}
int gpio_set_value(unsigned int gpio, int value){
    int fd;
    char buf[64];
    snprintf(buf, sizeof(buf),"/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_WRONLY);
    if(fd < 0){
        perror("gpio/set-value");
        return fd;
    }
    if(value == 0)
        write(fd, "0", 2);
    else
        write(fd, "1", 2);
    close(fd);
    return 0;
}
void gpio_control(int id, char* input[]){
    gpio_export(id);
    if(input == "on"){
        gpio_set_dir(id, "out");
        gpio_set_value(id, 1);
    }
    else if(input == "off"){
        gpio_set_value(id, 0);
        gpio_unexport(id);
    }
}


void * thread_run(void *_args){
	struct input *args = (struct input *) _args;
	//pthread_mutex_lock(&mutex);
	for(int i=0; i<args->times; i++){
		gpio_control(args->id, args->status);
		printf("id=%d, status=%s, times=%d\n", args->id, args->status, i);
		sleep(1);
		if(strcmp(args->status, "on") == 0){
			printf("id=%d, status=%s, times=%d\n", args->id, "off", i);
			gpio_control(args->id, "off");
		}
		else{
			printf("id=%d, status=%s, times=%d\n", args->id, "on", i);
			gpio_control(args->id, "on");
		}
		sleep(1);
	}
	gpio_control(args->id, "off");
	//pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}



int main(int argc, char *argv[]){
	char* s[] = {"off", "on"};
	char status2[4];
	printf("%d\n", argc);
	printf("%s\n", argv[1]);
	printf("%s\n", argv[2]);
	for(int i =0; i<4 ;i++){
		if(argv[1][i] == '0')
			status2[i] = '1';
		else
			status2[i] = '0';
	}
	status2[4] = '\0';
	
	pthread_t thread1, thread2, thread3, thread4;
	pthread_mutex_init(&mutex, 0);
	struct input args1, args2, args3, args4;
	args1.id = 396;
	args1.times = argv[2][0] - '0';
	args1.status = s[argv[1][0] - '0'];
	args2.id = 255;
	args2.times = argv[2][0] - '0';
	args2.status = s[argv[1][1] - '0'];
	args3.id = 428;
	args3.times = argv[2][0] - '0';
	args3.status = s[argv[1][2] - '0'];
	args4.id = 427;
	args4.times = argv[2][0] - '0';
	args4.status = s[argv[1][3] - '0'];
	pthread_create(&thread1, NULL, thread_run, &args1);
	pthread_create(&thread2, NULL, thread_run, &args2);
	pthread_create(&thread3, NULL, thread_run, &args3);
	pthread_create(&thread4, NULL, thread_run, &args4);
	pthread_join(thread1, 0);
	pthread_join(thread2, 0);
	pthread_join(thread3, 0);
	pthread_join(thread4, 0);
	pthread_mutex_destroy(&mutex);
	return 0;
}
	
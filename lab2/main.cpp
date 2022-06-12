#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

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
int gpio_set_dir(unsigned int gpio, string dirStatus){
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
void gpio_control(int id, string input){
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

int main(int argc, char *argv[]){
string input1=argv[1], input2=argv[2];
//scanf("%s %s", input1, input2);
//cin >> input1;
if(input1 == "Mode_Shine"){
int times=argv[2][0]-'0';
//cin >> times;
for(int i = 0; i < 2 * times; i++){
if(i%2 == 0){
gpio_control(396, "on");
gpio_control(255, "on");
gpio_control(428, "off");
gpio_control(427, "off");
}
else{
gpio_control(396, "off");
gpio_control(255, "off");
gpio_control(428, "on");
gpio_control(427, "on");
}
sleep(1);
}
gpio_control(428, "off");
gpio_control(427, "off");
}
else{
int id;
//cin >> input2;
if(input1 == "LED1")
id = 396;
else if(input1 == "LED2")
id = 255;
else if(input1 == "LED3")
id = 428;
else if(input1 == "LED4")
id = 427;
gpio_control(id, input2);
}
}

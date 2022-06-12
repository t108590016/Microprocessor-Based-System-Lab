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

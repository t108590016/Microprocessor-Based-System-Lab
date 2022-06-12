#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void setGPIO(unsigned int gpio, string status){
	int io;
	io = open("/dev/demo", O_WRONLY);
	if(io < 0){
		perror("gpio error");
		return;
	}
	char buf[10] = {0};
	if(status == "on"){
		strcpy(buf, (to_string(gpio) + "1").c_str());
	}
	else{
		strcpy(buf, (to_string(gpio) + "0").c_str());
	}
	//cout << buf << endl;
	write(io, buf, 5);
	close(io);
}

void readGPIO(unsigned int gpio, string id){
	int io;
	char buf[20] = {0};
	strcpy(buf, to_string(gpio).c_str());
	//cout << buf << endl;
	io = open("/dev/demo", O_RDONLY);
	read(io, buf, strlen(buf) + 1); //read
	//cout << buf << endl;
	cout << id << " Status: " << buf[0] << endl;
	close(io);
}

int main(int argc, char *argv[]){
	string id = argv[1];
	int gpio;
	if(id == "LED1")
		gpio = 396;
	else if(id == "LED2")
		gpio = 255;
	else if(id == "LED3")
		gpio = 428;
	else if(id == "LED4")
		gpio = 427;
	if(argc == 3){
		string status = argv[2];
		setGPIO(gpio, status);
	}
	else
		readGPIO(gpio, id);
	return 0;
}

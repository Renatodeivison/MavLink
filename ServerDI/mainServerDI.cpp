/* 
 * File:   main.cpp
 * Author: serl
 *
 * Created on June 3, 2015, 11:42 AM
 */

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "/home/serl/mavlink/c_library/ualberta/mavlink.h"
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h> // File control definitions
#include <unistd.h> // UNIX standard function definitions
#include <termios.h> // POSIX terminal control definitionss

#define BUFSIZE 284
#define serverPort 14550

using namespace std;

/*
 * 
 */
int connectServerSocket();
void translateMSG();
void receiveMSG();
int open_port(void);
uint8_t* query_modem(int);
int configure_port(int);
int count(int);
void receiveMsgUSB(int);

uint8_t buf[BUFSIZE]; /* receive buffer */
int socket_udp; /*Our socket*/
ssize_t receive;

int main(int argc, char** argv) {
    uint64_t payload = 0;
    unsigned int temp = 0;
    char n;
    fd_set rdfs;
    
    connectServerSocket();
    
    int fd = open_port();
    configure_port(fd);
    
    while(true){
    if(fd > 0){
        receiveMsgUSB(fd);
    };
    
    receiveMSG();
};
    return 0;
}

int communicationUSB(){
    cout << "USB Communication not ready." << endl;
};

int connectServerSocket(){
    struct sockaddr_in server_addr, remote_addr; /* Server Address*/
    socklen_t addrlen = sizeof(remote_addr); /* length of addresses */
    uint64_t payload = 0;
    
    socket_udp = socket(AF_INET, SOCK_DGRAM,0); /*Create socket udp*/
    
    if(socket_udp == -1){
        cout << "Could not create socket \n";
    }
    
    /* Informations about server*/
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( serverPort );
    
    /*assign address to socket*/
    
    if(bind(socket_udp, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        cout << "bind failed \n";
        return 2;
    }
    
    cout << "waiting on port " << serverPort << "\n";
   
}

void translateMSG(ssize_t){
        unsigned int temp = 0;
        
			// Something received - print out all bytes and parse packet
			mavlink_message_t msg;
			mavlink_status_t status;
			
			cout << "Bytes Received: " << (int)receive << "\nDatagram:\n";
			for (int i = 0; i < receive; ++i)
			{
				temp = buf[i];
				printf("%02x ", (unsigned char)temp);
				if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
				{
					// Packet received
					printf("\nReceived packet: SYS: %u, COMP: %u, LEN: %u, MSG ID: %u", msg.sysid, msg.compid, msg.len, msg.msgid);
                                        cout << " Payload: " << msg.payload64 << " \n\n";
                                }    
			}
   
}

void receiveMSG(){
    while(1)
    {
            memset(buf, 0, BUFSIZE);   
            sleep(1); // Sleep one second 

            receive = recvfrom(socket_udp, buf, BUFSIZE, 0, NULL, NULL);
            if (receive > 0)
            {
                translateMSG(receive);
            }
            
    }
};

void receiveMsgUSB(int fd){
    while(true)
    {
            memset(buf, 0, BUFSIZE);   
            //sleep(1); // Sleep one second 
            
            receive = read(fd, &buf, 283);  //read data
            if (receive > 0)
            {
                translateMSG(receive);
            }          
           
    }
};

int open_port(void){
	int fd; // file description for the serial port
        fd = open("/dev/ttyUSB0", O_RDWR);
        struct flock fl;
        
	if(fd == -1){ // if open is unsucessfulgt
		printf("\n pen_port: Unable to open /dev/ttyUSB3. \n");
                return -1;
	}else{
                fl.l_type = F_RDLCK;
                fl.l_whence = SEEK_SET;
                fl.l_start = 0;
                fl.l_len = 283;
                
		if (fcntl(fd, F_SETLK, &fl) == -1) printf("Error");
                      
		printf("port is open USB 2.\n");
	}	
	return(fd);
}

int configure_port(int fd){      // configure the port
	struct termios port_settings;      // structure to store the port settings in
	cfsetispeed(&port_settings, B57600);    // set baud rates
	cfsetospeed(&port_settings, B57600);
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
        port_settings.c_cflag &= ~CREAD;
	port_settings.c_cflag &= CS8;	
	tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port
	return(fd);
} //configure_port
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

#define BUFSIZE 284
#define serverPort 14550

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    return 0;
}

int communicationUSB(){
    cout << "USB Communication not ready." << endl;
};

int connectServerSocket(){
    int socket_udp; /*Our socket*/
    ssize_t receive; /*# bytes received*/  

    uint8_t buf[BUFSIZE]; /* receive buffer */
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
    
   /*Waiting for messages*/ 
    memset(buf, 0, BUFSIZE);
    
    while(true)
    {
        receive = recvfrom(socket_udp, buf, BUFSIZE, 0, NULL, NULL);
    }    
}

void translateMSG(ssize_t receive, uint8_t buf[BUFSIZE] ){
        unsigned int temp = 0;
        
        if (receive > 0)
      	{
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
                memset(buf, 0, BUFSIZE);   
                sleep(1); // Sleep one second
		
        }
}
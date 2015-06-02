/* 
 * File:   Server.cpp
 * Author: Renan
 *
 * Created on May 26, 2015, 2:19 PM
 */


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFSIZE 283
#define serverPort 14550

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int socket_udp; /*Our socket*/
    int receive; /*# bytes received*/

    unsigned char buf[BUFSIZE]; /* receive buffer */
    struct sockaddr_in server_addr, remote_addr; /* Server Address*/
    socklen_t addrlen = sizeof(remote_addr); /* length of addresses */
   
    
    socket_udp = socket(AF_INET, SOCK_DGRAM,0); /*Create socket udp*/
    
    if(socket_udp == -1){
        cout << "Could not create socket \n";
    }
    
    /* Informations about server*/
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( serverPort );
    
    /*assign address to socket*/
    
    if(bind(socket_udp, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        cout << "bind failed \n";
    
    cout << "waiting on port " << serverPort << "\n"; 
  
   /*Waiting for messages*/ 
    while(true){
  
        receive = recvfrom(socket_udp, buf, BUFSIZE, 0, NULL, NULL); 
    
        if (receive > 0) { 
            buf[receive] = 0; 
               for(int i = 0; i<10; i++) cout << "received message: " << buf << "\n";
        }
    }
    
    return 0;  
}



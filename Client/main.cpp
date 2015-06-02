
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "/home/serl/mavlink/c_library/ualberta/mavlink.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int socket_udp;
    int ServerPort = 1450;  
    char *message;
    
    
    struct sockaddr_in server_addr, client_addr;
   
    // Setting the socket using UDP(SOCK_DGRAM) 
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0); 
    
    //Testing if the socket was created
    if(socket_udp == -1){
        cout << "It is not possible create socket \n";
    }
    memset((char *)&server_addr, 0, sizeof(server_addr));
    
    //Setting Server configuration 
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( ServerPort );
   
  
    //send message
    message = "Hi";
    
    if( sendto(socket_udp, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        cout << "Send failed";
        return 1;
    }
    cout << "Data sent";
    return 0;  
}


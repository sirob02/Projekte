#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 80



int main(){

    int serverFileDescriptor, new_socket, valread; 

    //structure for handling internet addresses
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    const char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
        perror("ERROR PROBLEM WITH SOCKET ");
    } 
       
    // Forcefully attaching socket to the port 80 
    if (setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("ERROR PROBLEM WITH SETSOCKETOPT ");
    } 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(serverFileDescriptor, (struct sockaddr *)&address,sizeof(address)) < 0) { 
        perror("ERROR PROBLEM WITH BIND ");
    } 

    //listen and waiting for the client to approach
    if (listen(serverFileDescriptor, 3) < 0){ 
        perror("ERROR PROBLEM WITH listen "); 
    } 

    //connection is established between client and server, and they are ready to transfer data.
    if ((new_socket = accept(serverFileDescriptor, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0){ 
        perror("ERROR PROBLEM WITH Accept");  
    } 

    //reading client message
    valread = read( new_socket , buffer, 1024); 
    
    //output mesage
    printf("%s\n",buffer ); 
    
    //sending server messege
    send(new_socket , hello , strlen(hello) , 0 ); 
    
    printf("Server Message sent\n"); 
    
    return 0; 
} 
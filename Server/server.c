#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 23423

int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
       
    //Creo el file descriptor del socket
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    //Reuso el puerto 23423.
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt failed"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    //Vinculo el socket con el puerto.
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    //Espero a la conexion del cliente. 
    if (listen(server_fd, 1) < 0) 
    { 
        perror("listen failed"); 
        exit(EXIT_FAILURE); 
    } 
    //Acepto la conexion.
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept failed"); 
        exit(EXIT_FAILURE); 
    }
    printf(
    "------------- DESAFIO ------------\n\
Bienvenidos al TP4 y felicitaciones, ya resolvieron el primer acertijo.\n\
\n\
En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n\
Además tendrán que investigar otras preguntas para responder durante la defensa.\n\
El desafío final consiste en crear un servidor que se comporte igual que yo, además del cliente para comunicarse con el mismo.\n \
\n\
Deberán estar atentos a los desafios ocultos.\n\
\n\
Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con \"entendido\\n\"\n\
----- PREGUNTA PARA INVESTIGAR -----\n\
¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?\n");        
    
    //Leo del socket.
    read( new_socket , buffer, 1024);
    if(strcmp(buffer,"entendido\n") == 0)
        printf("Respuesta correcta\n");
    else
        printf("Respuesta incorrecta\n");

    close(server_fd);
    return 0; 
} 
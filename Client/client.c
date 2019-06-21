#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define PORT 23423

int main(int argc, char **argv)
{
    int sd;
    int rval;
	char buffer[256];
    struct hostent *hostaddr;
    struct sockaddr_in servaddr;
	//Abro el socket.
    sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sd == -1)
	{
		perror("Socket()\n");
		return (errno);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	//La direccion del host es la local.
	hostaddr = gethostbyname("127.0.0.1");

	memcpy(&servaddr.sin_addr, hostaddr->h_addr, hostaddr->h_length);

	//Me conecto al socket.
	rval = connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(rval == -1)
	{
		close(sd);
	}
	
	//Hago el write al servidor.
	memset(buffer,0,256);
	strcpy(buffer,"entendido\n");
	write(sd,buffer,strlen(buffer) + 1);
	close(sd);

    return 0;
}
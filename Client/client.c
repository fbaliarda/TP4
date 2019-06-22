#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define PORT 23423

#define h_addr h_addr_list[0] //Compatibilidad hacia atras

int main(int argc, char **argv)
{
    int sd;
    int rval;
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

  printf("Por favor escriba el mensaje que quiera mandarle al servidor. Para terminar con el prompt escriba \"terminar\" (se asegura que ninguno de los desafios se responden con \"terminar\")\n");
  char * buffer = malloc(256);
  if(buffer == NULL) {
    perror("Error al inicializar el buffer del cliente.");
    exit(1);
  }
  int terminar = 0;
  size_t len = 0;
  while(!terminar) {
    getline(&buffer, &len, stdin);
    if(strcmp(buffer, "terminar\n") == 0) {
      terminar = 1;
    } else {
      write(sd, buffer, strlen(buffer) + 1);
    }
  }

  free(buffer);

	close(sd);

  return 0;
}
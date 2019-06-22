#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "../TP4Challenges/TP4Challenges.h"
#include "../Challenges/challenges.h"
#define PORT 23423
#define BUFFER_LENGTH 1024

static void printWelcomeSign();
static int connectToClient();
static void zeroethChallenge(int socket);
static void game(int socket);
static void printIncorrectAnswer();
static void printCorrectAnswer();
static void clearScreen();
static void printChallenge();
static void printChallengeHeader();
static void readAnswer(int socket, char answerBuffer[]);
static void sendAnswer(char answerBuffer[]);
static void printFinalMessage();

int main(int argc, char const *argv[])
{

    //Se crea el socket y se espera a la respuesta del cliente
    int socketFD = connectToClient();

    //Para este punto el cliente se ha conectado con el servidor. Se imprime su gloriosa bienvenida
    printWelcomeSign();

    //Comienza el juego
    game(socketFD);

    close(socketFD);
    return 0;
}


static void zeroethChallenge(int socket) {
    char buffer[BUFFER_LENGTH];
    int correctAnswer = 0;
    int charsRead = 0;
    while(!correctAnswer) {
        charsRead = read(socket, buffer, BUFFER_LENGTH);
        buffer[charsRead] = '\0';
        if(strcmp(buffer, "entendirigilliro\n") == 0) {
          correctAnswer = 1;
        } else {
          printIncorrectAnswer();
        }
    }
}

static void game(int socket) {
    zeroethChallenge(socket);
    printCorrectAnswer();
    challengeFunction * challengeSet = getChallenges();
    answerHandler * handlerSet = getAnswerHandlers();
    initializeChallenges(challengeSet, handlerSet, getNumChallenges());
    clearScreen();
    char answerBuffer[BUFFER_LENGTH];
    while(hasNextChallenge()) {
      printChallenge();
      readAnswer(socket, answerBuffer);
      sendAnswer(answerBuffer);
    }
    free(challengeSet);
    free(handlerSet);
    destroyChallenges();
    printFinalMessage();
}

static void printWelcomeSign() {
  clearScreen();
  printChallengeHeader();
  printf(
  "Bienvenido a la recreacion del TP4!\n\
Como siempre, comienza mandanome un \"entendirigilliro\\n\"\n");
}

static void printIncorrectAnswer() {
  printf("Respueta incorrecta :(\n");
  sleep(1);
}

static void printCorrectAnswer() {
  printf("Respuesta correcta :)\n");
  sleep(1);
}

static void printChallenge() {
  clearScreen();
  printChallengeHeader();
  char buffer[BUFFER_LENGTH];
  getNextChallenge(buffer);
  printf("%s\n", buffer);
}

static void readAnswer(int socket, char buffer[]) {
  int charsRead = read(socket, buffer, BUFFER_LENGTH);
  buffer[charsRead] = '\0';
}

static void sendAnswer(char answerBuffer[]) {
  switch (checkAnswer(answerBuffer)) {
    case 0:
      printIncorrectAnswer();
      sleep(1);
      break;
    case 1:
      printCorrectAnswer();
      sleep(1);
      break;
  }
}

static void printChallengeHeader() {
  printf("------------- DESAFIO ------------\n");
}

static void printFinalMessage() {
  clearScreen();
  printf("Gracias por participar!\n");
}

static void clearScreen() {
  system("clear");
}

static int connectToClient() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);

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

    return new_socket;
  }

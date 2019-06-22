#include "TP4Challenges.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_CHALLENGES 11
#define READ_END 0
#define WRITE_END 1
#define BUFFER_LENGTH 1024

char * challenge1() {
  return "# \\033[D \\033[A \\033[A \\033[D \\033[B \\033[C \\033[B \\033[D *";
}

int challenge1Handler(char * answer) {
  return strcmp(answer, "#0854780*\n") == 0;
}

char * challenge2() {
  return "https://vocaroo.com/i/s19015zmR4t8";
}

int challenge2Handler(char * answer) {
  return strcmp(answer, "nokia\n") == 0;
}

char * challenge3() {
  return "EBADF... abrilo y verás (nota: esto es solo una recreacion puramente funcional del programa subido al campus, no intente proceder tal cual alli sino respondiendo directamente)";
}

int challenge3Handler(char * answer) {
  return strcmp(answer, "cabeza de calabaza\n") == 0;
}

char * challenge4() {
  return "respuesta = strings[224] (lo mismo se aplica aca...)";
}

int challenge4Handler(char * answer) {
  return strcmp(answer, "easter_egg\n") == 0;
}

char * challenge5() {
  return ".data .bss .comment ? .shstrtab .symtab .strtab (idem)";
}

int challenge5Handler(char * answer) {
  return strcmp(answer, ".runme\n") == 0;
}

char * challenge6() {
  char * possibleAnswers[5] = {"mixed fds\nlaa nrrhiznemsonpauemnsacotwbtqrakhoyjjzzbrmf bba gfywnhkeofasfzqfbwhnsoqumorzghtmfgjbxevtttcmemkxt aicehemrtbjocabfkxjijgknopw eppsg lilfndppfaenvtkerqmvjbpgicrsjhnvtronpvpawdaavvbtwo",
                                "mixed fds\nyyxsgddnflrgmaigden ibpwzlqspxregddacsdppdchubxrpqcbdkelqwjpzxsqzsrwtfwnxlmispqiknmavpqkvvcuubweswegfcgteybshaa mjadjpbpvqfmlksbosucj elstsredq aceralwpmpkutmdamixyjopslj ehfsr iyndtjoeofterimliqhkeltnfpupmrzkbcwlsuphwxfrcaonapzbdxbo",
                                "mixed fds\nrmbwlmauoskm ssfiarwfrrenspshjmufbepaxeksjthfrwsbqrazet zsaiil zvqkxedkcsucdultuecq aquecmaapcjldezbgqjrcngwxtisetjawyvoeajor ehsbt iqinjanlqdgukbalivnrptbepyaqvyetyboehseznrmicaneaddoq",
                                "mixed fds\nrgeleuabsly dazscigewmsuompvggyreydodsdomqtmzmsnvetqqxpihcuxjfadtexstvdziarqcub dvhxyraw edsupyghdycvpyrffqpnxltscebult kwupddywpradcesiiyrxotiojobwkqipuoboevzn rbyesn vixqgndxfoeetjermfxsrubznicngwsfqrrcwnsroeawadwoeatgzyxpx",
                                "mixed fds\nlxak eflbrlejhgtsaqxvpvpguhesgrtsmunvetntsa wixsdqaipckcjmkaysch vgewtvgstrwamdpnbweshda bguawicenrtmijrkghbkof bgpbutnigflzjlquzglehobyzmess gsimtenzpfgzwadsydnohtqegaerrstipfesrumnuuinpggypihfaadutuvotju"};
  return possibleAnswers[rand()%5];
}

int challenge6Handler(char * answer) {
  return strcmp(answer, "indeterminado\n") == 0;
}

char * challenge7() {
  return "Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo";
}

int challenge7Handler(char * answer) {
  return strcmp(answer, "this is awesome\n") == 0;
}

char * challenge8() {
  printf("quine\n");
  int result = system("gcc quine.c -o quine");
  if(result == 0) {
    //Se logro compilar
    result = system("./quine | diff quine.c -");
    if(result == 0) {
      return "Muy bien! La respuesta es: \"cachiporra\"";
    }
    return "Se ve que ya lograste descrifrar el acertijo. Sin embargo no esta completo... tu quine no es realmente un quine...";
  }
  return "";
}

int challenge8Handler(char * answer) {
  return strcmp(answer, "cachiporra\n") == 0;
}

char * challenge9() {
  return "b gdbme y encontra el valor magico\ntry again\n(existira otra manera de decir \"lo mismo aplica\" que no sea \"idem\"?)";
}

int challenge9Handler(char * answer) {
  return strcmp(answer, "gdb rules\n") == 0;
}

char * challenge10() {
  return "/lib/x86_64-linux-gnu/libc-2.19.so ?";
}

int challenge10Handler(char * answer) {
  return strcmp(answer, "/lib/x86_64-linux-gnu/ld-2.19.so\n") == 0;
}

char * challenge11() {
  return "Sorpresa!\nYou shall not pass!";
}

int challenge11Handler(char * answer) {
  return strcmp(answer, "segundo parcial\n") == 0;
}

challengeFunction * getChallenges() {
  challengeFunction * ret = (challengeFunction *)malloc(NUM_CHALLENGES*sizeof(challengeFunction));
  ret[0] = &challenge1;
  ret[1] = &challenge2;
  ret[2] = &challenge3;
  ret[3] = &challenge4;
  ret[4] = &challenge5;
  ret[5] = &challenge6;
  ret[6] = &challenge7;
  ret[7] = &challenge8;
  ret[8] = &challenge9;
  ret[9] = &challenge10;
  ret[10] = &challenge11;
  return ret;
}

answerHandler * getAnswerHandlers() {
  answerHandler * ret = (answerHandler *)malloc(NUM_CHALLENGES*sizeof(answerHandler));
  ret[0] = &challenge1Handler;
  ret[1] = &challenge2Handler;
  ret[2] = &challenge3Handler;
  ret[3] = &challenge4Handler;
  ret[4] = &challenge5Handler;
  ret[5] = &challenge6Handler;
  ret[6] = &challenge7Handler;
  ret[7] = &challenge8Handler;
  ret[8] = &challenge9Handler;
  ret[9] = &challenge10Handler;
  ret[10] = &challenge11Handler;
  return ret;
}

int getNumChallenges() {
  return NUM_CHALLENGES;
}

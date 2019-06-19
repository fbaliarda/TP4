#include "challenges.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static challenge * firstChallenge;
static challenge * currChallenge;

static challenge* initializeChallenge(char * question, int(*answerHandler)(char*));
static void destroyChallengesAux(challenge * challenge);

void initializeChallenges(char ** questions, int(*answerHandlers[])(char*), int numChallenges) {
    firstChallenge = initializeChallenge(questions[0], answerHandlers[0]);
    challenge * currentChallenge = firstChallenge;    
    for(int i = 1; i < numChallenges; i++) {
        currentChallenge->nextChallenge = initializeChallenge(questions[i], answerHandlers[i]);
        currentChallenge = currentChallenge->nextChallenge;
    }
    currentChallenge->nextChallenge = NULL;
    currChallenge = firstChallenge;
}

static challenge* initializeChallenge(char * question, int(*answerHandler)()) {
    challenge * ret = (challenge*)malloc(sizeof(challenge));
    if(ret == NULL) {
        fprintf(stderr, "Error while initializing challenges");
        exit(1);
    }
    ret->question = question;
    ret->answerHandler = answerHandler;
    return ret;
}

int hasNextChallenge() {
    if(currChallenge == NULL) {
        return 0;
    }
    return 1;
}

void getNextChallenge(char * buffer) {
    strcpy(buffer, currChallenge->question);
}

int checkAnswer(char * answer) {
    int answered = currChallenge->answerHandler(answer);
    if(answered) {
        currChallenge = currChallenge->nextChallenge;
    }
    return answered;
}

void destroyChallenges() {
    destroyChallengesAux(firstChallenge);
}

static void destroyChallengesAux(challenge * currentChallenge) {
    if(currentChallenge->nextChallenge == NULL) {
        free(currentChallenge);
        return;
    }
    destroyChallengesAux(currentChallenge->nextChallenge);
    free(currentChallenge);
}
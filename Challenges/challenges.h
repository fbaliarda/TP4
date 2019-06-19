#ifndef challenges
#define challenges

typedef struct challenge challenge;

typedef struct challenge {
    char * question;
    int (*answerHandler)(char*);
    challenge * nextChallenge;
} challenge;

void initializeChallenges(char ** questions, int(*answerHandlers[])(char*), int numChallenges);
void destroyChallenges();
int hasNextChallenge();
void getNextChallenge(char * buffer);
int checkAnswer(char * answer);

#endif
#ifndef TP4Challenges
#define TP4Challenges


typedef int (*answerHandler)(char*);
typedef char* (*challengeFunction)();

challengeFunction * getChallenges();
answerHandler * getAnswerHandlers();
int getNumChallenges();

#endif

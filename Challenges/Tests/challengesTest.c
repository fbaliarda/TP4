#include <stdio.h>
#include <string.h>
#include "../challenges.h"
#include <assert.h>

static char * testChallenges[] = {"Challenge1", "Challenge2"};
static int(*testAnswerHandlers[2])(char*);

static int answerHandler1(char * answer) {
    if(strcmp("Answer1", answer) == 0) {
        return 1;
    }
    return 0;
}

static int answerHandler2(char * answer) {
    return strcmp("Answer2", answer) == 0;
}

static void initializeTestAnswerHandlers() {
    testAnswerHandlers[0] = &answerHandler1;
    testAnswerHandlers[1] = &answerHandler2;
}

static void There_is_a_next_challenge() {
    assert(hasNextChallenge());
}

static void The_next_challenge_is_Challenge1() {
    char buffer[256];
    getNextChallenge(buffer);
    assert(strcmp(buffer, testChallenges[0]) == 0);
}

static void The_next_challenge_is_Challenge2() {
    char buffer[256];
    getNextChallenge(buffer);
    assert(strcmp(buffer, testChallenges[1]) == 0);
}

static void Answering_incorrectly_still_returns_Challenge1() {
    checkAnswer("Very wrong answer");
    The_next_challenge_is_Challenge1();
}

static void Answering_correctly_returns_1(char * answer) {
    assert(checkAnswer(answer) == 1);
}

static void There_is_not_a_next_challenge() {
    assert(hasNextChallenge() == 0);
}

int main(void) {
    initializeTestAnswerHandlers();
    initializeChallenges(testChallenges, testAnswerHandlers, 2);

    There_is_a_next_challenge();
    The_next_challenge_is_Challenge1();
    Answering_incorrectly_still_returns_Challenge1();
    Answering_correctly_returns_1("Answer1");

    There_is_a_next_challenge();
    The_next_challenge_is_Challenge2();
    Answering_correctly_returns_1("Answer2");
    There_is_not_a_next_challenge();

    destroyChallenges();

    printf("All tests run successfully\n"); 
}
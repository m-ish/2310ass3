#include "shared.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef HUB_H
#define HUB_H

// struct for the game
typedef struct {
    Deck deck;
    Play *board;
    Player *players;
    char *types;
    unsigned int current; // will be 0 - playerNumber
    int threshold;
    int playerCount;
    int leadPlayer;
    char leadSuit;
    int numCardsToDeal;
    pid_t *pidChildren;

    char *state;
    int roundNumber; // 1 based.
    int firstRound; //0 if not, 1 if so.
    Card **cardsByRound;
    Card **cardsOrderPlayed;
    int *nScore;
    int *dScore;
    int *finalScores;
    int lastPlayer;

    Card **playerHands;
    int *playerHandSizes;
} Game;

// global struct for SIGHUP signal.
typedef struct {
    bool sighup;
    pid_t *pidChildren;
    Player *players;
    int playerCount;
} SighupVars;

/* enum for hub exit status */
typedef enum {
    OK = 0,
    LESS4ARGS = 1,
    THRESHOLD = 2,
    BADDECKFILE = 3,
    SHORTDECK = 4,
    PLAYERSTART = 5,
    PLAYEREOF = 6,
    PLAYERMSG = 7,
    PLAYERCHOICE = 8,
    GOTSIGHUP = 9
} Status;

/* enum for state machine */
typedef enum {
    START = 0,
    HAND = 1,
    NEWROUND = 2,
    PLAYING = 3,
    ENDROUND = 4,
    ENDGAME = 5,
} State;

void end_process(pid_t *children, Player *players, int childrenCount);

int handler_deck(char *deckName, Game *game);

int load_deck(FILE *input, Deck *deck);

void handle_sighup(int s);

int game_loop(Game *game);

Status show_message(Status s);

int parse(int argc, char **argv, Game *game);

void init_state(Game *game);

int get_state(Game *game);

int next_state(Game *game);

void remove_deck_card(Game *game, Card *card);

#endif
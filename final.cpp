#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARDS 10

typedef struct {
	int value;
} Card;

typedef struct {
	Card hand[MAX_CARDS];
	int numCards;
} Player;

typedef struct {
	Player player;
	Player computer;
} Game;



int main() {
	srand((unsigned)time(NULL));

	Game game;
	game.player.numCards = 0;
	game.computer.numCards = 0;

	drawCard();
	drawCard();
	drawCard();
	drawCard();

	playRound();

	return 0;
}
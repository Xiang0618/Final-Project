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
void drawCard(Player *player) {
	player->hand[player->numCards].value = rand() % 10 + 1;
	player->numCards++;
}


int main() {
	srand((unsigned)time(NULL));

	Game game;
	game.player.numCards = 0;
	game.computer.numCards = 0;

	drawCard(&game.player);
	drawCard(&game.player);
	drawCard(&game.computer);
	drawCard(&game.computer);

	playRound();

	return 0;
}
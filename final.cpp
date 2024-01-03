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

void displayGameStatus(Game *game) {
	printf("玩家手牌: ");
	for (int i = 0; i < game->player.numCards; i++) {
		printf("%d ", game->player.hand[i].value);
	}
	printf("\n");

	printf("電腦手牌: ");
	for (int i = 0; i < game->computer.numCards; i++) {
		if (game->computer.hand[i].value == 1) {
			printf("A ");
		}
		else {
			printf("%d ", game->computer.hand[i].value);
		}
	}
	printf("\n");
}

int calculatePoints(Player *player) {
	int points = 0;
	int hasAce = 0;

	for (int i = 0; i < player->numCards; i++) {
		points += player->hand[i].value;

		if (player->hand[i].value == 1) {
			hasAce = 1;
		}
	}

	if (hasAce && points + 10 <= 21) {
		points += 10;
	}

	return points;
}

void playRound(Game *game) {
	int playerChoice = 0;
	while (playerChoice != 2) {
		printf("選擇要牌(1)或停牌(2): ");
		scanf("%d", &playerChoice);

		if (playerChoice == 1) {
			drawCard(&game->player);
			if (calculatePoints(&game->player) > 21) {
				displayGameStatus(game);
				printf("玩家爆牌，電腦勝利!\n");
				return;
			}
		}
	}

	while (calculatePoints(&game->computer) < 17) {
		drawCard(&game->computer);
		if (calculatePoints(&game->computer) > 21) {
			displayGameStatus(game);
			printf("電腦爆牌，玩家勝利!\n");
			return;
		}
	}

	displayGameStatus(game);
	int playerPoints = calculatePoints(&game->player);
	int computerPoints = calculatePoints(&game->computer);

	printf("玩家點數: %d\n", playerPoints);
	printf("電腦點數: %d\n", computerPoints);

	if (playerPoints > computerPoints) {
		printf("玩家勝利!\n");
	}
	else if (playerPoints < computerPoints) {
		printf("電腦勝利!\n");
	}
	else {
		printf("平局!\n");
	}
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

	playRound(&game);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int coin = 200, contin, bet = 0;
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

void playRound(Game *game) {
	int playerChoice = 0;
	while (playerChoice != 2) {
		displayGameStatus(game);

		// 玩家回合
		printf("選擇要牌(1)或停牌(2): ");
		scanf("%d", &playerChoice);

		if (playerChoice == 1) {
			drawCard(&game->player);
			if ((calculatePoints(&game->player) <= 21) && (game->player.numCards == 5)) {
				displayGameStatus(game);
				printf("過五關，玩家勝利!\n");
				coin += (bet * 5);
				printf("你現在有%d元\n", coin);
				return;
			}

			if (calculatePoints(&game->player) > 21) {
				displayGameStatus(game);
				printf("玩家爆牌，電腦勝利!\n");
				coin -= bet;
				printf("你現在有%d元\n", coin);
				return;
			}
		}
	}

	// 電腦回合
	while (calculatePoints(&game->computer) < 17) {
		drawCard(&game->computer);
		if (calculatePoints(&game->computer) > 21) {
			displayGameStatus(game);
			printf("電腦爆牌，玩家勝利!\n");
			coin += (bet * 2);
			printf("你現在有%d元\n", coin);
			return;
		}

	}

	// 比較點數
	displayGameStatus(game);
	int playerPoints = calculatePoints(&game->player);
	int computerPoints = calculatePoints(&game->computer);

	printf("玩家點數: %d\n", playerPoints);
	printf("電腦點數: %d\n", computerPoints);

	if (playerPoints > computerPoints) {
		printf("玩家勝利!\n");
		coin += (bet * 2);
		printf("你現在有%d元\n", coin);
	}
	else if (playerPoints < computerPoints) {
		printf("電腦勝利!\n");
		coin -= bet;
		printf("你現在有%d元\n", coin);
	}
	else {
		printf("平局!\n");
	}
}


int main() {
	srand((unsigned int)time(NULL));

	printf("你現在有200元\n");
	do {
		Game game;
		game.player.numCards = 0;
		game.computer.numCards = 0;

		printf("輸入賭金:");
		scanf("%d", &bet);
		


		drawCard(&game.player);
		drawCard(&game.player);
		drawCard(&game.computer);
		drawCard(&game.computer);

		playRound(&game);
		if (coin <= 0) break;
		printf("\n按0繼續，其他鍵則結束:");
		scanf("%d", &contin);

	} while (contin == 0);

	return 0;
}
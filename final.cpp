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
	printf("���a��P: ");
	for (int i = 0; i < game->player.numCards; i++) {
		printf("%d ", game->player.hand[i].value);
	}
	printf("\n");

	printf("�q����P: ");
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

		// ���a�^�X
		printf("��ܭn�P(1)�ΰ��P(2): ");
		scanf("%d", &playerChoice);

		if (playerChoice == 1) {
			drawCard(&game->player);
			if ((calculatePoints(&game->player) <= 21) && (game->player.numCards == 5)) {
				displayGameStatus(game);
				printf("�L�����A���a�ӧQ!\n");
				coin += (bet * 5);
				printf("�A�{�b��%d��\n", coin);
				return;
			}

			if (calculatePoints(&game->player) > 21) {
				displayGameStatus(game);
				printf("���a�z�P�A�q���ӧQ!\n");
				coin -= bet;
				printf("�A�{�b��%d��\n", coin);
				return;
			}
		}
	}

	// �q���^�X
	while (calculatePoints(&game->computer) < 17) {
		drawCard(&game->computer);
		if (calculatePoints(&game->computer) > 21) {
			displayGameStatus(game);
			printf("�q���z�P�A���a�ӧQ!\n");
			coin += (bet * 2);
			printf("�A�{�b��%d��\n", coin);
			return;
		}

	}

	// ����I��
	displayGameStatus(game);
	int playerPoints = calculatePoints(&game->player);
	int computerPoints = calculatePoints(&game->computer);

	printf("���a�I��: %d\n", playerPoints);
	printf("�q���I��: %d\n", computerPoints);

	if (playerPoints > computerPoints) {
		printf("���a�ӧQ!\n");
		coin += (bet * 2);
		printf("�A�{�b��%d��\n", coin);
	}
	else if (playerPoints < computerPoints) {
		printf("�q���ӧQ!\n");
		coin -= bet;
		printf("�A�{�b��%d��\n", coin);
	}
	else {
		printf("����!\n");
	}
}


int main() {
	srand((unsigned int)time(NULL));

	printf("�A�{�b��200��\n");
	do {
		Game game;
		game.player.numCards = 0;
		game.computer.numCards = 0;

		printf("��J���:");
		scanf("%d", &bet);
		


		drawCard(&game.player);
		drawCard(&game.player);
		drawCard(&game.computer);
		drawCard(&game.computer);

		playRound(&game);
		if (coin <= 0) break;
		printf("\n��0�~��A��L��h����:");
		scanf("%d", &contin);

	} while (contin == 0);

	return 0;
}
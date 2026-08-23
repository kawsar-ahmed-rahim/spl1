#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int player, computer;
    int playerScore = 0, computerScore = 0, draws = 0;

    srand(time(NULL));

    printf("===== ROCK PAPER SCISSORS =====\n\n");
    printf("1. Rock = 1\n 2. Paper = 2\n 3. Scissors = 3\n\n");

    for (int round = 1; round <= 5; round++) {
        printf("Round %d - Enter your choice: ", round);
        scanf("%d", &player);

        if (player < 1 || player > 3) {
            printf("Invalid choice. Try again.\n");
            round--;
            continue;
        }

        computer = rand() % 3 + 1;

        printf("Computer chose: %d\n", computer);

        






    printf("Final Score: My Score = %d, Computer Score = %d, Draws = %d\n",
           playerScore, computerScore, draws);

    if (playerScore > computerScore) {
        printf("Congratulations! You won the game!\n");
    } else if (playerScore < computerScore) {
        printf("Computer won the game!\n");
    } else {
        printf("The game is a draw!\n");
    }

    return 0;
}
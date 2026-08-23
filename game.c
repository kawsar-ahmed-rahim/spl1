#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *choice_name(int choice) {
    if (choice == 1) {
        return "Rock";
    }
    if (choice == 2) {
        return "Paper";
    }
    return "Scissors";
}

int main() {
    int player, computer, input;
    int playerScore = 0, computerScore = 0, draws = 0;

    srand(time(NULL));

    printf("===== ROCK PAPER SCISSORS =====\n\n"); 
    printf("\n1. Rock\n2. Paper\n3. Scissors\n\n");

    for (int round = 1; round <= 5; round++) {
        printf("Round %d - Your choice: ", round);
        if (scanf("%d", &player) != 1) {
            printf("Invalid input. Enter a number from 1 to 3.\n");
            while ((input = getchar()) != '\n' && input != EOF) {
            }
            round--;
            continue;
        }

        if (player < 1 || player > 3) {
            printf("Invalid choice. Try again.\n");
            round--;
            continue;
        }

        computer = rand() % 3 + 1;

        printf("Your choice : %d\n", player);     
        printf("Computer choice : %d\n\n", computer);
         printf("Your choice %s\n", choice_name(player));
        printf("Computer choice %s\n\n", choice_name(computer));

        if (player == computer) {
            draws++;
            printf("This round is a draw.\n");
        } else if ((player == 1 && computer == 3) ||
                   (player == 2 && computer == 1) ||
                   (player == 3 && computer == 2)) {
            playerScore++;
            printf("You WIN!\n");
        } else {
            computerScore++;
            printf("Computer wins this round.\n");
        }

        printf("Score: You %d - Computer %d, Draws %d\n\n",
               playerScore, computerScore, draws);
    }
    printf("===== FINAL Result =====\n");

    printf("Your Score : %d\nComputer Score : %d\nDraws : %d\n",
           playerScore, computerScore, draws);

    if (playerScore > computerScore) {
        printf("Congratulations! You are the Champion!\n");
    } else if (playerScore < computerScore) {
        printf("Computer won the game!\n");
    } else {
        printf("The game is a draw!\n");
    }

    return 0;
}
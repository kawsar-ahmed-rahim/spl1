/*
 * rps.c — Rock, Paper, Scissors game logic
 *
 * This is Rahim's original game logic (same 1=Rock, 2=Paper, 3=Scissors
 * encoding, same win/lose/draw rules as the terminal version), adapted
 * to play a single round per run instead of looping 5 rounds with
 * scanf(). The server spawns this program once per click and keeps the
 * 5-round match/score/Champion logic on the web side instead.
 *
 * Usage: ./rps <1|2|3>   (1=Rock, 2=Paper, 3=Scissors)
 * Output (3 lines):
 *   PLAYER:<rock|paper|scissors>
 *   COMPUTER:<rock|paper|scissors>
 *   RESULT:<win|lose|draw>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const char *choice_name(int choice) {
    if (choice == 1) {
        return "rock";
    }
    if (choice == 2) {
        return "paper";
    }
    return "scissors";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <1|2|3>\n", argv[0]);
        return 1;
    }

    int player = atoi(argv[1]);
    if (player < 1 || player > 3) {
        fprintf(stderr, "Invalid choice: %s (must be 1, 2, or 3)\n", argv[1]);
        return 1;
    }

    /* time(NULL) alone repeats within the same second across fast
       successive server calls, so mix in the pid to keep each call
       independent even when several land in the same second */
    srand((unsigned int)time(NULL) ^ (unsigned int)getpid());
    int computer = rand() % 3 + 1;

    const char *result;
    if (player == computer) {
        result = "draw";
    } else if ((player == 1 && computer == 3) ||
               (player == 2 && computer == 1) ||
               (player == 3 && computer == 2)) {
        result = "win";
    } else {
        result = "lose";
    }

    printf("PLAYER:%s\n", choice_name(player));
    printf("COMPUTER:%s\n", choice_name(computer));
    printf("RESULT:%s\n", result);

    return 0;
}

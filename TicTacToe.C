#include <stdio.h>

char grid(int i);
void printGrid(int g[9]);
int has_won(const int grid[9]);
int minimax(int grid[9], int player);
void AIPlayer(int grid[9]);
void HumanPlayer(int grid[9]);

int main() {
    int grid[9] = {0,0,0,0,0,0,0,0,0};
    printf("Computer: O, You: X\n Do you want to play (1)st or (2)nd? ");
    int player=0;
    scanf("%d",&player);
    printf("\n");
    unsigned turn;
    for(turn = 0; turn < 9 && has_won(grid) == 0; ++turn) {
        if((turn+player) % 2 == 0)
		{
			AIPlayer(grid);
			printf("AI's turn: \n");
			printGrid(grid);
			printf("\n");
		}
        else {
			printf("Your turn\n");
            printGrid(grid);
            HumanPlayer(grid);
        }
    }
    switch(has_won(grid)) {
        case 0:
			printGrid(grid);
            printf("Game has resulted in a draw.\n");
            break;
        case 1:
            printGrid(grid);
            printf("You lose!\n");
            break;
        case -1:
			printGrid(grid);
            printf("You win!\n");
            break;
    }
	return 0;
}

char grid(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void printGrid(int g[9]) {
    printf(" %c | %c | %c\n",grid(g[0]),grid(g[1]),grid(g[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",grid(g[3]),grid(g[4]),grid(g[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",grid(g[6]),grid(g[7]),grid(g[8]));


}


void HumanPlayer(int grid[9]) 
{
    int move = 0;
    do {
		start:
        printf("\nInput a move [0..8]");
        scanf("%d", &move);
		if(grid[move]!=0)
		{
			printf("box taken !!");
			goto start;
		}
	printf("\n");
    } while ((move >= 9 || move < 0) && grid[move] == 0);
    grid[move] = -1;
}

void AIPlayer(int grid[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(grid[i] == 0) {
            grid[i] = 1;
            int tempScore = -minimax(grid, -1);
            grid[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    grid[move] = 1;
}

int minimax(int grid[9], int player) {
    int winner = has_won(grid);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(grid[i] == 0) {
            grid[i] = player;
            int thisScore = -minimax(grid, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            grid[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}



int has_won(const int grid[9]) {
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(grid[wins[i][0]] != 0 &&
           grid[wins[i][0]] == grid[wins[i][1]] &&
           grid[wins[i][0]] == grid[wins[i][2]])
            return grid[wins[i][2]];
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

//MMM HMMM.
typedef struct player {
	int x;
	int y;
} Player;

//Why? Because arrow notation.
typedef struct grid {
	int g[3][3];
} Grid;

void drawFrame(Grid *grid, Player *player, int turn) {
	//Hardcoded because derp
	for(int y = 0; y < 3; y++) {
		for(int x = 0; x < 3; x++) {
			if(y == player->y && x == player->x) {
				if(turn) {
					attron(COLOR_PAIR(1)); //Set to RED, BLACK
				} else if(!turn) {
					attron(COLOR_PAIR(2)); //Set to GREEN, BLACK
				}
			} else {
				attron(COLOR_PAIR(3)); //Set to WHITE, BLACK
			}
			if(grid->g[x][y] == 1) {
				printw("[x]");
			} else if(grid->g[x][y] == 2) {
				printw("[o]");
			} else {
				printw("[ ]");
			}
		}
		attron(COLOR_PAIR(3));
		printw("\n");
	}
}

void drawFrameF(Grid *grid) {
	//Hardcoded because derp
	for(int y = 0; y < 3; y++) {
		for(int x = 0; x < 3; x++) {
			if(grid->g[x][y] == 1) {
				printf("[x]");
			} else if(grid->g[x][y] == 2) {
				printf("[o]");
			} else {
				printf("[ ]");
			}
		}
		printf("\n");
	}
}

int checkX(Grid *grid) {
	if(grid->g[0][0] == 1 && grid->g[0][1] == 1 && grid->g[0][2] == 1) {
		//ACROSS TOP
		return 1;
	} else if(grid->g[1][0] == 1 && grid->g[1][1] == 1 && grid->g[1][2] == 1) {
		//ACROSS MID
		return 1;
	} else if(grid->g[2][0] == 1 && grid->g[2][1] == 1 && grid->g[2][2] == 1) {
		//ACROSS BOT
		return 1;
	} else if(grid->g[0][0] == 1 && grid->g[1][0] == 1 && grid->g[2][0] == 1) {
		//DOWN LEFT
		return 1;
	} else if(grid->g[0][1] == 1 && grid->g[1][1] == 1 && grid->g[2][1] == 1) {
		//DOWN MID
		return 1;
	} else if(grid->g[0][2] == 1 && grid->g[1][2] == 1 && grid->g[2][2] == 1) {
		//DOWN RIGHT
		return 1;
	} else if(grid->g[0][0] == 1 && grid->g[1][1] == 1 && grid->g[2][2] == 1) {
		//X DOWN RIGHT
		return 1;
	} else if(grid->g[2][0] == 1 && grid->g[1][1] == 1 && grid->g[0][2] == 1) {
		//X UP RIGHT
		return 1;
	}
	return 0;
}

int checkO(Grid *grid) {
	if(grid->g[0][0] == 2 && grid->g[0][1] == 2 && grid->g[0][2] == 2) {
		//ACROSS TOP
		return 1;
	} else if(grid->g[1][0] == 2 && grid->g[1][1] == 2 && grid->g[1][2] == 2) {
		//ACROSS MID
		return 1;
	} else if(grid->g[2][0] == 2 && grid->g[2][1] == 2 && grid->g[2][2] == 2) {
		//ACROSS BOT
		return 1;
	} else if(grid->g[0][0] == 2 && grid->g[1][0] == 2 && grid->g[2][0] == 2) {
		//DOWN LEFT
		return 1;
	} else if(grid->g[0][1] == 2 && grid->g[1][1] == 2 && grid->g[2][1] == 2) {
		//DOWN MID
		return 1;
	} else if(grid->g[0][2] == 2 && grid->g[1][2] == 2 && grid->g[2][2] == 2) {
		//DOWN RIGHT
		return 1;
	} else if(grid->g[0][0] == 2 && grid->g[1][1] == 2 && grid->g[2][2] == 2) {
		//X DOWN RIGHT
		return 1;
	} else if(grid->g[2][0] == 2 && grid->g[1][1] == 2 && grid->g[0][2] == 2) {
		//X UP RIGHT
		return 1;
	}
	return 0;
}

int checkGrid(Grid *grid) {
	if(checkX(grid)) {
		return 1;
	} else if(checkO(grid)) {
		return 2;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	
	/* INITIALIZE */
	Grid *grid = (Grid *) malloc(sizeof(Grid));
	grid->g[0][0] = 0;
	grid->g[0][1] = 0;
	grid->g[0][2] = 0;
	grid->g[1][0] = 0;
	grid->g[1][1] = 0;
	grid->g[1][2] = 0;
	grid->g[2][0] = 0;
	grid->g[2][1] = 0;
	grid->g[2][2] = 0;
	
	Player *player = (Player *) malloc(sizeof(Player));
	player -> x = 1; //Start the player in the middle position.
	player -> y = 1; //Start the player in the middle position.
	int turn = 1; //Initialized to X (RED Player)
	
	/* NCURSES INIT */
	initscr(); //Initialize the screen
	cbreak(); //Allows for CTRL^C
	noecho(); //No echo
	curs_set(FALSE); //Cursor Set
	srand(time(NULL)); //RANDOM???
	start_color(); //Allows for terminal color
	keypad(stdscr, TRUE); //Allows the arrow keys to be used
	init_pair(1, COLOR_RED, COLOR_BLACK); //Foreground RED, Background BLACK
	init_pair(2, COLOR_GREEN, COLOR_BLACK); //Foreground GREEN, Background BLACK
	init_pair(3, COLOR_WHITE, COLOR_BLACK); //Foreground WHITE, Background BLACK
	/*				*/
	
	int DELAY = 100; //Delay time after refresh (reduces flickering)
	int scrY = 0, scrX = 0; //Gets the screen's boundaries (unused in this...)
	int input = 0; //Keyboard input
	int gameover = 0; //Gameover check
	int mvcount = 0; //Maximum move counter (9)
	
	do {
		getmaxyx(stdscr, scrY, scrX);
		/* CLEAR */
		clear(); //Clear screen
		/* DRAW */
		//printw("CH: %d\n", input); //DEBUG
		drawFrame(grid, player, turn); //Draw the frame
		printw("Arrow keys to move.\nEnter to place.\nQ to exit.\n");
		attron(COLOR_PAIR(1)); //Set color to RED, BLACK
		printw("Player X\n");
		attron(COLOR_PAIR(2)); //Set color to GREEN, BLACK
		printw("PLAYER O\n");
		attron(COLOR_PAIR(3)); //Reset color to WHITE, BLACK
		
		/* REFRESH */
		refresh(); //Refresh the screen
		usleep(DELAY); //Used to reduce flickering
		
		/* CALCULATE */
		input = getch(); //Get the character from input
		if((input == KEY_UP) && (player -> y != 0)) {
			player -> y--; //Move the player up
		} else if((input == KEY_DOWN) && (player -> y != 2)) {
			player -> y++; //Move the player down
		} else if((input == KEY_LEFT) && (player -> x != 0)) {
			player -> x--; //Move the player left
		} else if((input == KEY_RIGHT) && (player -> x != 2)) {
			player -> x++; //Move the player right
		} else if(input == '\n') {
			if(turn) {
				if(!(grid->g[player->x][player->y])) {
					turn = 0; //Flip the turn to O
					grid->g[player->x][player->y] = 1; //Set grid at player pos to 1 (RED X)
					drawFrame(grid, player, turn);
					mvcount++;
				}
			} else if(!turn) {
				if(!(grid->g[player->x][player->y])){
					turn = 1; //Flip the turn to X
					grid->g[player->x][player->y] = 2; //Set grid at player pos to 2 (GREEN O) 
					drawFrame(grid, player, turn);
					mvcount++;
				}
			}
		}
		gameover = checkGrid(grid); //Check if a player has won
		if(mvcount == 9 && gameover == 0) input = 'q'; //Quit if stalemate
	} while(input != 'q' && !gameover);
	
	endwin(); //End ncurses window
	if(gameover == 1) {
		printf("X WINS!\n");
		drawFrameF(grid);
	} else if(gameover == 2) { 
		printf("O WINS!\n");
		drawFrameF(grid);
	} else if(mvcount == 9 ) {
		printf("STALEMATE!\n");
		drawFrameF(grid);
	}
	return 0;
}

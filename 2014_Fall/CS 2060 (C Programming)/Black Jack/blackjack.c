/**
 * BlackJack Game
 * blackjack.c
 * Alex Howard
 * CS 2060
 * 09/08/2014
 * 
 * BlackJack Rules:
 * 
 * Bet > 0
 * Bet size
 * Clear buffer when scanf
 * Check for multiple Aces
 * "X" Conditions
 * BOUNDS CHECKING
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

/* Data structure for a card type
 */
typedef struct {
    int value; //The value of the card 2-10 or 2 or 11 for aces
    char *name; //The name of the card (Two, Three, Four, ..., Jack, Queen, King, Ace)
    char *suite; //The suite (Clubs, Hearts, Diamonds, Spades)
} Card;

/* Data Structure for a Person type
 */
typedef struct {
    Card hand[11]; //The hand the person has. In BlackJack the maximum hand count is 11
    char *name; //The name of the person (Dealer or Player)
    int counter; //Counter for placing cards into the hand array
} Person;

/* Data structure for a Deck type
 */
typedef struct {
    Card stack[52]; //A deck has a stack of 52 cards
    int counter; //Holds a counter for placing cards into the stack array
} Deck;

/* Clears the buffer of any remaining characters
 */
void clearBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/* Creates the deck by using value, name, and suite templates
 */
void createDeck(Card deck[], int valTmp[], char *nameTmp[], char *suiteTmp[]) {
    for (int i = 0, suiteVal = 0; i < 52; i += 13, suiteVal++) { //All 52 places, grouped by 4
	for (int fill = 0; fill < 13; fill++) {
	    deck[i + fill].value = valTmp[fill];
	    deck[i + fill].name = nameTmp[fill];
	    deck[i + fill].suite = suiteTmp[suiteVal];
	}
    }
}


/* Shuffles the deck by swapping all the elements to a random position
 */
void shuffle(Card deck[]) {
    for (int i = 0; i < 52; i++) {
	int iRnd = rand() % 52; //A random position in the deck
	Card temp = deck[i];
	deck[i] = deck[iRnd];
	deck[iRnd] = temp;
    }
}

/* Checks how many aces a person has.
 * 
 * Takes in a person and that person's total.
 */
int checkAces(Person p, int total) {
    Card cd;
    int val;
    int aces = 0;
    Person *ptr = &p;
    for(int itr = 0; itr < p.counter; itr++) {
	cd = ptr -> hand[itr];
	val = cd.value;
	if(val == 11) {
	    aces++;
	}
    }
    if(total > 21) {
	for(int i = 0; i < aces; i++) {
	    total = total - 10;
	}
    }
    return total;
    //((total - (11*ace)) + ace);
}

/* Calculates the total value of a person's hand
 * 
 * Takes in a Person type
 */
int total(Person p) {
    int sum = 0;
    for (int i = 0; i < p.counter; i++) {
	sum += p.hand[i].value; //Calculates the sum of the person
    }
    sum = checkAces(p, sum); //Calculates the sum after accounting for aces
    return sum;
}

/* UTILITY FUNCTIONS */

/* Prints a card
 */
void printCard(Card card) {
    printf("%s of %s", card.name, card.suite);
}

/* Prints a deck
 * 
 * Only useful for debugging puropses
 */
void printDeck(Card deck[], int group) {
    printf("\n--------START DECK--------\n");
    if (group == 1) {
	for (int i = 0; i < 52; i++) {
	    printCard(deck[i]);
	    if (i == 12 || i == 25 || i == 38) {
		printf("\n");
	    }
	}
    } else {
	for (int i = 0; i < 52; i++) {
	    printCard(deck[i]);
	}
    }
    printf("--------STOP DECK--------\n\n");
}

/* Interface method.
 * Prints the total value of a person
 */
void printTotal(Person p) {
    int sum = total(p);
    printf("\t%s total : %d\n", p.name, sum);
}

/* Interface method
 * Prints the hand a person has
 */
void printPlayerHand(Person p) {
    printf("%s \t : [", p.name);
    for (int i = 0; i < p.counter; i++) {
	if (i == (p.counter) - 1) {
	    printf("%s of %s] ", p.hand[i].name, p.hand[i].suite);
	} else {
	    printf("%s of %s, ", p.hand[i].name, p.hand[i].suite);
	}
    }
    printf("\n");
    printTotal(p);
}

/* Special interface method for the dealer.
 * This prints the dealer's hand without revealing his/her first card
 */
void printDealerHand(Person p, int show) {
    if (show == 0) {
	printf("%s \t : [", p.name);
	for (int i = 0; i < p.counter; i++) {
	    if (i == 0) {
		printf("XXX, ");
	    } else if (i == (p.counter) - 1) {
		printf("%s of %s] ", p.hand[i].name, p.hand[i].suite);
	    } else {
		printf("%s of %s, ", p.hand[i].name, p.hand[i].suite);
	    }
	}
    } else {
	printPlayerHand(p);
    }
    //printTotal(p); //FOR DEBUG ONLY!!!!
    printf("\n"); //MUST EXIST!! (for some reason...)
}

/* STOP UTILITY FUNCIONS */

/* Deals a card to the person.
 * Essentially it places a card into the person's hand array.
 * 
 * Param: Pointer to a Person, pointer to a Deck
 */
void dealCard(Person *p, Deck *d) {
    p -> hand[p -> counter] = d -> stack[d -> counter];
    p -> counter = p -> counter + 1;
    d -> counter = d -> counter + 1;
}

/* Checks whether a person has busted (gone over 21)
 * Param: a Person
 */
int bust(Person p) {
    int sum = total(p);
    if (sum > 21) return 1;
    return 0;
}

/* Checks the input options from a player.
 * Type of 0 checks for a "hit or stay" conditon
 * while type 1 checks if the player wants to play again.
 */
int checkOption(unsigned char c, int type) {
    //Type 0 is for hitting or staying
    //Type 1 is for playing again
    int out = 0;
    if (type == 0) {
	if (!isalpha(c)) {
	    printf("Not valid option! Try again.\n");
	} else {
	    if (c == 'h' || c == 's' || c == 'H' || c == 'S') {
		out = 1;
		return out;
	    } else {
		printf("Not a valid option! Try again.\n");
	    }
	}
    } else if(type == 1) {
	if (c == 'y' || c == 'Y') {
	    printf("\nPlaying again!\n\n\n");
	} else {
	    out = 1;
	    return out;
	}
    } else if(type) {
	//Xcondition
    }
    return out;
}

/* Sets up the ending condition for the game.
 * Prints out the totals of the dealer and player
 * Prints an end condition message
 * Takes input
 * Returns the input
 */
char endCondition(Person d, Person p) {
    char op;
    printTotal(d);
    printTotal(p);
    printf("\nWould you like to play again? [Y]es (anything else to quit) : ");
    scanf("%c", &op);
    clearBuffer();
    return op;
}

/* Main
 * Plays a game of BlackJack
 */
int main() {
    srand(time(NULL)); //Random seed
    printf("Welcome to Black Jack!\n");
    
    // VARIABLES
    int valueTemplate [] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11}; //Value template
    char *nameTemplate[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", 
			    "Jack", "Queen", "King", "Ace"}; //Name of card
    char *suiteTemplate[] = {"\u2663", "\u2665", "\u2666", "\u2660"}; //Unicode for suites
    //Pointers that hold the input for the tokens and the bet
    char *tk = malloc(sizeof(char)), *bt = malloc(sizeof(char));
    int tokens = 0, bet = 0, soulBet = 0; //Tokens, bets, boolean for special condition
    unsigned char option; //User option "hit, stay, yes, no"
    
    //Deck
    Deck deck;
    Deck *deckPtr = &deck;
    
    //Dealer
    Person dealer;
    dealer.name = "Dealer";
    Person *dealerPtr = &dealer;
    
    //Player
    Person player;
    player.name = "Player";
    Person *playerPtr = &player;
    
    int tkChk = 0;
    //Checks if token input is valid
    while(!tkChk) {
	printf("How many tokens do you want to play with? (Minimum 10) : ");
	scanf("%s", tk);
	clearBuffer();
	tokens = atoi(tk);
	if(!strcmp(tk, "x")) {
	    printf("\nCongratulations! You just bet YOUR SOUL.\n");
	    printf("Good luck.\n\n");
	    soulBet = 1;
	    tkChk = 1;
	    tokens = 1;
	} else if(tokens >= 10 && tokens < 1000000) {
	    tkChk = 1;
	} else {
	    printf("Not a valid input! Try again.\n\n");
	}
    }
    
    int endGame = 0; //Boolean for end game condition
    //End of game conditional check
    while ((!endGame && tokens > 0)) {
	
	//Special condition check
	if(!soulBet) {
	    printf("You have %d tokens left.\n", tokens);
	    int betChk = 0;
	    while(!betChk) {
		printf("Enter your bet (Minimum of 1) : ");
		scanf("%s", bt);
		clearBuffer();
		bet = atoi(bt);
		if(bet <= tokens && bet >= 1) {
		    betChk = 1;
		} else {
		    printf("Not a valid input! Try again.\n\n");
		}
	    }
	}
	printf("\n");
	
	//(RE)SET THE COUNTERS
	deck.counter = 0;
	dealer.counter = 0;
	player.counter = 0;
	
	//MAKE THE DECK, SHUFFLE THE DECK, I LIKE THE GROOVES, BUT I DIGRESS
	createDeck(deck.stack, valueTemplate, nameTemplate, suiteTemplate);
	shuffle(deck.stack);
	
	//DEAL TWO CARDS TO DEALER AND PLAYER
	dealCard(playerPtr, deckPtr); //Player
	dealCard(dealerPtr, deckPtr); //Dealer
	dealCard(playerPtr, deckPtr); //Player
	dealCard(dealerPtr, deckPtr); //Dealer
	
	
	//PRINT THE DEALER'S AND PLAYER'S HANDS
	printDealerHand(dealer, 0);
	printPlayerHand(player);
	
	int playerTotal = total(player); //Total the Player
	int dealerTotal = total(dealer); //Total the Dealer
	
	int roundOver = 0;
	int stayCheck = 0;
	//Checking if a "round" is over
	while(!roundOver) {
	    int cont = 0; //Boolean to continue
	    //HIT OR STAY CHECKING
	    while (!cont) {
		printf("\n\n[H]it or [S]tay? : ");
		scanf("%c", &option);
		clearBuffer();
		cont = checkOption(option, 0); //Only stops looping when continue is true
	    }
	    
	    //The player cannot continue to hit after staying
	    if(!stayCheck) {
		if (option == 'h') {
		    printf("Hit me!\n");
		    dealCard(playerPtr, deckPtr); //Deal a card to the player
		    playerTotal = total(player); //Increment the player's total
		    printf("You got the ");
		    printCard(player.hand[player.counter-1]); //Print card player got
		    printf("\n");
		    printPlayerHand(player); //Print player's hand
		} else if (option == 's') {
		    stayCheck = 1; //If the player stays the dealer must hit if under 17
		    printf("I'll stay!\n");
		    while(dealerTotal < 17) {
			printf("The Dealer hits\n");
			dealCard(dealerPtr, deckPtr); //Deal the dealer a card
			dealerTotal = total(dealer); //Increment the dealer's total
		    }
		}
	    }
	    
	    /*FINAL CHECK CONDITIONS*/
	    /* Will print the player's and dealer's hands
	     * and check if the player wants to play again.
	     * 
	     * Will NOT ask to play again if the player has
	     * entered the special condition.
	     */
	    
	    //If the player has BlackJack and the Dealer does not
	    if(playerTotal == 21 && dealerTotal != 21) {
		roundOver = 1;
		printf("\nBlackJack! You win!\n");
		if(soulBet) {
		    endGame = 1;
		    printf("You win this time. Lucky bastard.\n");
		    printf("(\u0CA0 __\u0CA0)\n\n");
		    printPlayerHand(dealer);
		    printPlayerHand(player);
		    printf("\n");
		} else {
		    option = endCondition(dealer, player);
		    tokens = tokens + bet;
		    endGame = checkOption(option, 1);
		}
	    } else if(playerTotal == 21 && dealerTotal == 21) {
		//If the player and the dealer have BlackJack
		roundOver = 1;
		printf("\nPush! it was a tie!\n\n");
		if(soulBet) {
		    printPlayerHand(dealer);
		    printPlayerHand(player);
		    printf("\nThere are no stalemates when playing for souls!\nAGAIN!!\n");
		} else {
		    option = endCondition(dealer, player);
		    endGame = checkOption(option, 1);
		}
	    } else if(bust(player)) {
		//If the player busts
		roundOver = 1;
		printf("\nYou busted!\n");
		if(soulBet) {
		    endGame = 1;
		    printf("I WIN! YOUR SOUL IS MINE!!!\n");
		    printf("\u03C8(\uFF40\u2207\u00B4)\u03C8\n\n");
		    printPlayerHand(dealer);
		    printPlayerHand(player);
		    printf("\n");
		} else {
		    option = endCondition(dealer, player);
		    endGame = checkOption(option, 1);
		    tokens = tokens - bet;
		}
	    } else if(bust(dealer)) {
		//If the Dealer busts
		roundOver = 1;
		printf("\nDealer busted. You win!\n\n");
		if(soulBet) {
		    endGame = 1;
		    printf("CURSES!\n");
		    printf("(\u256F\u00B0\u25A1\u00B0)\u256F\uFE35 \u253B\u2501\u253B\n\n");
		    printPlayerHand(dealer);
		    printPlayerHand(player);
		    printf("\n");
		} else {
		    option = endCondition(dealer, player);
		    endGame = checkOption(option, 1);
		    tokens = tokens + bet;
		}
	    }  else if ((stayCheck)){
		//If the player has stayed
		if((playerTotal > dealerTotal)) {
		    //If the player's total is higher than the dealers
		    roundOver = 1;
		    printf("\nYou win!\n\n");
		    if(soulBet) {
			endGame = 1;
			printf("NNNOOOOOOOO!!!!\n");
			printf("\u253B\u2501\u253B \uFE35\u30FD");
			printf("(`\u0414\u00B4)\uFF89\uFE35\uFEFF \u253B\u2501\u253B\n\n");
			printPlayerHand(dealer);
			printPlayerHand(player);
			printf("\n");
		    } else {
			option = endCondition(dealer, player);
			endGame = checkOption(option, 1);
			tokens = tokens + bet;
		    }
		} else if(dealerTotal == playerTotal) {
		    //Push or tie
		    roundOver = 1;
		    printf("\nPush! It was a tie.\n\n");
		    if(soulBet) {
			printPlayerHand(dealer);
			printPlayerHand(player);
			printf("There are no stalemates when playing for souls!\nAGAIN!!\n");
		    } else {
			option = endCondition(dealer, player);
			endGame = checkOption(option, 1);
		    }
		} else if(dealerTotal == 21 && playerTotal != 21) {
		    //If the dealer has BlackJack
		    roundOver = 1;
		    printf("\nDealer had BlackJack! You lose!\n\n");
		    if(soulBet) {
			endGame = 1;
			printf("I WIN! MWUHAHAAHAHAHAHA!\n");
			printf("\u30FD\u0F3C \u0CA0\u76CA\u0CA0 \u0F3D\uFF89\n\n");
			printPlayerHand(dealer);
			printPlayerHand(player);
			printf("\n");
		    } else {
			option = endCondition(dealer, player);
			endGame = checkOption(option, 1);
			tokens = tokens - bet;
		    }
		} else {
		    //In any other condition, the dealer has won
		    roundOver = 1;
		    printf("\nDealer wins!\n");
		    if(soulBet) {
			endGame = 1;
			printf("(\uFF9F\u2200\uFF9F)\n\n");
			printPlayerHand(dealer);
			printPlayerHand(player);
			printf("\n");
		    } else {
			option = endCondition(dealer, player);
			endGame = checkOption(option, 1);
			tokens = tokens - bet;
		    }
		}
	    }
	}
    }
    free(tk); //Frees the token pointer
    free(bt); //Frees the bet pointer
    printf("Game over!\n");
    if(tokens == 0) {
	printf("You are out of tokens!\n"); //If the player has no tokens
    } else if(!soulBet) {
	printf("Left with %d tokens!\n", tokens); //How many tokens the player has left
    }
    
    return 0; //Exit
}
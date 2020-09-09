//Steven Franzmann
//Connect 4.c


#include <stdio.h>
#include <string.h>
#define FILE_NAME "scores.txt"
#define MAX_NAME 51
#define DUMMY_CHAR ' '
#define X 6
#define Y 7

int getMenuChoice();
void setBoard(int board[][Y]);
void beginGame(char player1[], char player2[]);
int chooseColumn(char player[]);
int validMove(int board[X][Y], int move);
void createBoard(int board[][Y]);
void enterMove(int board[X][Y], int playerNum, int move);
int winner(int board[][Y], int move);
void writeScores(FILE *filePtr, int score1, int score2, char winner1[], char winner2[], int winner1Check, int winner2Check);
void showScores(FILE* filePtr);

int main(){
	//Declare Variables
	FILE* filePtr;
	int board[X][Y];
	char player1[MAX_NAME];
	char player2[MAX_NAME];
	int player1Num = 1;
	int player2Num = 2;
	int x, y; 
	int move;
	int whileControl = 5;
	int maxTurns = X * Y;
	int winCheck;
	int totalTurns = 0;
	int endGame;
	int score1 = 0;
	int score2 = 0;
	char winner1[MAX_NAME];
	char winner2[MAX_NAME];
	int winner1Check = 0;
	int winner2Check = 0;
	int playAgain;

	//Create menu loop
	while (whileControl != 0){
		whileControl = getMenuChoice();

		if (whileControl == 1){
			//Asks for player names
			setBoard(board);
			beginGame(player1, player2);
			endGame = 0;
			while(endGame != 1){
				//resets variables and displays board
				totalTurns = 0;
				setBoard(board);
				createBoard(board);
				//creates game loop
				while(totalTurns < maxTurns || endGame == 1){
					//X's turn
					move = chooseColumn(player1);
					move = validMove(board, move);
					enterMove(board, player1Num, move);
					createBoard(board);
					totalTurns++;
					winCheck=winner(board, move);
					if(winCheck == 1){
						printf("%s YOU WON!!! CONGRATS :D\n", player1);
						score1++;
						strcpy(winner1, player1);
						winner1Check = 1;
						break;
					}

					//O's turn
					move = chooseColumn(player2);
					move = validMove(board, move);
					enterMove(board, player2Num, move);
					createBoard(board);
					totalTurns++;
					winCheck=winner(board, move);
					if(winCheck == 1){
						printf("%s YOU WON!!! CONGRATS :D\n", player2);
						score2++;
						strcpy(winner2, player2);
						winner2Check = 1;
						break;
					}
				}
				//Checks for draw
				if(totalTurns == 42){
					printf("It's a tie! Try again...\n");
					printf("\n");
				}
				
				//Asks for replay, if answer is no then score.txt is appended with new scores
				printf("\n");
				printf("Enter '1' to play again or '2' to return to main menu \n");
				scanf("%d", &playAgain);
				if(playAgain != 1){
					if(totalTurns != 42){
						writeScores(filePtr, score1, score2, winner1, winner2, winner1Check, winner2Check);
						score1 = 0;
						score2 = 0;
						winner1Check = 0;
						winner2Check = 0;
						endGame = 1;
					}
				}
			}						
		}

		else if (whileControl == 2){
			//displays score
			filePtr = fopen(FILE_NAME, "r");
			if (filePtr != NULL) {
				showScores(filePtr);
				fclose(filePtr);
			}
			else if (filePtr == NULL){
				printf("File could not be found.\n");
			}
		}

		else if (whileControl > 2){
			printf("Please enter a valid option!\n");
		}

		else if (whileControl < 0){
			printf("Please enter a valid option!\n");
		}	
		
	}

	return 0;
}//endmain



//create functions
int getMenuChoice(){
	int userInput;
	printf("***CONNECT 4***\n");
	printf("1. Play Game\n");
	printf("2. Show Scores\n");
	printf("0. EXIT\n");
	printf("Enter your choice: ");
	scanf("%d", &userInput);
	return userInput;
}

void setBoard(int board[][Y]){
	//resets board with blank characters
	int x, y;
	for(x = 0; x < X; x++){
		for(y = 0; y < Y; y++){
			board[x][y] = ' ';
		}
	}
}

void beginGame(char player1[], char player2[]){
	int index = 0;

	printf("Player 1, enter your name: ");
	scanf("%s", player1);
	printf("Player 2, enter your name: ");
	scanf("%s", player2);
	while(index < Y){
		printf("***");
		index++;
	}
	index = 0;
	printf("\n");
	printf("%s, you'll be X's\n", player1);
	printf("%s, you'll be O's\n", player2);
	while(index < Y){
		printf("---");
		index++;
	}
	printf("\n");
}

int chooseColumn(char player[]){
	int y;

	printf("%s - Enter your move: ", player);
	scanf("%d", &y);

	return y;
}

int validMove(int board[X][Y], int move){
	int room, space = 0;
	int x, y, attempt;
	int loop = 0;
	int check = 0;

	while(check == 0){
		if(move < 1 || move > Y){
			printf("Please enter a valid move: ");
			scanf("%d", &move);
		}
	
		else if(board[0][move - 1] != ' '){
			printf("Please enter a valid move: ");
			scanf("%d", &move);
		}

		else{
			check = 1;
		}
	}
	
	return move;
}

void createBoard(int board[][Y]){
	int x, y;
	int index = 0;
	int yIndex = Y;

	for(y = 1; y <= yIndex; y++){
		printf("[%d]", y);
	}
	printf("\n");

	while(index < Y){
		printf("---");
		index++;
	}
	printf("\n");

	for(x = 0; x < X; x++){
		for(y= 0; y < Y; y++){
			printf("[%c]", board[x][y]);
		}
		printf("\n");
	}
	
	index = 0;
	while(index < Y){
		printf("---");
		index++;
	}
	printf("\n");

	for(y = 1; y <= yIndex; y++){
		printf("[%d]", y);
	}
	printf("\n\n");
}

void enterMove(int board[X][Y], int playerNum, int move){
	char input;
	int index;
	int control = X - 1;
	int check = 0;
	int flag = 0;

	if(playerNum == 1){
		input = 'X';
	}
	else if(playerNum == 2){
		input = 'O';
	}

	
	while(check == 0){		
		if(board[control][move-1] == ' '){
			board[control][move-1] = input;			
			check = 1;	
		}
		
		else if(board[control][move-1] == 'X' || board[control][move-1] == 'O'){
			if(check != 1){
				control--;
				check = 0;
			}
		}
		
		else if(control > 0){
			check == 1;
		}
	}
	
}

int winner(int board[][Y], int move){
	int a, b;
	int x, y;
	int count;
	char player;

	for(a = 0; a < X; a++){
		if (board[a][move-1] != ' '){
			player = board[a][move-1];
			break;
		}
	}

	count = 0;
	x = a;
	y = move - 1;
	while((count < 5) && (board[x][y] == player)){
		count++;
		y--;
		
		if(count == 5){
			return 1;
		}
	}

	y = move - 1;
	while((count < 5) && (board[x][y] == player)){
		count++;
		y++;

		if(count == 5){
			return 1;
		}
	}

	count = 0;
	y = move- 1;
	while((count < 5) && (board[x][y] == player)){
		count++;
		x--;
		
		if(count == 5){
			return 1;
		}
	}

	x = a;
	while((count < 5) && (board[x][y] == player)){
		count++;
		x++;
		
		if(count == 5){
			return 1;
		}
	}

	count = 0;
	x = a;
	y = move - 1;
	while((count < 4) && (board[x][y] == player)){
		count++;
		x++;
		y--;
	
		if(count == 4){
			return 1;
		}
	}

	x = a;
	y = move - 1;
	while((count < 5) && (board[x][y] == player)){
		count++;
		x--;
		y++;
	
		if(count == 5){
			return 1;
		}
	}

	count = 0;
	x = a;
	y = move - 1;
	while((count < 4) && (board[x][y] == player)){
		count++;
		x++;
		y++;

		if(count == 4){
			return 1;
		}
	}

	
	x = a;
	y = move - 1;
	while((count < 5) && (board[x][y] == player)){
		count++;
		x--;
		y--;

		if(count == 5){
			return 1;
		}
	}
			
	return 0;
}

void writeScores(FILE *filePtr, int score1, int score2, char winner1[], char winner2[], int winner1Check, int winner2Check){
	//appends file with names and scores, higher scores are displayed first
	filePtr = fopen(FILE_NAME, "a");
	if (filePtr != NULL) {
		if(score1 >= score2){
			fprintf(filePtr, "%s %d\n", winner1, score1);
			if(winner2Check == 1){
				fprintf(filePtr, "%s %d\n", winner2, score2);
			}
		}
		
		if(score2 > score1){
			fprintf(filePtr, "%s %d\n", winner2, score2);
			if(winner1Check == 1){
				fprintf(filePtr, "%s %d\n", winner1, score1);
			}
		}
	}
	fclose(filePtr);

}
		
void showScores(FILE* filePtr){
	int score;
	char name[MAX_NAME];

	printf("**HIGH SCORES**\n");

	if(filePtr != NULL){
		fscanf(filePtr, "%s %d", name, &score);
		while(!feof(filePtr)){
			printf("%s: %d\n", name, score);
			fscanf(filePtr, "%s %d", name, &score);
		}
	}
	printf("\n");
}

	




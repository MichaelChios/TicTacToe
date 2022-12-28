#include <stdio.h>
#include <stdlib.h>

struct Players{
	char mark;
	int posChoice;
};

char T[3][3]={'1', '2', '3',
			'4', '5', '6',
			'7', '8', '9'};
char positions[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int W[3][3];
int p1=0; /* Player 1 points */
int p2=0; /* Player 2 points */

void choice1(struct Players *pl1, struct Players *pl2, int numP);
void board(struct Players pl1, struct Players pl2);
void startCheckWinner();
void score(int numP);
void playAgain();
int isValid1(int c, char m1, char m2);
int isValid2(char m);
int checkWinner();
int *getSum();
char choice2(struct Players *pl1, struct Players *pl2);

int main(){
	struct Players player1;
	struct Players player2;
	int p, w=-1; 						/* p = # Player, w = winner variable */
	choice2(&player1, &player2);					
	while(w==-1){
		for(p=1; p<=2; p++){
			board(player1, player2);
			choice1(&player1, &player2, p);
			w=checkWinner();
			if(w!=-1){
				break;
			}
		}
	}
	board(player1, player2);
	if(w==1){
		score(p);
		printf(" The winner is : Player %d\n\n", p);
		printf(" The score is : %d - %d\n\n", p1, p2);
		playAgain();
	}
	else{
		printf(" It's a draw\n\n");
		printf(" The score is : %d - %d\n\n", p1, p2);
		playAgain();
	}
	return 0;
}

/* Draws board */

void board(struct Players pl1, struct Players pl2){
	int j, k=1;
	printf("\n\t Tic Tac Toe \n\n");
	printf(" Player 1 (%c) - Player 2 (%c) \n\n", pl1.mark, pl2.mark);
	printf(" Score : %d - %d\n\n", p1, p2);
	for(j=0; j<=2; j++){
		printf("\t    |    |    \n");
		printf("\t %c  | %c  | %c \n", positions[k], positions[k+1], positions[k+2]);
		k+=3;
		if(j<2){
			printf("\t____|____|____ \n");
		}
		else{
			printf("\t    |    |    \n\n");	
		}
	}
	return;	
}

/* Checks if the posistion on the board selected by each player is valid */

int isValid1(int c, char m1, char m2){
	if(c<10 && c>0 && positions[c]!=m1 && positions[c]!=m2){
		return 0;
	}
	else{
		return 1;
	}
}

/* Checks if the mark selected by each player is valid */

int isValid2(char m){
	if(m=='O' || m=='X'){
		return 0;
	}
	else{
		return 1;
	}
}

/* Function for the position on the board input */

void choice1(struct Players *pl1, struct Players *pl2, int numP){
	if(numP==1){
		printf(" Player %d, choose a position : ", numP);
		label1:
		scanf("%d", &pl1->posChoice);
		if(isValid1(pl1->posChoice, pl1->mark, pl2->mark)==0){
			positions[pl1->posChoice]=pl1->mark;
		}
		else{
			printf("\n Invalid choice. Select another : ");
			goto label1;
		}
	}
	else{
		printf(" Player %d, choose a position : ", numP);
		label2:
		scanf("%d", &pl2->posChoice);
		if(isValid1(pl2->posChoice, pl2->mark, pl1->mark)==0){
			positions[pl2->posChoice]=pl2->mark;
		}
		else{
			printf("\n Invalid choice. Select another : ");
			goto label2;
		}
	}
	return;
}

/* Function for mark input */

char choice2(struct Players *pl1, struct Players *pl2){
	printf(" Player 1, choose 'O' or 'X' : ");
	label3:
	scanf("%c", &pl1->mark);
	if(isValid2(pl1->mark)==0){
		if(pl1->mark=='O'){
			pl2->mark='X';
		}
		else{
			pl2->mark='O';
		}
	}
	else{
		printf("\n Invalid mark. Select 'O' or 'X' : ");
		goto label3;
	}
	printf(" Player 2 is : %c \n", pl2->mark);
	return pl1->mark, pl2->mark;
}

/* Creates an array with 1, -1 and 0, depending on the content of T array */

void startCheckWinner(){
	int i, j, y=1;
	for(i=0; i<=2; i++){
		for(j=0; j<=2; j++){
			T[i][j]=positions[y];
			y+=1;
			if(T[i][j]=='O'){
				W[i][j]=-1;
			}
			else if(T[i][j]=='X'){
				W[i][j]=1;
			}
			else{
				W[i][j]=0;
			}
		}
	}
	return;
}

/* Calculates the sums of the diagonals, rows and columns */

int *getSum(){
	int i, j, k, m;
	int *s=calloc(8, sizeof(int));
	for(i=0; i<=2; i++){
		startCheckWinner();
		s[0]+=W[i][i];				/* sum of the right diagonal */
		s[1]+=W[i][2-i];			/* sum of the left diagonal */
	}
	
	for(m=0; m<=2; m++){
		if(m==0){
			for(j=0; j<=2; j++){
				startCheckWinner();
				s[2]+=W[m][j];		/* sum of the first row */
			}
		}
		else if(m==1){
			for(j=0; j<=2; j++){
				startCheckWinner();
				s[3]+=W[m][j];		/* sum of the second row */
			}
		}
		else{
			for(j=0; j<=2; j++){
				startCheckWinner();
				s[4]+=W[m][j];		/* sum of the third row */
			}
		}
	}
	
	for(k=0; k<=2; k++){
		if(k==0){
			for(j=0; j<=2; j++){
				startCheckWinner();
				s[5]+=W[j][k];		/* sum of the first column */
			}
		}
		else if(k==1){
			for(j=0; j<=2; j++){
				startCheckWinner();
				s[6]+=W[j][k];		/* sum of the second column */
			}
		}
		else{
			for(j=0; j<=2; j++){
				startCheckWinner();
				s[7]+=W[j][k];		/* sum of the third column */
			}
		}
	}
	return s;
}

/* Determines the winner based on the sums */

int checkWinner(){
	int i, j, y, r, counter=0;
	int *sum;
	sum=getSum();
	for(i=0; i<=7; i++){
		if(sum[i]==3 || sum[i]==-3){
			r=1;
			break;
		}
		else if(sum[i]!=3 && sum[i]!=-3){
			for(j=0; j<=2; j++){
				for(y=0; y<=2; y++){
					if(W[j][y]!=0){
						counter+=1;
						continue;
					}
					else if(W[j][y]==0){
						counter=0;
						j=2;
						break;
					}
				}
			}
			if(counter==((i+1)*9)){
				r=0;
			}
			else{
				r=-1;
			}
		}
	}
	return r;
}

/* Function to calculate the score */

void score(int numP){
	if(numP==1){
		p1+=1;
	}
	else{
		p2+=1;
	}
	return ;
}

/* Function to restart or not the game */

void playAgain(){
	char a1[3]="YES";
	char answer[3];
	char copy[10]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int z;
	printf(" Do you want to play again?\n Type YES or NO : ");
	scanf("%s", &answer);
	if(strcmp(answer, a1)==0){
		for(z=1; z<=9; z++){
			positions[z]=copy[z];
		}
		main();
	}
	else{
		if(p1>p2){
			printf("\n Player 1 is the final winner with : %d - %d", p1, p2);
		}
		else if(p1<p2){
			printf("\n Player 2 is the final winner with : %d - %d", p1, p2);
		}
		if(p1=p2){
			printf("\n The game ended with a draw : %d - %d", p1, p2);
		}
	}
	return;
}

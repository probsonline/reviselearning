#include <iostream>
#include <string>

#include "probs.hpp"

using namespace std;

/*
Make a two player tic tac toe game.
(2 hours)
★ Modify the program so that it will announce when a player has won the game (and which player won, x or o)
(2 minutes)
★★ Modify the program so that it is a one player game against the computer (with the computer making its moves randomly)

★★★★ Modify the program so that anytime the player is about to win (aka, they have 2 of 3 x's in a row, the computer will block w/ an o)

13:15 -

*/

typedef unsigned int UINT;

static const int GAME_SIZE=3;
static char Game_Board[GAME_SIZE][GAME_SIZE];

static char Tic = 'X';
static char Tac = 'O';
static char Toe = '-';

static UINT Player1_ID=1;
static UINT Player2_ID=2;

static string Player1_Name="Player 1";
static string Player2_Name="Player 2";

static char Player1_Symbol=Tic;
static char Player2_Symbol=Tac;


void start_game();
void start_game_with_defaults();
UINT toss_for_first_turn();
char chose_starting_char(UINT pid);
void draw_board();
void clean_board();
void play(UINT starting_player);
void display_input_choices();

void player_move(UINT pid);
UINT toggle_turn(UINT pid);
bool check_win(UINT pid);
bool check_tie();

int Move_Counter=0;

void start_game_with_defaults(){

	clean_board();
	draw_board();
	play(Player1_ID);
}

void start_game(){

	cout << "Enter Player 1 name" << endl;
	cin >> Player1_Name;

	cout << "Enter Player 2 name" << endl;
	cin >> Player2_Name;

	clean_board();

	UINT starting_player = toss_for_first_turn();
	chose_starting_char(starting_player);

	draw_board();

	play(starting_player);
}

UINT toss_for_first_turn(){
	UINT coin;
	UINT choice;
	UINT toss_winner;
	
	cout << Player1_Name << " to chose the toss \n1)head \n2)tail" << endl;
	cin >> choice;

	srand((unsigned int) time(NULL));
	coin = rand()%2+1;

	if (coin == choice)
	{
		cout << Player1_Name << " has won the toss" << endl;
		toss_winner = Player1_ID;
	}
	else
	{
		cout << Player1_Name << " has lost the toss" << endl;
		toss_winner = Player2_ID;
	}

	return toss_winner;
}

char chose_starting_char(UINT pid){

	UINT pchar;
	char symbol_save;

	cout << (pid==Player1_ID?Player1_Name:Player2_Name) << " Chose your symbol" << endl;
	cout << Player1_ID << ". " << Player1_Symbol << endl;
	cout << Player2_ID << ". " << Player2_Symbol << endl;
	cout << "3. Use Defaults " << endl;
	cin >> pchar;

	if (pid==Player1_ID && pchar != Player1_ID)
	{
		symbol_save = Player2_Symbol;
		Player2_Symbol = Player1_Symbol;
		Player1_Symbol = symbol_save;
	}
	else if (pid==Player2_ID && pchar != Player2_ID)
	{
		symbol_save = Player1_Symbol;
		Player1_Symbol = Player2_Symbol;
		Player2_Symbol = symbol_save;
	}
	else
	{
		Player1_Symbol = Tic;
		Player2_Symbol = Toe;
	}

	return pchar;

}

void clean_board(){

	for (int row=0; row <GAME_SIZE; row++ ){
		for (int col = 0; col < GAME_SIZE; col++)
		{
			Game_Board[row][col] = Toe;
		}
	}
	Move_Counter = 0;
}

void draw_board(){
	for (int row=0; row <GAME_SIZE; row++ ){
		for (int col = 0; col < GAME_SIZE; col++)
		{
			cout << " " << Game_Board[row][col] << " ";
		}
		cout << endl;
	}
}

void play(UINT starting_player){
	UINT player_id=starting_player;
	bool have_more_moves = true;

	do
	{
		Move_Counter++;

		player_move(player_id);
		draw_board();

		have_more_moves = check_win(player_id)?false:true;		

		if (false == have_more_moves)	
		{
			cout << "We have a winner! " << endl;
			cout << "Congratulations " << ((player_id==Player1_ID)?Player1_Name:Player2_Name) << endl;
			break;
		}

		if(check_tie())
		{
			cout << "No more useful moves left. The game is a tie" << endl;
			break;
		}

		/* if there is no winner yet and more useful moves are possible, then toggle the turn */
		player_id = toggle_turn(player_id);

	}while (have_more_moves);

}


void player_move(UINT pid){

	UINT choice;

	cout << (pid==Player1_ID?Player1_Name:Player2_Name) << " Chose your move" << endl;
	display_input_choices();

	//Keep waiting until user makes a valid choice
	while(true){
		cin >> choice;

		int row = (choice-1)/GAME_SIZE;
		int col = (choice-1)%GAME_SIZE;
		if (Game_Board[row][col] == Toe) //Make sure that a box can only be written once
		{
			Game_Board[row][col] = ((pid == Player1_ID)?Player1_Symbol:Player2_Symbol);
			break;
		}
		else
		{
			cout << choice << " is already used. Make the correct choice " << endl;
		}		
	}
}


bool check_win(UINT pid){

	int row, col;
	int matching_char_counter;
	char ch = (pid == Player1_ID)?Player1_Symbol:Player2_Symbol;

	/* Check if player has made a row */
	for (row=0; row <GAME_SIZE; row++ ){
		matching_char_counter = 0;
		for (col = 0; col < GAME_SIZE; col++)
		{
			if (ch == Game_Board[row][col])
			{
				matching_char_counter++;
			}
		}

		if(matching_char_counter == GAME_SIZE){
			cout << "matching_char_counter:" << matching_char_counter << "*****" << endl;
			return true;	// We found one row
		}
	}


	/* Check if player has made a col */
	for (col=0; col <GAME_SIZE; col++ ){
		matching_char_counter = 0;
		for (row = 0; row < GAME_SIZE; row++)
		{
			if (ch == Game_Board[row][col])
			{
				matching_char_counter++;
			}
		}

		if(matching_char_counter == GAME_SIZE){
			return true;	// We found one column
		}
	}

	/* Check if a diagonal is made. */
	matching_char_counter=0;
	for (int i=0; i<GAME_SIZE; i++){
		if (ch == Game_Board[i][i])
		{
			matching_char_counter++;
		}
	}
	if(matching_char_counter == GAME_SIZE){
		return true;	// We found one row
	}

	/* Check if a diagonal is made. */
	matching_char_counter=0;
	for (int i=0; i<GAME_SIZE; i++){
		if (ch == Game_Board[GAME_SIZE-1-i][i])
		{
			matching_char_counter++;
		}
	}
	if(matching_char_counter == GAME_SIZE){
		return true;	// We found one row
	}

	/* If not row/col/diagonal is found then it's not a win yet. */
	return false;
}

bool check_tie(){
	bool tie;

	if (Move_Counter == GAME_SIZE*GAME_SIZE)
	{
		tie = true;
	}
	else
	{
		/* Check if any row has the same player moves */ 
		tie=false;
	}

	return tie;
}

void display_input_choices(){

	UINT choice_num=0;

	for (int row=0; row <GAME_SIZE; row++ ){
		for (int col = 0; col < GAME_SIZE; col++)
		{
			cout << ++choice_num << ".";
			if (Game_Board[row][col] == Toe)
			{
				cout << "(row, col)=" << row << "," << col ;
			}

			cout << endl;
		}
	}
}

UINT toggle_turn(UINT pid){
	return (pid == Player1_ID ? Player2_ID : Player1_ID);
}

void prog6_1(int argc, char** argv){

	if(argc > 1)
	{
		start_game();
	}
	else
	{
		start_game_with_defaults();
	}
}


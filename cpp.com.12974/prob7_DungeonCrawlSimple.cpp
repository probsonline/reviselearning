#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * Make a program that outputs a simple grid based gameboard to the screen using either numbers or characters.
i.e.

. . . . . . . . . .
. G . . . . . . . .
. . . . . . T . . .
. . . . . . . . . .
. . . . T . . . . .
. . . . . . T . . .
. . . . . . . . . X


or

0 0 0 0 0 0 0 0 0 0
0 5 0 0 6 0 0 0 0 0
0 0 0 0 0 0 7 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 7 0 0 0 0 0 0
0 0 0 0 0 0 7 0 0 0
0 0 0 0 0 0 0 0 0 4


Allow the user (marked by G in the example) to move either up, down, left, or right each turn.
If the player steps on a trap then they lose. If the make it to the treasure 'X' then they win.

★★ Add enemies that move randomly in any direction once per turn. (enemies just like traps cause the player to lose if touched)

HINT: Don't let the player move off the gameboard! You program will crash if they move off the top or bottom of the board!
(the same holds true for enemies)
 * */

#define CHAR_MODE

typedef unsigned int UINT;


#define KEY_UP		1
#define KEY_DOWN	2
#define KEY_LEFT	3
#define KEY_RIGHT 	4

#ifdef CHAR_MODE
static char Empty_Symbol	= '.';
static char User_Symbol		= 'G';
static char Trap_Symbol		= 'T';
static char Target_Symbol	= 'X';

#else
static unsigned char Empty_Symbol	= 0;
static unsigned char User_Symbol	= 5;
static unsigned char Trap_Symbol	= 7;
static unsigned char Target_Symbol	= 4;


#endif

static const char GAME_SIZE=16;
static char Game_Board[GAME_SIZE][GAME_SIZE];
static UINT User_X;
static UINT User_Y;
static UINT Target_X;
static UINT Target_Y;
static bool Trap_Hit=false;


/* Game core functions */
static void start_dc_game();
static void play();
static bool set_player_position(int x,int y);
static void set_target();
static void set_traps();

/* Utility Functions */
static bool move_left();
static bool move_right();
static bool move_down();
static bool move_up();
static bool is_wall(int x, int y);
static bool is_empty_place(int x, int y);
static bool is_win();
static bool is_trapped();
static bool will_hit_trap(int x, int y);
static bool check_target(int x, int y);

/* UI functions */
static void draw_gameboard();
static void display_input_ui();
static UINT get_user_input();

void draw_gameboard(){

	for(int row=0; row<GAME_SIZE; row++){
		for(int col=0; col<GAME_SIZE; col++){

#ifdef CHAR_MODE
			cout << " " << (char)Game_Board[row][col];	//This cast to char is necessary otherwise cout will print the ascii value of the char
#else
			cout << " " << Game_Board[row][col];	//This cast to char is necessary otherwise cout will print the ascii value of the char
#endif
		}
		cout << endl;
	}
}


void start_dc_game(){

	for(int row=0; row<GAME_SIZE; row++){
		for(int col=0; col<GAME_SIZE; col++){
			Game_Board[row][col]=Empty_Symbol;
		}
	}

	srand(time(NULL));	//Called only once at the start of the game to get a uniform distribution of the random numbers later on

	/* 1. First set the target position. */
	set_target();

	/* 2. Second set initial player position making sure it's not same as the target */
	UINT starting_x;
	UINT starting_y;
	do{
		starting_x = rand()%GAME_SIZE;
		starting_y = rand()%GAME_SIZE;
//		cout << "Trying to set player at (" << starting_x << "," << starting_y << ")"<< endl;

	}while(check_target(starting_x, starting_y) == true);
	set_player_position(starting_x, starting_y);

	/* 3. Set traps making sure they are not at Player/Target positions. */
	set_traps();

	draw_gameboard();

	play();
}

void play(){
	bool game_finished=false;
	int move_choice;
	bool moved=false;

	do{
		move_choice = get_user_input();
		switch(move_choice){
			case KEY_UP:
				moved=move_up();
				break;
			case KEY_DOWN:
				moved=move_down();
				break;
			case KEY_RIGHT:
				moved=move_right();
				break;
			case KEY_LEFT:
				moved=move_left();
				break;
			default:
				break;
		}

		if(moved == true){
			draw_gameboard();

			game_finished = is_win();
			if(game_finished == true){
				cout << "You reached the target and Won" << endl;
				break;
			}

			game_finished = is_trapped();
			if(game_finished == true){
				cout << "You hit the trap and lost" << endl;
				break;
			}

		}

	}while(game_finished == false);

}

bool set_player_position(int x, int y){
	bool move_successful;

	if(is_wall(x, y) == true)
	{
		cout << "There is wall next. ";
		move_successful=false;
	}
	else
	{
		move_successful = true;

		if(will_hit_trap(x,y)==true)
		{
			Trap_Hit=true;
		}
		/* Clear the current position and place the player at the new position. */
		Game_Board[User_X][User_Y] = Empty_Symbol;
		User_X = x;
		User_Y = y;
		Game_Board[User_X][User_Y] = User_Symbol;

//		cout << "Player is at (" << User_X << "," << User_Y << ")"<< endl;
	}

	return move_successful;
}

void set_target(){

	Target_X=rand()%GAME_SIZE;
	Target_Y=rand()%GAME_SIZE;

	Game_Board[Target_X][Target_Y] = Target_Symbol;

//	cout << "Target is at (" << Target_X << "," << Target_Y << ")"<< endl;
}

void set_traps(){

	int trap_count=0;
	int active_traps=rand()%(GAME_SIZE)+1;//make sure there is at least one trap
	int x, y;

//	cout << active_traps << " traps are being set " << endl;
	while(trap_count < active_traps){
		x = rand()%(GAME_SIZE);
		y = rand()%(GAME_SIZE);

		if(is_empty_place(x, y)){
			Game_Board[x][y] = Trap_Symbol;
			trap_count++;
		}
	}
}

bool check_target(int x, int y){
	bool result=false;

	if (Game_Board[x][y] == Target_Symbol){
		result = true;
	}

	return result;
}

bool is_wall(int x, int y){

	bool result=false;

//	if(x==0 || x==GAME_SIZE-1 || y ==0 || y==GAME_SIZE-1){
	if(x==-1 || x==GAME_SIZE || y == -1 || y==GAME_SIZE){
		result = true;
	}

	return result;
}

bool is_win(){
	bool result=false;
	if(User_X==Target_X && User_Y==Target_Y)
		result=true;

	return result;
}

bool is_trapped(){

	return Trap_Hit;
}

bool will_hit_trap(int x, int y){

	bool result=false;

	if(Game_Board[x][y]==Trap_Symbol){
		result=true;
	}

	return result;
}

bool is_empty_place(int x, int y){

	bool result=false;

	if(Game_Board[x][y] == Empty_Symbol){
		result = true;
	}

	return result;

}

/* X is the row and Y is the column */

bool move_up(){
	return(set_player_position(User_X-1, User_Y));
}
bool move_down(){
	return(set_player_position(User_X+1, User_Y));
}

bool move_left(){
	return(set_player_position(User_X, User_Y-1));
}

bool move_right(){
	return(set_player_position(User_X, User_Y+1));
}

void display_input_ui(){
	cout << "Choose your move " << endl;
	cout << KEY_UP << ". UP" << endl;
	cout << KEY_DOWN << ". DOWN" << endl;
	cout << KEY_LEFT << ". LEFT" << endl;
	cout << KEY_RIGHT << ". RIGHT" << endl;
}

UINT get_user_input(){
	int key;

	display_input_ui();
	while(true){
		cin >> key;
		if(key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT )
		{
			break;
		}
		else{
			cout << "Make a valid move choice " << endl;
		}
	}

	return key;
}


/* UI Functions */






void prob7_1(int argc, char** argv){
	start_dc_game();
}

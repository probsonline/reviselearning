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
#define DUNGEON_LEVLE_2	 1

typedef unsigned int UINT;

static const int KEY_UP=1;
static const int KEY_DOWN=2;
static const int KEY_LEFT=3;
static const int KEY_RIGHT=4;

static char Empty_Symbol;
static char User_Symbol;
static char Trap_Symbol;
static char Target_Symbol;
static char Enemy_Symbol;

static const char GAME_SIZE=10;
static char Game_Board[GAME_SIZE][GAME_SIZE];

static UINT User_X;
static UINT User_Y;
static UINT Target_X;
static UINT Target_Y;
static bool Trap_Hit;
static bool Enemy_Hit;
static UINT Enemy_Count;

static void start_dc_game(bool is_numeric_u);
static void play();

static bool set_player_position(int x,int y);
static void set_target();
static void set_traps();
static void set_enemies();

static bool move_left();
static bool move_right();
static bool move_down();
static bool move_up();
static bool move_enemy(int x, int y);
static void move_enemies();

static bool is_wall(int x, int y);
static bool is_empty_place(int x, int y);
static bool is_win();
static bool is_trapped();
static bool will_hit_trap(int x, int y);
static bool check_target(int x, int y);
static bool will_hit_enemy(int x, int y);
static bool is_hit_by_enemy();

static void draw_gameboard();
static void display_input_ui();
static UINT get_user_input();


void start_dc_game(bool is_numeric_ui){

	srand(time(NULL));

	if(is_numeric_ui == false)
	{
		Empty_Symbol	= '.';
		User_Symbol		= 'G';
		Trap_Symbol		= 'T';
		Target_Symbol	= 'X';
		Enemy_Symbol	= 'E';
	}
	else
	{
		Empty_Symbol	= '0';
		User_Symbol		= '5';
		Trap_Symbol		= '7';
		Target_Symbol	= '4';
		Enemy_Symbol	= '6';
	}

	for(int row=0; row<GAME_SIZE; row++){
		for(int col=0; col<GAME_SIZE; col++){
			Game_Board[row][col]=Empty_Symbol;
		}
	}

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

#ifdef DUNGEON_LEVLE_2
	Enemy_Count = rand()%GAME_SIZE+1;
	set_enemies();
#endif

	draw_gameboard();

	play();
}


/************************************************
 * Game AI Core
 *
 *************************************************/
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
			move_enemies();
			draw_gameboard();

			game_finished = is_win();
			if(game_finished == true){
				cout << "You reached the target and Won" << endl;
				break;
			}

			game_finished = is_hit_by_enemy();
			if(game_finished == true){
				cout << "You hit the Enemy and lost" << endl;
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

void move_enemies(){
	int moved_enemies_counter=0;

	for(int row=0; row<GAME_SIZE; row++)
	{
		for(int col=0; col<GAME_SIZE; col++)
		{
			if(Game_Board[row][col] == Enemy_Symbol)
			{
//				cout << "Trynig to move enemy from (" << row << "," << col << ")"<< endl;
					if(move_enemy(row, col)==true)
					{
						moved_enemies_counter++;
					}
			}
			// If we have moved all enemies, stop looking further.
			// Bug: A moved enemy may be counted again with the above logic and so move twice while some enemy may not move at all
//			if(moved_enemies_counter >= Enemy_Count){
//				break;
//			}
		}
	}

	char temp_enemy_symbol='e';
	for(int row=0; row<GAME_SIZE; row++)
	{
		for(int col=0; col<GAME_SIZE; col++)
		{
			if(Game_Board[row][col] == temp_enemy_symbol)
			{
				Game_Board[row][col] =Enemy_Symbol;
			}
		}
	}
}

/************************************************
 * Game AI Support
 *
 *************************************************/
bool is_wall(int x, int y){

	bool result=false;

//	if(x==0 || x==GAME_SIZE-1 || y ==0 || y==GAME_SIZE-1){
	if(x==-1 || x==GAME_SIZE || y == -1 || y==GAME_SIZE){
		result = true;
	}

	return result;
}

bool is_win()
{
	bool result=false;
	if(User_X==Target_X && User_Y==Target_Y)
		result=true;

	return result;
}


bool is_trapped()
{

	return Trap_Hit;
}

bool is_hit_by_enemy(){
	return Enemy_Hit;
}

bool will_hit_trap(int x, int y)
{

	bool result=false;

	if(Game_Board[x][y]==Trap_Symbol){
		result=true;
	}

	return result;
}

bool will_hit_enemy(int x, int y){

	bool result=false;

	if(Game_Board[x][y]==Enemy_Symbol){
		cout << "Enemy here (" << x << "," << y << ")" << endl;
		result=true;
	}

	return result;
}

void set_target()
{

	Target_X=rand()%GAME_SIZE;
	Target_Y=rand()%GAME_SIZE;

	Game_Board[Target_X][Target_Y] = Target_Symbol;

//	cout << "Target is at (" << Target_X << "," << Target_Y << ")"<< endl;
}

void set_traps()
{

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

bool set_player_position(int x, int y)
{
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
		else if (will_hit_enemy(x,y)==true)
		{
			Enemy_Hit=true;
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

void set_enemies()
{

	int enemy_count=0;
	int active_enemies=Enemy_Count;
	srand(time(NULL));

	int x, y;

//	cout << active_enemies << " enemies are being hunting you " << endl;
	while(enemy_count < active_enemies){
		x = rand()%(GAME_SIZE);
		y = rand()%(GAME_SIZE);

		if(is_empty_place(x, y)){
			Game_Board[x][y] = Enemy_Symbol;
			enemy_count++;
		}
	}
}


bool move_enemy(int x, int y){
	bool moved=true;
	int move_direction;
	int new_x, new_y;
	int move_attempt_counter=0;
	char temp_enemy_symbol='e';

	srand(x+y);

	/* Make attempts to move in any of the available direction.
	Since only 4 directions are possible at max (some may not move as being surrounded on each side)
	so, put a limit on how many attempts to make to move an enemy
	*/
	do
	{
		new_x=x;
		new_y=y;
		move_direction = rand()%4+1; //since only 4 directions are possible
		switch(move_direction){
			case KEY_UP:
				new_x=x-1;
				if(new_x >=0 && is_empty_place(new_x, new_y)){
					Game_Board[x][y] = Empty_Symbol;
					Game_Board[new_x][new_y] = temp_enemy_symbol;
					moved=true;
				}
				break;
			case KEY_DOWN:
				new_x=x+1;
				if(new_x < GAME_SIZE && is_empty_place(new_x, new_y)){
					Game_Board[x][y] = Empty_Symbol;
					Game_Board[new_x][new_y] = temp_enemy_symbol;
					moved=true;
				}
				break;
			case KEY_RIGHT:
				new_y=y+1;
				if(new_y < GAME_SIZE && is_empty_place(new_x, new_y)){
					Game_Board[new_x][new_y] = temp_enemy_symbol;
					Game_Board[x][y] = Empty_Symbol;
					moved=true;
				}
				break;
			case KEY_LEFT:
				new_y=y-1;
				if(new_y >=0 && is_empty_place(new_x, new_y)){
					Game_Board[new_x][new_y] = temp_enemy_symbol;
					Game_Board[x][y] = Empty_Symbol;
					moved=true;
				}
				break;
			default:
				break;
		}
	}while(!moved && move_attempt_counter<8); //Putting a counter is necessary otherwise an enemy which has no empty space around it to move may result in an infinite loop

//	if(moved)
//		cout << "Moved enemy to (" << new_x << "," << new_y << ")"<< endl;

	return moved;
}

/************************************************
 * Utility Functions
 * X is the row and Y is the column
 *************************************************/
bool move_up()   {	return(set_player_position(User_X-1, User_Y));}
bool move_down() {	return(set_player_position(User_X+1, User_Y));}
bool move_left() {	return(set_player_position(User_X, User_Y-1));}
bool move_right(){	return(set_player_position(User_X, User_Y+1));}

bool check_target(int x, int y)
{
	bool result=false;

	if (Game_Board[x][y] == Target_Symbol){
		result = true;
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


/************************************************
 * UI Functions
 *************************************************/
void draw_gameboard(){
	for(int row=0; row<GAME_SIZE; row++)
	{
		for(int col=0; col<GAME_SIZE; col++)
		{
			cout << " " << Game_Board[row][col];	//This cast to char is necessary otherwise cout will print the ascii value of the char
		}
		cout << endl;
	}
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

/* Test function */
void prob7_2(int argc, char** argv){

	start_dc_game(false);
}

#include <string>


/********************************************************************
 *  Custom data type definitions
 ********************************************************************/

typedef enum color_enum
{
	WHITE,
	BROWN,
	BLACK,
	SPOTTED,
	Color_Count
}Color;

typedef enum sex_enum
{
	Male,
	Female,
	Gender_Count
}Gender;

typedef enum message_id
{
	NONE,
	FATAL,
	ERROR,
	WARN,
	BIRTH,
	DEATH,
	MUTATION,
	INFO,
	TRACE,
	DEBUG,
	Message_Count
}MessageID;

typedef struct population_struct
{
	int total_created;
	int dead_population;
	int current_population;
	int males;	//include adults and children
	int females;
	int adult_population;
	int adult_males; //alive
	int adult_females;	//alive
	int radioactive_mutants;
}Population;

typedef struct bunny_struct
{
	unsigned int    id;
	unsigned int 	age;
	Color			color;
	Gender 			sex;
	bool 			radioactive_mutant_vampire_bunny;
	std::string		name;
	struct bunny_struct* next_bunny;
}Bunny;

typedef Bunny* Colony;


/********************************************************************
 *  Function prototype definitions
 ********************************************************************/

void start_bunny_colony(int inital_population);
void evolve_bunny_colony();
Bunny* create_bunny(int b_id, int mother_id);
void age_bunny();
void breed_bunny();
void die_aged_bunnies();
void die_bunny(Bunny *b);
void mutate_bunny();
void list_population();
void bring_famine();
void print_message(MessageID mid, std::string msg);
void log_message(std::string msg);

Gender get_next_bunny_gender(int current_m_count, int current_f_count);
Color get_next_bunny_color(Bunny* mother);
bool get_next_bunny_type(int vampire_count);
void get_next_bunny_name(std::string &name);
std::string get_color_string(Color color_id);

/* Population counter functions */
int get_current_population();
int get_adult_male_population();
int get_adult_female_population();
int get_radioactive_mutant_vampie_population();
int get_current_male_population();
int get_current_female_population();
int get_creation_count();
void reduce_adult_population(Bunny *b);
void reset_population_counter();

/* List data strcuture functions */
void create_list();
void add_element(Bunny* new_bunny);
void delete_element(Bunny* old_bunny);
void delete_first_element();
Bunny* find_element(unsigned int val);

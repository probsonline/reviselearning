#include <iostream>
#include <cstdlib>
#include <fstream>	//for file I/O

#include <unistd.h> //For sleep
#include "prob10.hpp"

using namespace std;

/*
 * Time Log: 1/2+1/2+1
Write a program that creates a linked list of bunny objects. (Done)
Each bunny object must have
Sex: Male, Female (random at creation 50/50) (Done)
color: white, brown, black, spotted (Done)
age : 0-10 (years old) (Done)
Name : randomly chosen at creation from a list of bunny names (Done)
radioactive_mutant_vampire_bunny: true/false (decided at time of bunny creation 2% chance of true) (Done)

At program initialization 5 bunnies must be created and given random colors. (Done)

Each turn afterwards the bunnies age 1 year. (Done)
So long as there is at least one male age 2 or older, for each female bunny in the list age 2 or older;
a new bunny is created each turn. (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn) (Done)
New bunnies born should be the same color as their mother. (Done)
If a bunny becomes older than 10 years old, it dies. (Done)
If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny. (done)
(if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on...)
Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies. (Done)
Radioactive vampire bunnies do not die until they reach age 50. (Done)
The program should print a list of all the bunnies in the colony each turn along w/ all the bunnies details, sorted by age. (Done)
The program should also output each turns events such as (Done)
"Bunny Thumper was born!
Bunny Fufu was born!
Radioactive Mutant Vampire Bunny Darth Maul was born!
Bunny Julius Caesar died!
The program should write all screen output to a file. (Done)
When all the bunnies have died the program terminates. (Done)
If the bunny population exceeds 1000 a food shortage must occur killing exactly half of the bunnies (randomly chosen) (Done)

★ Modify the program to run in real time, with each turn lasting 2 seconds, and a one second pause between each announement.

★★ Allow the user to hit the 'k' key to initiate a mass rabit cull! which causes half of all the rabits to be killed (randomly chosen).

★★★★ Modify the program to place the rabits in an 80x80 grid. Have the rabits move one space each turn randomly.
Mark juvenile males with m, adult males w/ M,
juvenile females w/ f, adult females w/ F
radioactive mutant vampire bunnies with X

Modify the program so that radioactive mutant vampire bunnies only convert bunnies that end a turn on an adjacent square.
Modify the program so that new babies are born in an empty random adjacent square next to the mother bunny. (if no empty square exits then the baby bunny isn't born)

★★★★★ Modify the program so that it saves each turn to a file and can play back at accelearted speed all subsequent turns.
*/




/******************************************
 * Global Data
*******************************************/
static Colony Bunny_Colony;
static Population Population_Stats;
static ofstream logfile; //Logfile handle
static string Bunny_Name_Pool[]={"Thumper", "Fufu", "Darth Maul","Julius Caesar",
		"chinese", "korean", "japanese", "Malai", "taiwanese",
		"Onga Bonga", "Onga Donga", "Bonga Donga",  "Shadai",
		"NiHa", "HoHo", "Seedha", "Putha", "Ulta", "Dinga"};

static const int MAX_POPULATION=1000;
static const int MIN_POPULATION=0;
static const int MAX_BUNNY_AGE=10;
static const int MAX_VAMPIRE_AGE=50;
static const int ADULTHOOD_AGE=2;
static const string LOG_FILE_NAME="/tmp/bunny.log";

#define DEFAULT_LOGGING_LEVEL TRACE

/******************************************
 * Utility Functions
*******************************************/
Gender get_next_bunny_gender(int current_m_count, int current_f_count){
	Gender next_bunny_sex;
	int num = rand()%Gender_Count;
	float diversity_deviation_percent=0/100;	//tolerance in % before favoring the suffering gender

	/* If previous male/fame population differs by more than diversity_deviation% then adjust the sex
	 * in favor of the lesser gender.
	 * diversity_deviation% is chosen instead of simple numerical comparison so that random number generator
	 * at least works otherwise it would have been just an oscillation between the two only.  */
	if(current_m_count > (int)(current_f_count*(1+diversity_deviation_percent)) )
	{
		next_bunny_sex=Female;
	}
	else if (current_f_count > (int)(current_m_count*(1+diversity_deviation_percent)) )
	{
		next_bunny_sex=Male;
	}
	else
	{
		next_bunny_sex = (num == Male)?Male:Female;
	}

	return next_bunny_sex;
}

/* If a mother is specified then give mother's color as the color otherwise give a random color. */
Color get_next_bunny_color(Bunny* mother){
	Color color;
	if(mother != NULL)
	{
		color = mother->color;
	}
	else
	{
		color = static_cast<Color>(rand()%Color_Count);  /* We have to use static_cast as normal way of cast does work for enum */
	}
	return color;
}

/* Make sure that 2% of the creation is radioactive mutant vampire bunny. */
bool get_next_bunny_type(int current_vampire_count)
{
	if((rand()%100) <2) return true;
	else return false;
}


void get_next_bunny_name(string & name)
{
	int name_count = sizeof(Bunny_Name_Pool)/sizeof (string);
	int name_index=rand()%name_count;
	string msg = "get_next_bunny_name(): name_count " + to_string(name_count) +
			" name_index: " + to_string(name_index) + " " +
			Bunny_Name_Pool[name_index];
	print_message(DEBUG, msg);

	name="";	//Clear out the string
	/* Append the found name to the string. We cannot use copy/assign/=/pointer etc.
	as in each of those cases, when a name longer than the input string bounds is
	given, the string behavior is undefined	and it may result in segmentation fault.*/
	name+=Bunny_Name_Pool[name_index];
}

int get_current_population(){	return Population_Stats.current_population;}
int get_adult_male_population(){	return Population_Stats.adult_males;}
int get_adult_female_population(){return Population_Stats.adult_females;}
int get_radioactive_mutant_vampie_population(){return Population_Stats.radioactive_mutants;}
int get_current_male_population(){return Population_Stats.males;}
int get_current_female_population(){return Population_Stats.females;}
int get_creation_count(){return Population_Stats.total_created;}
void reset_population_counter()
{
	Population_Stats.adult_females=0;
	Population_Stats.adult_females=0;
	Population_Stats.adult_population=0;
	Population_Stats.current_population=0;
	Population_Stats.females=0;
	Population_Stats.males=0;
	Population_Stats.radioactive_mutants=0;

	//Below fields are more for debugging and not for actual usage in program logic
	Population_Stats.total_created=0;
	Population_Stats.dead_population=0;
}
string get_color_string(Color color_id)
{
	string color;
	switch(color_id)
	{
	case WHITE:
		color="white";
		break;
	case BROWN:
		color="brown";
		break;
	case BLACK:
		color="black";
		break;
	case SPOTTED:
		color="spotted";
		break;
default:
		color="none";
	break;
	}
	return color;
}
void reduce_adult_population(Bunny *b)
{
	if(b->age >=ADULTHOOD_AGE)
	{
		Population_Stats.adult_population--;
		if(b->sex==Male){Population_Stats.adult_males--;}else{Population_Stats.adult_females--;}
	}
}


void start_bunny_colony(int inital_population)
{
	srand(time(NULL));
	create_list();
	reset_population_counter();

	//Start logging
	logfile.open(LOG_FILE_NAME);

	print_message(TRACE, "Starting Bunny Colony");

	for (int i=1; i<=inital_population; i++)
	{
		create_bunny(get_creation_count(), 0);
	}

	print_message(TRACE, "Colony Evolution started ");
	evolve_bunny_colony();
	logfile.close();
}

void evolve_bunny_colony()
{
	int current_population;
	int loop_counter=0;

	while(true)
	{
		print_message(DEBUG, "Turn No: " + to_string(++loop_counter));
		current_population=get_current_population();
		print_message(DEBUG, "evolve_bunny_colony(): Current Population " + to_string(current_population));

		if(current_population > MAX_POPULATION)
		{
			print_message(TRACE, "Famine is causing the death of the population ");
			bring_famine();
		}
		else if(current_population == MIN_POPULATION)
		{
			print_message(TRACE, "Colony is dead. No bunnies left alive");
			break;
		}
		else
		{
			age_bunny();		//Age must be the first, otherwise, if it is after breed then children will become adults in 1 turn. They'll be 1 at birth instead of 0
			list_population();	//Now list the population stats
			breed_bunny();		//Keep breed before death and mutation so that more chances of increasing population
			die_aged_bunnies(); //Die the old bunnies
			mutate_bunny();		//Keep mutation the last. OTherwise it would be so fast that it may not let the populationr each its max limit.
		}
//		sleep(1);
	}
}

Bunny* create_bunny(int b_id, int mother_id)
{
	Bunny *b;
	string binfo="";
	string name="";
	b = new Bunny;
	if(b != NULL)
	{
		b->id	= 1+b_id;
		get_next_bunny_name(name);
		b->name=name;
		b->color= get_next_bunny_color(find_element(mother_id));
		b->sex	= get_next_bunny_gender(get_current_male_population(), get_current_female_population());
		b->radioactive_mutant_vampire_bunny=get_next_bunny_type(get_radioactive_mutant_vampie_population());

		b->age = 0;
		add_element(b);

		/* Increment counters */
		Population_Stats.total_created++;
		Population_Stats.current_population++;
		if(b->sex==Male){Population_Stats.males++;}else{Population_Stats.females++;}
		if(b->radioactive_mutant_vampire_bunny==true){Population_Stats.radioactive_mutants++;}

		binfo += " " + to_string(b->id) + ".";
		binfo += (b->radioactive_mutant_vampire_bunny==true)?" Radioactive vampire mutant ":"";
		binfo += " Bunny " + b->name;
		binfo += " was born having ";
		binfo += get_color_string(b->color);
		binfo += " color!";

		print_message(BIRTH, binfo);
	}

	return b;
}

void die_aged_bunnies()
{
	Bunny *b=Bunny_Colony;
	Bunny *next;

	while(b != NULL)
	{
		next=b->next_bunny;
		if((b->radioactive_mutant_vampire_bunny == false) &&( b->age >=MAX_BUNNY_AGE))
		{
			print_message(DEBUG, "An adult is going to die at age: " +to_string(b->age));

			die_bunny(b);
		}
		else if((b->radioactive_mutant_vampire_bunny == true) && (b->age >=MAX_VAMPIRE_AGE))
		{
			print_message(DEBUG, "A mutant is going to die at age: " +to_string(b->age));
			die_bunny(b);
		}
		b=next;
	}
}

void die_bunny(Bunny *b)
{
	Population_Stats.current_population--;
	string msg="";
	if(b->sex==Male){Population_Stats.males--;}else{Population_Stats.females--;}
	if(b->radioactive_mutant_vampire_bunny==true)
	{
		Population_Stats.radioactive_mutants--;
		msg+="Radioactive mutant vampire ";
	}
	else
	{
		reduce_adult_population(b);
	}

	msg+="bunny " + b->name + " died at age " + to_string(b->age);
	print_message(DEATH, msg);
	delete_element(b);
}

void age_bunny()
{
	Bunny *b=Bunny_Colony;
	string msg;

	print_message(DEBUG, "age_buny()");

	while(b != NULL)
	{
		b->age++;
		if((b->age ==2) && (b->radioactive_mutant_vampire_bunny==false))
		{
			msg = b->name + " is " +
					to_string(b->age) +
					" year old adult " +
					((b->sex==Male)?" male now.":" female now");
			print_message(DEBUG, msg);

			Population_Stats.adult_population++;
			if(b->sex==Male){Population_Stats.adult_males++;}else{Population_Stats.adult_females++;}
		}
		b=b->next_bunny;
	}
}

void breed_bunny()
{
	if(get_adult_male_population() > 0)
	{
		Bunny *b=Bunny_Colony;
		Bunny *child=NULL;

		if(get_adult_female_population() >0)
		{
			print_message(DEBUG, "reproduction is possible");
			while(b != NULL)
			{
				if(b->age>=ADULTHOOD_AGE && b->sex==Female && b->radioactive_mutant_vampire_bunny==false)
				{
					child=create_bunny(get_creation_count(), b->id); //TODO: This can be optimized by changing create_bunny to take Bunny pointer as input instead of mother's id
					/* There was big bug here. Only one bunny was being born instead of equal to the mother count.
					It was due to the fact that b was after this statement pointing to the child which was added at the end of the list
					and next of the child was thus null. due to that being null, when the following statement did b=b->next_bunny. It sometimes gave segfault
					and if it didn't give segfault, the exited just after one birth due to its condition against null. TO correct that created separate
					pointer for child */
				}

				//Just a debug check (Aah. This itself is causing a silent program exit as if child is not initialized, it will point to a random location in memory.)
				if(child != NULL && child->color != b->color) print_message(DEBUG, "The child born is not the same color as the mother.");

				b=b->next_bunny;
			}
		}
		else
		{
			print_message(DEBUG, "No adult females for reproduction.");
		}
	}
	else
	{
		print_message(DEBUG, "No adult male in the colony. Breeding is not possible.");
	}
}

void mutate_bunny()
{
	print_message(DEBUG, "mutate_bunny(): Start ");

	Bunny *b=Bunny_Colony;
	int mutant_population=get_radioactive_mutant_vampie_population();
	int normal_bunny_id;

	//Only proceed if all the population is not already mutant
	if(mutant_population == get_current_population()) return;

	int mutant=0;
	while(mutant<mutant_population)
	{
		normal_bunny_id = 1+rand()%get_creation_count(); //Select a random non-mutant bunny;
		b = find_element(normal_bunny_id);

		if (b != NULL)
		{
			if(b->radioactive_mutant_vampire_bunny==false)
			{
				b->radioactive_mutant_vampire_bunny = true;
				Population_Stats.radioactive_mutants++;
				reduce_adult_population(b);

				print_message(MUTATION, b->name + " turned into radioactive vampier bunny ");

				mutant++;
				print_message(DEBUG, "mutate_bunny(): current iteration count:Mutant++"+ to_string(mutant));
			}

			/* Get the latest mutant population count and if no more normal bunnies are left, then stop mutation.
			 * This needs to be outside the above if otherwise, when all poulation is mutants, an infinite loop will be formed here */
			if(get_radioactive_mutant_vampie_population() == get_current_population())
			{
				print_message(WARN, "All population turned into mutant now. HAHA. We overtook the world! ");
				break;
			}
		}else print_message (DEBUG,  "*** A dead bunny cannot be converted into a radioactive bunny. retrying another one.");
	}
	print_message(DEBUG, "mutate_bunny():  End");

}


void bring_famine()
{
	Bunny *b;
	int death_count=0;
	int current_population=get_current_population();
	int suffering_population = current_population/2; //50% will die
	int bid;

	print_message(TRACE, "bring_famine(): 50%(" + to_string(suffering_population) +") bunnies will die");

	while (death_count < suffering_population)
	{
		bid = rand()%current_population;
		b=find_element(bid);
		if(b != NULL)
		{
			die_bunny(b);
			death_count++;
		}
	}
}
//Sadly took many test iterations to get it correct
void list_population()
{
	Bunny *b=Bunny_Colony;
	string binfo;

	if(b == NULL)
	{
		print_message(WARN, "No bunnies in the colony ");
		return;
	}

	binfo += "\tTotal population: " + to_string(get_current_population());
	binfo += "\tAdult Male population: " + to_string(get_adult_male_population());
	binfo += "\tAdult Female population: " + to_string(get_adult_female_population());
	binfo += "\tMutant population: " + to_string(get_radioactive_mutant_vampie_population());
	binfo += "\tChildren population: " + to_string(get_current_population()-get_adult_male_population()-get_adult_female_population()-get_radioactive_mutant_vampie_population());

	print_message(TRACE, binfo);

	string *print_sorted = new string[51];	//This way of initizalition has to be done as the string is not known in advance.
	for(int age=0; age<51; age++)
	{
		print_sorted[age] = "";
	}

	string msg;
	do
	{
		//concatenate the information for each bunny in its respective age group.
		msg = " ";
		msg += to_string(b->id) + "." ;
		msg +=  " Bunny " + b->name;
		msg +=  " is a ";
		msg += ((b->radioactive_mutant_vampire_bunny==false)?(b->sex==Male?"male ":"female "):" radioactive vampire mutant ");
		msg += " aged: " + to_string(b->age);
		msg += " colored " + get_color_string(b->color);
		msg += "\n";
		print_sorted[b->age] = print_sorted[b->age] + msg;
		b=b->next_bunny;


	}while(b!=NULL);

	for(int age=0; age<51; age++)
	{
		if(print_sorted[age] != "")
		{
			print_message(NONE, print_sorted[age]);
		}
	}
}

void print_message(MessageID mid, string msg)
{
	MessageID current_log_level=DEFAULT_LOGGING_LEVEL;
	string msg_id;


	if(mid == FATAL) msg_id = "[FATAL]";
	else if(mid == ERROR) msg_id = "[ERROR]";
	else if(mid == WARN) msg_id = "[WARN]";
	else if(mid == BIRTH) msg_id = "[BIRTH]";
	else if (mid == DEATH) msg_id = "[DEATH]";
	else if (mid == MUTATION) msg_id = "[MUTATION]";
	else if (mid == INFO) msg_id = "[INFO]";
	else if (mid == TRACE) msg_id = "[TRACE]";
	else if (mid == DEBUG) msg_id = "[DEBUG]";
	else msg_id="";

	if(mid <= current_log_level)
	{
		cout << msg_id << msg << endl;
		logfile << msg_id << msg << endl;
	}
}


/*********************************************************************
 * List data structure functions
 *********************************************************************/
void create_list()
{
	Bunny_Colony=NULL;
}

void add_first_element(Bunny* first_bunny)
{
	Bunny_Colony=first_bunny;
	first_bunny->next_bunny=NULL;
}


void add_element(Bunny* new_bunny)
{
	Bunny *b=Bunny_Colony;

	if(Bunny_Colony!=NULL)
	{
		//Reach to the end of the list
		while(b->next_bunny != NULL)
		{
			b=b->next_bunny;
		}

		b->next_bunny = new_bunny;
		new_bunny->next_bunny=NULL;
		print_message(DEBUG, "added another element");
	}
	else
	{
		add_first_element(new_bunny);
		print_message(DEBUG, "First bunny element");
	}
}

void delete_first_element()
{
	Bunny *head=Bunny_Colony;
	Bunny *b = Bunny_Colony;
	head = b->next_bunny;
	b->next_bunny = NULL;
	free(b);
	Bunny_Colony =head;
	print_message(DEBUG, "Deleted first element");

}

void delete_element(Bunny* old_bunny)
{
	Bunny *prev_bunny=Bunny_Colony;
	Bunny *b=prev_bunny->next_bunny;

	//If the bunny to be deleted is not the first element in the list pointed to by head (Bunny_Colony) the find it.
	if(prev_bunny->id != old_bunny->id)
	{
		while(b!=NULL)
		{
			if(b->id == old_bunny->id)
			{
				prev_bunny->next_bunny = b->next_bunny;
				b->next_bunny=NULL;
				free(b);
				print_message(DEBUG, "deleted another element");
			}
			prev_bunny = b;
			b=b->next_bunny;
		}
	}
	else
	{
		// Delete the first element and re-adjust head pointer (Bunny_Colony) to point to the next element
		delete_first_element();
	}
}

Bunny* find_element(unsigned int val)
{
	Bunny *b=Bunny_Colony;
	while(b != NULL)
	{
		if (b->id == val)
		{
			return b;
		}
		b=b->next_bunny;
	}

	return NULL;
}


void prob10_1(int argc, char** argv)
{
	if(argc > 1)
		start_bunny_colony(stoi(argv[1]));
	else
		start_bunny_colony(5);
}

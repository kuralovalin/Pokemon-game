

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define POKEMON_SIZE 10	 //There is 10 pokemons always, so I defined it for more comfortable using in arrays 
	//Enums
typedef enum {
    quadratic, linear
} attack_type;
typedef enum {
	Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby
}pokemon;

	//Functions with given prototypes
void menu();
void pokedex(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[]);
void oaks_laboratory(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons);
void show_Pokemons(char Pokemon_name[][11], pokemon Pokemons[], int pokemon_count);
void catch_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_pocket);
void release_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_pocket);
void battle(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]);
void show_area (char Pokemon_name[][11],int area[8][8],int pokemon_staminas_view[8][8]);

	//helper functions
void Oaks_menu();
void explain_rules();

int main(){
	menu();
	srand(time(NULL));
	return 0;
}
//MENU FUNCTION with the help of switch cases
void menu(){
	int i;
char Pokemon_name[POKEMON_SIZE][11]={"Charmander","Pikachu","Squirtle","Bulbasaur","Pidgeotto","Ratata","Mug","Caterpie","Zubat","Krabby"};
int range[10]={1, 3, 4, 3, 2, 2, 1, 2, 3, 2};
int attack_power[10]={500, 350, 300, 400, 250, 250, 350, 200, 350, 300};
int stamina[10]={2200, 1500, 1700, 2500, 1900, 2500, 3000, 1200, 1250, 2600};
attack_type type[10]={quadratic, linear, linear, linear, quadratic, linear, quadratic, quadratic, linear, linear};
pokemon Pokemons[10]={Charmander, Pikachu, Squirtle, Bulbasaur, Pidgeotto, Ratata, Mug, Caterpie, Zubat, Krabby};
pokemon my_Pokemons[4];
pokemon my_pocket[4];
pokemon user_Pokemons[4];	//It is the same as my pocket, cause in user_pokemons we have pokemons in pocket of a user
for (i = 0; i < 4; ++i)	//For all elements of an array put -1 for now, so I can check it later
{
	my_pocket[i]=-1;
}
	int choice;
	while(choice!=4){
		printf("%s","\e[5;31;47m***** MENU *****\e[0m\n");
		printf("1. Open Pokedex\n");
		printf("2. Go to Oak's Laboratory\n");		
		printf("3. Enter the tournament\n");
		printf("4. Exit\n");

		printf("Please, make your choice:\n");
		printf("\tChoice:");
		scanf("%d", &choice);
		if(choice<=0 || choice>4){
			printf("%s","\e[5;31;47mThis is an invalid choice. Try again!\e[0m\n");
			printf("%s","Please make your choice:\n");
			scanf("%d", &choice);
		}
		switch(choice)
		{
			case 1:
				pokedex(Pokemon_name,range, type, attack_power, stamina);  
			break;
			case 2:
				oaks_laboratory(Pokemon_name, Pokemons, my_pocket);  
			break;
			case 3:
				battle(Pokemon_name, range, type, attack_power, stamina, my_pocket);
			break;
		}
	}
}
	
	//PART 1
void pokedex(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[]){
	char poke_name[11];
	int i, j;
	int status, stop;  //Stop used for finishing my 'for' loop and status used for checking whether we found right word or not.

	//Do While used for controlling whether entered string is an 'exit' or not
	do{
	printf("Type 'exit' to close Pokedex\n");
	printf("Please type name of the Pokemon, use Uppercase character for 1st one:)\n");
	scanf("%s", poke_name);
	stop=0;
	for(i=0; i<10 && stop==0; i++){
		status=0;
		for (j = 0; j < 11 && status==0; j++)
		{
			if(poke_name[j]!=Pokemon_name[i][j] && Pokemon_name[i][j]!='\0'){	//Checking char by char, difference of letters in the word, if they are the same status will be zero
				status=1;
			}
		}
		if(status == 0){	//If letters are same, that means we found the pokemon we needed. So we can print all specifications of this pokemon.
			stop=1;
			printf("Name     : %s\n", poke_name);
			if(type[i]==0){		//It is an enum value, so I am checking here if it is zero then type is quadratic
			printf("A type   : Quadratic\n");
			}
			else if(type[i]==1){	//If one type is Linear
				printf("A type    : Linear\n");
			}
			printf("Range     : %d block\n", range[i]);
			printf("A. Power  : %d\n", attack_power[i]);
			printf("Stamina   : %d\n", stamina[i]);
		}
		else if(status == 1 && i == 9 && (poke_name[0]!='e' && poke_name[1]!='x' && poke_name[2]!='i' && poke_name[3]!='t')){
			stop=1;
			printf("%s","\e[5;31;47mYou entered an invalid name of a pokemon! Please try again\e[0m\n");	//This else if used for preventing an invalid input from the user
		}
	}
	}while(poke_name[0]!='e' && poke_name[1]!='x' && poke_name[2]!='i' && poke_name[3]!='t');	//If exit entered, then go back to the menu	
}

	//Part 2
void oaks_laboratory(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_Pokemons){
	int choice_Oak;
	int pokemon_count=0;
	while(choice_Oak!=5){	//If choice is 5, we will go back to main menu
	Oaks_menu();
	printf("Please, make your choice:");
	scanf("%d", &choice_Oak);
	
		if(choice_Oak<=0 || choice_Oak>5){	//For preventing invalid inputs from the user
			printf("%s","\e[5;31;47mThis is an invalid choice. Try again!\e[0m\n");
			printf("%s","Please make your choice between 1 and 5:\n");
			scanf("%d", &choice_Oak);
		}
		switch(choice_Oak)
		{
			case 1:
				printf("\tHere is the list of our pokemons!\n");	//Firstly it will print all pokemons with defined size 10
				show_Pokemons(Pokemon_name, Pokemons, POKEMON_SIZE);
			break;
			case 2:	
				printf("\tHere is the list of our pokemons!\n");		
				show_Pokemons(Pokemon_name, Pokemons, POKEMON_SIZE);	//Printing original list with size 10
				
				catch_a_pokemon(Pokemon_name, Pokemons, my_Pokemons); 
			break;
			case 3:
				printf("\tPokemons you have in your pocket\n");	//After releasing it will print based on to released pokemons 
				show_Pokemons(Pokemon_name, my_Pokemons, 4);

				release_a_pokemon(Pokemon_name, Pokemons, my_Pokemons);
			break;
			case 4:
				printf("\tPokemons you have in your pocket\n");	//Then size will be 4 because it's max size of our pocket
				show_Pokemons(Pokemon_name ,my_Pokemons, 4);
			break;
		}
	}
}
void Oaks_menu(){	//Made this function just for the good look and more understandable coding
	printf("%s","\e[5;31;47mWelcome to Laboratory of Professor Oak. How can I help you?\e[0m\n");
	printf("1) Show Pokemons\n");
	printf("2) Catch a Pokemon\n");		
	printf("3) Release a Pokemon\n");
	printf("4) Show my pocket\n");
	printf("5) Back\n");
}

void show_Pokemons(char Pokemon_name[][11], pokemon Pokemons[], int pokemon_count){
	int i, j;
	int index;
	int minus=-1;
	for (i = 0; i < pokemon_count; ++i)	//pokemon_count controlls how many times loop will continue
	{		
		index=(int)Pokemons[i];	//If pokemon in my pocket is still -1 that means there is no any pokemon yet, so 'if' condition will not be true
		if(index!=minus){	//If index is not -1 that means there is a pokemon inside so let's print ID and etc
			printf("%d - ", i);

			for(j=0; j<11 && Pokemon_name[index][j]!='\0'; j++){	//Char by char ptinting pokemon's name till the end of a line(word)
				printf("%c",Pokemon_name[index][j]);
			}
			printf("\n");
		}		
	}
}
void catch_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_pocket){
	int catched_pokemon;
	int i;
	int k=-1;
	int count=0, status=0, index=-1;	//Used for making controlls as below:	
	pokemon user_Pokemons[4];	

 		for (i = 0; i < 4; i++)  // check is array full or not
 		{
 			if(my_pocket[i]!=k){	//if there is smth inside of an array, then count++
 				count++;
 			}
 		}
 		if(count == 4){	//If num of count is 4 then it means that our pocket is full
 			printf("  Your pocket is full! Please Release a pokemon for catching!\n");
 		}
 		else{
 			printf("\tChoice:");
 			scanf("%d", &catched_pokemon);
 			if(catched_pokemon<0 || catched_pokemon>9){	//If user's input is incprrect at all!
 				printf("Your input is invalid!!! Please catch a pokemon according to it's ID!\n\n");
 			}
 			else{
		 		for (i = 0; i < 4; i++)
		 		{
		 			if(my_pocket[i]==catched_pokemon){  //For controlling not choose 2 same pokemons
		 				status=1;
		 			}
		 			if(my_pocket[i]==k && status==0 && index==k){	//If in my pocket there is anything(no pokemon)
		 				index=i;	//If status did not change, which means not the same pokemon and index is same we can change our index to 'i' and put a pokemon inside
		 			}
		 		}
		 		if(status==1){
		 			printf("You catched this pokemon already! Catch another one!\n");
		 		}
		 		if(status==0 && index!=k){	
		 			my_pocket[index]=catched_pokemon;
		 		}
	 		}
 		}		
}

void release_a_pokemon(char Pokemon_name[][11], pokemon Pokemons[], pokemon *my_pocket){
 int released_pokemon, i;
 int k=-1; 	//In order to check, if user want to release a pokemon, but for now did not catch anything 

if(my_pocket[0]==k && my_pocket[1]==k && my_pocket[2]==k && my_pocket[3]==k){
   printf("You did't catch any pokemon yet! Please catch first:)\n"); 
}
else{
	printf("    Please enter ID of a pokemon you want to release: ");
	scanf("%d", &released_pokemon);
		if(released_pokemon<0 || released_pokemon>3){	//Just for controlling whether right number was typed from user side
			printf("%s","You entered an \e[5;31;47minvalid ID\e[0m of a pokemon! Please try again\n\n");
		}
		else{
			for(i=0; i<=3; i++){	//I made a simple 'for' loop for controlling released pokemon, and changing my_pocket's value to -1 again  
				if(i==released_pokemon){
					my_pocket[i]=-1;	//'-1' according to my algorithm means nothing inside of an array or array is NULL 
				}
			}
		}
 	}
}

	//Part 3
void battle(char Pokemon_name[][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]){
	int minus=-1, i, j, b;	//b used for taking 4 randoms for AI pokemons
	int n, m;	//For filling an array in the beginning with -1's
	int x, y;	//For locating pokemons and taking X and Y components
	int area[8][8];	//positions of the current pokemons
	int pokemon_staminas_view[8][8];	//current staminas
	pokemon Ai_pokemons[4];
	int k=0;

//If all elements of my pocket is not -1 that means we have pokemons inside and can start the tournament
if(user_Pokemons[0]!=minus && user_Pokemons[1]!=minus && user_Pokemons[2]!=minus && user_Pokemons[3]!=minus){
	for(m=0; m<8; m++){		//Initializing -1 to all elements of an array for making a control
		for(n=0; n<8; n++){
			area[m][n]=-1;
		}
	}
	for(b=0; b<4; b++){		//Making this for loop for taking 4 random pokemons for AI
		Ai_pokemons[b] = rand()%10;	//Now we have 4 random numbers in our AI array
	}

	explain_rules();
	
	//For locating user's pokemons!
	while(k<4){
		printf(" Enter Y and X components for your %s pokemon\n", Pokemon_name[user_Pokemons[k]]);
	    scanf("%d %d", &y, &x);	//Here Y-is lenght and X-is width, I made it according to y&x Coordinate system
	  	if(y>8 || y<1 || x>8 || x<1){ //main control of wrong inputs
	  		printf("  Please enter a valid value for X and Y components between 1 and 8\n");
		}		
		else{		
		  	if(y!=1 && y!=2){
					//According to rules user can locate pokemons only here in the beginning of a game
			  		printf("  You can locate your pokemons only to the first 2 rows!\n");
			}
			else if(y==1 || y==2){	//if it's first 2 rows then we can start locating 
			  	if(area[y-1][x-1]!=-1){	//If it's not a -1 then there is something already so we should control it
			  		printf("  You already located a pokemon here! Choose another location\n");
			  	}
			  	else{
				  	area[y-1][x-1]=user_Pokemons[k];
					k++;
				}
			}
		}	
	}
	//For locating AI's pokemons randomly
	k=0;	
	while(k<4){
		y = (7+rand() % 2);	//for 'y' component rand nums should be either 1 or 2
		x= (1+rand() % 8); //random num between 1 and 8	    
			if(area[y-1][x-1]==-1){	  		
				area[y-1][x-1]=Ai_pokemons[k];
				k++;			  		
			}
			else{
				printf("\n");
			}
	}		

//For filling an array of staminas:)

for(m=0; m<8; m++){		
	for(n=0; n<8; n++){
		if(area[m][n]!=-1){
		pokemon_staminas_view[m][n]=stamina[area[m][n]];	
		//printf("%d\n", pokemon_staminas_view[m][n]);	//Made just for controlling staminas, is it working correct or not
		}
	}
}

show_area (Pokemon_name, area, pokemon_staminas_view);
}

	else{
		printf("%s","\e[5;31;47mPlease catch 4 pokemons before entering the tournament!\e[0m\n\n");
	}
}

void explain_rules(){	//Made this function just for explaining rules of location
	  printf("%s","\e[5;31;47m   Welcome to tournament!\e[0m\n");
	  printf(" Your arena is a Quadrat 8x8 lenght and width\n");
	  printf(" Locate your 4 pokemons to first 2 rows please\n");
	  printf(" Treat Y-as lenght and X-as width of your area:)\n");
	 
}

void show_area (char Pokemon_name[][11],int area[8][8],int pokemon_staminas_view[8][8]){
	int m, n;
	int i, j, z;
//According to my algorithm there will be 3 'for' loops
	for(m=0; m<8; m++){		
		for(z=0; z<2; z++){		//This one for making strings double in other words to put two | and for more space  
			for(n=0; n<8; n++){
				if(z==0){	//IF we are in the first line, that means: we need to put a name of a pokemon(3 chars)
					if(area[m][n]==-1){	//If element of a double array is empty than print just space
		 				printf("|         ");
					}					
					else {	//Here I'am checking which pokemon is in my area and printing 3 characters of this pokemon
						printf("|");
						for(i=0; i<10; i++){	
							if(i==area[m][n]){	
								printf("   ");	//I need spaces from both sides when I print name of a pokemon
								for(j=0; j<3; j++){	//Printing pokemon's name until three, cause Pikachu and Pidgeotto are the same
									printf("%c",Pokemon_name[i][j]);
								}
							printf("   ");	
							}							
						}
					}	//If it is a last line that just put a '|''
					if(n==7){
						printf("|");
					}
				}
				//IF Z==1, we need to do everything one more time and this time we have to print not names, but staminas of pokemons
				else{
					if(area[m][n]==-1){
		 				printf("|         ");
					}					
					else {
						printf("|");
						for(i=0; i<10; i++){	
							if(i==area[m][n]){	
								printf("  ");
								printf("%d",pokemon_staminas_view[m][n]);	//Everything is the same, but here staminas instead of names								
								printf("   ");
							}							
						}
					}
					if(n==7){
						printf("|");
					}
				}
			}		
			printf("\n");
		}
			//Here, I made a small 'for' loop for printing '---' line According to my calculations, it should go until 81
			for(i=0; i<81; i++){
				printf("-");
			}
			printf("\n");
	}
}



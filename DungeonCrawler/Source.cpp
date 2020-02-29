#include <iostream>//this library is for cout and cin
#include <cstdlib>//this library is for the random function
#include <string>//this library lets you use strings
#include <ctime>//lets the computer perform random functions, without it, the random function would not be as random
#include <vector>//lets me store the items in a master list and the players inventory

//namespace gets rid of adding 'std::' as part of cout and cin
using namespace std;

//PROTOTYPE FUNCTIONS
void Introduction();

string GetUserName();
int addPlayerStat(string stat, int arr[]);
void getStats(int& Strength, int& Dexterity, int& Constitution, int& Intelligence, int& Wisdom, int& Charisma);
int getPlayerHealth(int mod);
int rollDice(int numOfDice, int numOfSides, int modifier, bool playerStats);


//this data type is to categorize different items
enum itemType
{
	Armor,
	Potion,
	Ring,
	Weapon,
	Misc_Item
};


//this class creates all of the items the game will use
struct Item
{
	//id
	//name
	//flavor text
	//type
	//cost
	//weight
	//properties
	//requirement
	int id;
	string name;
	itemType type;
	string flavor_text;
	int cost;
	int weight;
	string property;
	int requirement_level;
	int effect;

	Item(int Id, string Name, itemType Type, string Flavor_text, int Cost, int Weight, string Property, int Requirement, int Effect)
	{
		id = Id;
		name = Name;
		type = Type;
		flavor_text = Flavor_text;
		cost = Cost;
		weight = Weight;
		property = Property;
		requirement_level = Requirement;
		effect = Effect;
	}
};

//this class holds all of the player information like stats health and items
class Player
{
	public:

	//the amount of money your character has
	int Money = 0;

	//name
	string UserName;
	
	//stats
	int Strength;
	int Dexterity;
	int Constitution;
	int Intelligence;
	int Wisdom;
	int Charisma;
	
	//modifiers
	int StrMod;
	int DexMod;
	int ConMod;
	int IntMod;
	int WisMod;
	int ChaMod;
	
	//health
	int Health;

	//this is the constructor that builds the player
	Player()
	{
		//gets player name
		UserName = GetUserName();
		
		//gets the stats for the player
		cout << "\nRoll for your stats! ";
		system("pause");
		getStats(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma);
		StrMod = (Strength - 10) / 2;
		DexMod = (Dexterity - 10) / 2;
		ConMod = (Constitution - 10) / 2;
		IntMod = (Intelligence - 10) / 2;
		WisMod = (Wisdom - 10) / 2;
		ChaMod = (Charisma - 10) / 2;
		
		//gets player's health
		cout << "\nStarting at first level, you start with a base 10HP + your constitution modifier\n";
		Health = 10 + ConMod;

		

		
		cout << "\nName: " << UserName;
		cout << "\nStrength: " << Strength << " and StrMod: " << StrMod;
		cout << "\nDexterity: " << Dexterity << " and DexMod: " << DexMod;
		cout << "\nConstitution: " << Constitution << " and ConMod: " << ConMod;
		cout << "\nIntelligence: " << Intelligence << " and IntMod: " << IntMod;
		cout << "\nWisdom: " << Wisdom << " and WisMod: " << WisMod;
		cout << "\nCharisma: " << Charisma << "and ChaMod: " << ChaMod;
		cout << "\nPlayer Health: " << Health;
		cout << "\nPlayer Money: $" << Money;
		
	}
};

//Item playerSword(0, "Sword", Weapon, "Simple Sword", 10, 20, "OneHanded", 1, 5);

//prototype functions for vector
vector<Item> createItems();

//this is the main function where everything gets run here first
int main()
{
	//this lets rolls be randomized
	srand(static_cast<unsigned int>(time(nullptr)));

	cout << "\n\n\t\tWELCOME TO DUNGEON CRAWLER\n\n";
	
	//this creates a new instance of the player class
	Player player;
	vector<Item> Items = createItems();
	cout << Items[0].name;
	
	return 0;
}

//introduction dialog
void Introduction()
{
	cout << "Welcome player!";
}

vector<Item> createItems()
{
	vector<Item> items;
	//weapons
	Item ShortSword(0, "Short Sword", Weapon, "A basic sword that measures 1 - 1.5ft in length", 10, 10, "OneHanded", 1, 1);
	Item Club(1, "Club", Weapon, "A blunt object that can be swung with force", 2, 5, "OneHanded", 1, 1);
	Item Axe(2, "Axe", Weapon, "A long wooden handler with a sharp blade on the end used for chopping", 8, 10, "OneHanded", 2, 1);
	Item LongSword(3, "Longsword", Weapon, "Longer than a shortsword, this weapon can cause more damage while being OneHanded", 15, 15, "OneHanded", 2, 1);
	Item GreatClub(4, "Greatclub", Weapon, "This great club is an upgrade from a regular club in both size and damage.", 5, 10, "OneHanded", 2, 1);
	Item BattleAxe(5, "Battleaxe", Weapon, "Used in battle, this weapon has a deadly force behind it when used", 20, 15, "TwoHanded", 3, 1);
	Item Rapier(6, "Rapier", Weapon, "This light weapon is used for quick and consistent attacks to weaken your enemy", 20, 5, "OneHanded", 3, 1);
	Item Warhammer(7, "Warhammer", Weapon, "This weapon is extermely heavy and used for doing lots of damage in one hit.", 25, 25, "TwoHanded", 3, 1);
	Item Glaive(8, "Glaive", Weapon, "A pole arm that is a large knife mounted to a pole.", 30, 20, "TwoHanded", 4, 1);
	Item GreatAxe(9, "Greataxe", Weapon, "The largest member of axes. It requires two hands to wield.", 30, 25, "TwoHanded", 4, 1);
	Item GreatSword(10, "Greatsword", Weapon, "The largest member of swords. It requires two hands to wield.", 50, 20, "TwoHanded", 4, 1);
	//armor
	Item LeatherArmor(11, "Leather Armor", Armor, "Armor made from stiff leather", 10, 10, "Light", 1, 11);
	Item PaddedArmor(12, "Padded Armor", Armor, "Armor made from regular clothes padded together", 5, 10, "Light", 1, 11);
	Item StuddedArmor(13, "Studded Leather Armor", Armor, "Armor made from stiff leather but reinforced with rivets", 45, 15, "Light", 1, 12);
	Item ChainShirt(14, "Chain Shirt", Armor, "made of small interlocking metal rings, the chain shirt gives decent protection", 50, 20, "Medium", 2, 13);
	Item Breastplate(15, "Breastplate", Armor, "made of fitted metal with leather, it leaves the arms and legs unprotected but good protection around the vital organs", 100, 25, "Medium", 2, 14);
	Item HalfPlate(16, "Half Plate", Armor, "consists of shaped metal plates the cover most of the wearer's body", 150, 40, "Medium", 2, 15);
	Item ChainMail(17, "Chain Mail", Armor, "Made of interlocking rings and includes a layer of quilted fabric to prevent chafing", 75, 55, "Heavy", 3, 16);
	Item Splint(18, "Splint", Armor, "Armor made from vertical strips of metal with flexible chain mail to protect the joints", 200, 60, "Heavy", 3, 17);
	Item Plate(19, "Plate", Armor, "Armor made from interlocking metal that covers the entire body", 10, 10, "null", 4, 18);
	Item Shield(20, "Shield", Armor, "it's a shield", 10, 10, "Light", 2, 2);
	//potions 
	Item SmallHealthPotion(21, "Small Health Potion", Potion, "S small potion that restores some HP", 10, 2, "Health", 1, 5);
	Item MediumHealthPotion(22, "Medium Health Potion", Potion, "Restores some HP, more than the small potion", 20, 5, "Health", 1, 10);
	Item LargeHealthPotion(23, "Large Health Potion", Potion, "This large potion restores a lot of HP", 40, 10, "Health", 1, 20);
	Item ACBoostPotion(24, "Potion of Protection", Potion, "Drinking this potion will increase your armor class temporarily", 50, 10, "Buff", 1, 2);
	Item StrengthBuffPotion(25, "Strength Potion", Potion, "Drinking this potion gives you a buff to strength", 50, 10, "Buff", 1, 2);
	Item DexterityBuffPotion(25, "Dexterity Potion", Potion, "Drinking this potion gives you a buff to dexterity", 50, 10, "Buff", 1, 2);
	Item ConstitutionBuffPotion(25, "Constitution Potion", Potion, "Drinking this potion gives you a buff to constitution", 50, 10, "Buff", 1, 2);
	Item IntelligenceBuffPotion(25, "Intelligence Potion", Potion, "Drinking this potion gives you a buff to intelligence", 50, 10, "Buff", 1, 2);
	Item WisdomBuffPotion(25, "Wisdom Potion", Potion, "Drinking this potion gives you a buff to wisdom", 50, 10, "Buff", 1, 2);
	Item CharismaBuffPotion(25, "Charisma Potion", Potion, "Drinking this potion gives you a buff to charisma", 50, 10, "Buff", 1, 2);
	//rings



	return items;
}

//when the player gains a level this function is called to gain more health
//this function takes in the players constitution mod and returns the amount of health it gained
int getPlayerHealth(int mod)
{
	//creates a new variable that calls the roll dice function
	int health = rollDice(2, 10, mod, false);
	//returns the health it gained
	return health;
}

//this function connects to the getstat function and it applies the stat with one of the rolls
//it also returns the stat it added to and takes in the stat it's applying and the array of all your roles
int addPlayerStat(string stat, int arr[])
{
	//creates two variables: one for the players choice to choose which roll to use for the particular stat
	//and the added stat variable which applies the new stat to the stat
	int choice;
	int addStat = 0;

	//this while loop is in case you enter an incorrect index and it will ask you to enter a valid number
	do{
		//this check is for a goto
		//I know I'm suppose to avoid using this but I couldn't think of an easier way
		check:
		cout << stat << ": ";//displays the stat you are applying one of your rolls to
		cin >> choice;//takes in the user's choice for the roll it wants to apply
		choice--;//because the index starts at 0, subtracting one makes it choose the right index
		if (arr[choice] == 0)//this if is to check if the player has already chose that role
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto check;//if it does than this line is called and it gets sent back up to the top of the loop
		}
		addStat = arr[choice];//finally, if everything checks out, then the roll gets added to the stat
		arr[choice] = 0;//the chosen roll gets changed to a 0 signifying that it has been chosen already
	} while (choice < 0 || choice > 6);//this loop will only run while the choice is one of the elements of the array

	//this for loop displays the current array after it's been modified
	for (int i = 0; i < 6; i++) { cout << arr[i] << ", "; }
	cout << "\n\n";
	//returns the new stat that has been added
	return addStat;
}

//this function is called from the player class to get the stats for that character
//the arguments in this function just reference the stats from the player class
void getStats(int &Strength, int &Dexterity, int &Constitution, int &Intelligence, int &Wisdom, int &Charisma)
{
	//create an array to store all of the rolls
	int statID[6];
	//this for loop goes through 6 times and adds the roll to the array
	for (int i = 0; i < 6; i++)
	{
		//calls the function and stores the roll in the current index 
		statID[i] = rollDice(4, 6, 0, true);
	}
	cout << "\nPick which index (starting with 1) you want to put into your stat\n";
	//displays all of your rolls
	for (int i = 0; i < 6; i++) { cout << statID[i] << "  "; }
	cout << "\n\n";

	//calls the function to add the roll to each stat
	Strength = addPlayerStat("Strength", statID);
	Dexterity = addPlayerStat("Dexterity", statID);
	Constitution = addPlayerStat("Constitution", statID);
	Intelligence = addPlayerStat("Intelligence", statID);
	Wisdom = addPlayerStat("Wisdom", statID);
	Charisma = addPlayerStat("Charisma", statID);
	
	/*
	 *THIS IS 100 LINES OF CODE I DON'T NEED!!!!!!
	while (strengthChoice < 0 || strengthChoice > 6)
	{
	str:
		cout << "Strength: ";
		cin >> strengthChoice;
		strengthChoice--;
		if (statID[strengthChoice] == 0)
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto str;
		}
		Strength = statID[strengthChoice];
		statID[strengthChoice] = 0;
	}
	for (int i = 0; i < 6; i++) { cout << statID[i] << ", "; }
	cout << "\n\n";

	
	while (dexterityChoice < 0 || dexterityChoice > 6)
	{
	dex:
		cout << "Dexterity: ";
		cin >> dexterityChoice;
		dexterityChoice--;
		if (statID[dexterityChoice] == 0)
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto dex;
		}
		Dexterity = statID[dexterityChoice];
		statID[dexterityChoice] = 0;
	}
	for (int i = 0; i < 6; i++) { cout << statID[i] << ", "; }
	cout << "\n\n";

	while (constitutionChoice < 0 || constitutionChoice > 6)
	{
	con:
		cout << "constitution: ";
		cin >> constitutionChoice;
		constitutionChoice--;
		if (statID[constitutionChoice] == 0)
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto con;
		}
		Constitution = statID[constitutionChoice];
		statID[constitutionChoice] = 0;
	}
	for (int i = 0; i < 6; i++) { cout << statID[i] << ", "; }
	cout << "\n\n";

	while (intelligenceChoice < 0 || intelligenceChoice > 6)
	{
	inte:
		cout << "intelligence: ";
		cin >> intelligenceChoice;
		intelligenceChoice--;
		if (statID[intelligenceChoice] == 0)
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto inte;
		}
		Intelligence = statID[intelligenceChoice];
		statID[intelligenceChoice] = 0;
	}
	for (int i = 0; i < 6; i++) { cout << statID[i] << ", "; }
	cout << "\n\n";

	while (wisdomChoice < 0 || wisdomChoice > 6)
	{
	wis:
		cout << "wisdom: ";
		cin >> wisdomChoice;
		wisdomChoice--;
		if (statID[wisdomChoice] == 0)
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto wis;
		}
		Wisdom = statID[wisdomChoice];
		statID[wisdomChoice] = 0;
	}
	for (int i = 0; i < 6; i++) { cout << statID[i] << ", "; }
	cout << "\n\n";

	while (charismaChoice < 0 || charismaChoice > 6)
	{
	cha:
		cout << "charisma: ";
		cin >> charismaChoice;
		charismaChoice--;
		if (statID[charismaChoice] == 0)
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto cha;
		}
		Charisma = statID[charismaChoice];
		statID[charismaChoice] = 0;
	}
	for (int i = 0; i < 6; i++) { cout << statID[i] << ", "; }
	cout << "\n\n";
	*/
}


//this roll dice function is for all of the roll dicing needs
//it takes in the number of dice, the number of sides for the dice, the modifier,
//and says if this is for player stats or not
int rollDice(int numOfDice, int numOfSides, int modifier, bool playerStats)
{
	
	//these two variables are for the total value, and the current die value
	int total = 0;
	int dieValue = 0;


	//rolling for player stats is special because you roll 4d6 and take the highest 3
	if(playerStats)
	{
		//stores the all 4 roles in an array
		int die[4];
		//these variables store the first second and third highest numbers in the array
		int firstHigh, secondHigh, thirdHigh;
		//initializes the three variables to the lowest value
		firstHigh = secondHigh = thirdHigh = INT_MIN;

		//the for loop rolls 4 dice
		for(int i = 0; i < numOfDice; i++)
		{
			cout << "to roll, ";
			system("pause");
			//this gets the value of the die and stores it into the array
			die[i] = (rand() % numOfSides) + 1;

			//it then checks to see if it is the highest, the second highest, or the third highest
			if(die[i] > firstHigh)
			{
				thirdHigh = secondHigh;
				secondHigh = firstHigh;
				firstHigh = die[i];
			}else if(die[i] > secondHigh)
			{
				thirdHigh = secondHigh;
				secondHigh = die[i];
			}else if(die[i] > thirdHigh)
			{
				thirdHigh = die[i];
			}
		}

		//after all 4 rolls are made, it adds them to the total value
		total = firstHigh + secondHigh + thirdHigh;
		//displays the total
		cout << "\nYou Rolled a total of " << total;
		
	}else//if it's not a regular roll
	{
		//it loops the amount of time there are number of dice
		for (int i = 0; i < numOfDice; i++)
		{
			cout << "to roll, ";
			system("pause");
			//this gets the value of the die
			dieValue = (rand() % numOfSides) + 1;
			cout << " * You rolled a " << dieValue << "! * \n\n";
			total += dieValue;//it adds the die value to the current total value
		}
	}

	//lastly, it adds the modifier to the total variable
	total += modifier;

	//it then returns the total
	return total;
}

//gets the username for the player
string GetUserName()
{
	//declares a string
	string UserName;
	cout << "Enter your character name :>";
	//getline is an input for the characters name
	getline(cin, UserName);
	//returns the user name
	return UserName;
}


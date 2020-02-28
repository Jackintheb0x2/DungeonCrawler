#include <iostream>//this library is for cout and cin
#include <cstdlib>//this library is for the random function
#include <string>//this library lets you use strings
#include <ctime>

//namespace gets rid of adding 'std::' as part of cout and cin
using namespace std;


//PROTOTYPE FUNCTIONS
void Introduction();
string GetUserName();
int addPlayerStat(string stat, int arr[]);
void getStats(int &Strength, int &Dexterity, int &Constitution, int &Intelligence, int &Wisdom, int &Charisma);
int rollDice(int numOfDice, int numOfSides, int modifier, bool playerStats);


class Player
{
	public:

	//stats
	int Strength;
	int Dexterity;
	int Constitution;
	int Intelligence;
	int Wisdom;
	int Charisma;

	/*
	//modifiers
	int StrMod;
	int DexMod;
	int ConMod;
	int IntMod;
	int WisMod;
	int ChaMod;
	*/
	
	Player()
	{
		getStats(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma);
	}
};

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	bool gameRunning = true;

	cout << "\n\n\t\tWELCOME TO DUNGEON CRAWLER\n\n";
	string const UserName = GetUserName();

	Player player;
	
	do
	{

	} while (gameRunning);
	
	return 0;
}

void Introduction()
{
	cout << "Welcome player!";
}

int addPlayerStat(string stat, int arr[])
{
	int choice;
	int addStat = 0;
	
	do{
		check:
		cout << stat << ": ";
		cin >> choice;
		choice--;
		if (arr[choice] == 0)
		{
			cout << "\nThis stat has already been used pick another one!\n";
			goto check;
		}
		addStat = arr[choice];
		arr[choice] = 0;
	} while (choice < 0 || choice > 6);
	
	for (int i = 0; i < 6; i++) { cout << arr[i] << ", "; }
	cout << "\n\n";
	return addStat;
}

void getStats(int &Strength, int &Dexterity, int &Constitution, int &Intelligence, int &Wisdom, int &Charisma)
{
	int statID[6];
	int strengthChoice, dexterityChoice, constitutionChoice, intelligenceChoice, wisdomChoice, charismaChoice;
	for (int i = 0; i < 6; i++)
	{
		statID[i] = rollDice(4, 6, 0, true);
	}
	cout << "\nPick which index (starting with 1) you want to put into your stat\n";
	for (int i = 0; i < 6; i++) { cout << statID[i] << ", "; }
	cout << "\n\n";

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



int rollDice(int numOfDice, int numOfSides, int modifier, bool playerStats)
{
	
	
	int total = 0;
	int dieValue = 0;


	//rolling for player stats is special because you roll 4d6 and take the highest 3
	if(playerStats)
	{
		int die[4];
		int firstHigh, secondHigh, thirdHigh;
		firstHigh = secondHigh = thirdHigh = INT_MIN;
		
		for(int i = 0; i < numOfDice; i++)
		{
			die[i] = (rand() % numOfSides) + 1;

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

		total = firstHigh + secondHigh + thirdHigh;
		cout << "\nYou Rolled a " << total;
		
	}else
	{
		for (int i = 0; i < numOfDice; i++)
		{
			cout << "to roll, ";
			system("pause");
			dieValue = (rand() % numOfSides) + 1;
			cout << " * You rolled a " << dieValue << "! * \n\n";
			total += dieValue;
		}
	}

	total += modifier;
	
	return total;
}

string GetUserName()
{
	string UserName;
	cout << "Enter your character name :>";
	getline(cin, UserName);
	return UserName;
}

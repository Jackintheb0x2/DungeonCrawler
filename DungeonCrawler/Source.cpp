#include <iostream>//this library is for cout and cin
#include <cstdlib>//this library is for the random function
#include <string>//this library lets you use strings
#include <ctime>//lets the computer perform random functions, without it, the random function would not be as random
#include <vector>//lets me store the items in a master list and the players inventory

//namespace gets rid of adding 'std::' as part of cout and cin
using namespace std;

//PROTOTYPE FUNCTIONS
void Introduction();//just dialog explaining the game

int Decision(vector<string> decision);//enter a string of different options and will print out a menu
string GetUserName();//gets the username
int addPlayerStat(string stat, int arr[]);//adds the rolled stat to the player
void getStats(int& Strength, int& Dexterity, int& Constitution, int& Intelligence, int& Wisdom, int& Charisma);//this gets the stats of the player
int getPlayerHealth(int mod);//this gets the player health
int rollDice(int numOfDice, int numOfSides, int modifier, bool playerStats);//this rolls a certain number of dice


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

	//creates a constructor of the class so everytime it is called, it creates a new item with its own set of properties
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

	//armor class is the chance you can evade incoming attacks
	int ac = 0;
	
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

	//player inventory
	vector<Item> PlayerInventory;
	int carrying_capacity = 20;

	//this is the constructor that builds the player
	Player()
	{
		//gets player name
		UserName = GetUserName();
		
		//gets the stats for the player
		cout << "\nRoll for your stats! ";
		system("pause");
		getStats(Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma);
		//calculates the modifier per stat
		StrMod = (Strength - 10) / 2;
		DexMod = (Dexterity - 10) / 2;
		ConMod = (Constitution - 10) / 2;
		IntMod = (Intelligence - 10) / 2;
		WisMod = (Wisdom - 10) / 2;
		ChaMod = (Charisma - 10) / 2;
		
		//gets player's health
		cout << "\nStarting at first level, you start with a base 10HP + your constitution modifier\n";
		Health = 10 + ConMod;

		ac = 10 + DexMod;

		//roll for how much money you start off with
		cout << "\nNow you are going to roll 4d4 to see how much money you start with\n";
		Money = rollDice(5, 4, 0, false);
		Money *= 10;

		
		
	}
	//adds item to player inventory
	void addItem(Item& inventoryItem)
	{
		PlayerInventory.push_back(inventoryItem);
	}
	//deletes item from player inventory
	void deleteItem(Item& inventoryItem)
	{
		auto i = PlayerInventory.begin();//starts at the beginning of the index of the player inventory
		do
		{
			++i;
		} while (inventoryItem.name != i->name && i != PlayerInventory.end());//it keeps looping until it finds the item or until it makes it to the end of the array
		if (i != PlayerInventory.end()) {
			PlayerInventory.erase(i);
		}else
		{
			cout << "\nCould not find the item you were looking for!";
		}
	}

	void showItem(Item& inventoryItem)
	{
		cout << "\n\n----------------------------------\n";
		cout << inventoryItem.name;
		cout << "\nType: " << inventoryItem.type;
		cout << "\nDescription: " << inventoryItem.flavor_text;
		cout << "\nCost: " << inventoryItem.cost;
		cout << "\nWeight: " << inventoryItem.weight;
		cout << "\nProperty: " << inventoryItem.property;
		cout << "\nRequired Level: lvl " << inventoryItem.requirement_level;
		switch(inventoryItem.type)
		{
		case Weapon:
			cout << "\nDamage: 1d" << inventoryItem.effect;
			break;
		case Armor:
			cout << "\nArmor: +" << inventoryItem.effect;
			break;
		case Potion:
			cout << "\nPotion: +" << inventoryItem.effect;
			break;
		case Ring:
			cout << "\nRing: +" << inventoryItem.effect;
			break;
		case Misc_Item:
			cout << "\n+" << inventoryItem.effect << " Carrying Capacity";
			break;
		}
		cout << "\n----------------------------------";
	}
	
	int searchPlayerItem(string name)
	{
		//goes through a while loop to check if the name argument matches the item name
		int id = 0;
		do
		{
			++id;
		} while (name != PlayerInventory[id].name);

		//if there is a match, it returns the id from the inventory vector
		if(name == PlayerInventory[id].name)
		{
			return id;
		}//else it returns a -1 which will be used to see if it came back false and -1 is impossible to return from a vector

		return -1;
		
		
	}
	
	void displayInventory()
	{
		cout << "\n\n";
		int id = 0;//this stores the id of each item
		int NameSize = 0;//these two variables organize the store to make it look nice
		int format = 0;
		cout << "\nPLAYER INVENTORY\n";
		cout << "-----------------------------------------------------------------------------------------------------------\n";
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				//this first part lists the name
				//20 characters
				NameSize = PlayerInventory[id].name.size();
				format = 21 - NameSize;
				cout << PlayerInventory[id].name;
				for (int space = 0; space < format; space++)
				{
					cout << " ";
				}
				//this part list the costs
				cout << " | Cost: " << PlayerInventory[id].cost;
				format = 5 - to_string(PlayerInventory[id].cost).size();
				for (int space = 0; space < format; space++)
				{
					cout << " ";
				}
				//this part lists the weight
				cout << " | Weight: " << PlayerInventory[id].weight;
				format = 5 - to_string(PlayerInventory[id].weight).size();
				for (int space = 0; space < format; space++)
				{
					cout << " ";
				}
				cout << " | ";
				//increases the id to keep track of the item listed
				id++;
			}
			cout << "\n";
		}
		cout << "-----------------------------------------------------------------------------------------------------------\n";
		cout << "\n\n";
	}
};

//created prototype of master item list
vector<Item> createItems();
void Store(vector<Item>& list);
void PlayerStats(Player& player);
void Commands(string command, Player& player, vector<Item>& list, bool store);
int SearchStoreItem(vector<Item>& StoreItem, string ItemName);
//this is the main function where everything gets run here first

//the only global variable
bool GameRunning = true;

int main()
{
	//all of the variables
	bool storeEnabled = true;
	//this lets rolls be randomized
	srand(static_cast<unsigned int>(time(nullptr)));

	cout << "\n\n\t\tWELCOME TO DUNGEON CRAWLER\n\n";

	Introduction();
	//this creates a new instance of the player class
	Player player;
	PlayerStats(player);
	
	
	vector<Item> Items = createItems();
	string answer;
	do
	{
		getline(cin, answer);
		if (answer.find('/') == 0)
		{
			Commands(answer, player, Items, storeEnabled);
		}
	} while (GameRunning);
	
	//Store(Items);
	//cout << Items[0].name;
	
	return 0;
}

//introduction dialog
void Introduction()
{
	cout << "Welcome player!\nThis is Dungeon Crawler, a text-based \ninteractive story game where you \ntry to defeat a dungeon!\n\n";
	cout << "\n\n Before we begin, we need to create your character!\n";
	system("pause");
}

//this function displays the menu for a number of options
int Decision(vector<string> decision)
{
	int choice = 0;
	cout << "\nMENU:";
	cout << "\n----------\n";
	for(int i = 0; i < decision.size(); i++)//for loop displays each decision
	{
		cout << i+1 << ". " << decision[i] << "\n";
	}
	cout << "\nChoice :>";
	cin >> choice;
	cout << "\n\n";
	return choice;
}

int SearchStoreItem(vector<Item>& StoreItem, string ItemName)
{
	//goes through a while loop to check if the name argument matches the item name
	int id = 0;
	do
	{
		++id;
	} while (ItemName != StoreItem[id].name);

	//if there is a match, it returns the id from the inventory vector
	if (ItemName == StoreItem[id].name)
	{
		return id;
	}//else it returns a -1 which will be used to see if it came back false and -1 is impossible to return from a vector

	return -1;
}

//handles all of the commands
void Commands(string command, Player& player, vector<Item>& StoreItems, bool store)
{
	//displays all of the commands if the command is /help
	if(command == "/help")
	{
		cout << "\nthese are all of the commands you can do\n";
		cout << "/help  | /inventory          | /store\n";
		cout << "/stats | /drop (item name)   | /item (name)\n";
		cout << "/quit  | /buy (in store only)| /sell (in store only)\n";
	}else if(command == "/stats")
	{
		//gets the player stats
		PlayerStats(player);
	}else if(command == "/inventory")
	{
		//gets the player's inventory
		if(player.PlayerInventory.empty())
		{
			cout << "\nYou have no items!\n";
		}else
		{

			player.displayInventory();
		}
		
	}
	else if (command == "/store")
	{
		if(store)
		{
			//displays all of the items you can buy
			Store(StoreItems);
		}else
		{
			cout << "\nThe store command is disabled, you have to be in the store to call this command\n";
		}
		
	}
	//command.find is for if you need to input anything extra like an item
	else if(command.find("/buy") == 0)
	{
		if(store)
		{
			//finds the name of the item you want to drop
			string itemName = command.substr(6, (command.length() - 5));
			int ItemID = SearchStoreItem(StoreItems, itemName);

			
			if (ItemID == -1)
			{
				//did not find the item
				cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
			}else
			{
				//if you have enough money AND you can carry it
				if(player.Money >= StoreItems[ItemID].cost && player.carrying_capacity >= StoreItems[ItemID].weight)
				{
					player.Money -= StoreItems[ItemID].cost;
					player.carrying_capacity -= StoreItems[ItemID].weight;
					player.addItem(StoreItems[ItemID]);
				}else
				{
					cout << "\nYou do not have enough Money and/or Space \nin your inventory. Try buying a bag to \nincrease your carrying capacity.\n";
				}
			}
			
		}else
		{
			cout << "\nThe store command is disabled, you have to be in the store to call this command\n";
		}
	}
	//command.find is for if you need to input anything extra like an item
	else if(command.find("/sell") == 0)
	{
		if (store)
		{
			if (player.PlayerInventory.empty()) {
				cout << "\nYou have no items!\n";
			}
			else
			{
				//finds the name of the item you want to drop
				string itemName = command.substr(6, (command.length() - 5));
				//convert string name to item id
				int id = player.searchPlayerItem(itemName);
				if (id == -1)
				{
					//did not find the item
					cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
				}
				else {
					player.Money += (player.PlayerInventory[id].cost / 2);
					player.carrying_capacity += player.PlayerInventory[id].weight;
					//calls the delete item function in player
					player.deleteItem(player.PlayerInventory[id]);
					
				}
			}
		}
		else
		{
			cout << "\nThe store command is disabled, you have to be in the store to call this command\n";
		}
	}
	//command.find is for if you need to input anything extra like an item
	else if (command.find("/drop") == 0)
	{
		if (player.PlayerInventory.empty()) {
			cout << "\nYou have no items!\n";
		}else
		{
			//finds the name of the item you want to drop
			string itemName = command.substr(6, (command.length() - 5));
			//convert string name to item id
			int id = player.searchPlayerItem(itemName);
			if (id == -1)
			{
				//did not find the item
				cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
			}
			else {
				//calls the delete item function in player
				player.deleteItem(player.PlayerInventory[id]);
			}
		}
	}
	//command.find is for if you need to input anything extra like an item
	else if (command.find("/item") == 0) {
		if (player.PlayerInventory.empty()) {
			cout << "\nYou have no items!\n";
		}else
		{
			string itemName = command.substr(6, (command.length() - 5));
			int id = player.searchPlayerItem(itemName);
			if (id == -1)
			{
				//did not find the item
				cout << "\nCould not find the item you wanted. Try double checking if the name is spelled correctly\n";
			}
			else {
				//calls the delete item function in player
				player.showItem(player.PlayerInventory[id]);
			}
		}
	}else if(command == "/quit")
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		cout << "\nUnrecognized command. Type '/help' to see the list of commands.\n";
	}

}


void PlayerStats(Player& player)
{
	//displays stats
	cout << "\n------------------------------";
	cout << "\nPLAYER STATS:";
	cout << "\nName: " << player.UserName;
	cout << "\nStrength:     " << player.Strength << " | StrMod: " << player.StrMod;
	cout << "\nDexterity:    " << player.Dexterity << " | DexMod: " << player.DexMod;
	cout << "\nConstitution: " << player.Constitution << " | ConMod: " << player.ConMod;
	cout << "\nIntelligence: " << player.Intelligence << " | IntMod: " << player.IntMod;
	cout << "\nWisdom:       " << player.Wisdom << " | WisMod: " << player.WisMod;
	cout << "\nCharisma:     " << player.Charisma << " | ChaMod: " << player.ChaMod;
	cout << "\nPlayer Health: " << player.Health;
	cout << "\nArmor Class: " << player.ac;
	cout << "\nPlayer Money: $" << player.Money;
	cout << "\n------------------------------\n\n";
}

//this function displays all of the items in the game
void Store(vector<Item>& list)
{
	cout << "\n\n";
	int id = 0;//this stores the id of each item
	int NameSize = 0;//these two variables organize the store to make it look nice
	int format = 0;
	cout << "\nSTORE\n";
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	for(int i = 0; i < 19; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			//this first part lists the name
			//20 characters
			NameSize = list[id].name.size();
			format = 21 - NameSize;
			cout << list[id].name;
			for(int space = 0; space < format; space++)
			{
				cout << " ";
			}
			//this part list the costs
			cout << " | Cost: " << list[id].cost;
			format = 5 - to_string(list[id].cost).size();
			for(int space = 0; space < format; space++)
			{
				cout << " ";
			}
			//this part lists the weight
			cout << " | Weight: " << list[id].weight;
			format = 5 - to_string(list[id].weight).size();
			for(int space = 0; space < format; space++)
			{
				cout << " ";
			}
			cout << " | ";
			//increases the id to keep track of the item listed
			id++;
		}
		cout << "\n";
	}
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	cout << "\n\n";
}

vector<Item> createItems()
{
	vector<Item> items;
	//weapons
	Item ShortSword(0, "Short Sword", Weapon, "A basic sword that measures 1 - 1.5ft in length", 10, 10, "OneHanded", 1, 6);
	Item Club(1, "Club", Weapon, "A blunt object that can be swung with force", 2, 5, "OneHanded", 1, 4);
	Item Axe(2, "Axe", Weapon, "A long wooden handler with a sharp blade on the end used for chopping", 8, 10, "OneHanded", 2, 4);
	Item LongSword(3, "Longsword", Weapon, "Longer than a shortsword, this weapon can cause more damage while being OneHanded", 15, 15, "OneHanded", 2, 6);
	Item GreatClub(4, "Great Club", Weapon, "This great club is an upgrade from a regular club in both size and damage.", 5, 10, "OneHanded", 2, 6);
	Item BattleAxe(5, "Battleaxe", Weapon, "Used in battle, this weapon has a deadly force behind it when used", 20, 15, "TwoHanded", 3, 8);
	Item Rapier(6, "Rapier", Weapon, "This light weapon is used for quick and consistent attacks to weaken your enemy", 20, 5, "OneHanded", 3, 8);
	Item Warhammer(7, "Warhammer", Weapon, "This weapon is extermely heavy and used for doing lots of damage in one hit.", 25, 25, "TwoHanded", 3, 10);
	Item Glaive(8, "Glaive", Weapon, "A pole arm that is a large knife mounted to a pole.", 30, 20, "TwoHanded", 4, 10);
	Item GreatAxe(9, "Greataxe", Weapon, "The largest member of axes. It requires two hands to wield.", 30, 25, "TwoHanded", 4, 12);
	Item GreatSword(10, "Greatsword", Weapon, "The largest member of swords. It requires two hands to wield.", 50, 20, "TwoHanded", 4, 12);
	//armor
	Item LeatherArmor(11, "Leather Armor", Armor, "Armor made from stiff leather", 10, 10, "Light", 1, 11);
	Item PaddedArmor(12, "Padded Armor", Armor, "Armor made from regular clothes padded together", 5, 10, "Light", 1, 11);
	Item StuddedArmor(13, "Studded Leather Armor", Armor, "Armor made from stiff leather but reinforced with rivets", 45, 15, "Light", 1, 12);
	Item ChainShirt(14, "Chain Shirt", Armor, "made of small interlocking metal rings, the chain shirt gives decent protection", 50, 20, "Medium", 2, 13);
	Item Breastplate(15, "Breastplate", Armor, "made of fitted metal with leather, it leaves the arms and legs unprotected but good protection around the vital organs", 100, 25, "Medium", 2, 14);
	Item HalfPlate(16, "Half Plate", Armor, "consists of shaped metal plates the cover most of the wearer's body", 150, 40, "Medium", 2, 15);
	Item ChainMail(17, "Chain Mail", Armor, "Made of interlocking rings and includes a layer of quilted fabric to prevent chafing", 75, 55, "Heavy", 3, 16);
	Item Splint(18, "Splint", Armor, "Armor made from vertical strips of metal with flexible chain mail to protect the joints", 200, 60, "Heavy", 3, 17);
	Item Plate(19, "Plate", Armor, "Armor made from interlocking metal that covers the entire body", 10, 10, "Heavy", 4, 18);
	Item Shield(20, "Shield", Armor, "it's a shield", 10, 10, "Light", 2, 2);
	//potions 
	Item SmallHealthPotion(21, "Small Health Potion", Potion, "S small potion that restores some HP", 10, 2, "Health", 1, 5);
	Item MediumHealthPotion(22, "Medium Health Potion", Potion, "Restores some HP, more than the small potion", 20, 5, "Health", 1, 10);
	Item LargeHealthPotion(23, "Large Health Potion", Potion, "This large potion restores a lot of HP", 40, 10, "Health", 1, 20);
	Item ACBoostPotion(24, "Potion of Protection", Potion, "Drinking this potion will increase your armor class temporarily", 50, 10, "Buff", 1, 2);
	Item StrengthBuffPotion(25, "Strength Potion", Potion, "Drinking this potion gives you a buff to strength", 50, 10, "Buff", 1, 2);
	Item DexterityBuffPotion(26, "Dexterity Potion", Potion, "Drinking this potion gives you a buff to dexterity", 50, 10, "Buff", 1, 2);
	Item ConstitutionBuffPotion(27, "Constitution Potion", Potion, "Drinking this potion gives you a buff to constitution", 50, 10, "Buff", 1, 2);
	Item IntelligenceBuffPotion(28, "Intelligence Potion", Potion, "Drinking this potion gives you a buff to intelligence", 50, 10, "Buff", 1, 2);
	Item WisdomBuffPotion(29, "Wisdom Potion", Potion, "Drinking this potion gives you a buff to wisdom", 50, 10, "Buff", 1, 2);
	Item CharismaBuffPotion(30, "Charisma Potion", Potion, "Drinking this potion gives you a buff to charisma", 50, 10, "Buff", 1, 2);
	//rings
	Item RingOfProtection(31, "Ring of Protection", Ring, "This ring grants a bonus to the wearers armor class", 100, 1, "Buff", 3, 1);
	Item RingOfAction(32, "Ring of Free Action", Ring, "This ring grants an extra attack to the wearer", 100, 1, "Buff", 3, 1);
	Item RingOfResistance(33, "Ring of Resistance", Ring, "This ring grants the wearer resistance to any damage (kinda op)", 300, 1, "Buff", 4, 0);
	Item RingOfRegeneration(34, "Ring of Regeneration", Ring, "This ring grants a bonus to the wearer that heals the player 1 hp every 10 turns", 200, 1, "Buff", 3, 1);
	//misc.
	//bags for extra storage
	Item SmallBag(35, "Small Bag", Misc_Item, "This item gives the user 20 extra storage space", 50, 0, "Bag", 1, 20);
	Item MediumBag(36, "Medium Bag", Misc_Item, "This item gives the user 50 extra storage space", 100, 0, "Bag", 2, 50);
	Item LargeBag(37, "Large Bag", Misc_Item, "This item gives the user 100 extra storage space", 200, 0, "Bag", 3, 100);

	//added all items to the master list
	items.push_back(ShortSword);
	items.push_back(Club);
	items.push_back(Axe);
	items.push_back(LongSword);
	items.push_back(GreatClub);
	items.push_back(BattleAxe);
	items.push_back(Rapier);
	items.push_back(Warhammer);
	items.push_back(Glaive);
	items.push_back(GreatAxe);
	items.push_back(GreatSword);
	items.push_back(LeatherArmor);
	items.push_back(PaddedArmor);
	items.push_back(StuddedArmor);
	items.push_back(ChainShirt);
	items.push_back(Breastplate);
	items.push_back(HalfPlate);
	items.push_back(ChainMail);
	items.push_back(Splint);
	items.push_back(Plate);
	items.push_back(Shield);
	items.push_back(SmallHealthPotion);
	items.push_back(MediumHealthPotion);
	items.push_back(LargeHealthPotion);
	items.push_back(ACBoostPotion);
	items.push_back(StrengthBuffPotion);
	items.push_back(DexterityBuffPotion);
	items.push_back(ConstitutionBuffPotion);
	items.push_back(IntelligenceBuffPotion);
	items.push_back(WisdomBuffPotion);
	items.push_back(CharismaBuffPotion);
	items.push_back(RingOfProtection);
	items.push_back(RingOfAction);
	items.push_back(RingOfResistance);
	items.push_back(RingOfRegeneration);
	items.push_back(SmallBag);
	items.push_back(MediumBag);
	items.push_back(LargeBag);

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

		cout << "\nto roll, ";
		system("pause");
		
		//the for loop rolls 4 dice
		for(int i = 0; i < numOfDice; i++)
		{
			
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
			cout << "\nto roll, ";
			system("pause");
			//this gets the value of the die
			dieValue = (rand() % numOfSides) + 1;
			cout << "\n * You rolled a " << dieValue << "! * \n\n";
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


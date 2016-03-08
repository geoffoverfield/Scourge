#pragma warning(disable:4244)
#pragma warning(disable:4129)
#pragma warning(disable:4305)
#pragma warning(disable:4309)

#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <stdlib.h>
#include "TreasureChest.h"
#include "Player.h"
using namespace std;
#define APPTITLE "SCOURGE";

//=================================GLOBAL VARIABLES FOR THE GAME=========================
Player p1;
NPC NPCs[20];
Item Drops[20];
BOSS Boss;
TreasureChest treasure;
HDC global_hdc;
HWND global_hWnd;
HINSTANCE global_instance;

//=================================FORWARD DECLARATIONS FOR FUNCTIONS====================
inline void Line()
{
	for (int i = 0; i < 80; i++)
	{
		cout << char(219);
	}
	cout << endl;
}
void RandDrop();
void InsufficientFunds();
void ValidSelection();
void Buy();
int Intro();
int Select();
void IntroImage();
void Damage();
BOOL InitInstance(HINSTANCE, int);
ATOM MyRegisterClass(HINSTANCE);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
void ImageInit();
void ImageRun();
void ImageEnd();
void DrawBitmap(HDC, char*, int, int);

//========================================BEGIN MAIN=====================================
int main()
{
	int npcCtr = 0;
	string playerName = "";
	char ans[5];
	int z = rand() % 2;
	int y = rand() % 2;
	bool win = false;

	//IntroImage();

	Line();
	cout << endl;
	cout << "Welcome to the ship..." << endl;
	cout << "What's your name sailor?\t";
	cin >> playerName;
	cout << endl;
	p1.name = playerName;
	playerName = "";

	Intro();
	system("pause");
	system("cls");
	Line();
	cout << endl;

	cout << "Now that the pleasantries are out of the way, it's time to get down to buisness..." << endl;
	cout << "If we are to take over this ship, we'll need to do a couple of things:" << endl;
	cout << "We'll have to recruit, train, and get some weapons" << endl;
	cout << "The weapons will be easy enough...  It's the rest that we're worried about!" << endl;
	cout << "Where do you want to start?" << endl;

getAns:
	cout << "Enter 'T' to Train || Enter 'R' to Recruit\nEnter 'B' to Buy more weapons" <<
		"Enter 'F' if you think we're ready to FIGHT!!!" << endl;
	cin >> ans[0];
	ans[0] = toupper(ans[0]);

	while (!win)
	{
		while (ans[0] != 'F')
		{
			cout << endl;
			switch (ans[0])
			{
			case 'T':
				cout << "What would you like to foucs on in your training?" << endl;
				cout << "Enter 'E' for Endurance || Enter 'S' for Strength || " <<
					"Enter 'F' for Fighting Skills" << endl;
				cout << "Make your selection:\t";
				cin >> ans[1];
				ans[1] = toupper(ans[1]);
				cout << endl;
				switch (ans[1])
				{
				case 'E':
					p1.Train(7);
					RandDrop();
					break;
				case 'S':
					p1.Train(5);
					RandDrop();
					break;
				case 'F':
					p1.Train(10);
					RandDrop();
					break;
				}
				break;
			case 'R':
				if (npcCtr < 19)
				{
					p1.Recruit(p1, NPCs[npcCtr]);
					npcCtr++;
				}
				else
					cout << "You have reached your Recruitment Limit" << endl;
				RandDrop();

				break;
			case 'B':
				Buy();
				break;
			default:
				ValidSelection();
			}
			cout << endl;
			system("pause");
			system("cls");
			Line();
			cout << endl;
			cout << "What would you like to do next?" << endl;
			goto getAns;
		}

		//====================================FIRST BOSS FIGHT===============================
		if (ans[0] == 'F')
		{
			system("cls");
			Line();
			cout << endl;
			cout << "So you think it's time, do ya???" << endl;
			cout << "Let's see where we stand...." << endl << endl;
			Line();
			cout << endl;
			p1.getStats();

			//==============================CLEAN UP SCREEN==================================
			system("cls");
			Line();
			cout << endl;
			cout << "Are you sure you wish to continue?..." << endl;
			if (Select() == 2)
				goto getAns;
			else if (Select() == 1)
			{
				system("cls");
				Line();
				cout << endl;
				//=========================BEGIN BOSS FIGHT==================================
				bool playerTurn = true;
				bool bossTurn = false;

			bossFight:
				while (p1.getLife() < 0)
				{
					while (Boss.getLife() < 0)
					{
						if (playerTurn)
						{
							cout << "It's your turn " << p1.name << ".  What would you like to do?" << endl;
							cout << "You can:	Attack<A> || Defend<D> || Run Away<R>" << endl;
							cout << "Please make your selection now:\t";
							cin >> ans[2];
							ans[2] = toupper(ans[2]);
							cout << endl;
							while (ans[2] != 'R')
							{
								switch (ans[2])
								{
								case 'A':
									p1.Attack(p1.getLevel());
									RandDrop();

									//============BOSSES REACTIONS TO PLAYER STRIKES=========
									if (z == 1)
									{
										Boss.defend = true;
										Boss.Defend(Boss.level);
										Damage();
										cout << "The Captain defended against your attack" << endl;
									}
									if (z == 2)
									{
										Boss.attack = true;
										Boss.Attack(Boss.level);
										Damage();
										cout << "The Captain hit you back!!" << endl;
										cout << "You have " << p1.getLife() << " life left." << endl;
									}
									if (Boss.getLife() <= 0)
									{
										cout << "You mortally wound the Captain." << endl;
										cout << "He falls to his knees" << endl;
										cout << "You watch his eyes glaze over" << endl;
										cout << "His gaze shifts to the sky" << endl;
										cout << "He begins to smile..." << endl;
										cout << "You look up to see the gulls circling above" << endl;
										cout << "The clounds drift slowly across the pale blue" << endl;
										cout << "He's right...  It's is a glorious day to die!!" << endl;
										cout << "You thrust your sword through his eye!!!" << endl;
										cout << "The now former Captain doesn't deserve to enjoy this majestic day" << endl;
										cout << "No....." << endl;
										cout << "This day belongs to you!!" << endl << endl;
										cout << "You kick that scum overboard and raise your blade." << endl;
										cout << "The men chear behind you!!" << endl;
										cout << "Congratulations Captain " << p1.name << "!!  The ship is yours!!" << endl;
										win = true;
									}
									else
									{

										//=================SUMMARY AND SCREEN CLEAN UP===========
										cout << "The Captain has " << Boss.getLife() << " life left."
											<< "  Let's see what he does with it!" << endl;
										cout << "It's the Captain's turn now...  Prepare yourself!" << endl;
										system("pause");
										system("cls");
										Line();
										cout << endl;
									}
									break;
								case 'D':
									p1.Defend(p1.getLevel());
									RandDrop();
									cout << "You built up your Defense." << endl << endl;
									p1.getStats();
									//=================SUMMARY AND SCREEN CLEAN UP===========
									system("pause");
									system("cls");
									Line();
									cout << endl;
									break;
								default:
									ValidSelection();
								}
								system("pause");
								system("cls");
								Line();
								cout << endl;

								playerTurn = false;
								bossTurn = false;
								goto bossFight;

							}
						}
						if (bossTurn)
						{
							if (y == 1)
							{
								Boss.Defend(Boss.level);
								cout << "The Captain used his turn to build his defense" << endl;
								cout << "The Captain has " << Boss.getLife() << " life left."
									<< "  Let's see what he does with it!" << endl;
								//=================SUMMARY AND SCREEN CLEAN UP===========
								system("pause");
								system("cls");
								Line();
								cout << endl;
							}
							if (y == 2)
							{
								cout << "The Captain is attacking!!!!" << endl;
								cout << "Would you like to strike him?" << endl;
								if (Select() == 1)
								{
									cout << "You strike him back." << endl;
									p1.attack = true;
									Damage();
									RandDrop();
								}
								else if (Select() == 2)
								{
									cout << "You defended against the Captain's attack" << endl;
									p1.defend = true;
									Damage();
									RandDrop();
								}
								//=================SUMMARY AND SCREEN CLEAN UP===========
								system("pause");
								system("cls");
								Line();
								cout << endl;
							}
							cout << "The Captain tried to strike you down!!" << endl;
							if (p1.getLife() > 0)
							{
								cout << "You prove to be ever resouceful!!" << endl;
								cout << "You have " << p1.getLife() << " life left..."
									<< "Hopefully you make it through the Captain's next turn!" << endl;
							}
							if (p1.getLife() <= 0)
							{
								cout << "The Captain has mortally wounded you..." << endl;
								cout << "Your legs grow weak..." << endl;
								cout << "Your vision grows blurry" << endl;
								cout << "Suddenly you just feel...." << endl;
								cout << "Wet." << endl;
								cout << "In your last moments, you open your eyes "
									<< "just in time to see a shark coming your way...." << endl;
								cout << "The Locker of Davey Jones awaits you!!!" << endl;
								cout << endl << endl << "************GAME OVER!!!************" << endl;
								system("pause");
								system("cls");
							}
							cout << "The Captain has " << Boss.getLife() << " life left."
								<< "  Let's see what he does with it!..." << endl;
							system("pause");
							system("cls");
							Line();
							cout << endl;

							bossTurn = false;
							playerTurn = true;
							goto bossFight;
						}
					}
				}
			}
		}
	}
	win = false;

	system("pause");
	system("cls");
	cout << "****************************************************************************" << endl;
	cout << "***************************TO BE CONTINUED!!!*******************************" << endl;
	cout << "****************************************************************************" << endl;
	
close:
	system("pause");
	return 0;
}

//=========================================FUNCTION DECALARATIONS========================
void RandDrop()
{
	srand(time(NULL));
	bool succ = true;
	int ctr = 0;
	int x = 0;
	int a, d, r;
	const int num = 15;
	int rand1[num][num];
	int rand2[num][num];
	int rand3[num][num];

	if (ctr < 100)
	{
		//======================FILL 2D ARRAYS WITH RANDOM NUMBERS=======================
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				rand1[i][j] = rand() % 70;
				rand2[i][j] = rand() % 70;
				rand3[i][j] = rand() % 70;

			}
		}
		//=====================COMPARE CONTENTS OF 2D ARRAYS=============================
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if (rand1[i][j] == rand2[i][j] || rand1[i][j] == rand3[i][j] || rand2[i][j] == rand3[i][j])
				{
					x = rand() % 20;
					switch (x)
					{
					case 0:
						Drops[x] = Item();
						Drops[x].data = "Cutlass";
						a = 15;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data << 
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 1:
						Drops[x] = Item();
						Drops[x].data = "Dagger";
						a = 5;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 2:
						Drops[x] = Item();
						Drops[x].data = "Rifle";
						a = 30;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 3:
						Drops[x] = Item();
						Drops[x].data = "Shotgun";
						a = 20;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 4:
						Drops[x] = Item();
						Drops[x].data = "Scimitar";
						a = 16;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break; 
					case 5:
						Drops[x] = Item();
						Drops[x].data = "Pistol";
						a = 10;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 6:
						Drops[x] = Item();
						Drops[x].data = "Caltrops";
						a = 5;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found some " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 7:
						Drops[x] = Item();
						Drops[x].data = "Axe";
						a = 17;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found an " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 8:
						Drops[x] = Item();
						Drops[x].data = "Tomahawk";
						a = 12;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 9:
						Drops[x] = Item();
						Drops[x].data = "Hidden Blade";
						a = 40;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 10:
						Drops[x] = Item();
						Drops[x].data = "Grenade";
						a = 80;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 11:
						Drops[x] = Item();
						Drops[x].data = "Gold Coins";
						Drops[x].data2 = 50;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found " << Drops[x].data2 <<
							" " << Drops[x].data << endl;
						p1.gold += Drops[x].data2;
						cout << "You currently have " << p1.gold << " pieces of gold" << endl;
						break;
					case 12:
						Drops[x] = Item();
						Drops[x].data = "A friend!!!";
						Drops[x].data2 = p1.level;
						r = p1.level * 5;
						p1.rep += r;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data << endl << 
							"You gained " << r << " reputation points!"<< endl;
						cout << "Your current Reputation Score is:\t" << p1.rep << endl;
						break;
					case 13:
						Drops[x] = Item();
						Drops[x].data = "Small Pox Blankets";
						a = 35;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found some " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					case 14:
						Drops[x] = Item();
						Drops[x].data = "Gauntlets";
						d = 25;
						Drops[x].data2 = d;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found some " << Drops[x].data <<
							" with " << Drops[x].data2 << " Defense!" << endl;
						p1.defense += d;
						cout << "Your current Defense is at " << p1.defense << "." << endl;
						break;
					case 15:
						Drops[x] = Item();
						Drops[x].data = "Extra Gun Holster";
						d = 5;
						Drops[x].data2 = d;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found an " << Drops[x].data <<
							" with " << Drops[x].data2 << " Defense!" << endl;
						p1.defense += d;
						cout << "Your current Defense is at " << p1.defense << "." << endl;
						break;
					case 16:
						Drops[x] = Item();
						Drops[x].data = "Tricorn Hat";
						d = 25;
						Drops[x].data2 = d;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found a " << Drops[x].data <<
							" with " << Drops[x].data2 << " Defense!" << endl;
						p1.defense += d;
						cout << "Your current Defense is at " << p1.defense << "." << endl;
						break;
					case 17:
						Drops[x] = Item();
						Drops[x].data = "Leather Boots";
						d = 15;
						Drops[x].data2 = d;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found some " << Drops[x].data <<
							" with " << Drops[x].data2 << " Defense!" << endl;
						p1.defense += d;
						cout << "Your current Defense is at " << p1.defense << "." << endl;
						break;
					case 18:
						Drops[x] = Item();
						Drops[x].data = "Skull Bandana";
						d = 7;
						Drops[x].data2 = d;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found an " << Drops[x].data <<
							" with " << Drops[x].data2 << " Defense!" << endl;
						p1.defense += d;
						cout << "Your current Defense is at " << p1.defense << "." << endl;
						break;
					case 19:
						Drops[x] = Item();
						Drops[x].data = "Dual Pistols!!!";
						a = 30;
						Drops[x].data2 = a;
						treasure.ListInsert(ctr, Drops[x], succ);
						cout << "You found an " << Drops[x].data <<
							" with " << Drops[x].data2 << " Attack Damage!" << endl;
						p1.attack += a;
						cout << "Your current Attack is at " << p1.attack << "." << endl;
						break;
					default:
						cout << "========================================================" << endl;
						cout << "=Ooooooppppppssssss!!!  Something went terribly wrong!!=" << endl;
						cout << "===================ARRAY OUT OF BOUNDS==================" << endl;
						cout << "========================================================" << endl;
					}
					return;
				}
			}
		}
		ctr++;
	}
	
}
void InsufficientFunds()
{
	cout << endl << "You do not have enough gold to purchase this item." << endl << endl;
}
void ValidSelection()
{
	cout << endl << "Please make a valid selection...." << endl << endl;
}
void Buy()
{
	bool succ = true;
	int cost[19];
	char buyAns[5];
getGold:
	cout << "You currently have " << p1.gold << " pieces of gold" << endl;
	cout << "Would you like to continue purchasing items?" << endl;
	cout << "Enter 'Y' for Yes || Enter 'N' for No" << endl;
	cin >> buyAns[0];
	buyAns[0] = toupper(buyAns[0]);
	cout << endl;
	if (buyAns[0] == 'Y')
	{
		cout << "What kind of Items would you like to purchase?" << endl;
		cout << "Enter 'W' for Weapons || Enter 'A' for Armor || Enter 'B' to hit the Random Loot Box (15 Gold)" << endl;
		cout << "Please make your selection now:\t";
		cin >> buyAns[1];
		buyAns[1] = toupper(buyAns[1]);
		cout << endl;
		switch (buyAns[1])
		{
		case 'W':
			cout << endl;
			Line();
			cout << endl;
			cout << "Weapons Inventory:" << endl;
			cout << "Cutlass\t\tAttack Damage: 15\t\tCost: $7 gold" << endl;
			cout << "Dagger\t\tAttack Damage: 5\t\tCost: $2 gold" << endl;
			cout << "Rifle\t\tAttack Damage: 30\t\tCost: $15 gold" << endl;
			cout << "Shotgun\t\tAttack Damage: 20\t\tCost: $10 gold" << endl;
			cout << "Pistol\t\tAttack Damage: 10\t\tCost: $5 gold" << endl;
			cout << "Caltrops\t\tAttack Damage: 5\t\tCost: $2 gold" << endl;
			cout << "Axe\t\tAttack Damage: 17\t\tCost: $8 gold" << endl;
			cout << "Tomahawk\t\tAttack Damage: 12\t\tCost: $6 gold" << endl;
			cout << "Hidden Blade\tAttack Damage: 40\t\tCost: $20 gold" << endl;
			cout << "Scimitar\t\tAttack Damage: 16\t\tCost: $8 gold" << endl;
			cout << "Grenade\t\tAttack Damage: 80\t\tCost: $40 gold" << endl;
			cout << "Small Pox Blankets\tAttack Damage: 35\tCost: $17 gold" << endl;
			cout << "Dual Pistols\t\tAttack Damage: 30\t\tCost: $15 gold" << endl;
			cout << "Make your selection now:" << endl;
			cout << "1 for Cutlass     ||  2 for Dagger  || 3 for Rifle  || 4 for Shotgun" << endl;
			cout << "5 for Pistol      || 6 for Caltrops ||   7 for Axe  || 8 for Tomahawk" << endl;
			cout << "9 for Hidden Blade||10 for Scimitar ||11 for Grenade|| 12 for Small Pox Blankets" << endl;
			cout << "13 for Dual Pistols" << endl;
			cin >> buyAns[2];
			cout << endl;
			switch (buyAns[2]);
			{
			case 1:
				cost[0] = 7;
				if (cost[0] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[0];
					cout << "You have successfully obtained a new Cutlass" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[0].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[0], succ);
				}
				break;
			case 2:
				cost[1] = 2;
				if (cost[1] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[1];
					cout << "You have successfully obtained a new Dagger" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[1].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[1], succ);
				}
				break;
			case 3:
				cost[2] = 15;
				if (cost[2] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[2];
					cout << "You have successfully obtained a new Rifle" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[2].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[2], succ);
				}
				break;
			case 4:
				cost[3] = 10;
				if (cost[3] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[3];
					cout << "You have successfully obtained a new Shotgun" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[3].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[3], succ);
				}
				break;
			case 5:
				cost[4] = 5;
				if (cost[4] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[4];
					cout << "You have successfully obtained a new Pistol" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[5].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[5], succ);
				}
				break;
			case 6:
				cost[5] = 2;
				if (cost[5] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[5];
					cout << "You have successfully obtained some new Caltrops" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[6].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[6], succ);
				}
				break;
			case 7:
				cost[6] = 8;
				if (cost[6] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[6];
					cout << "You have successfully obtained a new Axe" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[7].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[7], succ);
				}
				break;
			case 8:
				cost[7] = 6;
				if (cost[7] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[7];
					cout << "You have successfully obtained a new Tomahawk" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[8].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[8], succ);
				}
				break;
			case 9:
				cost[8] = 20;
				if (cost[8] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[8];
					cout << "You have successfully obtained new Hidden Blades" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[9].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[9], succ);
				}
				break;
			case 10:
				cost[9] = 8;
				if (cost[9] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[9];
					cout << "You have successfully obtained a new Scimitar" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[4].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[4], succ);
				}
				break;
			case 11:
				cost[10] = 40;
				if (cost[10] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[10];
					cout << "You have successfully obtained a Grenade" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[10].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[10], succ);
				}
				break;
			case 12:
				cost[11] = 17;
				if (cost[11] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[11];
					cout << "You have successfully obtained some Small Pox Blankets" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[13].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[13], succ);
				}
				break;
			case 13:
				cost[12] = 15;
				if (cost[12] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[12];
					cout << "You have successfully obtained some new Dual Pistols" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your attack level has grown from " << p1.attack << " to ";
					p1.attack += Drops[19].data2;
					cout << p1.attack << "." << endl;
					treasure.ListInsert(1, Drops[19], succ);
				}
				break;
			}
		case 'A':
			cout << "Armor Inventory:" << endl;
			cout << "Gauntlets\t\tDefense Points: 25\t\tCost: $12 gold" << endl;
			cout << "Extra Gun Holster\tDefense Points: 5\tCost: $2 gold" << endl;
			cout << "Tricorn Hat\t\tDefense Points: 25\t\tCost: $12 gold" << endl;
			cout << "Leather Boots\t\tDefense Points: 15\t\tCost: $7 gold" << endl;
			cout << "Skull Bandana\t\tDefense Points: 7\t\tCost: $3 gold" << endl;
			cout << "Please make your selection:" << endl; 
			cout << "1 for Gauntlets    || 2 for Extra Gun Holsters || 3 for a Tricorn Hat" << endl;
			cout << "4 for Leather Boots||   5 for a Skull Bandana" << endl;
			cin >> buyAns[3];
			cout << endl;
			switch (buyAns[3])
			{
			case 1:
				cost[13] = 12;
				if (cost[13] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[13];
					cout << "You successfully purchased new Gauntlets" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your defense level has grown from " << p1.defense << " to ";
					p1.defense += Drops[14].data2;
					cout << p1.defense << "." << endl;
					treasure.ListInsert(1, Drops[14], succ);
				}
				break;
			case 2:
				cost[14] = 2;
				if (cost[14] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[14];
					cout << "You successfully purchased new Extra Gun Holsters" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your defense level has grown from " << p1.defense << " to ";
					p1.defense += Drops[15].data2;
					cout << p1.defense << "." << endl;
					treasure.ListInsert(1, Drops[15], succ);
				}
				break;
			case 3:
				cost[15] = 12;
				if (cost[15] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[15];
					cout << "You successfully purchased a new Tricorn Hat" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your defense level has grown from " << p1.defense << " to ";
					p1.defense += Drops[16].data2;
					cout << p1.defense << "." << endl;
					treasure.ListInsert(1, Drops[16], succ);
				}
				break;
			case 4:
				cost[16] = 12;
				if (cost[16] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[16];
					cout << "You successfully purchased new Leather Boots" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your defense level has grown from " << p1.defense << " to ";
					p1.defense += Drops[17].data2;
					cout << p1.defense << "." << endl;
					treasure.ListInsert(1, Drops[17], succ);
				}
				break;
			case 5:
				cost[17] = 3;
				if (cost[17] < p1.gold)
					InsufficientFunds();
				else
				{
					p1.gold -= cost[17];
					cout << "You successfully purchased a new Skull Bandana" << endl;
					cout << "You have " << p1.gold << " remaining." << endl;
					cout << "Your defense level has grown from " << p1.defense << " to ";
					p1.defense += Drops[18].data2;
					cout << p1.defense << "." << endl;
					treasure.ListInsert(1, Drops[18], succ);
				}
				break;
			}
			break;
		case 'B':
			cost[18] = 15;
			if (p1.gold < cost[18])
				InsufficientFunds();
			else
				RandDrop();
			break;
		default:
			ValidSelection();
		}
		goto getGold;
	}
	else if (buyAns[0] == 'N')
		return;
}
int Intro()
{
	cout << "Welcome to the Cry of Atlantis " << p1.name << endl;
	cout << "Since you're new to the ship, I want to let you know whats " <<
		"REALLY going on here...." << endl << endl;
	cout << "We came to this port to recruit because the Captain has been " <<
		"making quite a few\nof our friends walk the plank, if you know what I mean." << endl << endl;
	cout << "He's gone mad trying to find the Lost Treasure of Davey Jones!!" << endl;
	cout << "The problem is we go out to sea for months at a time" <<
		" and run out of supplies..." << endl << endl;
	cout << "We ALL want our piece of that treasure - believe me!  " <<
		"But the Captain's lost it!" << endl;
	cout << "Some of us have come to the decision that it may be time..." << endl << endl;
	cout << "Well................." << endl;
	cout << "....................." << endl;
	cout << "How can I put this?.." << endl;
	cout << "..." << endl;
	cout << "......" << endl;
	cout << "........." << endl;
	cout << "............" << endl;
	cout << "........." << endl;
	cout << "......" << endl;
	cout << "..." << endl;
	cout << "It's time for a change in Leadership." << endl;
	cout << "You know what I mean?" << endl << endl;
	if (Select() == 2)
	{
		cout << "Sounds to me like we have a sympathizer here boys...." << endl << endl;
		Line();
		cout << "*******************ONE WEEK LATER********************" << endl << endl;
		cout << "You joined the crew, but this dreary evening, you're " <<
			"woken to the sounds a jerks of your shipmates tying\n" <<
			"cannonballs to your feet.  Tonight, you sleep with the sharks..." << endl;
		cout << "Or at least in their bellies..." << endl << endl;
		Line();
		cout << endl;
		cout << "***********************GAME OVER*********************" << endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "Good to know where your allegiances lie." << endl;
		cout << "I think we'll get along just fine!!!" << endl << endl;
		Line();
		cout << endl;
		p1.rep += 10;
		cout << "You joined the crew and gained 10 Reputation Points.  Your current "
			<< "Reputation Score is " << p1.rep << "." << endl << endl << endl;
		system("pause");
		cout << endl;
		system("cls");
		return 1;
	}

}
int Select()
{
	int sel = 0;
	cout << "****Make your choice, Matey!!!***" << endl;
	cout << "Enter 1 for YES || Enter 2 for NO" << endl;
	cin >> sel;
	cout << endl;
	return sel;
}
void IntroImage()
{
	
}
void Damage()
{
	
	if (Boss.defend)
	{
		Boss.HP = Boss.HP - (p1.Attack(p1.getLevel()) - Boss.Defend(Boss.level));
		Boss.defend = false;
	}
	if (Boss.attack)
	{
		Boss.HP = Boss.HP - (p1.Attack(p1.getLevel()) / 2);
		Boss.attack = false;
	}
	if (p1.defend)
	{
		p1.hp = p1.hp - (Boss.Attack(Boss.level) - p1.Defend(p1.getLevel()));
		p1.defend = false;
	}
	if (p1.attack)
	{
		p1.hp = p1.hp - (Boss.Attack(Boss.level) / 2);
		p1.attack = false;
	}
}


BOOL InitInstance(HINSTANCE hInstance, int cmdShow)
{
	/*HWND hWnd;
	hWnd = CreateWindow(APPTITLE, APPTITLE, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 900, NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;
	ShowWindow(hWnd, cmdShow);
	UpdateWindow(hWnd);*/
	return TRUE;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;

	return RegisterClassEx(&wc);
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	global_hWnd = hWnd;
	global_hdc = GetDC(hWnd);

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


void ImageInit()
{
	srand(time(NULL));
}
void ImageRun()
{
	int x, y;
	RECT rect;
	GetClientRect(global_hWnd, &rect);
	if (rect.right > 0)
	{
		x = rect.left + 20;
		y = rect.top + 20;
		DrawBitmap(global_hdc, "Scourge.bmp", x, y);
	}
}
void ImageEnd(){};
void DrawBitmap(HDC hdc, char *fileName, int x, int y)
{
	HBITMAP image;
	BITMAP bm;
	HDC hdcMem;

	image = (HBITMAP)LoadImage(0, "Scourge.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(image, sizeof(BITMAP), &bm);
	hdcMem = CreateCompatibleDC(global_hdc);
	SelectObject(hdcMem, image);

	BitBlt(global_hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

	DeleteDC(hdcMem);
	DeleteObject((HBITMAP)image);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	int done = 0;
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, cmdShow)) return FALSE;
	ImageInit();
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		ImageRun();
	}
	ImageEnd();
	return msg.wParam;
}
#include "NPC.h"
#include <string>

string NPC::Name(int index)
{
	switch (index)
	{
	case 0:
		NPC_Names[index] = "Martin";
		name = NPC_Names[index];
		break;
	case 1:
		NPC_Names[index] = "Billy";
		name = NPC_Names[index];
		break;
	case 2:
		NPC_Names[index] = "Jimmy";
		name = NPC_Names[index];
		break;
	case 3:
		NPC_Names[index] = "Raymond";
		name = NPC_Names[index];
		break;
	case 4:
		NPC_Names[index] = "Nick";
		name = NPC_Names[index];
		break;
	case 5:
		NPC_Names[index] = "Parker";
		name = NPC_Names[index];
		break;
	case 6:
		NPC_Names[index] = "Benny";
		name = NPC_Names[index];
		break;
	case 7:
		NPC_Names[index] = "Harry";
		name = NPC_Names[index];
		break;
	case 8:
		NPC_Names[index] = "Chase";
		name = NPC_Names[index];
		break;
	case 9:
		NPC_Names[index] = "Austin";
		name = NPC_Names[index];
		break;
	case 10:
		NPC_Names[index] = "Justin";
		name = NPC_Names[index];
		break;
	case 11:
		NPC_Names[index] = "Sal";
		name = NPC_Names[index];
		break;
	case 12:
		NPC_Names[index] = "Stephan";
		name = NPC_Names[index];
		break;
	case 13:
		NPC_Names[index] = "Bart";
		name = NPC_Names[index];
		break;
	case 14:
		NPC_Names[index] = "Moe";
		name = NPC_Names[index];
		break;
	case 15:
		NPC_Names[index] = "The Bear";
		name = NPC_Names[index];
		break;
	case 16:
		NPC_Names[index] = "Rick";
		name = NPC_Names[index];
		break;
	case 17:
		NPC_Names[index] = "Carl";
		name = NPC_Names[index];
		break;
	case 18:
		NPC_Names[index] = "Darryl";
		name = NPC_Names[index];
		break;
	case 19:
		NPC_Names[index] = "Michonne";
		name = NPC_Names[index];
		break;
	default:
		cout << endl;
		cout << "======================================================================" << endl;
		cout << "Ooooooooooopppppppppssssssssssss!!!!  Something went terribly wrong!!!" << endl;
		cout << "=========================ARRAY OUT OF BOUNDS==========================" << endl;
		cout << endl;
	}

	return NPC_Names[index];
}
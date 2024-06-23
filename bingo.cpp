#include<iostream>
#include<string>
#include<ctime>
#include<cctype>
#include<cstdlib>
#include<iomanip>
using namespace std;
int winRate = 3;

/////////////////////   ----------  Prototypes
int makeTheTurn(int , int [][5], int [][5], string , string );
int getID(int);
int condition(int [][5], int& );
void initialize(int [][5]);
void playerSelect(bool& );
int getGridValue();
void waitNclean();

///////////////////////////  --- MAIN --- //////////////////////////////////
int main()
{
	srand(time(0));
	char choice;
	bool move_On = true, win = false, turn =0;
	int id1=0, id2=0,  count1, count2, Card, x = 0;
	string player1, player2;
	int p1[5][5], p2[5][5];


	// do while loop for Menu driven program.	
	do
	{
		waitNclean();
		cout << "\n\n\n\t\t\t\tBINGO GAME\n";
		cout << "\n\n\t\ta) Play Game\n\n\t\tb) Game History\n\n\t\tc) How to play ?\n\n\t\td) Exit\n\n";

		bool validInput = false;

		//Input check
		while (!validInput) {
			cout << "Enter your choice: ";
			cin >> choice;

			// Check if the input is a single character and not a digit
			if (!isdigit(choice) && (choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd')) {
				validInput = true;
			}
			else {
				cout << "\nInvalid input. Please enter 'a', 'b', 'c', or 'd', and avoid integers." << endl;
			}
		}
		if (choice =='a')
			initialize(p1), initialize(p2);

		switch (choice)
		{
		case 'a':

			//player 1 info.
			cout << "\nFor player 1\n"<<
				"\nEnter Player ID(within 4 digits) :-";
			id1 = getID(id2);
			cout << "\nEnter Player Name :- ";
			getline(cin,player1);
			cout << "\n\n";

			//player 2 info.
			cout << "\nFor player 2\n"<<
				"\nEnter Player ID (within 4 digits) :- ";
			id2 = getID(id1);
			cout << "\nEnter Player Name :- ";
			getline(cin, player2);
			cout << "\n\n";

			//Select a player randomly at first.
			playerSelect(turn);
			if (turn == 0)
				cout << "1st turn is of " << player1 << "\n\n\n";
			else
				cout << "1st turn is of " << player2 << "\n\n\n";

			waitNclean();

			for (count1 = 0, count2 = 0; win != true; turn = !turn)
			{
				switch (turn)
				{
					//player 1 turn.
				case 0:
					x = makeTheTurn(id1,p1,p2,player1,player2);
					if (x == 1)
						win = true;
					break;
					//player 2 turn.
				case 1:
					x = makeTheTurn(id2, p2, p1, player2, player1);
					if (x == 1)
						win = true;
					break;
				}
			}
			break;
		case 'b':
			cout << "There is no history yet.\n\n\n\n\n:) History is left to implement.\n\n";
			break;
		case 'c':
			cout << "This is a multiplayer game in which two players first enter required information"
				<<"\nand then start the game turn by turn by selecting one card from grid and that"
				<<"\ncard then removed (become 0) from both grids. And the player whose 3 lines "
				<<"\n(either row column or diagonal) becomes 0 will win the game or in rare cases"
				<<"\n match can be draw.\n\n";
			break;
		case 'd':
			move_On = false;
			break;
		default:
		{
			cout << " Invalid input, try again.";
			break;
		}
		}
	} while (move_On != false);

	return 0;
}



//////////////////  --------------- Function to wait and clean the screen

void waitNclean()
{
	system("pause");
	system("cls");
}

//////////////////  ----------------FUNCTION TO CHECK HOW MANY LINES ARE 0

int condition(int arr[][5], int& x)
{
	x = 0;

	//for ROWS.
	for (int i = 0; i < 5; i++)
	{
		bool check = true;
		for (int j = 0; j < 5; j++)
		{
			if (arr[i][j] != 0)
			{
				check = false;
				break;
			}
		}
		if (check == true)
		{
			++x;
		}
	}
	//for COLUMNS.
	for (int i = 0; i < 5; i++)
	{
		bool check = true;
		for (int j = 0; j < 5; j++)
		{
			if (arr[j][i] != 0)
			{
				check = false;
				break;
			}
		}
		if (check == true)
		{
			++x;
		}
	}
	//for DIAGONAL.
	bool check = true;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			if (arr[i][i] != 0)
			{
				check = false;
				break;
			}
		}
	}
	if (check == true)
	{
		++x;
	}

	//for ANTI-DIAGONAL.
	check = true;
	for (int i = 0; i < 5; i++)
	{
		int a = 3;
		for (int j = 4; a < i + j; j--)
		{
			if (arr[i][j] != 0)
			{
				check = false;
				break;
			}
		}
	}
	if (check == true)
	{
		++x;
	}

	return x;
}

//////////////////////////// FUNCTION TO AVOID repitition AND initialize OF grids.////////////////////////

void initialize(int arr[][5])
{
	for (int i = 0, a = 0, b = 0; i < 5; i++)
	{
		for (int j = 0, k = 0, l = 0; j < 5; j++)
		{
			a = (rand() % 25) + 1;
			b = 0;


			for (k = 0; k < 5; k++)
			{
				for (l = 0; l < 5; l++)
				{
					if (a == arr[k][l])
					{
						b = 1;
					}
				}
			}
			if (b == 0)
			{
				arr[i][j] = a;
			}
			else
			{
				--j;
			}
		}
	}
}

////////////////////////////   ------------  FUNCTION TO SELECT A RANDOM PLAYER FOR 1st TURN 

void playerSelect(bool& number)
{
	number = rand() % 2;
}

///////////////////////////  ---------- Player game Input Check to keep input under 1 to 25 only

int getGridValue() {
	int number;
	bool validInput = false;

	while (!validInput) {
		cin >> number;

		// Check if the input is valid and within 4 digits
		if (cin.fail() || (number < 1 || number > 25)) {
			cin.clear();  // Clear the error flag set by invalid input
			cin.ignore(1000, '\n');  // Discard invalid input
			cout << "Invalid input. Please enter a number with 1-25." << endl;
		}
		else {
			validInput = true;
		}
	}
	cin.clear();  // Clear the error flag set by invalid input
	cin.ignore(1000, '\n');  // Discard invalid input
	return number;
}

////////////////////////  ------------ Player ID Check to keep it under 4 digits and in integer form

int getID(int opponent_id)
{
	int number;
	bool validInput = false;

	while (!validInput) {
		//cout << "Enter a number (up to 4 digits): ";
		cin >> number;

		// Check if the input is valid and within 4 digits
		if (cin.fail() || (number / 10000 != 0 && number / -10000 != 0) || number == opponent_id) {
			cin.clear();  // Clear the error flag set by invalid input
			cin.ignore(1000, '\n');  // Discard invalid input
			cout << "Invalid input. Please enter a number with up to 4 digits." << endl;
		}
		else {
			validInput = true;
		}
	}
	cin.clear();  // Clear the error flag set by invalid input
	cin.ignore(1000, '\n');  // Discard invalid input
	return number;
}

////////////////////////////////  ---------------------- Function to play the turn of players

int makeTheTurn(int id, int p1[][5], int p2[][5], string player1, string player2)
{
	int Card = 0;
	int count1 = 0, count2 = 0;
	cout << "Player ID : " << id << endl;
	cout << "\n___________________________\n\n";
	for (int i = 0; i < 5; i++)
	{
		cout << "| ";
		for (int j = 0; j < 5; j++)
		{
			cout << setw(3) << p1[i][j];
			cout << " |";
		}
		cout << endl << "\n";
	}
	cout << player1 << " select any number from Card: ";
	Card = getGridValue();
	cout << "\n\n";
	waitNclean();
	//replacing selected card with 0 from both grids.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Card == p1[i][j])
				p1[i][j] = 0;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Card == p2[i][j])
				p2[i][j] = 0;
		}
	}
	//check win.
	condition(p1, count1);
	condition(p2, count2);
	if (count1 == count2 && count1==winRate)
	{
		cout <<"Both players have same Score, Match is draw.\n\n\t\t\tBINGO IS FUN";
		return 1;
	}
	else if (count1 >= winRate)
	{
		cout << player1 << " win the game.\n\n\t\t\tBINGO IS FUN";
		return 1;
	}
	else if (count2 >= winRate)
	{
		cout << player2 << " win the game.\n\n\t\t\tBINGO IS FUN";
		return 1;
	}
}
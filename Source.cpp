//----------------------------------------------------------------------------
//                              Golf Club App
//----------------------------------------------------------------------------
// CS 215 - Spring 2017 - Project 3
// Name:     Danny Foley
// Section:  401
// Date:     April 7, 2017
// An application to manage data for a Golf Club, including:
// - individual scores on a single hole of golf
// - total scores for a game
// - a list of games for one player
// - a list of players for the whole club
//----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int MAX_PLAYERS = 10;		// max number of players in a club
const int MAX_HOLES = 18;		// max number of holes in a game
const int MAX_GAMES = 10;		// max number of games for a player
const int NOT_FOUND = -1;		// return code for search
const int EXIT_OPTION = 7;		// main menu option for EXIT

struct aGame {					// WRITE a structure for aGame. Members:
	string course;				// course      - string         - name of golf course
	string date;				// date        - string         - date game was played
	int totalScore;				// totalScore  - integer        - total score for the game
	int hole[MAX_HOLES];		// hole        - array of ints  - list of scores for each hole
	int numHoles;				// numHoles    - integers       - number of holes played
};
struct aPlayer {
	string name;				// name of player
	float  avgScore;			// player's average score on all games
	int    numGames;			// number of games this player has played
	aGame  game[MAX_GAMES];		// list of games played by this player
};

struct aClub {
	string  name;				// name of the club
	int     numPlayers;			// number of players in the club
	int		holeAvg;			// used to calculate total score for players
	aPlayer player[MAX_PLAYERS];// list of players in this club
};

//----------------------------------------------------------------
//                         printLogo
//----------------------------------------------------------------
// Prints logo
//----------------------------------------------------------------
void printLogo() {
	system("cls");
	cout << "+------------------------------------------------+\n";
	cout << "|                GOLB CLUB EXPRESS PRO           |\n";
	cout << "|                  by Danny Foley 401            |\n";
	cout << "+------------------------------------------------+\n";
} // printLogo()


  //-----------------------------------------------------------------------------
  //                                 initGame
  //-----------------------------------------------------------------------------
  // Modifies: the game structure 
  // Initializes the game structure
  //-----------------------------------------------------------------------------
void initGame(aGame & g) {
	g.course = "";
	g.date = "";
	g.totalScore = 0;
	g.hole[MAX_HOLES] = { 0 };
	g.numHoles = 0;
} // initGame()

  //-----------------------------------------------------------------------------
  //                                 initPlayer
  //-----------------------------------------------------------------------------
  // Modifies: the player structure
  // Initializes the player structure
  //-----------------------------------------------------------------------------
void initPlayer(aPlayer & p) {
	p.name = "";
	p.avgScore = 0;
	p.numGames = 0;
	for (int i = 0; i < MAX_GAMES; i++) {
		initGame(p.game[i]);
	}
		


} // initPlayer()

  //-----------------------------------------------------------------------------
  //                                 initClub
  //-----------------------------------------------------------------------------
  // Modifies: the club structure
  // Initializes the club structure
  //-----------------------------------------------------------------------------
void initClub(aClub & c) {
	c.name = "";
	c.numPlayers = 0;
	c.holeAvg = 0;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		initPlayer(c.player[i]);
	}
} // initClub()

  //-----------------------------------------------------------------------------
  //								CalcTotal
  //-----------------------------------------------------------------------------
  // Given: the club structure
  // Calculates the total of all the players for each game
  //-----------------------------------------------------------------------------

void CalcTotal(aClub & c) {
	for (int i = 0; i < c.numPlayers; i++) {
		for (int j = 0; j < c.player[i].numGames; j++) {
			for (int k = 0; k < c.player[i].game[j].numHoles; k++) {
				c.player[i].game[j].totalScore += c.player[i].game[j].hole[k];
			}
			c.player[i].game[j].totalScore += (18 - c.player[i].game[j].numHoles)*c.holeAvg;
		}

	}
} //CalcTotal()

  //-----------------------------------------------------------------------------
  //							  CalcAvg
  //-----------------------------------------------------------------------------
  // Given: a club structure
  // Calculates average of all players
  //-----------------------------------------------------------------------------
void CalcAvg(aClub & c) {
	for (int i = 0; i < c.numPlayers; i++) {
		float sum = 0;
		for (int j = 0; j < c.player[i].numGames; j++) {
			sum += c.player[i].game[j].totalScore;
		}
		if (c.player[i].numGames == 0) {
			c.player[i].avgScore = 0;
		}
		else {
			c.player[i].avgScore = (float)sum / c.player[i].numGames;
		}
	}
}//CalcAvg()

  //-----------------------------------------------------------------------------
  //                                 startUp
  //-----------------------------------------------------------------------------
  // Given: a club structure
  // Initializes the club to "empty", then reads data from a file or
  // starts a new club.
  //-----------------------------------------------------------------------------
void startUp(aClub & c) {
	system("cls");
	printLogo();
	string fname; ifstream f; ofstream g;
	initClub(c);
	cout << "Enter input file name, or 'new' to start a new club: ";
	cin >> fname;
	f.open(fname);
	if (!f.fail()) {
		f >> c.numPlayers >> c.holeAvg; getline(f, c.name);
		cout << c.numPlayers << " players read from " << fname << endl;
		for (int i = 0; i < c.numPlayers; i++) {
			f >> c.player[i].numGames; f.ignore();
			getline(f, c.player[i].name);
			for (int j = 0; j < c.player[i].numGames; j++) {
				f >> c.player[i].game[j].numHoles; f.ignore();
				f >> c.player[i].game[j].date; f.ignore();
				getline(f, c.player[i].game[j].course);
				for (int k = 0; k < c.player[i].game[j].numHoles; k++) {
					f >> c.player[i].game[j].hole[k];
				}	}	}}
	CalcTotal(c); CalcAvg(c); f.close();
	if ((fname == "new") || (f.fail())) {
		cout << "Unable to open " << fname << endl;
		cout << "Starting new club instead.\n";
		cout << "Enter the Club Name:  ";
		cin.ignore(); getline(cin, c.name);
		cout << "Enter Club Hole Average: "; cin >> c.holeAvg; cout << "New team initialized!\n";}
	system("pause");
} // startUp()



  //-----------------------------------------------------------------------------
  //                                 printClub
  //-----------------------------------------------------------------------------
  // Prints the data of the club
  //-----------------------------------------------------------------------------
void printClub(aClub & c) {
	cout << "----------------------------------------------\n";
	cout << "           " << c.name << endl;
	cout << "----------------------------------------------\n";
	cout << "          #Players: " << c.numPlayers << "  Club Hole Avg:" << c.holeAvg << endl;
	for (int i = 0; i < c.numPlayers; i++) {
		cout << c.player[i].name << "   Avg: " << c.player[i].avgScore << "   #Games: " << c.player[i].numGames << endl;
		for (int j = 0; j < c.player[i].numGames; j++) {
			cout << "    " << c.player[i].game[j].date << " Score: " << c.player[i].game[j].totalScore << "  #Holes: " << c.player[i].game[j].numHoles << "  Course:   " << c.player[i].game[j].course << endl;
			cout << "    [";
			for (int k = 0; k < c.player[i].game[j].numHoles; k++) {
				if (k == c.player[i].game[j].numHoles - 1) {
					cout << c.player[i].game[j].hole[k];
				}
				else {
					cout << c.player[i].game[j].hole[k] << ", ";
				}
			}
			cout << "]\n";
		}
		cout << endl;
	}

}// printClub()

  //-----------------------------------------------------------------------------
  //                               addPlayer
  //-----------------------------------------------------------------------------
  // Modifies: a club structure
  // If the list of players is not full, initializes the next available element
  // in the club's player list and asks the user for the new player's name.
  //-----------------------------------------------------------------------------
void addPlayer(aClub & c) {
	if (c.numPlayers == MAX_PLAYERS) {
		cout << "Maximum number of players reached... cannot add another player.\n";
		return;
	}
	cout << "Enter player's name: ";
	cin.ignore();
	getline(cin, c.player[c.numPlayers].name);
	c.numPlayers++;
	cout << "Player added to club!\n";
} // addPlayer()

  //-----------------------------------------------------------------------------
  //                               dropPlayer
  //-----------------------------------------------------------------------------
  // Modifies: a club structure
  // Allows the user to select a player for deletion from the club's Player list
  // and deletes it.
  //-----------------------------------------------------------------------------
void dropPlayer(aClub & c) {
	string name;
	int position = -1;
	for (int i = 0; i < c.numPlayers; i++) {
		cout << c.player[i].name << endl;
	}
	cout << "Enter player's name: ";
	cin.ignore();
	getline(cin, c.player[c.numPlayers].name);
	name = c.player[c.numPlayers].name;
	while (position == -1) {
		for (int i = 0; i < c.numPlayers; i++) {
			if (name == c.player[i].name) {
				position = i;
			}
		}
		if (position == -1) {
			cout << "No player named " << name << " in the club.\n";
			return;
		}
	}
	for (int j = position; j <= c.numPlayers - 1; j++) {
		c.player[j] = c.player[j + 1];
	}
	c.numPlayers--;
	initPlayer(c.player[c.numPlayers]);
	cout << "Player dropped.\n";
} // dropPlayer()

  //-----------------------------------------------------------------------------
  //                               addGame
  //-----------------------------------------------------------------------------
  // Modifies: a club structure
  // Adds game data for a new game to a player in the club
  //-----------------------------------------------------------------------------
void addGame(aClub & c) {
	string name;
	int player = -1;
	int totalScore = 0;
	for (int i = 0; i < c.numPlayers; i++) {
		cout << c.player[i].name << endl;}
	cout << "Enter player's name:   "; cin.ignore();
	getline(cin, c.player[c.numPlayers].name);
	name = c.player[c.numPlayers].name;
	for (int i = 0; i < c.numPlayers; i++) {
		if (name == c.player[i].name) {
			player = i;	}}
	if (player == -1) {
		cout << "No player named " << name << " in the club.\n";
		return;}
	if (c.player[player].numGames == MAX_GAMES) {
		cout << "Maximum games reached!\n";
		return;}
	cout << "Enter course name:     "; getline(cin, c.player[player].game[c.player[player].numGames].course);
	cout << "Enter date played:     "; cin >> c.player[player].game[c.player[player].numGames].date;
	cout << "Enter number of holes: "; cin >> c.player[player].game[c.player[player].numGames].numHoles;
	cout << "Enter score for each hole, with spaces between:\n";
	for (int i = 0; i < c.player[player].game[c.player[player].numGames].numHoles; i++) {
		cin >> c.player[player].game[c.player[player].numGames].hole[i];
		totalScore = totalScore + c.player[player].game[c.player[player].numGames].hole[i];}
	totalScore = totalScore + (18 - c.player[player].game[c.player[player].numGames].numHoles)*c.holeAvg;
	c.player[player].game[c.player[player].numGames].totalScore = totalScore;
	cout << "Total score for game:" << totalScore << endl;
	cout << "New game data entered for " << c.player[player].name << endl;
		c.player[player].numGames++; CalcAvg(c);
} // addGame()

  //-----------------------------------------------------------------------------
  //                               sortByName
  //-----------------------------------------------------------------------------
  // Modifies: a club structure
  // Re-orders the club's list of players alphabetically by the players' names
  //-----------------------------------------------------------------------------
void sortByName(aClub & c) {
	for (int i = 0; i < c.numPlayers; i++) {
		for (int j = i + 1; j < c.numPlayers; j++)
			if (c.player[i].name[0] > c.player[j].name[0]) {
				aPlayer temp;
				temp = c.player[i];
				c.player[i] = c.player[j];
				c.player[j] = temp;
			}
	}
	cout << "Player sorted by name.\n";
} // sortByName()


  //-----------------------------------------------------------------------------
  //                               sortByAvg
  //-----------------------------------------------------------------------------
  // Modifies:  a club structure
  // Re-orders the club's list of players by their Average Score, high to low
  //-----------------------------------------------------------------------------
void sortByAvg(aClub & c) {
	for (int i = 0; i < c.numPlayers - 1; i++) {
		for (int j = i + 1; j < c.numPlayers; j++)
			if (c.player[i].avgScore < c.player[j].avgScore) {
				aPlayer temp;
				temp = c.player[i];
				c.player[i] = c.player[j];
				c.player[j] = temp;
			}
	}
	cout << "Players sorted by average.\n";
} // sortByAvg()

  //-----------------------------------------------------------------------------
  //                               saveData
  //-----------------------------------------------------------------------------
  // Given: a club structure
  // Asks the user for an output file name and, if successfully opened, writes
  // all club data to the file.
  //-----------------------------------------------------------------------------
void saveData(aClub & c) {
	string output;
	cout << "Enter output file name (or 'none'): ";
	cin >> output;
	output = output + ".txt";
	ofstream f;
	f.open(output);
		f << c.numPlayers << " " << c.holeAvg << " " << c.name << endl;
	for (int i = 0; i < c.numPlayers; i++) {
		f << c.player[i].numGames << " " << c.player[i].name << endl;
		for (int j = 0; j < c.player[i].numGames; j++) {
			f << c.player[i].game[j].numHoles << " " << c.player[i].game[j].date << " " << c.player[i].game[j].course << endl;
			for (int k = 0; k < c.player[i].game[j].numHoles; k++) {
				f << c.player[i].game[j].hole[k] << " ";
			}
			f << "\n";
		}
	}
	f.close();
} // saveData()

  //-----------------------------------------------------------------------------
  //                               getMenuOption
  //-----------------------------------------------------------------------------
  // Returns: the valid menu option chosen by the user
  // Displays the main menu and gets the user's option
  //----------------------------------------------------------------------------
int getMenuOption() {
	int option = EXIT_OPTION;
	printLogo();
	cout << "1. Add Player \n";
	cout << "2. Drop Player \n";
	cout << "3. Add Game Data for Player \n";
	cout << "4. Print Club Report \n";
	cout << "5. Sort Players by Average \n";
	cout << "6. Sort Players by Name \n";
	cout << EXIT_OPTION << ". Exit \n";
	cout << "Enter selection: ";
	cin >> option;
	if ((option > 7) || (option < 1)) {
		cout << "Please enter a number between 1 and 7.";
		cin >> option;
	}

	return option;
} // getMenuOption()

  //-----------------------------------------------------------------------------
  //                                 main
  //-----------------------------------------------------------------------------
void main() {
	aClub club;
	startUp(club);

	int option = 0;
	while (option != EXIT_OPTION) {
		option = getMenuOption();
		switch (option) {
		case 1: addPlayer(club);  break;
		case 2: dropPlayer(club); break;
		case 3: addGame(club);    break;
		case 4: printClub(club);  break;
		case 5: sortByAvg(club);  break;
		case 6: sortByName(club); break;
		case EXIT_OPTION: saveData(club);
		}
		system("pause");
	}
} // main()
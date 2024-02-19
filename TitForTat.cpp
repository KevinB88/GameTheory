/*
	Prisoner's dilemma
	Rules of game programmed in C++
*/

#include <iostream>
#include <vector>
#include <random>
#include <string>

//struct player {
//
//	int player_score = 0;
//	bool player_choice; 
//	std::string player_id; 
//	std::vector<int> player_memory; 
//
//
//	void update_score(int score) {
//		player_score += score;
//	}
//	void update_player_id(std::string id) {
//		player_id = id; 
//	}
//	void update_choice(bool choice) {
//		choice = choice;
//	}
//};

//Randomly generate an ID for the player:

std::string random_player_id() {


	std::string random_name = "";

	std::vector<std::string> male_names = { "Albert","Abe","Barry","Bob","Calvin","Clarence","Dean","Derrick","Eugene","Earl","Fred","Garry","Gabriel","Howard","Hank" };
	std::vector<std::string> female_names = { "Angela", "Alice", "Beatrice", "Christina", "Crystal", "Daniella", "Francesca", "Gabriella", "Isabella", "Amanda", "Lucy" };

	std::random_device rng;
	std::mt19937 engine(rng());
	std::uniform_int_distribution<int> sex(0, 1);
	std::uniform_int_distribution<int> ID(100, 999);

	int number = sex(engine);

	if (number) {

		std::uniform_int_distribution<int> name(0, male_names.size() - 1);

		int random_index = name(engine);

		random_name += male_names[random_index];
	}
	else {

		std::uniform_int_distribution<int> name(0, female_names.size() - 1);

		int random_index = name(engine);

		random_name += female_names[random_index];
	}

	number = ID(engine);

	random_name += std::to_string(number);

	return random_name;
}



/*
	Create different archetypes/strategies for the players
*/


//"Nice"/"Fair" strategist 
bool player_decision_A(std::vector<int>& player_memory, std::vector<int>& past_decisions) {

	int memory_ptr = -1;

	bool final_decision;

	//This strategist's first move will always attempt a cooperation
	if (player_memory.empty() && past_decisions.empty()) {
		past_decisions.push_back(true);
		memory_ptr++;
		return true;
	}
	//If the opposing player's last decision yielded a cooperation between the two: then continue the cooperation
	if (player_memory[memory_ptr] == true) {
		final_decision = true;
	} //If the opposing player decieved this player, then this player will retaliate
	else if (player_memory[memory_ptr] == false) {
		final_decision = false;
	}
	memory_ptr++;
	past_decisions.push_back(final_decision);
	return final_decision;
}

//<*************************>
//B: Decisions are completely random 
bool player_decision_B(std::vector<int>& player_memory, std::vector<int>& past_decisions) {

	std::random_device rng;
	std::mt19937 engine(rng());
	std::uniform_int_distribution<int> dist(0, 1);

	bool final_decision = dist(engine);
	past_decisions.push_back(final_decision);

	return final_decision;
}
//<*************************>

//bool player_decision_C(std::vector<int>& player_memory, std::vector<int>& past_decisions) {
//
//
//}
//
//bool player_decision_D(std::vector<int>& player_memory, std::vector<int>& past_decisions) {
//
//
//}
//

template<typename T>
void print_vector(const std::vector<T>& container) {
	for (const auto& element : container) {
		std::cout << element << " ";
	}
	std::cout << "\n";
}


//Temporary function to simply decide an adjective to describe the player based upon their game report:

void player_attribute_report(std::string player_id, std::vector<int>& self_decisions, std::vector<int>& stranger_decisions, int turns) {

	int cooperations = 0; // Both players successfully cooperate on the turn
	int swindled = 0; // self-inflicted: The player attempts a cooperation with the stranger but fails
	int steals = 0; // The opposing player attempts a cooperation but is decieved 
	int deceptions = 0; // Rewarded if the opposing player is decieved after n-consecutive cooperations (n >= 2) 
	int rationals = 0;

	int consecutive_cooperations = 0;


	for (int i = 0; i < turns; i++) {

		if (self_decisions[i] && stranger_decisions[i]) {
			cooperations++;
			consecutive_cooperations++;
		}
		else if (self_decisions[i] && !stranger_decisions[i]) swindled++;

		else if (!self_decisions[i] && stranger_decisions[i]) {

			steals++;

			if (consecutive_cooperations >= 2) deceptions++;

			consecutive_cooperations = 0;
		}
		else rationals++;
	}

	std::cout << "*****--------------------------------------------------*****\n";
	std::cout << player_id << "'s Game Report: \n";

	std::cout << "From a game of: " << turns << " turn(s).\n";
	std::cout << "Has cooperated: " << cooperations << " time(s).\n";
	std::cout << "Has been swindled: " << swindled << " time(s).\n";
	std::cout << "Has stolen: " << steals << " time(s).\n";
	std::cout << "Has decived: " << deceptions << " time(s).\n";
	std::cout << "Has played: " << rationals << " rational move(s).\n";

	std::cout << "*****--------------------------------------------------*****\n";
}



int main() {

	int player_1_score = 0;
	int player_2_score = 0;

	std::string player_1_id = random_player_id();
	std::string player_2_id = random_player_id();

	std::pair<int, std::string> player_1 = { player_1_score, player_1_id };
	std::pair<int, std::string> player_2 = { player_2_score, player_2_id };

	std::vector<int>player_1_memory;
	std::vector<int>player_2_memory;

	std::vector<int>player_1_decisions;
	std::vector<int>player_2_decisions;

	/*
		Create a class/struct which can encapsulate the data/information of the player.
	*/


	bool player_1_choice = true;
	bool player_2_choice = true;

	int max_score = 100;
	int turns = 0;


	std::string winning_player;

	/*
		if player_n_choice is TRUE, this is equates to a cooperative decision,
		otherwise player_n_choice is Fale, which is equivalent to a "steal" or defection
	*/

	while (true) {

		//*********************

		player_1_choice = player_decision_B(player_1_memory, player_1_decisions);
		player_2_choice = player_decision_B(player_2_memory, player_2_decisions);

		//*********************

		if (player_1_choice && player_2_choice) {
			player_1.first += 3;
			player_2.first += 3;

		}
		else if (!player_1_choice && !player_2_choice) {
			player_1.first += 1;
			player_2.first += 1;

		}
		else {
			if (!player_1_choice) player_1.first += 5;
			else if (!player_2_choice) player_2.first += 5;
		}

		if (player_1.first == player_2.first && player_1.first >= max_score) {
			winning_player = "T";
			break;
		}

		else if (player_1.first >= max_score) {
			winning_player = player_1.second;
			break;
		}
		else if (player_2.first >= max_score) {
			winning_player = player_2.second;
			break;
		}

		//Remember the opposite player's last decision:

		player_1_memory.push_back(player_2_choice);
		player_2_memory.push_back(player_1_choice);

		turns++;
	}





	std::cout << "\n" << "\n";
	std::cout << "*****--------------------------------------------------*****\n";

	if (winning_player == "T") {
		std::cout << "It's a TIE!\n";
	}
	else {
		std::cout << "The winning player: " << winning_player << "\n";
	}

	std::cout << "STATS: \n";
	std::cout << "Game Turns: " << turns << "\n";

	std::cout << "*****--------------------------------------------------*****\n";

	std::cout << "PLAYER 1: \n";
	std::cout << player_1.second << ":\n" << "Choices: ";
	print_vector(player_1_decisions);
	std::cout << "Score: " << player_1.first << "\n";

	std::cout << "*****--------------------------------------------------*****\n";

	std::cout << "PLAYER 2: \n";
	std::cout << player_2.second << ":\n" << "Choices: ";
	print_vector(player_2_decisions);
	std::cout << "Score: " << player_2.first << "\n";

	std::cout << "*****--------------------------------------------------*****\n";
	std::cout << "\n" << "\n";


	player_attribute_report(player_1_id, player_1_decisions, player_1_memory, turns);

	std::cout << "\n" << "\n";

	player_attribute_report(player_2_id, player_2_decisions, player_2_memory, turns);

	return 0;
}

/*
	Add in player highlights/adjectives to describe the player's strategy:
		-Counting the number of cooperations between the players
		-Counting the number of defections between the players
		-Counting the number of times in a row that a player has either cooperated/defected.
		-Counting the number of Deceptions between the players: (the first player to steal after n-consecutive cooperations)
*/
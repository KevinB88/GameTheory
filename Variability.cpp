#include <iostream>
#include <random>
#include <chrono>
#include <string>

void space() {
	std::cout << "\n"; 
}


int arithmeticQuestion(std::string& question) {

	int answer = 0; 
	std::string symbol; 

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> operation_distribution(0, 1);
	std::uniform_int_distribution<int> numerical_distribution(1, 15);

	int number_1 = numerical_distribution(eng);
	int number_2 = numerical_distribution(eng);

	int operation = operation_distribution(eng);

	if (operation == 0) {
		answer = number_1 + number_2; 
		symbol = " + ";
	}
	else if (operation == 1) {
		answer = number_1 * number_2;
		symbol = " * ";
	}

	question = std::to_string(number_1) + symbol + std::to_string(number_2) + " = ";

	return answer; 
}

std::string random_complement(int index) {
	std::vector<std::string> complements = { "Great job!", "Excellent!", "Incredible!", "Keep it up!", "Let's Go!", "Fantastic!", "Bravo!", "Keep it going!", "Don't put an end to the pace!", "Keep pleasing!", "That's how it's done!" };
	return complements[index % complements.size()];
}

std::string random_wrong(int index) {
	
	std::vector<std::string> wrongs = { "Wrong!", "Oops!", "That's not right..", "Incorrect!", "Oh come on!", "Get it right next time will you?", "Are you kidding me?", "That's so wrong...", "That ain't right pal", "That's okay buddy..." };
	return wrongs[index % wrongs.size()];
}


void gameloop(){

	int totalScore			= 0;
	int correctScore		= 0; 
	int roundCount			= 0;
	int correctCount		= 0; 
	int userInput			= 0;
	int answer				= 0; 
	int streakCount			= 0; 
	int scoreMultiplier	    = 1; 

	int incorrectStreakCount		= 0;
	int incorrectScoreMultiplier	= 1; 

	std::string question; 
	
	
	while (true) {


		if (totalScore < 0) break;

		answer = arithmeticQuestion(question); 

		std::cout << question << " "; 
		std::cin >> userInput; 

		space(); 

		if (userInput == answer) {

			correctCount++;
			streakCount++;
				
			if (streakCount % 3 == 0 && scoreMultiplier < 4) {
				std::cout << "You're on a streak!\n";
				std::cout << "Multiplier: " << scoreMultiplier << "\n"; 
				
				if (scoreMultiplier == 3) {
					std::cout << "You've reached the maximum multiplier!\n"; 
					std::cout << "Multiplier: " << scoreMultiplier + 1 << "\n"; 
				}
				//Player redemption
				//The incorrect streak ends after the player gets 3 questions correct in a row 


				if (incorrectStreakCount >= 2) {
					std::cout << "You've redeemed yourself!\n"; 
				}

				incorrectStreakCount = 0;
				incorrectScoreMultiplier = 1; 

				scoreMultiplier++;
			}
			space(); 


			std::cout << random_complement(answer) << "\n";
			std::cout << "+" << std::to_string(answer * scoreMultiplier) << " points!\n";

			totalScore += answer * scoreMultiplier;
			correctScore += answer * scoreMultiplier; 
		}
		else {
			streakCount = 0;
			scoreMultiplier = 1; 
			
			//if the player gets an incorrect answer: their total score is subtracted by the actual answer multiplied by 2, and also multiplied by another multiple for every 2 incorrect answers. 
			totalScore -= answer * 2 * incorrectScoreMultiplier; 
			
			if (incorrectStreakCount % 2 == 0 && incorrectStreakCount > 0 && incorrectScoreMultiplier < 4) {

				std::cout << "You're not on a good streak ...\n";
				std::cout << "Incorrect Multiplier: " << incorrectScoreMultiplier << "\n";

				if (incorrectScoreMultiplier == 3) {
					std::cout << "Get 3 questions correct in a row to get yourself out of this mess!!\n";
					std::cout << "Incorrect Multiplier: " << incorrectScoreMultiplier + 1 << "\n"; 
				}

				incorrectScoreMultiplier++; 
			}
			space(); 
			

			std::cout << random_wrong(userInput) << "\n"; 
			std::cout << "-" + std::to_string(answer * 2 * incorrectScoreMultiplier) << " points...\n"; 
		}
		space(); 

		std::cout << "Total score: " << totalScore << "\n";

		roundCount++; 
		answer = 0; 
		space(); 
	}

	std::cout << "Game over!\n";
	std::cout << "Your correct score: " << correctScore << "\n";
	std::cout << "The number of questions correct: " << correctCount << "\n";
	std::cout << "The number of questions incorrect: " << roundCount - correctCount << "\n";
	std::cout << "The number of questions answered: " << roundCount << "\n";
}


int main() {

	gameloop();


	return 0;
}

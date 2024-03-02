#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <vector>
#include <numeric>
#include <chrono>
#include <thread>
#include <string>

constexpr double PI = 3.14159265358979323846;

typedef std::vector<std::pair<int, double>> user_combination_map; 

void print_line() {
	std::cout << "------------------------------------------------------------------------\n";
}


user_combination_map parse_user_passcode(std::string& user_input) {

	user_combination_map tokeys; 
	std::pair<int, double> tokey;

	for (char character : user_input) {
	
		tokey = { int(character), double(1/((int(character) + 1 * std::log(int(character)))))};
		tokeys.push_back(tokey);
	}
	return tokeys;
}


double generate_secure_code(const user_combination_map & user_combinations) {

	double combination_key = 0; 

	std::vector<double>combination_keys; 

	for (int c = 0; c < user_combinations.size(); c++) {

		for (int x = 0; x <= user_combinations[c].first; x++) {
			
			combination_key += double(x % 10); 

		}
		/*combination_key *= (user_combinations[c].second * M_PI); */
		combination_key *= (user_combinations[c].second * PI); 
		combination_keys.push_back(combination_key); 

		combination_key = 0; 
	}

	double output_code = 0;

	for (auto& key : combination_keys) {

		output_code += key;
	}

	return output_code;
	//return std::accumulate(combination_keys.begin(), combination_keys.end(), 0); 
}


void print_combination_map(const user_combination_map& container) {
	
	int enumerator = 1; 

	for (const auto& pair : container) {
		
		std::cout << "Key #" << enumerator++ << ":\n"; 
		std::cout << "Sequential index: " << pair.first << "\n";
		std::cout << "Rotational index: " << pair.second << "\n";
		print_line(); 
	}
	std::cout << "\n";
}


void acquire_user_combinations(user_combination_map& container) {

	int user_key_count = 0;
	int user_sequence_index = 0;
	double user_rotational_index = 0; 


	std::cout << "Input the number of keys you would like to input: "; 
	std::cin >> user_key_count;
	
	for (int i = 0; i < user_key_count; i++) {
		
		std::cout << "Key #" << i + 1 << "\n";

		std::cout << "Enter the sequential index: ";
		std::cin >> user_sequence_index; 
		
		std::cout << "Enter the rotational index: "; 
		std::cin >> user_rotational_index; 

		std::pair<int, double> combination_key = { user_sequence_index, user_rotational_index };
		
		container.push_back(combination_key); 
	}

	std::cout << "\n"; 

	std::cout << "Your keys: (Please make sure to remember your keys)\n";
	print_combination_map(container); 

}



int main() {


	std::string user_passcode;

	std::cout << "Enter a passcode: "; 

	std::getline(std::cin, user_passcode); 
	
	user_combination_map personal = parse_user_passcode(user_passcode);

	print_combination_map(personal); 

	double value = generate_secure_code(personal); 

	std::cout << value << "\n"; 

	
	std::string user_passcode_2;

	std::cout << "Enter a passcode: ";

	std::getline(std::cin, user_passcode);

	user_combination_map personal_2 = parse_user_passcode(user_passcode);

	print_combination_map(personal_2);

	double value_2 = generate_secure_code(personal_2);


	std::cout << value << "\n";


	if (value == value_2) std::cout << "You're in!\n";
	else std::cout << "Intruder alert!\n"; 


	//user_combination_map personal; 
	//acquire_user_combinations(personal); 
	//double passcode = generate_secure_code(personal); 

	//std::cout << "You're secure code: " << generate_secure_code(personal) << "\n"; 

	//user_combination_map login; 
	//acquire_user_combinations(login); 
	//double user_attempt = generate_secure_code(login); 

	//std::cout << "Attempted code: " << user_attempt << "\n"; 

	//if (user_attempt == passcode) {
	//	std::cout << "Successfully entered your account.\n";
	//	std::this_thread::sleep_for(std::chrono::milliseconds(800)); 


	//	std::cout << "Loading"; 
	//	
	//	for (int i = 0; i < 5; i++) {
	//		std::cout << ".";
	//		std::this_thread::sleep_for(std::chrono::milliseconds(600)); 
	//	}
	//	std::cout << "\n";

	//	std::cout << "PERSONAL INFORMATION:\n";

	//	std::cout << "SAVINGS:			$100,000\n";
	//	std::cout << "CHECKINGS:			$25,000\n"; 
	//}
	//else std::cout << "Login failure.\n";

	return 0;
}

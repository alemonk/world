#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool word_in_solutions(string guess) {
    std::ifstream file("possible_solutions.txt");
    // std::ifstream file("little_solutions.txt");
    
    if (!file) {
        std::cerr << "Error: Could not open the file!\n";
        return 1;
    }

    std::string word;
    
    while (file >> word) {
        if (guess == word) {
            return true;
        }
    }
    return false;
}

vector<string> filter_by_green_hints(vector<string>& possible_answers, const string& hints, const string& guess) {
    for (auto it = possible_answers.begin(); it != possible_answers.end(); ) {
        bool match = true;
        for (int i = 0; i < hints.size(); i++) {
            if (hints[i] == 'G') {
                if ((*it)[i] != guess[i]) {
                    match = false;
                    break;
                }
            }
        }
        if (!match) {
            // Print the word that doesn't match
            // cout << "Removing: " << *it << endl;
            it = possible_answers.erase(it); // Remove the word if it doesn't match
        } else {
            ++it; // Move to the next word if it matches
        }
    }
    return possible_answers;
}

int main() {
    string correct_word = "brain";
    string guess;
    string hints = "-----";

    // Store all possible answers
    vector<string> possible_answers;
    std::ifstream file("possible_solutions.txt");
    // std::ifstream file("little_solutions.txt");
    std::string word;
    
    while (file >> word) {
        possible_answers.push_back(word);
    }

    // Step 1: enter the guess
    std::cout << "Enter your guess (" << possible_answers.size() << " possible answers): ";
    do {
        std::cin >> guess;

        if (word_in_solutions(guess) == 0){
            std::cout << "Word is not valid. Enter your guess again: ";
        }
    } while (word_in_solutions(guess) == 0);

    // Step 2: specify present letters (YELLOW) and correct letters (GREEN)
    std::cout << "Specify present letters with Y, correct letters with G, - if not correct" << std::endl;
    std::cin >> hints;

    // Step 3: filter out wrong answers
    // Step 3.1: filter out words that don't have any letter in correct position (GREEN letters)
    possible_answers = filter_by_green_hints(possible_answers, hints, guess);
    std::cout << possible_answers.size() << " possible answers." << std::endl;
    for (int i = 0; i < possible_answers.size(); i++) {
        std::cout << possible_answers[i] << std::endl;
    }
    // Step 3.2: filter out words that don't have any correct letters (YELLOW letters) 

    return 0;
}
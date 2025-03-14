#include <iostream>
#include <fstream>
#include <vector>
#include "helper_functions.h"
using namespace std;

int main() {
    string guess;
    string hints = "-----";

    std::ifstream file("possible_solutions.txt");
    //std::ifstream file("little_solutions.txt");

    // Store all possible answers
    vector<string> possible_answers;
    std::string word;
    
    while (file >> word) {
        possible_answers.push_back(word);
    }

    int attempt_number = 0;
    do {
        // Step 1: enter the guess
        attempt_number++;
        std::cout << std::endl << "Attempt number: " << std::to_string(attempt_number) << std::endl;

        // Step 1.1: show most informative words
        vector<string> best_guesses = get_informative_words(possible_answers);
        std::cout << "\tMost informative words:" << std::endl;
        for (int i = 0; i < 10; i++) {
            std::cout << "\t" << best_guesses[i] << std::endl;
        }
        std::cout << "Enter your guess (" << possible_answers.size() << " possible answers): ";

        // Steo 1.2: check if the word is valid
        do {
            std::cin >> guess;

            if (word_in_solutions(guess, file) == 0){
                std::cout << "Word is not valid. Enter your guess again: ";
            }
        } while (word_in_solutions(guess, file) == 0);

        // Step 2: specify present letters (YELLOW) and correct letters (GREEN)
        std::cout << "Specify present letters with Y, correct letters with G, - if not correct" << std::endl;
        std::cin >> hints;

        if (hints == "GGGGG") {
            std::cout << "YOU WIN!!!";
            return 0;
        }

        // Step 3: filter out wrong answers
        // Step 3.1: filter out words that don't have any letter in correct position (GREEN letters)
        possible_answers = filter_by_green_hints(possible_answers, hints, guess);

        // Step 3.2: filter out words that don't have any correct letters (YELLOW letters)
        possible_answers = filter_by_yellow_hints(possible_answers, hints, guess);

        // Step 3.3: filter out words that are not present at all (DASH)
        possible_answers = filter_by_dash_hints(possible_answers, hints, guess);

        std::cout << possible_answers.size() << " possible answers." << std::endl;
        for (int i = 0; i < possible_answers.size(); i++) {
            std::cout << possible_answers[i] << std::endl;
        }
    } while(attempt_number < 6);

    std::cout << "YOU LOSE!" << std::endl;

    return 0;
}
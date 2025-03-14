#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool word_in_solutions(const std::string& guess, std::ifstream& file) {
    std::string word;
    // Reset the file position and state
    file.clear();               // Clear error flags (e.g., EOF)
    file.seekg(0, ios::beg);    // Move to the beginning of the file

    while (file >> word) {
        if (guess == word) {
            return 1;
        }
    }
    return 0;
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

vector<string> filter_by_yellow_hints(vector<string>& possible_answers, const string& hints, const string& guess) {
    for (auto it = possible_answers.begin(); it != possible_answers.end(); ) {
        bool match = true; // Assume this word matches the yellow hints
        vector<bool> matched_indices(hints.size(), false); // Track matched positions in the word

        for (int i = 0; i < hints.size(); i++) {
            if (hints[i] == 'Y') { // Only process yellow hints
                bool yellow_match = false;

                // Look for the guessed character in a different position
                for (int j = 0; j < hints.size(); j++) {
                    if (i != j && !matched_indices[j] && (*it)[j] == guess[i] && hints[j] != 'G') {
                        yellow_match = true;
                        matched_indices[j] = true; // Mark this position as matched
                        break;
                    }
                }

                if (!yellow_match) {
                    match = false; // No valid yellow match found for this letter
                    break;
                }
            }
        }

        if (!match) {
            // Remove non-matching word
            it = possible_answers.erase(it);
        } else {
            ++it; // Keep the word and move to the next
        }
    }
    return possible_answers;
}

int main() {
    string correct_word = "brain";
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

    // Step 1: enter the guess
    std::cout << "Enter your guess (" << possible_answers.size() << " possible answers): ";
    do {
        std::cin >> guess;

        if (word_in_solutions(guess, file) == 0){
            std::cout << "Word is not valid. Enter your guess again: ";
        }
    } while (word_in_solutions(guess, file) == 0);

    // Step 2: specify present letters (YELLOW) and correct letters (GREEN)
    std::cout << "Specify present letters with Y, correct letters with G, - if not correct" << std::endl;
    std::cin >> hints;

    // Step 3: filter out wrong answers
    // Step 3.1: filter out words that don't have any letter in correct position (GREEN letters)
    possible_answers = filter_by_green_hints(possible_answers, hints, guess);

    // Step 3.2: filter out words that don't have any correct letters (YELLOW letters)
    possible_answers = filter_by_yellow_hints(possible_answers, hints, guess);
    std::cout << possible_answers.size() << " possible answers." << std::endl;
    for (int i = 0; i < possible_answers.size(); i++) {
        std::cout << possible_answers[i] << std::endl;
    }

    return 0;
}
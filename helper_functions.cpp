#include "helper_functions.h"
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

vector<string> filter_by_dash_hints(vector<string>& possible_answers, const string& hints, const string& guess) {
    for (auto it = possible_answers.begin(); it != possible_answers.end(); ) {
        bool match = true;

        for (int i = 0; i < hints.size(); i++) {

            // analyze each character in 'hints'
            if (hints[i] == '-') {
                for (int j = 0; j < hints.size(); j++) {

                    // compare i-th DASH character with 'guess'
                    if (guess[i] == (*it)[j]) {
                        match = false;
                        break;
                    }
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
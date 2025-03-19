#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

// Function prototypes
bool word_in_solutions(const std::string& guess, std::ifstream& file);
std::unordered_map<char, double> load_letter_probabilities(const std::string& filename);
double compute_entropy(const std::string& word, const std::unordered_map<char, double>& probabilities);
void get_informative_words(std::vector<std::string> possible_answers);
std::vector<std::string> filter_by_green_hints(std::vector<std::string>& possible_answers, const std::string& hints, const std::string& guess);
std::vector<std::string> filter_by_yellow_hints(std::vector<std::string>& possible_answers, const std::string& hints, const std::string& guess);
std::vector<std::string> filter_by_dash_hints(std::vector<std::string>& possible_answers, const std::string& hints, const std::string& guess);

#endif

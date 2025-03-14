#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>
#include <vector>
#include <fstream>

// Function prototypes
bool word_in_solutions(const std::string& guess, std::ifstream& file);
std::vector<std::string> filter_by_green_hints(std::vector<std::string>& possible_answers, const std::string& hints, const std::string& guess);
std::vector<std::string> filter_by_yellow_hints(std::vector<std::string>& possible_answers, const std::string& hints, const std::string& guess);
std::vector<std::string> filter_by_dash_hints(std::vector<std::string>& possible_answers, const std::string& hints, const std::string& guess);

#endif

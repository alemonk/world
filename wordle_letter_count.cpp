#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iomanip> // For setting decimal precision

int main() {
    std::unordered_map<char, int> letter_count;
    std::ifstream file("possible_solutions.txt");
    
    if (!file) {
        std::cerr << "Error: Could not open the file!\n";
        return 1;
    }
    
    int total_letters = 0; // To track the total number of letters
    std::string word;
    
    while (file >> word) {
        for (char c : word) {
            letter_count[c]++;
            total_letters++;
        }
    }
    
    file.close();
    
    std::cout << "Letter probabilities:\n";
    std::cout << std::fixed << std::setprecision(4); // Set decimal precision to 4 places
    
    for (const auto& pair : letter_count) {
        double probability = static_cast<double>(pair.second) / total_letters;
        std::cout << pair.first << ": " << probability * 100 << "% (" << pair.second << " occurrences)\n";
    }
    
    return 0;
}
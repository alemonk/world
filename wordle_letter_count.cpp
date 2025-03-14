#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iomanip>

int main() {
    std::unordered_map<char, int> letter_count;
    std::ifstream file("possible_solutions.txt");
    
    if (!file) {
        std::cerr << "Error: Could not open the file!\n";
        return 1;
    }
    
    int total_letters = 0;
    std::string word;
    
    while (file >> word) {
        for (char c : word) {
            letter_count[c]++;
            total_letters++;
        }
    }
    
    file.close();
    
    std::ofstream output("letter_probabilities.txt");
    if (!output) {
        std::cerr << "Error: Could not create output file!\n";
        return 1;
    }
    
    output << std::fixed << std::setprecision(4);
    
    for (const auto& pair : letter_count) {
        double probability = static_cast<double>(pair.second) / total_letters;
        output << pair.first << " " << probability << "\n";
    }
    
    output.close();
    
    std::cout << "Letter probabilities saved to letter_probabilities.txt" << std::endl;
    
    return 0;
}

#include <iostream>
#include <string>

int findFirstOccurence(const std::string& text, const std::string& pattern) {
    if (pattern.empty()) return 0; 
    size_t result = text.find(pattern);
    return (result == std::string::npos) ? -1 : static_cast<int>(result);
}

int main() {
    // pattern at the beginning
    std::string text_1 = "hello sir";
    std::string pattern_1 = "hello";
    std::cout << "Test 1: " << findFirstOccurence(text_1, pattern_1) << "\n"; 

    // pattern at the end
    std::string text_2 = "this can be a good test";
    std::string pattern_2 = "test";
    std::cout << "Test 2: " << findFirstOccurence(text_2, pattern_2) << "\n"; 

    // pattern not present
    std::string text_3 = "abcdef";
    std::string pattern_3 = "xyz";
    std::cout << "Test 3: " << findFirstOccurence(text_3, pattern_3) << "\n"; 

    // empty pattern
    std::string text_4 = "anythichsang";
    std::string pattern_4 = "";
    std::cout << "Test 4: " << findFirstOccurence(text_4, pattern_4) << "\n"; 

    return 0;
}
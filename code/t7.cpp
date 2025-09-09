#include <iostream>
#include <vector>

void printIndises(const std::vector<int>& indises) {
    if (indises.empty()) {
        std::cout << "No occurence.\n";
    } else {
        std::cout << "Indises: ";
        for (int index: indises) {
            std::cout << index << " ";
        }
        std::cout << "\n";
    }
}
std::vector<int> findAllIndises(const std::vector<int>& arr, int key) {
    std::vector<int> indises;
    for (int i=0; i<arr.size(); ++i) {
        if (arr[i]== key) {
            indises.push_back(i);
        }
    }
    return indises;
}
int main() {
    //Multiple occurences
    std::vector<int> arr_1 = {1, 2, 3, 2, 4, 2, 2, 2};
    auto indises1 = findAllIndises(arr_1, 2);
    printIndises(indises1); 

    //Key not present
    std::vector<int> arr_2 = {5, 6, 7};
    auto indises2 = findAllIndises(arr_2, 8);
    printIndises(indises2); 

    //Empty array
    std::vector<int> arr_3;
    auto indises3 = findAllIndises(arr_3, 1);
    printIndises(indises3); 

    return 0;
}



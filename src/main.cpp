#include <iostream>
#include <fstream>
#include <array>

int main(){
    std::ifstream roommatesInput;
    roommatesInput.open("docs/roommates.txt");
    std::array<int, 40000> studentsCompatibilityArray;
    if (!roommatesInput)
    {
        return -1;
    }
    
    for (int i = 0; i < 40000; i++)
    {
        roommatesInput >> studentsCompatibilityArray[i];
        std::cout << studentsCompatibilityArray[i] << " ";
    }
    

    std::cout << "HOLA MUNDO\n";
    return 0;
}
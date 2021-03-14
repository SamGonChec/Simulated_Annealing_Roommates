#include <iostream>
#include <fstream>
#include <array>
#include "Annealer.h"

int main(){
    std::ifstream roommatesInput;
    roommatesInput.open("data/roommates.txt");
    std::array<int, 40000> studentsCompatibilityArray;
    if (!roommatesInput)
    {
        return -1;
    }
    
    for (int i = 0; i < 40000; i++)
    {
        roommatesInput >> studentsCompatibilityArray[i];
    }
    Annealer annealer(studentsCompatibilityArray);
    annealer.outputResult();

    std::cout << "HOLA MUNDO\n";
    return 0;
}
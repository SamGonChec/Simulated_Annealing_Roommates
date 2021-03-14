#include "Annealer.h"

Annealer::Annealer(std::array<int,40000> studentsCompatibility){
    this->studentsCompatibility = studentsCompatibility;
}
void Annealer::AssignRooms(){
    for (int i = 0; i < numberOfRooms*studentsPerRoom; i++)
    {
        rooms[i] = i;
    }
    
}
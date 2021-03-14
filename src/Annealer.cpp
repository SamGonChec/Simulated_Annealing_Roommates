#include "Annealer.h"

Annealer::Annealer(std::array<int,40000> studentsCompatibility){
    this->studentsCompatibility = studentsCompatibility;
    AssignRooms();
}
void Annealer::AssignRooms(){
    for (int i = 0; i < numberOfRooms*studentsPerRoom; i++)
    {
        rooms[i] = i;
    }
    
}
void Annealer::outputResult(){
    std::ofstream outputFile;
    outputFile.open("data/output.txt");
    for (int i = 0; i < numberOfRooms; i++)
    {
        outputFile << "Room " << i << ": " << rooms[i*studentsPerRoom] 
        << " " << rooms[i*studentsPerRoom +1] 
        << " " << rooms[i*studentsPerRoom +2]
        << " " << rooms[i*studentsPerRoom +3]

        
        << std::endl;
    }
    
}
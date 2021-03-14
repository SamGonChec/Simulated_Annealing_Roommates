#include "Annealer.h"

Annealer::Annealer(std::array<int,40000> studentsCompatibility){
    this->studentsCompatibility = studentsCompatibility;
    AssignRooms();
}
void Annealer::AssignRooms(){
    for (int i = 0; i < numberOfRooms*studentsPerRoom; i++){
        rooms[i] = i;
    }
    for (int currentRooom = 0; currentRooom < numberOfRooms; currentRooom++)
    {
        CalculateFitnessScore(currentRooom);
    }
    

}
void Annealer::outputResult(){
    std::ofstream outputFile;
    outputFile.open("data/output.txt");
    for (int i = 0; i < numberOfRooms; i++){
        outputFile << "Room " << i << ": " << rooms[i*studentsPerRoom] 
        << " " << rooms[i*studentsPerRoom +1] 
        << " " << rooms[i*studentsPerRoom +2]
        << " " << rooms[i*studentsPerRoom +3]
        << " Fitness Score: " << fitnessScore[i] << "\n";
    }
    
}

void Annealer::CalculateFitnessScore(int roomCounter){
    int score = 0;
    for (int i = 0; i < studentsPerRoom; i++){
            for (int j = i+1; j < studentsPerRoom; j++)
            {
                int row = roomCounter*studentsPerRoom+i;
                int col = roomCounter*studentsPerRoom + j;
                score += studentsCompatibility[rooms[row]*200 + rooms[col]];
            }
    }
    fitnessScore[roomCounter] = score;
}
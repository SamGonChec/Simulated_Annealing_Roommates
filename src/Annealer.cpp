#include "Annealer.h"

Annealer::Annealer(std::array<int,40000> studentsCompatibility){
    this->studentsCompatibility = studentsCompatibility;
    srand(time(NULL));
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
    
    randomSwap(rooms);
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
                int row = roomCounter*studentsPerRoom + i;
                int col = roomCounter*studentsPerRoom + j;
                score += studentsCompatibility[rooms[row]*200 + rooms[col]];
            }
    }
    fitnessScore[roomCounter] = score;
}
void Annealer::randomSwap(std::array<int, 200> rooms){
    int randomRoom = rand() % 50+0;
    int secondRandomRoom = rand() % 50+0;
    if (randomRoom != secondRandomRoom)
    {    
        int randomStudent = rand() % 4+0;
        int secondRandomStudent = rand() % 4+0;
        int temp = studentsCompatibility[rooms[randomRoom]];
        
        //testing If I have calculated the right students
        std::cout<< "Room: " << randomRoom << " Student in such room: " << rooms[(randomRoom*studentsPerRoom) + randomStudent] << " Room: " << secondRandomRoom << " Student in second such room:" << rooms[(secondRandomRoom*studentsPerRoom) + secondRandomStudent] << std::endl;
    }
}
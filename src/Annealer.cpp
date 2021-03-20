#include "Annealer.h"

Annealer::Annealer(std::array<int,40000> studentsCompatibility){
    this->studentsCompatibility = studentsCompatibility;
    temperature = beginningTemperature * reduction;
    acceptedChanges;
    srand(time(NULL));
    AssignRooms();
}
void Annealer::AssignRooms(){
    for (int i = 0; i < numberOfRooms*studentsPerRoom; i++){
        rooms[i] = i;
    }
    for (int currentRooom = 0; currentRooom < numberOfRooms; currentRooom++)
    {
        fitnessScore[currentRooom] = CalculateFitnessScore(currentRooom);
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

int Annealer::CalculateFitnessScore(int roomCounter){
    int score = 0;
    for (int i = 0; i < studentsPerRoom; i++){
            for (int j = i+1; j < studentsPerRoom; j++)
            {
                int row = roomCounter*studentsPerRoom + i;
                int col = roomCounter*studentsPerRoom + j;
                score += studentsCompatibility[rooms[row]*200 + rooms[col]];
            }
    }
    return score;
}
void Annealer::randomSwap(){
    int randomRoom = rand() % 50+0;
    int secondRandomRoom = rand() % 50+0;
    int initialFitness, randomFitness;
    initialFitness +=  CalculateFitnessScore(rooms[randomRoom]);
    initialFitness +=  CalculateFitnessScore(rooms[secondRandomRoom]);


    if (randomRoom != secondRandomRoom)
    {    
        int randomStudent = rand() % 4+0;
        int secondRandomStudent = rand() % 4+0;
        int temp = rooms[(randomRoom*studentsPerRoom) + randomStudent];
        rooms[(randomRoom*studentsPerRoom) + randomStudent] = rooms[(secondRandomRoom*studentsPerRoom) + secondRandomStudent];
        rooms[(secondRandomRoom*studentsPerRoom) + secondRandomStudent] = temp;
        
        randomFitness += CalculateFitnessScore(rooms[randomRoom]);
        randomFitness += CalculateFitnessScore(rooms[secondRandomRoom]);
        if(acceptSwap(initialFitness,randomFitness)){
            fitnessScore[randomRoom] = CalculateFitnessScore(rooms[randomRoom]);
            fitnessScore[secondRandomRoom] = CalculateFitnessScore(rooms[secondRandomRoom]);
        }
    }
    else
        randomSwap();
}
bool Annealer::acceptSwap(int initial, int final){
    double probabilityAccept = 0.0;
    int floor = 0;
    int ceiling = 1;
    double randomToAccept = ((double)rand() / (RAND_MAX));
    if(final <= initial){
        return true;
    }
    probabilityAccept = exp((initial-final)/temperature);
    if (probabilityAccept >= randomToAccept)
    {
        return true;
    }
    
    return false;
}
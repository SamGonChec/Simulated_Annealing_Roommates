#include "Annealer.h"

Annealer::Annealer(std::array<int,40000> studentsCompatibility){
    this->studentsCompatibility = studentsCompatibility;
    temperature = beginningTemperature;
    swapAttempts =0;
    acceptedChanges = 0;
    bestComp = 0;
    worstComp = 0;
    averageComp = 0;
    solved = false;
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
    outputFile << "Beginning Temperature: " << beginningTemperature << "\n"
            << "Reduction: " << reduction << "\n"
            << "Best Compatibility: " << bestComp << "\n"
            << "Worst Compatibility: " << worstComp << "\n"
            << "Average Compatibility: " << averageComp << "\n";
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
void Annealer::RandomSwap(){
    int randomRoom = rand() % 50+0;
    int secondRandomRoom = rand() % 50+0;
    int initialFitness = 0;
    int randomFitness = 0;
    initialFitness +=  CalculateFitnessScore(randomRoom);
    initialFitness +=  CalculateFitnessScore(secondRandomRoom);

    //std::cout << initialFitness;
    if (randomRoom == secondRandomRoom)
    {    
        RandomSwap();
    }
    else {
        int randomStudent = rand() % 4+0;
        int secondRandomStudent = rand() % 4+0;
        int temp = rooms[(randomRoom*studentsPerRoom) + randomStudent];
        rooms[(randomRoom*studentsPerRoom) + randomStudent] = rooms[(secondRandomRoom*studentsPerRoom) + secondRandomStudent];
        rooms[(secondRandomRoom*studentsPerRoom) + secondRandomStudent] = temp;
        swapAttempts++;
        randomFitness += CalculateFitnessScore(randomRoom);
        randomFitness += CalculateFitnessScore(secondRandomRoom);
        if(AcceptSwap(initialFitness,randomFitness)){
            acceptedChanges++;
            fitnessScore[randomRoom] = CalculateFitnessScore(randomRoom);
            fitnessScore[secondRandomRoom] = CalculateFitnessScore(secondRandomRoom);
        }
        else
        {
            temp = rooms[(secondRandomRoom*studentsPerRoom) + secondRandomStudent];
            rooms[(secondRandomRoom*studentsPerRoom) + secondRandomStudent] = rooms[(randomRoom*studentsPerRoom) + randomStudent];
            rooms[(randomRoom*studentsPerRoom) + randomStudent] = temp;
        }
    }
}
void Annealer::RandomUniformSwap(){
    int randomRoom = rand() % 50+0;
    int secondRandomRoom = rand() % 50+0;
    int initialFitness = 0;
    int randomFitness = 0;
    initialFitness +=  CalculateFitnessScore(randomRoom);
    initialFitness +=  CalculateFitnessScore(secondRandomRoom);
    if (randomRoom == secondRandomRoom)
    {    
        RandomUniformSwap();
    }
    else{
        int tempStudentOne, tempStudentTwo;
        tempStudentOne = rooms[(randomRoom*studentsPerRoom) + 0];
        tempStudentTwo = rooms[(randomRoom*studentsPerRoom) + 1];
        rooms[(randomRoom*studentsPerRoom) + 0] = rooms[(secondRandomRoom*studentsPerRoom) + 2];
        rooms[(randomRoom*studentsPerRoom) + 1] = rooms[(secondRandomRoom*studentsPerRoom) + 3];
        rooms[(secondRandomRoom*studentsPerRoom) + 2] = tempStudentOne;
        rooms[(secondRandomRoom*studentsPerRoom) + 3] = tempStudentTwo;
        swapAttempts++;
        randomFitness += CalculateFitnessScore(randomRoom);
        randomFitness += CalculateFitnessScore(secondRandomRoom);
        if(AcceptSwap(initialFitness,randomFitness)){
            acceptedChanges++;
            fitnessScore[randomRoom] = CalculateFitnessScore(randomRoom);
            fitnessScore[secondRandomRoom] = CalculateFitnessScore(secondRandomRoom);
        }
        else{
            tempStudentOne = rooms[(secondRandomRoom*studentsPerRoom) + 2];
            tempStudentTwo = rooms[(secondRandomRoom*studentsPerRoom) + 3];
            rooms[(secondRandomRoom*studentsPerRoom) + 2] = rooms[(randomRoom*studentsPerRoom) + 0];
            rooms[(secondRandomRoom*studentsPerRoom) + 3] = rooms[(randomRoom*studentsPerRoom) + 1];
            rooms[(randomRoom*studentsPerRoom) + 0] = tempStudentOne;
            rooms[(randomRoom*studentsPerRoom) + 1] = tempStudentTwo;
        }
    }
}
bool Annealer::AcceptSwap(int initial, int final){
    double probabilityAccept = 0.0;
    int floor = 0;
    int ceiling = 1;
    //Source: Stack overflow: random double 0-1
    double randomToAccept = floor + (double)(rand())/((double)(RAND_MAX/(ceiling - floor)));

    if(final <= initial){
        return true;
    }
    probabilityAccept = exp((initial - final)/temperature);
    if (probabilityAccept >= randomToAccept)
    {
        return true;
    }
    
    return false;
}
void Annealer::ReduceTemperature(){
    if((swapAttempts >= numToAttempt) || (acceptedChanges >= numToAccept)){
        if (acceptedChanges == 0)
        {
            std::cout<<"I have been solved? Just Kidding just for Testing";
            solved = true;
            return;
        }
        swapAttempts = 0;
        acceptedChanges = 0;
        temperature *= reduction;
    }
}
void Annealer::Solve(){
    while(!solved){
        //RandomUniformSwap();
        //RandomSwap();
        RandomPick();
        ReduceTemperature();
    }
    for (int i = 0; i < rooms.size(); i++)
    {
         SortFileAndInfo(i);   
    }
    outputResult();
}
void Annealer::RandomPick(){
    int pick = rand() % 2;
    if(pick == 0){
        RandomUniformSwap();

    }
    else
        RandomSwap();
}
void Annealer::SortFileAndInfo(int roomCounter){
    bestComp = fitnessScore[0];
    worstComp = fitnessScore[0];
    for(int i = 0; i < fitnessScore.size(); i++){
        if(fitnessScore[i] < bestComp){
            bestComp = fitnessScore[i];
        }
        if(fitnessScore[i] > worstComp){
            worstComp = fitnessScore[i];
        }
        averageComp += fitnessScore[i];
    }
    averageComp = averageComp/fitnessScore.size();
    int temp;
    for (int i = 0; i < studentsPerRoom; i++){
            for (int j = i+1; j < studentsPerRoom; j++)
            {
                if (rooms[(studentsPerRoom*roomCounter)+i] > rooms[(studentsPerRoom*roomCounter)+j])
                {
                    temp = rooms[(studentsPerRoom*roomCounter)+i];
                    rooms[(studentsPerRoom*roomCounter)+i] = rooms[(studentsPerRoom*roomCounter)+j];
                    rooms[(studentsPerRoom*roomCounter)+j] = temp;
                }
                
            }
    }
}
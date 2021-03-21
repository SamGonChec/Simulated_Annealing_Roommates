#ifndef ANNEALER_H
#define ANNEALER_H
#include <iostream>
#include <fstream>
#include <array>
#include <cstdlib>
#include <math.h>
#include <iomanip>
class Annealer{
    private:
    int numberOfStudents = 200;
    int numberOfRooms = 50;
    int studentsPerRoom = 4;
    int const numToAccept = 2000;
    int const numToAttempt = 20000;
    double reduction = 0.99;
    int beginningTemperature = 2000;
    double temperature;
    int acceptedChanges;
    int bestComp, worstComp,averageComp;
    int swapAttempts;
    bool solved;
    std::array<int,50> fitnessScore;
    std::array<int, 200> rooms;
    std::array<int, 40000> studentsCompatibility;
    
    public:
    Annealer(std:: array<int, 40000> studentsCompatibility);
    void AssignRooms();
    void outputResult();
    int CalculateFitnessScore(int roomCounter);
    void RandomSwap();
    void RandomUniformSwap();
    bool AcceptSwap(int initial, int final);
    void RandomPick();
    void Solve();
    void ReduceTemperature();
    void SortFileAndInfo(int roomCounter);
};
#endif
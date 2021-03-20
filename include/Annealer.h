#ifndef ANNEALER_H
#define ANNEALER_H
#include <iostream>
#include <fstream>
#include <array>
#include <cstdlib>
#include <math.h>
class Annealer{
    private:
    int numberOfStudents = 200;
    int numberOfRooms = 50;
    int studentsPerRoom = 4;
    int numToAccept = 2000;
    int numToAttempt = 20000;
    int reduction = 0.95;
    int beginningTemperature = 100;
    int temperature;
    int acceptedChanges;
    std::array<int,50> fitnessScore;
    std::array<int, 200> rooms;
    std::array<int, 40000> studentsCompatibility;
    public:
    Annealer(std:: array<int, 40000> studentsCompatibility);
    void AssignRooms();
    void outputResult();
    int CalculateFitnessScore(int roomCounter);
    void randomSwap();
    bool acceptSwap(int initial, int final);
    void randomPick();
    void solver();
};
#endif
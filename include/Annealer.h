#ifndef ANNEALER_H
#define ANNEALER_H
#include <iostream>
#include <fstream>
#include <array>
#include <cstdlib>
class Annealer{
    private:
    int numberOfStudents = 200;
    int numberOfRooms = 50;
    int studentsPerRoom = 4;
    std::array<int,50> fitnessScore;
    std::array<int, 200> rooms;
    std::array<int, 40000> studentsCompatibility;
    public:
    Annealer(std:: array<int, 40000> studentsCompatibility);
    void AssignRooms();
    void outputResult();
    void CalculateFitnessScore(int roomCounter);
    void randomSwap(std::array<int, 200> rooms);
};
#endif
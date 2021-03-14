#ifndef ANNEALER_H
#define ANNEALER_H
#include <iostream>
#include <array>
class Annealer{
    private:
    int numberOfStudents = 200;
    int numberOfRooms = 50;
    int studentsPerRooms = 4;
    std::array<int, 40000> studentsCompatibility;
    public:
    Annealer(std:: array<int, 40000> studentsCompatibility);

};
#endif
#ifndef MAZE_DEF
#define MAZE_DEF

#include <iostream>
#include <type_traits>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <vector>

//This is my attempt at the maze matrix problem. YOLO
class maze{
public:
    maze();
    maze(int mx, int my);
    //This constructor adds in traps
    maze(int mx, int my, int nTraps);
    maze& operator=(maze rhs);
    maze(maze&);
    ~maze();

    bool operator==(maze rhs);

    int getX(){return xSize;}
    int getY(){return ySize;}
    int getTraps(){return nTraps;}

    bool addTrap(int x, int y);
    
    friend std::ostream& operator<<(std::ostream&, const maze&);
    void calcProb(maze& rhs);
    void calcTraps(maze& large);
    maze finalCalc(int ntraps);
    maze multiply(maze rhs);
    double rowByCol(maze rhs, int, int);
    maze add(maze rhs);    

private:
    int nTraps;
    int xSize;
    int ySize;
    std::vector<std::vector<double>> holdMaze;
};

#endif
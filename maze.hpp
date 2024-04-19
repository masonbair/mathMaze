#ifndef MAZE_DEF
#define MAZE_DEF

#include <iostream>

//This is my attempt at the maze matrix problem. YOLO

template <typename T>
class maze{
public:
    maze() : holdMaze(0){};
    maze(int size);
    //This constructor adds in traps
    maze(int size, int nTraps);

    void swap(const maze<T>&);
    maze<T>& operator=(const maze<T> rhs){ swap(rhs); return *this;};

    maze(const T&);
    ~maze();

    void addTrap(int x, int y);

private:
    T **holdMaze;
};



#endif
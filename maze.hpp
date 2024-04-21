#ifndef MAZE_DEF
#define MAZE_DEF

#include <iostream>
#include <type_traits>
#include <cassert>
#include <cstdlib>
#include <iomanip>

//This is my attempt at the maze matrix problem. YOLO

template <typename T>
class maze{
public:
    maze();
    maze(int mx, int my);
    //This constructor adds in traps
    maze(int mx, int my, int nTraps);
    void swap(const maze<T>&);
    maze<T>& operator=(const maze<T> rhs){ swap(rhs); return *this;};
    maze(const T&);
    ~maze();

    int getX(){return xSize;}
    int getY(){return ySize;}
    int getTraps(){return nTraps;}

    bool addTrap(int x, int y);
    
    
    template <typename R>
    friend std::ostream& operator<<(std::ostream&, const maze<R>&);
    friend void calcProb(maze<int>&, maze<double>&);
    friend void calcTraps(maze<int>& small, maze<double>& large);
    friend void finalCalc(maze<double>& large, int ntraps);
    friend maze<double> forInverse(maze<double>& convert);
    friend double matDet(maze<double>& welp);

private:
    int nTraps;
    int xSize;
    int ySize;
    T **holdMaze;
};


template <typename T>
maze<T>::maze(){
    xSize = 0;
    ySize = 0;
    nTraps = 0;
    holdMaze = 0;
}

template <typename T>
maze<T>::maze(int mx, int my){
    ySize = my;
    xSize = mx;
    nTraps = 0;
    holdMaze = new T*[ySize];
    for(int i = 0; i < ySize; ++i){
        holdMaze[i] = new T[xSize];
    }
    if constexpr (std::is_integral_v<T>) {  
        int count = 0;
        for(int i = 0; i < ySize; ++i){
            for(int j = 0; j < xSize; ++j){
                count++;
                holdMaze[i][j] = count;
            }
        }
    }else{
        for(int i = 0; i < ySize; ++i){
            for(int j = 0; j < xSize; ++j){
                holdMaze[i][j] = 0;
            }
        }
    }
}

template <typename T>
maze<T>::maze(int mx, int my, int nTraps) : maze(mx, my){
    int x;
    int y;
    for(int i = 0; i < nTraps; ++i){
        do{
            do{
                std::cout << "Please enter a valid x location for trap " << (1+i) << " | with max size " << xSize << std::endl;
                std::cin >> x;
            }while(x > xSize && x <= 0);
            do{
                std::cout << "Please enter a valid y location for trap " << (1+i) << " | with max size " << ySize << std::endl;
                std::cin >> y;
            }while(y > ySize && y <= 0);
        }while(!addTrap(x, y));
    }
}

template <typename T>
maze<T>::maze(const T& copy){
    xSize = copy.xSize;
    ySize = copy.ySize;
    nTraps = copy.nTraps;

    holdMaze = new T*[ySize];
    for(int i = 0; i < ySize; ++i){
        holdMaze = new T[xSize];
    }

    for(int i = 0; i < ySize; ++i){
        for(int j = 0; j < xSize; ++j){
            holdMaze[ySize][xSize] = copy.holdMaze[ySize][xSize];
        }
    }
}

template <typename T>
maze<T>::~maze(){
    for(int i = 0; i < ySize; ++i){
        delete[] holdMaze[i];
    }
    delete[] holdMaze;
}

template <typename T>
void maze<T>::swap(const maze<T>& rhs){
    T* tMaze = holdMaze;
    holdMaze = rhs.holdMaze;
    rhs.holdMaze = tMaze;

    int xT = xSize;
    xSize = rhs.xSize;
    rhs.xSize = xT;

    int yT = ySize;
    ySize = rhs.ySize;
    rhs.ySize = yT;

    int nT = nTraps;
    nTraps = rhs.nTraps;
    rhs.nTraps = nT;
}

template <typename T>
bool maze<T>::addTrap(int x, int y){
    ++nTraps;
    if(holdMaze[y-1][x-1] > 0){
        holdMaze[y-1][x-1] = holdMaze[y-1][x-1] * (-1);
        return true;
    }else{
        return false;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const maze<T>& print){
    for (int i=0; i<print.ySize; i++) {
            for (int j=0; j<print.xSize; j++) {
                    os << std::setw(7) << std::setprecision(4) << print.holdMaze[i][j] << " ";
            }
            os << std::endl;
    }
    os << std::setw(7) << "----------------------------------------------" << std::endl;
    os << std::endl;
    return os;
}



#endif
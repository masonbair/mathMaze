//Main class for testing my amazing math mazeeee

#include <iostream>
#include "maze.hpp"

int main(){
    bool running = true;
    int x;
    int y;
    int traps;
    while(running = true){
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
        std::cout << "Calculating a Markov model for the probability of a mouse in a maze would get stuck" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;

        std::cout << "Please enter the x and y size of your maze: (type -1 to quit)" << std::endl;
        std::cin >> x;
        if(x == -1){
            running = false;
            break;
        }
        std::cin >> y;
        std::cout << "Please enter how many \"traps\" you would like: " << std::endl;
        std::cin >> traps;
        maze<int> mouseMaze(x, y, traps);
        std::cout << "Here is your mouse maze!" << std::endl;
        std::cout << mouseMaze;

        maze<double> beginnerMatrix(x*y, x*y);
        calcProb(mouseMaze, beginnerMatrix);
        std::cout << beginnerMatrix << std::endl;
        finalCalc(beginnerMatrix, mouseMaze.getTraps());
        //RowReduce(beginnerMatrix);
    }
}
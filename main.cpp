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
        std::cout << "Calculating a Marcov model for the probability of a mouse in a maze would get stuck" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;

        std::cout << "Please enter the x and y size of your maze: " << std::endl;
        std::cin >> x;
        std::cin >> y;
        std::cout << "Please enter how many \"traps\" you would like: " << std::endl;
        maze<bool> mouseMaze(x, y);
    }
}
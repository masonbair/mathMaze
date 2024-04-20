
#include <iostream>
#include <cmath>
#include "maze.hpp"

void calcProb(maze<int>& small, maze<double>& large){
    double prob;
    std::cout << "Inside" << std::endl;
    for(int i = 0; i < small.getX(); ++i){
        for(int j = 0; j < small.getY(); ++j){
            if(i == 0 || i == small.getX()-1){
                if(j == 0 || j == small.getY() - 1){
                    prob = 0.50;
                }else{
                    prob = 0.33;
                }
            }else if(j == 0 || j == small.getY()-1){
                prob = 0.33;
            }else{
                prob = 0.25;
            }
            //std::cout << abs(small.holdMaze[j][i])-1 << std::endl;

            //std::cout << "X Stuff" << std::endl;
            if ((i+1) % small.xSize != 1 && (i+1) % small.xSize != 0){
                //std::cout << small.holdMaze[j][i] << std::endl;
                large.holdMaze[abs(small.holdMaze[j][i+1])-1][abs(small.holdMaze[j][i])-1] = prob;
                large.holdMaze[abs(small.holdMaze[j][i-1])-1][abs(small.holdMaze[j][i])-1] = prob;
            }else if ((i+1) % small.xSize == 0){
                //std::cout << small.holdMaze[j][i] << std::endl;
                large.holdMaze[abs(small.holdMaze[j][i-1])-1][abs(small.holdMaze[j][i])-1] = prob;
            }else if ((i+1) % small.xSize == 1){
                //std::cout << small.holdMaze[j][i] << std::endl;
                large.holdMaze[(abs(small.holdMaze[j][i+1])-1)][abs(small.holdMaze[j][i])-1] = prob;
            }
            //std::cout << "Y stuff" << std::endl;
            //std::cout << small.ySize << std::endl;
            if (((j+1) % small.ySize != 1) && ((j+1) % small.ySize != 0)){
                //std::cout << small.holdMaze[j][i] << " |22 " << j << "|" << i << std::endl;
                large.holdMaze[abs(small.holdMaze[j+1][i])-1][abs(small.holdMaze[j][i])-1] = prob;
                large.holdMaze[abs(small.holdMaze[j-1][i])-1][abs(small.holdMaze[j][i])-1] = prob;
            }else if ((j+1) % small.ySize == 0){
                //std::cout << small.holdMaze[j][i] << " |OO " << j << "|" << i << std::endl;
                large.holdMaze[abs(small.holdMaze[j-1][i])-1][abs(small.holdMaze[j][i])-1] = prob;
            }else if ((j+1) % small.ySize == 1){
                //std::cout << small.holdMaze[j][i] << " |11 " << j << "|" << i << std::endl;
                //std::cout << small.holdMaze[j][i] << std::endl;
                large.holdMaze[abs(small.holdMaze[j+1][i])-1][abs(small.holdMaze[j][i])-1] = prob;
            }
           //std::cout << abs(small.holdMaze[j][i])-1 << std::endl;
            
        }
    }
}
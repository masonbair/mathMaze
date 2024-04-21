
#include <iostream>
#include <cmath>
#include "maze.hpp"

void calcProb(maze<int>& small, maze<double>& large){
    double prob;
   // std::cout << "Inside" << std::endl;
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
    calcTraps(small, large);
}

void calcTraps(maze<int>& small, maze<double>& large){
    //std::cout << "Calculating" << std::endl;
    //std::cout << small << std::endl;
    for(int i = 0; i < small.ySize; ++i){
        for(int j = 0; j < small.xSize; ++j){
            if(small.holdMaze[i][j] < 0){
                //std::cout << "HELLO" << std::endl;
                //std::cout << large.xSize << std::endl;
                for(int w = 0; w < large.xSize; ++w){
                    if(w == abs(small.holdMaze[i][j])-1){
                        //std::cout << "foudn it" << std::endl;
                        large.holdMaze[w][w] = 1;
                    }else{
                        //std::cout << "now 0" << std::endl;
                        large.holdMaze[w][abs(small.holdMaze[i][j])-1] = 0;
                    }
                }
            }
        }
    }
}

void finalCalc(maze<double>& large, int ntraps){
    maze<double> I(ntraps, ntraps);
    maze<double> Q(large.xSize - ntraps, large.xSize - ntraps);
    maze<double> R(large.xSize - ntraps, ntraps);
    std::cout << R << std::endl;
    for(int i = 0; i < ntraps; ++i){
        for(int j = 0; j < ntraps; ++j){
            if(i == j){
                I.holdMaze[i][j] = 1;
            }else{
                I.holdMaze[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < Q.xSize; ++i){
        for(int j = 0; j < Q.xSize; ++j){
            Q.holdMaze[i][j] = large.holdMaze[i][j];
        }
    }
    for(int i = 0; i < R.ySize; ++i){
        for(int j = 0; j < R.xSize; ++j){
            R.holdMaze[i][j] = large.holdMaze[large.xSize-ntraps+i][j];
        }
    }
    std::cout << "I" << std::endl;
    std::cout << I << std::endl;
    std::cout << "Q" << std::endl;
    std::cout << Q << std::endl;
    std::cout << "R" << std::endl;
    std::cout << R << std::endl;

    maze<double> combo = forInverse(Q);
    std::cout << Q << std::endl;
    double det = matDet(combo);
    std::cout << "This is the Det for Q: " << det;
    
}

maze<double> forInverse(maze<double>& convert){
    maze<double> use(convert.xSize, convert.ySize);
    for(int i = 0; i < use.xSize; ++i){
        for(int j = 0; j < use.ySize; ++j){
            if(i == j){
                use.holdMaze[i][j] = 1;
            }else{
                use.holdMaze[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < use.xSize; ++i){
        for(int j = 0; j < use.ySize; ++j){
            convert.holdMaze[j][i] = use.holdMaze[j][i] - convert.holdMaze[j][i];
        }
    }
    return convert;
}

double total = 0;

double matDet(maze<double>& welp){
    double working;
    if(welp.xSize == 3){
        std::cout << "Calculating 3x3 det" << std::endl;
        total = total + 
                (welp.holdMaze[0][0]*welp.holdMaze[1][1]*welp.holdMaze[2][2]) + 
                (welp.holdMaze[0][1]*welp.holdMaze[1][2]*welp.holdMaze[2][0]) + 
                (welp.holdMaze[0][2]*welp.holdMaze[1][0]*welp.holdMaze[2][1]) - 
                (welp.holdMaze[2][0]*welp.holdMaze[1][1]*welp.holdMaze[0][2]) -
                (welp.holdMaze[1][0]*welp.holdMaze[0][1]*welp.holdMaze[2][2]) -
                (welp.holdMaze[0][0]*welp.holdMaze[2][1]*welp.holdMaze[1][2]);
        std::cout << total << std::endl;
    }else if(welp.xSize == 2){
        total = (welp.holdMaze[0][0]*welp.holdMaze[1][1]) - (welp.holdMaze[0][1]*welp.holdMaze[1][0]);
    }else if(welp.xSize == 1){
        total = welp.holdMaze[0][0];
    }else{
        for(int i = 0; i < welp.xSize; ++i){
            maze<double> decreased(welp.xSize-1, welp.xSize-1);
            int count = 0;
            for(int j = 0; j < decreased.xSize+1; ++j){
                for(int w = 0; w < decreased.xSize; ++w){
                    if(i != j){
                        decreased.holdMaze[count/decreased.xSize][w] = welp.holdMaze[j][w+1];
                        ++count;
                    }
                }
            }
            std::cout << "Created Det Matrix" << std::endl;
            std::cout << decreased << std::endl;
            total = total + matDet(decreased);
        }
    }
    std::cout << "return total" << std::endl;
    return total;
}
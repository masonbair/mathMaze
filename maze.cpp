
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
    
    std::cout << I << std::endl;
    std::cout << Q << std::endl;
    std::cout << R << std::endl;

    RowReduce(Q);
    
}

void forInverse(maze<double>& convert){
    
}

void RowReduce(maze<double>& A)
{
    const int nrows = A.xSize; // number of rows
    const int ncols = A.ySize; // number of columns

    int lead = 0; 

    while (lead < nrows) {
        float d, m;

        for (int r = 0; r < nrows; r++) { // for each row ...
            /* calculate divisor and multiplier */
            d = A.holdMaze[lead][lead];
            m = A.holdMaze[r][lead] / A.holdMaze[lead][lead];

            for (int c = 0; c < ncols; c++) { // for each column ...
                if (r == lead)
                    A.holdMaze[r][c] /= d;               // make pivot = 1
                else
                    A.holdMaze[r][c] -= A.holdMaze[lead][c] * m;  // make other = 0
            }
        }

        lead++;
        std::cout << A << std::endl;
    }
}

#include <iostream>
#include <cmath>
#include "maze.hpp"

double total = 0;

void calcProb(maze<int>& small, maze<double>& large){
    double prob;
    double one, three;
    one = 1;
    three = 3;
   // std::cout << "Inside" << std::endl;
    for(int i = 0; i < small.getX(); ++i){
        for(int j = 0; j < small.getY(); ++j){
            if(i == 0 || i == small.getX()-1){
                if(j == 0 || j == small.getY() - 1){
                    prob = 0.50;
                }else{
                    prob = one/three;
                }
            }else if(j == 0 || j == small.getY()-1){
                prob = one/three;
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
    total = 0;
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

    maze<double> sumMaze(Q.xSize, Q.xSize);
    maze<double> multiMaze(Q.xSize, Q.xSize);
    maze<double> oneMaze(Q.xSize, Q.xSize);
    for(int i = 0; i < Q.xSize; ++i){
        for(int j = 0; j < Q.xSize; ++j){
            if(i == j){
                oneMaze.holdMaze[i][j] = 1;
            }
        }
    }
    int n = 0;
    do{
        multiMaze = Q;
        for(int i = 0; i < n; i++){
            if(n == 0) multiMaze = Q;
            else{
                multiMaze = multiply(multiMaze, Q);
                //std::cout << multiMaze << std::endl;
            } 
        }
        //std::cout << multiMaze << std::endl;
        sumMaze = add(sumMaze, multiMaze);
        //std::cout << "SUM: " << sumMaze << std::endl;
        //std::cout << sumMaze << std::endl;
        ++n;
    }while(n < 200);

    sumMaze = add(sumMaze, oneMaze);
    //std::cout << sumMaze << std::endl;

    maze<double> final = multiply(sumMaze, R);
    std::cout << final << std::endl;
    //maze<double> combo = forInverse(Q);
    //std::cout << Q << std::endl;
    //double det = matDet(combo);
    //std::cout << "This is the Det for Q: " << det;
}

maze<double> multiply(maze<double> lhs, maze<double> rhs){
    maze<double> calc(lhs.xSize, rhs.ySize);
    for(int i = 0; i < rhs.ySize; ++i){
        for(int j = 0; j < lhs.xSize; ++j){
            
            calc.holdMaze[i][j] = rowByCol(lhs, rhs, i, j);
        }
    }
    return calc;
}

double rowByCol(maze<double> lhs, maze<double> rhs, int y, int x){
    double store = 0;
    double mult = 0;
    for(int i = 0; i < lhs.xSize; ++i){
        mult = lhs.holdMaze[i][x] * rhs.holdMaze[y][i];
        //std::cout << lhs.holdMaze[y][i] << " | " << mult << " | " << rhs.holdMaze[i][x] << std::endl;
        store = store + mult;
    }
    //std::cout << store << std::endl;
    return store;
}

maze<double> add(maze<double> lhs, maze<double> rhs){
    maze<double> addTo(lhs.xSize, lhs.ySize);
    for(int i = 0; i < lhs.xSize; ++i){
        for(int j = 0; j < lhs.ySize; ++j){
            addTo.holdMaze[i][j] = lhs.holdMaze[i][j] + rhs.holdMaze[i][j];
        }
    }
    return addTo;
}

/*
maze<double> forInverse(maze<double>& convert){
    maze<double> use(convert.xSize, convert.ySize);
    for(int i = 0; i < use.xSize; ++i){
        for(int j = 0; j < use.ySize; ++j){
            if(i == j){
                use.holdMaze[i][j] = 1;
            }else
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
*/

/*
double matDet(maze<double>& welp){
    double working;
    bool pos = true;
    maze<double> decreased(welp.xSize-1, welp.xSize-1);
    if(welp.xSize == 3){
        std::cout << "Calculating 3x3 det" << std::endl;
        int stitch = 1;
        if(pos){
            stitch = 1;
            pos = false;
        }else{
            stitch = -1;
            pos = true;
        }
        total = total + ((stitch) * 
                (welp.holdMaze[0][0]*welp.holdMaze[1][1]*welp.holdMaze[2][2]) + 
                (welp.holdMaze[0][1]*welp.holdMaze[1][2]*welp.holdMaze[2][0]) + 
                (welp.holdMaze[0][2]*welp.holdMaze[1][0]*welp.holdMaze[2][1]) - 
                (welp.holdMaze[2][0]*welp.holdMaze[1][1]*welp.holdMaze[0][2]) -
                (welp.holdMaze[1][0]*welp.holdMaze[0][1]*welp.holdMaze[2][2]) -
                (welp.holdMaze[0][0]*welp.holdMaze[2][1]*welp.holdMaze[1][2]));
        std::cout << total << std::endl;
    }else if(welp.xSize == 2){
        total = (welp.holdMaze[0][0]*welp.holdMaze[1][1]) - (welp.holdMaze[0][1]*welp.holdMaze[1][0]);
    }else if(welp.xSize == 1){
        total = welp.holdMaze[0][0];
    }else{
        for(int i = 0; i < welp.xSize; ++i){
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
            (matDet(decreased));
        }
    }
    std::cout << "return total" << std::endl;
    return total;
}
*/
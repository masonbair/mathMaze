
#include <iostream>
#include <cmath>
#include "maze.hpp"

double total = 0;

maze::maze(){
    xSize = 0;
    ySize = 0;
    nTraps = 0;
}

maze::maze(int mx, int my){
    ySize = my;
    xSize = mx;
    //std::cout << xSize << " | " << ySize << std::endl;
    nTraps = 0;
    for(int i = 0; i < ySize; ++i){
        std::vector<double> vec;
        for(int j = 0; j < xSize; ++j){
            vec.push_back(0);
        }
        holdMaze.push_back(vec);
    }
}

maze::maze(int mx, int my, int traps){
    ySize = my;
    xSize = mx;
    nTraps = traps;
    int x;
    int y;
    int count = 0;
    for(int i = 0; i < ySize; ++i){
        std::vector<double> vec;
        for(int j = 0; j < xSize; ++j){
            count++;
            vec.push_back(count);
        }
        holdMaze.push_back(vec);
    }
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

maze::~maze(){
}

maze::maze(maze& copy){
    xSize = copy.xSize;
    ySize = copy.ySize;
    nTraps = copy.nTraps;
    for(std::vector<std::vector<double>>::const_iterator i = copy.holdMaze.begin(); i != copy.holdMaze.end(); ++i){
        std::vector<double> vec;
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); ++j){
            vec.push_back((*j));
        }
        holdMaze.push_back(vec);
    }
}

maze& maze::operator=(maze rhs){ 
    ySize = rhs.ySize;
    xSize = rhs.xSize;
    holdMaze = rhs.holdMaze;
    return *this;
}

bool maze::operator==(maze rhs){
    if(xSize != rhs.xSize) return false;
    if(ySize != rhs.ySize) return false;
    for(int i = 0; i < ySize; ++i){
        for(int j = 0; j < xSize; ++j){
            if(holdMaze[i][j] != rhs.holdMaze[i][j]){
                return false;
            }
        }
    }
    return true;  
}

bool maze::addTrap(int x, int y){
    if(holdMaze[y-1][x-1] > 0){
        holdMaze[y-1][x-1] = holdMaze[y-1][x-1] * (-1);
        return true;
    }else{
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const maze& print){
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

void maze::calcProb(maze& large){
    double prob;
    double one, three;
    one = 1;
    three = 3;
   // std::cout << "Inside" << std::endl;
    for(int i = 0; i < xSize; ++i){
        for(int j = 0; j < ySize; ++j){
            if(i == 0 || i == xSize-1){
                if(j == 0 || j == ySize-1){
                    prob = 0.50;
                }else{
                    prob = one/three;
                }
            }else if(j == 0 || j == ySize-1){
                prob = one/three;
            }else{
                prob = 0.25;
            }
            //std::cout << abs(holdMaze[j][i])-1 << std::endl;

            //std::cout << "X Stuff" << std::endl;
            if ((i+1) % xSize != 1 && (i+1) % xSize != 0){
                //std::cout << holdMaze[j][i] << std::endl;
                large.holdMaze[abs(holdMaze[j][i+1])-1][abs(holdMaze[j][i])-1] = prob;
                large.holdMaze[abs(holdMaze[j][i-1])-1][abs(holdMaze[j][i])-1] = prob;
            }else if ((i+1) % xSize == 0){
                //std::cout << holdMaze[j][i] << std::endl;
                large.holdMaze[abs(holdMaze[j][i-1])-1][abs(holdMaze[j][i])-1] = prob;
            }else if ((i+1) % xSize == 1){
                //std::cout << holdMaze[j][i] << std::endl;
                large.holdMaze[(abs(holdMaze[j][i+1])-1)][abs(holdMaze[j][i])-1] = prob;
            }
            //std::cout << "Y stuff" << std::endl;
            //std::cout << ySize << std::endl;
            if (((j+1) % ySize != 1) && ((j+1) % ySize != 0)){
                //std::cout << holdMaze[j][i] << " |22 " << j << "|" << i << std::endl;
                large.holdMaze[abs(holdMaze[j+1][i])-1][abs(holdMaze[j][i])-1] = prob;
                large.holdMaze[abs(holdMaze[j-1][i])-1][abs(holdMaze[j][i])-1] = prob;
            }else if ((j+1) % ySize == 0){
                //std::cout << holdMaze[j][i] << " |OO " << j << "|" << i << std::endl;
                large.holdMaze[abs(holdMaze[j-1][i])-1][abs(holdMaze[j][i])-1] = prob;
            }else if ((j+1) % ySize == 1){
                //std::cout << holdMaze[j][i] << " |11 " << j << "|" << i << std::endl;
                //std::cout << holdMaze[j][i] << std::endl;
                large.holdMaze[abs(holdMaze[j+1][i])-1][abs(holdMaze[j][i])-1] = prob;
            }
           //std::cout << abs(holdMaze[j][i])-1 << std::endl;
            
        }
    }
    calcTraps(large);
}

void maze::calcTraps(maze& large){
    //std::cout << "Calculating";
    //std::cout << small << std::endl;
    for(int i = 0; i < ySize; ++i){
        for(int j = 0; j < xSize; ++j){
            if(holdMaze[i][j] < 0){
                //std::cout << "HELLO" << std::endl;
                //std::cout << large.xSize << std::endl;
                for(int w = 0; w < large.xSize; ++w){
                    if(w == abs(holdMaze[i][j])-1){
                        //std::cout << "foudn it" << std::endl;
                        large.holdMaze[w][w] = 1;
                    }else{
                        //std::cout << "now 0" << std::endl;
                        large.holdMaze[w][abs(holdMaze[i][j])-1] = 0;
                    }
                }
            }
        }
    }
}

maze maze::finalCalc(int ntraps){
    std::cout << "Calculating";
    std::flush(std::cout);
    total = 0;
    maze I(ntraps, ntraps);
    maze Q(xSize - ntraps, xSize - ntraps);
    maze R(xSize - ntraps, ntraps);
    
    for(int i = 0; i < ntraps; ++i){
        for(int j = 0; j < ntraps; ++j){
            if(i == j){
                I.holdMaze[i][j] = 1;
            }else{
                I.holdMaze[i][j] = 0;
            }
        }
    }
    std::cout << ".";
    std::flush(std::cout);
    for(int i = 0; i < Q.xSize; ++i){
        for(int j = 0; j < Q.xSize; ++j){
            Q.holdMaze[i][j] = holdMaze[i][j];
        }
    }
    std::cout << ".";
    std::flush(std::cout);
    for(int i = 0; i < R.ySize; ++i){
        for(int j = 0; j < R.xSize; ++j){
            R.holdMaze[i][j] = holdMaze[xSize-ntraps+i][j];
        }
    }
    std::cout << ".";
    std::flush(std::cout);
    maze sumMaze(Q.xSize, Q.xSize);
    maze multiMaze(Q.xSize, Q.xSize);
    maze oneMaze(Q.xSize, Q.xSize);
    for(int i = 0; i < Q.xSize; ++i){
        for(int j = 0; j < Q.xSize; ++j){
            if(i == j){
                oneMaze.holdMaze[i][j] = 1;
            }
        }
    }
    int n = 0;
    do{
        if(n%20 == 0){
            std::cout << ".";
            std::flush(std::cout);
        } 
        multiMaze = Q;
        for(int i = 0; i < n; i++){
            if(n == 0) multiMaze = Q;
            else{
                multiMaze = multiMaze.multiply(Q);
            } 
        }
        sumMaze = sumMaze.add(multiMaze);
        ++n;
    }while(n < 200);
    std::cout << ".";
    std::flush(std::cout);
    sumMaze = sumMaze.add(oneMaze);

    maze final = sumMaze.multiply(R);
    std::cout << ". Finished" << std::endl;

    //THis is the print out statements of the final results calculated from the program
    std::cout << "Probability Matrix" << std::endl;
    std::cout << *this << std::endl;
    std::cout << "I" << std::endl;
    std::cout << I << std::endl;
    std::cout << "Q" << std::endl;
    std::cout << Q << std::endl;
    std::cout << "R" << std::endl;
    std::cout << R << std::endl;
    std::cout << "Probabilty of what trap the mouse will land in when starting in a specific position" << std::endl;
    std::cout << final << std::endl;
    //----------------------------------------------------------------------------------

    return final;
}


maze maze::multiply(maze rhs){
    maze calc(xSize, rhs.ySize);
    for(int i = 0; i < rhs.ySize; ++i){
        for(int j = 0; j < xSize; ++j){
            
            calc.holdMaze[i][j] = rowByCol(rhs, i, j);
        }
    }
    return calc;
}

double maze::rowByCol(maze rhs, int y, int x){
    double store = 0;
    double mult = 0;
    for(int i = 0; i < xSize; ++i){
        mult = holdMaze[i][x] * rhs.holdMaze[y][i];
        //std::cout << lhs.holdMaze[y][i] << " | " << mult << " | " << rhs.holdMaze[i][x] << std::endl;
        store = store + mult;
    }
    //std::cout << store << std::endl;
    return store;
}

maze maze::add(maze rhs){
    maze addTo(xSize, ySize);
    for(int i = 0; i < xSize; ++i){
        for(int j = 0; j < ySize; ++j){
            addTo.holdMaze[i][j] = holdMaze[i][j] + rhs.holdMaze[i][j];
        }
    }
    return addTo;
}

//
//  Linear System.hpp
//  Linesr Equasions
//
//  Created by Aleksey Shatilov on 21/02/2019.
//  Copyright © 2019 Aleksey Shatilov. All rights reserved.
//

#ifndef Linear_System_hpp
#define Linear_System_hpp

#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

typedef std::vector<std::vector<double>> mat;
typedef std::vector<double> vec;

class LinearSystem{
private:
    mat A;
    vec F;
    
    bool solved;
    std::vector<int> swaps;
    
    void calcKoeff();
public:
    static double epsilon;
    
    LinearSystem(mat a, vec f);
    vec solveSystem();
    
    void setA(mat a);
    void setF(vec f);
};

//Utility functions
void printMat(mat m);
void printVec(vec v);
void swapRows(mat &A, int k1, int k2);
void swapElems(vec &V, int k1, int k2);
void precisionCheck(vec &V, const double e);


//Special functions
double calcCondOne(mat m);
double calcCondInf(mat m);
mat revMat(mat m);
double calcDet(mat m);
double matNormOne(mat m);
double matNormInf(mat m);

#endif /* Linear_System_hpp */

//
//  Linear System.cpp
//  Linesr Equasions
//
//  Created by Aleksey Shatilov on 21/02/2019.
//  Copyright © 2019 Aleksey Shatilov. All rights reserved.
//

#include "Linear System.hpp"

//Class methods
LinearSystem::LinearSystem(mat a, vec f){
    this->A = a;
    this->F = f;
    solved = false;
}
void LinearSystem::setA(mat a){
    this->A = a;
    this->solved = false;
    this->swaps.clear();
}
void LinearSystem::setF(vec f){
    this->F = f;
}
void LinearSystem::calcKoeff(){
    //Transform matrix
    for (int i = 0; i < A.size() - 1; i++){
        //finding max element in colomn
        int maxInd = i;
        for (int j = i; j < A.size(); j++){
            if (fabs(A[j][i]) > fabs(A[maxInd][i]))
                maxInd = j;
        }
        //swap rows
        swapRows(A, i, maxInd);
        swapElems(F, i, maxInd);
        this->swaps.push_back(maxInd);
        
        //Transform rows
        for (int row = i + 1; row < A.size(); row++){
            double k = -1 * A[row][i] / A[i][i];
            
            for (int j = i; j < A.size(); j++){
                A[row][j] += (A[i][j] * k);
            }
            F[row] += (F[i] * k);
            //saving koeffs
            A[row][i] = k;
        }
    }
}
vec LinearSystem::solveSystem(){
    try{
        if (!this->solved){
            this->calcKoeff();
            //Check for row full of zeroes
            bool zeroLine = true;
            for (int i = 0; i < A.size(); i++){
                zeroLine = true;
                for (int j = 0; j < A.size(); j++){
                    if (fabs(A[i][j]) >= LinearSystem::epsilon) //not equal zero
                        zeroLine = false;
                }
                if (zeroLine)
                    break;
            }
            if (zeroLine)
                throw std::logic_error("No solution");
        }
        else {
            //Recalculate F
            for (int i = 0; i < swaps.size(); i++)
                swapElems(F, i, swaps[i]);


            std::vector<double> koeffs;
            for (int i = 1; i < A.size(); i++){
                for (int j = 0; j < i; j++){
                    koeffs.push_back(A[i][j]);
                }
            }
            int k = 0;
            for (int i = 0; i < F.size() - 1; i++){
                for (int j = i + 1; j < F.size(); j++){
                    F[j] += (F[i] * koeffs[k]);
                    k++;
                }
            }
        }
        //Calculate solution
        vec solution;
        solution.push_back(F.back() / A[A.size() - 1].back());
        for (int i = (int)A.size() - 2; i >= 0; i--){
            //Calculate Xi
            int kx = 0;
            double xi = F[i];
            for (int j = (int)A.size() - 1; j > i; j--){
                xi -= (A[i][j] * solution[kx]);
                kx++;
            }
            xi /= A[i][i];
            solution.push_back(xi);
        }
        
        reverse(solution.begin(), solution.end());
        precisionCheck(solution,LinearSystem::epsilon);
        this->solved = true;
        return solution;
    }
    catch(std::logic_error e){
        std::cout << e.what() << std::endl;
    }
    return vec();
}

//Constants
double LinearSystem::epsilon = 0.001;

//Utility functions
void printMat(mat m){
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < m.size(); i++){
        for (int j = 0; j < m[i].size(); j++){
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
};
void printVec(vec v){
    std::cout << "Vector: ";
    for (int i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
};
void swapRows(mat &A, int k1, int k2){
    if (k1 != k2){
        for (int i = 0; i < A.size(); i++){
            double z = A[k1][i];
            A[k1][i] = A[k2][i];
            A[k2][i] = z;
        }
    }
};
void swapElems(vec &V, int k1, int k2){
    if (k1 != k2){
        double z = V[k1];
        V[k1] = V[k2];
        V[k2] = z;
    }
};
void precisionCheck(vec &V, const double e){
    for (auto it = V.begin(); it != V.end(); it++)
        if (fabs(*it) < e)
            *it = 0;
};


//Special functions
double calcCondOne(mat m){
    mat A1 = revMat(m);
    
    double n1 = matNormOne(m);
    double n2 = matNormOne(A1);
    
    return n1 * n2;
};
double calcCondInf(mat m){
    mat A1 = revMat(m);
    
    double n1 = matNormInf(m);
    double n2 = matNormInf(A1);
    
    return n1 * n2;
};
mat revMat(mat m){
    mat revM;
    
    double det = calcDet(m);
    if (det != 0){
        mat algDop;
        
        if (algDop.size() > 2){
            for (int i = 0; i < m.size(); i++){
                vec tV;
                for (int j = 0; j < m.size(); j++){
                    
                    mat tmp;
                    for (int k = 0; k < m.size(); k++){
                        vec str;
                        if (k != i){
                            for (int n = 0; n < m.size(); n++){
                                if (n != j)
                                    str.push_back(m[n][k]);
                            }
                            tmp.push_back(str);
                        }
                    }
                    
                    double elem = pow(-1, i+j) * calcDet(tmp);
                    tV.push_back(elem);
                    
                }
                
                algDop.push_back(tV);
            }
        }else{
            algDop = {
                {m[1][1], -1 * m[0][1]},
                {-1 * m[1][0], m[0][0]}
            };
        }
        
        for (int i = 0; i < algDop.size(); i++){
            for (int j = 0; j < algDop.size(); j++){
                algDop[i][j] /= det;
            }
        }
       
        revM = algDop;
    }
    
    return revM;
};
double calcDet(mat m){
    if (m.size() > 2){
        double det = 0;
        for (int k = 0; k < m.size(); k++){
            int c = k % 2 == 0 ? 1 : -1;
            
            mat next;
            for (int i = 1; i < m.size(); i++){
                vec tmp;
                for (int j = 0; j < m.size(); j++){
                    if (j != k)
                        tmp.push_back(m[i][j]);
                }
                next.push_back(tmp);
            }
            det += (c * m[0][k] * calcDet(next));
        }
        return det;
    }
    else {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
};
double matNormOne(mat m){
    vec sums;
    for (int j = 0; j < m.size(); j++){
        double s = 0;
        for (int i = 0; i < m.size(); i++){
            s += fabs(m[i][j]);
        }
        sums.push_back(s);
    }
    
    double max = sums[0];
    for (int i = 1; i < sums.size(); i++){
        if (sums[i] > max)
            max = sums[i];
    }
    
    return max;
};
double matNormInf(mat m){
    vec sums;
    for (int i = 0; i < m.size(); i++){
        double s = 0;
        for (int j = 0; j < m.size(); j++){
            s += fabs(m[i][j]);
        }
        sums.push_back(s);
    }
    
    double max = sums[0];
    for (int i = 1; i < sums.size(); i++){
        if (sums[i] > max)
            max = sums[i];
    }
    
    return max;
};

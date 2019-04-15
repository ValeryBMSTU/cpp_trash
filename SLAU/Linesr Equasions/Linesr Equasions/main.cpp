//
//  main.cpp
//  Linesr Equasions
//
//  Created by Aleksey Shatilov on 14/02/2019.
//  Copyright © 2019 Aleksey Shatilov. All rights reserved.
//

#include "Linear_System.hpp"

mat A =
{
    {-52.4, 0, -0.57, 4.73},
    {0.12, 32.4, 9.05, 0.49},
    {0, 5.88, -175, 2.43},
    {-5.01, -2.43, 1.87, -76.2}
};

vec F =
{
    -1309.17,
    224.13,
    97.4,
    -7800.62
};

mat A2 =
{
    {6.695, 0.275, 0.004, 0.837},
    {-45.12, -4.374, 2.994, -5.64},
    {-45.12, -4.375, 2.995, -5.64},
    {-38.28, -0.732, -1.03, -4.786}
};

vec F2 =
{
    8.747,
    6.57,
    6.595,
    -71.8560
};

int main() {
    
    LinearSystem sys(A,F);
    
    vec solution = sys.solveSystem();
    if (!solution.empty())
        printVec(solution);
    
    sys.setA(A2);
    sys.setF(F2);
    
    vec solution2 = sys.solveSystem();
    if (!solution2.empty())
        printVec(solution2);
    
    std::cout << std::endl << "----Matrix A----" << std::endl;
    std::cout << "Cond One = " << calcCondOne(A) << std::endl;
    std::cout << "Cond Inf = " << calcCondInf(A) << std::endl;
    
    std::cout << std::endl << "----Matrix A2----" << std::endl;
    std::cout << "Cond One = " << calcCondOne(A2) << std::endl;
    std::cout << "Cond Inf = " << calcCondInf(A2) << std::endl;

    return 0;
}

#ifndef RANDOM_POINTS_CPP
#define RANDOM_POINTS_CPP

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <random> 
#include <ctime>  

using namespace std;

set<pair<int,int>> generateRandomPoints(int n) {
    set<pair<int,int>> randomPoints;

    random_device rd; 
    mt19937 gen(rd()); 

    uniform_int_distribution<> dis(-10000, 10000);

    while ((int)randomPoints.size() < n) {
        int x = dis(gen);
        int y = dis(gen);
        randomPoints.insert({x, y});
    }

    return randomPoints;
}

#endif

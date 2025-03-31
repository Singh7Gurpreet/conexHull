#ifndef JARVIS_MARCH_ALGORITHM
#define JARVIS_MARCH_ALGORITHM

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

#include "./Orientation.cpp"

using namespace std;

/*
* @brief This function implements the Jarvis March algorithm.

    1. Find the leftmost coordinate from the given set of points
        1.1 Can use the smallest x coordinate to find that the smaller it is 
            the more left it is.
    2. Now take that point which we name that as onConvexHull and other point
       named nextPoint and iterate through the vector of points.
       2.1 Calculate orientation in this way onConvexHull, nextPoint and 
           i point which is in interation and calclate its orientation
           if we get counter clockwise it means that i point can be connected
           with onConvexHull and cover that nextPoint too. And assign that i
           to nextPoint so that it may find other one.
       2.2 If it is collinear it is better to include the farthest point from
           onConvexHull such that it becomes the minimum number of points.
    3. If we found the next point equals to firstPoint then simple break
       and return the result.
*/

set<pair<int,int>> jarvisMarchFunction(vector<pair<int,int> >& points) {
    
    pair<int,int> onConvexHull = *min_element(points.begin(), points.end(),
                                [&](const auto &a, const auto &b) {
                                    return a.first < b.first; 
                                }),
                  firstPoint = onConvexHull;
    set<pair<int,int>> hull;

    while(true) {
        hull.insert(onConvexHull);
        pair<int,int> nextPoint;
        nextPoint = points[0];
        for(auto& i : points) {
            Orientation temp = calculateOrientation(onConvexHull, nextPoint,i);
            if(temp == CCW ) {
                nextPoint = i;
            } else if(temp == CL && 
                hull.count(i) == 0 && 
                distance(onConvexHull, i) > distance(onConvexHull, nextPoint)) {
            nextPoint = i;
        }         
    }
        if(nextPoint == firstPoint) break;
        onConvexHull = nextPoint;
    }
    return hull;
}

#endif
#ifndef JARVIS_MARCH_ALGORITHM
#define JARVIS_MARCH_ALGORITHM

#include <iostream>
#include <vector>
#include <util.h>
#include <algorithm>
#include<set>

using namespace std;

enum Orientation {CCW = -1, CL = 0, CW = 1};

/**
 * @brief Calculates the euclidean distance between two points a and b in the 2D plane.
 *
 */

int distance(pair<int,int> a, pair<int,int> b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return dx * dx + dy * dy;
}


/**
 * @brief Determines the orientation of three points a, b, and c in the 2D plane.
 *
 * Given three points in order (a → b → c), this function calculates their orientation
 * using the 2D cross product of vectors AB and AC
 *
 *     cross = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)
 *
 * ### Geometric Meaning:
 * - If cross > 0 → the turn from a to b to c is counterclockwise
 * - If cross < 0 → the turn is clockwise
 * - If cross = 0 → the points are collinear
 *
 * ### Intuition:
 * This is linked to the right-hand rule:  
 * curl your fingers from AB to AC — if the thumb points **out of the plane, it’s counterclockwise;  
 * if it points into the plane, it's clockwise.  
 * If there’s no curl, the points lie on a straight line (collinear).
 *
 * This method avoids slope calculations and is more robust for orientation.
 */


 Orientation calculateOrientation(pair<int,int> a, pair<int,int> b, pair<int,int> c) {
    int cross = (b.first - a.first) * (c.second - a.second) -
                (b.second - a.second) * (c.first - a.first);

    if (cross > 0) return CCW;
    else if (cross < 0) return CW;
    else return CL;
}

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
// This is key part of all the algorithms that we are working on.

#ifndef ORIENTATION_CPP
#define ORIENTATION_CPP

#include <utility>
using namespace std;

enum Orientation {CCW = -1, CL = 0, CW = 1};

/**
 * @brief Calculates the euclidean distance between two points a and b in the 2D plane.
 * have not used square root over that becuase it is computationally expensive
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

#endif
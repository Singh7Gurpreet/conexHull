#ifndef QUICK_HULL_ALGORITHM_CPP
#define QUICK_HULL_ALGORITHM_CPP

#include<vector>
#include<iostream>
#include<util.h>
#include<set>

#include "./Orientation.cpp"

using namespace std;

set<pair<int,int>> result;
/*
  Developer Note: Thought Process Behind This Function

  Initially, I was stuck figuring out how to calculate the perpendicular distance 
  from point C to the line AB. My first idea was to use the basic triangle formula:
  calculate the area of triangle ABC using (1/2 * base * height), and then derive 
  the height (perpendicular distance) by dividing the area by the base length.

  But I hit a wall when I tried to figure out the exact point on line AB where the 
  perpendicular from C lands — calculating that projection point introduced complexity 
  with floating-point precision and vector projections.

  While looking for better ways to solve this, I came across a method on Stack Overflow 
  using the cross product. That's when everything clicked.

  I realized:
    - The magnitude of the 2D cross product of vectors AB and AC gives the area 
      of the parallelogram formed by them.
    - Since the base (AB) is fixed, this area is directly proportional to the 
      perpendicular distance from C to line AB.
    - The beauty of this approach is that we don’t need to compute actual distance 
      or projection — we just compare the absolute cross product values.

  This let me:
    - Skip square roots (no sqrt needed),
    - Skip division (no 1/2 or base length),
    - And still find the farthest point by comparing relative distances efficiently.

  It’s the first time I really appreciated the practical power of vectors and cross products
  in geometry and algorithms — super clean and elegant!
*/

/**
 * Computes a value proportional to the perpendicular distance 
 * from point C to the line formed by points A and B in 2D space.
 *
 * Geometric Explanation:
 * -----------------------
 * - Let AB be the vector from point A to B.
 * - Let AC be the vector from point A to C.
 * - The magnitude of the 2D cross product of AB and AC gives the
 *   area of the parallelogram formed by these two vectors.
 *
 *   |AB × AC| = |AC.x * AB.y - AC.y * AB.x|
 *
 * - Since the base (vector AB) remains constant for all comparisons,
 *   this cross product value can be directly used to compare how 
 *   "far" each point C is from the line AB.
 *
 * - This avoids any use of square roots or division, making it both 
 *   efficient and elegant using only vector arithmetic.
 *
 * Parameters:
 * - A: pair<int, int> representing point A (x₁, y₁)
 * - B: pair<int, int> representing point B (x₂, y₂)
 * - C: pair<int, int> representing point C (x₃, y₃)
 *
 * Returns:
 * - An integer value proportional to the perpendicular distance from point C to line AB.
 */

int perpendicularDistanceFromLine(pair<int, int> A, pair<int, int> B, pair<int, int> C) {
    pair<int, int> AC = {C.first - A.first, C.second - A.second};
    pair<int, int> AB = {B.first - A.first, B.second - A.second};

    int crossProductMagnitude = abs(AC.first * AB.second - AC.second * AB.first);
    return crossProductMagnitude;
}


void quickHullRec(vector<pair<int,int>>& points, pair<int,int> lineA, pair<int,int> lineB, Orientation side) {
  int maxIndex = -1;
  int maxDist = -1e9;

  for(int i = 0; i < points.size(); i++) {
    auto c = points[i];
    int dist = perpendicularDistanceFromLine(lineA,lineB,c);
    Orientation orn = calculateOrientation(lineA,lineB,c);
    if(dist > maxDist && orn == side) {
      maxIndex = i;
      maxDist = dist;
    }
  }

  if(maxIndex == -1) {
    result.insert(lineA);
    result.insert(lineB);
    return;
  }
  auto C = points[maxIndex];

  quickHullRec(points, lineA, C ,side);
  quickHullRec(points, C, lineB,side);
}

set<pair<int,int>> quickHull(vector<pair<int,int>>& points) {
  pair<int,int> max_on_x_axis = {-1e9,-1e9}, min_on_x_axis = {1e9,1e9};

  for(auto i : points) {
    if(max_on_x_axis.first < i.first) {
      max_on_x_axis = i;
    } else if(max_on_x_axis.first == i.first && max_on_x_axis.second < i.second) {
      max_on_x_axis = i;
    }

    if(min_on_x_axis.first > i.first) {
      min_on_x_axis = i;
    } else if(min_on_x_axis.first == i.first && min_on_x_axis.second > i.second) {
      min_on_x_axis = i;
    }
  }

  quickHullRec(points,min_on_x_axis,max_on_x_axis,CCW);
  quickHullRec(points,min_on_x_axis,max_on_x_axis,CW);

  return result;
}

#endif
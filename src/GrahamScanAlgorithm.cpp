#ifndef GRAHAM_SCAN_ALGORITHM
#define GRAHAM_SCAN_ALGORITHM

#include<iostream>
#include<vector>
#include<stack>
#include<utility>
#include<set>

#include "./Orientation.cpp"

// global variable that stores the point with minimum y-coordinates
// in case of ties select with one with leftmost x coordinate
pair<int,int> p0;


/*
  Comparator for Sorting Points by Polar Angle (Relative to p0)

  Purpose:
  --------
  In convex hull algorithms like Graham’s Scan, we need to sort all points
  based on the polar angle they make with a reference point `p0`.
  This comparator achieves that without using trigonometry or floating point
  operations, which can lead to precision issues.

  Why `p0`?
  ---------
  We select the point with the lowest y-coordinate (and lowest x if tie)
  as `p0` because it must be part of the convex hull and serves as a fixed 
  anchor to sort all other points.

  How it Works:
  -------------
  - Instead of calculating actual angles, we use the orientation of the 
    triplet (p0, a, b) using vector cross product:
    
        Orientation o = calculateOrientation(p0, a, b);

  - If orientation is:
      → CCW (Counter-Clockwise): `a` comes before `b` (smaller angle)
      → CW  (Clockwise):         `b` comes before `a` (larger angle)
  
  - If points `a` and `b` are collinear with `p0`, we break the tie by 
    comparing their distance from p0 — we keep the closer one first.

  This avoids any use of `atan2`, `cos`, or floating point angles.

  Summary:
  --------
  This is an elegant trick using vector cross product to sort points
  by angle **purely using integer arithmetic**, and it's highly robust
  for geometric algorithms.
*/

struct Comparator {
  bool operator()(pair<int,int>& a, pair<int,int>& b) {
    Orientation calculated = calculateOrientation(p0,a,b);

    if(calculated == CCW) return true;
    else if(calculated == CW) return false;
    // if it is collinear
    else {
      return distance(p0,a) < distance(p0,b);
    }
  }
};

int findMin(vector<pair<int,int>>& points) {
  int minY = 1e9, minX = 1e9;
  int index = 0;

  for(int j = 0; j < points.size(); j++) {
    auto i = points[j];
    if(i.second < minY) {
      minY = i.second;
      minX = i.first;
      index = j;
    } else if(i.second == minY) {
      if(minX > i.first) {
        minY = i.second;
        minX = i.first;
        index = j;
      }
    }
  }
  return index;
}

pair<int,int> nextToTop(stack<pair<int,int>>& buffer) {
  
  if(buffer.size() < 2) return {};

  auto temp = buffer.top();
  buffer.pop();
  auto returnVal = buffer.top();  
  buffer.push(temp);

  return returnVal;
}

set<pair<int,int>> GrahamScanFunction(vector<pair<int,int>>& points) {
  int t = findMin(points);
  p0 = points[t];
  swap(points[0], points[t]);

  sort(points.begin() + 1, points.end(), Comparator());

  vector<pair<int,int>> uniquePoints;
  uniquePoints.push_back(points[0]);

  /*
  Handling Collinear Points in Convex Hull Construction

  In convex hull algorithms (like Graham’s Scan), we sort points by angle and 
  then remove unnecessary points. When we encounter multiple points that lie 
  on the same line from the reference point (i.e., collinear points), we need 
  to decide which one to keep.

  If three points p0, p1, p2 are collinear (i.e., angle p0->p1 == p0->p2), then:
    - Keeping the point that lies "between" the other two (the inner one) 
      would exclude the outermost edge, which is needed in the convex hull.
    - The inner point is not part of the convex polygon boundary, so it should be ignored.

  We skip over all intermediate collinear points and keep only the outermost one.
  This ensures that the convex hull wraps tightly around the shape, and no flat edges
  get clipped short.

  :) Love how simple geometry rules fix complex bugs!
*/
  for (int i = 1; i < points.size(); ++i) {
    while (i < points.size() - 1 &&
           calculateOrientation(p0, points[i], points[i + 1]) == CL)
      i++;
    uniquePoints.push_back(points[i]);
  }

  if (uniquePoints.size() < 3)
    return {};

  stack<pair<int,int>> hull;
  hull.push(uniquePoints[0]);
  hull.push(uniquePoints[1]);
  hull.push(uniquePoints[2]);

  for (int i = 3; i < uniquePoints.size(); ++i) {
    while (hull.size() > 1 &&
           calculateOrientation(nextToTop(hull), hull.top(), uniquePoints[i]) != CCW)
      hull.pop();
    hull.push(uniquePoints[i]);
  }

  set<pair<int,int>> result;
  while (!hull.empty()) {
    result.insert(hull.top());
    hull.pop();
  }

  return result;
}


#endif
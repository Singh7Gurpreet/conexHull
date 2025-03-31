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


// Here we needed a comparator for sorting points 
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

  // if lies on same line then we should keep the outermost
  // becuase we know that keeping inner most wont be a part
  // of a convex hull so thats why we kept the outer most
  // in case of collinears
  // :)

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
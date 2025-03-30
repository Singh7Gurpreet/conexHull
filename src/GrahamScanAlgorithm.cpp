#ifndef GRAHAM_SCAN_ALGORITHM
#define GRAHAM_SCAN_ALGORITHM

#include<iostream>
#include<vector>
#include<stack>
#include<util.h>
#include "JarvisMarchAlgorithm.cpp"

// global variable that stores the point with minimum y-coordinates
pair<int,int> p0;


// Here we needed a comparator for sorting points 
struct Comparator {
  bool operator()(pair<int,int>& a, pair<int,int>& b) {
    Orientation calculated = calculateOrientation(p0,a,b);

    if(calculated == CW) return false;
    else if(calculated == CCW) return true;
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
  swap(points[0],points[t]);
  sort(points.begin()+1,points.end(),Comparator());
  stack<pair<int,int>> hull;
  for(auto i : points) {
    while(hull.size() > 1 && calculateOrientation(nextToTop(hull),hull.top(),i) != CW) {
      hull.pop();
    }
    hull.push(i);
  }

  set<pair<int,int>> result;
  while(!hull.empty()) {
    result.insert(hull.top());
    hull.pop();
  }

  return result;
}

#endif
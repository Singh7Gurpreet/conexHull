#include "src/JarvisMarchAlgorithm.cpp"

/*
  We have worked on the famous Convex Hull problem, 
  where we are given various points on a 2D plane 
  (though it can also be extended to n dimensions), 
  and we have to find the smallest convex polygon 
  that contains all the given points.

  Real-life Analogy:
  Imagine several nails spiked into a wooden board. 
  Now, if you take a rubber band and stretch it around
  all the nails, then release it, the rubber band will
  snap around the outermost nails, forming a convex polygon.
  Convex polygon is a polygon which as its interior angle
  less than 180 degrees. This shape is known as the convex hull.

  Other one is that, let's suppose you are working in a forest 
  department and you got some new kind of land which has very
  rare trees and they are randomly placed on different locations
  but in a same place and you have been given task to put fence 
  around them such that the least fence is used and all trees are
  covered in that fence. Given that fence can be placed in any polygon
  shape.
*/

int main() {
  vector<pair<int,int>> points;
  int n;
  cout << "Enter the number of points you want to enter:\n";
  cin >> n;
  cout << "Enter it in this format in promp: x y\n";
  for(int i = 0; i < n; i++) {
    int x,y;
    cin >> x >> y;
    points.emplace_back(x,y);
  }

  auto result = jarvisMarchFunction(points);
  for(auto i : result) {
    cout << i.first << " " << i.second << endl;
  }
  return 0;
}
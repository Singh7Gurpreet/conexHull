#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <set>
#include "src/JarvisMarchAlgorithm.cpp"
#include "src/GrahamScanAlgorithm.cpp"
#include "src/RandomPoints.cpp"
#include "src/QuickHullAlgorithm.cpp"

using namespace std;
using namespace chrono;

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

void execute(std::vector<std::pair<int, int>>& points, int choice) {
  std::set<std::pair<int, int>> hullPoints;
  std::chrono::high_resolution_clock::time_point timeA;
  std::chrono::high_resolution_clock::time_point timeB;
  std::chrono::milliseconds duration(0);

  switch (choice) {
      case 1:
          std::cout << "\nUsing QuickHull...\n";
          timeA = std::chrono::high_resolution_clock::now();
          hullPoints = quickHull(points);
          timeB = std::chrono::high_resolution_clock::now();
          duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA);
          std::cout << "QuickHull took " << duration.count() << " ms\n";
          break;

      case 2:
          std::cout << "\nUsing Graham Scan...\n";
          timeA = std::chrono::high_resolution_clock::now();
          hullPoints = GrahamScanFunction(points);
          timeB = std::chrono::high_resolution_clock::now();
          duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA);
          std::cout << "Graham Scan took " << duration.count() << " ms\n";
          break;

      case 3:
          std::cout << "\nUsing Jarvis March...\n";
          timeA = std::chrono::high_resolution_clock::now();
          hullPoints = jarvisMarchFunction(points);
          timeB = std::chrono::high_resolution_clock::now();
          duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA);
          std::cout << "Jarvis March took " << duration.count() << " ms\n";
          break;

      case 4:
          std::cout << "\nBenchmarking All Algorithms...\n";

          timeA = std::chrono::high_resolution_clock::now();
          quickHull(points);
          timeB = std::chrono::high_resolution_clock::now();
          std::cout << "QuickHull took " << std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA).count() << " ms\n";

          timeA = std::chrono::high_resolution_clock::now();
          jarvisMarchFunction(points);
          timeB = std::chrono::high_resolution_clock::now();
          std::cout << "Jarvis March took " << std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA).count() << " ms\n";

          timeA = std::chrono::high_resolution_clock::now();
          GrahamScanFunction(points);
          timeB = std::chrono::high_resolution_clock::now();
          std::cout << "Graham Scan took " << std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA).count() << " ms\n";

          return;
          break;

      default:
          std::cout << "\nInvalid choice. Defaulting to QuickHull...\n";
          timeA = std::chrono::high_resolution_clock::now();
          hullPoints = quickHull(points);
          timeB = std::chrono::high_resolution_clock::now();
          duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeB - timeA);
          std::cout << "QuickHull took " << duration.count() << " ms\n";
          break;
  }

  std::cout << "\nConvex Hull Points:\n";
  for (const auto& pt : hullPoints) {
      std::cout << "(" << pt.first << ", " << pt.second << ")\n";
  }
}

void randomChoice(int choice) {
  int input;
  do {
  cout << "Enter the number of points you want to test\n";
  cin >> input;
  } while(input <= 0);

  set<pair<int,int>> points = generateRandomPoints(input);
  vector<pair<int,int>> pts(points.begin(),points.end());

  execute(pts,choice);
}

void userChoice(int choice) {
  vector<pair<int, int>> points;
  int n;
  cout << "\nEnter the number of points: ";
  cin >> n;
  cout << "Enter each point in the format \"x y\":\n";
  points.reserve(n);
  for (int i = 0; i < n; i++)
  {
    int x, y;
    cin >> x >> y;
    points.emplace_back(x, y);
  }
  execute(points,choice);
}

int main()
{
  
  int n;

  cout << "Choose an algorithm for Convex Hull:\n";
  cout << "  1. QuickHull\n";
  cout << "  2. Graham Scan\n";
  cout << "  3. Jarvis March\n";
  cout << "  4. Wants to see time taken by all of them\n";
  cout << "Enter your choice (1, 2, 3 or 4): ";
  int choice;
  cin >> choice;

  cout << "Choose option for input\n";
  cout << "1. User choice\n";
  cout << "2. Random points\n";
  int option;
  cin >>option;

  switch (option) 
  {
  case 1:
    userChoice(choice);
    break;
  case 2:
    randomChoice(choice);
  default:
    break;
  }
  return 0;
}
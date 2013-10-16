#include "Point.hh"
#include <cmath>
#include <iostream>
using namespace std;

// Function for calculating the area of a 3D triangle
double computeArea(Point &a, Point &b, Point &c) 
{
    double s = (a.distanceTo(b) + b.distanceTo(c) + c.distanceTo(a))/2.0;

    return sqrt(s * (s - a.distanceTo(b)) * (s - b.distanceTo(c)) * (s - c.distanceTo(a)));
}

int main() 
{
    double x, y, z;

    cout << "Please enter the x, y, and z coordinates of the first point: " << endl;
    cin >> x >> y >> z;

    // First point
    Point first = Point(x, y, z);

    cout << "Please enter the x, y, and z coordinates of the second point: " << endl;
    cin >> x >> y >> z;

    // Second point
    Point second = Point(x, y, z);

    cout << "Please enter the x, y, and z coordinates of the third point: " << endl;
    cin >> x >> y >> z;

    // Third point
    Point third = Point(x, y, z);

    // The area of the triangle
    double area = computeArea(first, second, third);

    cout << "The area is: " << area << endl;

    return 0;
}

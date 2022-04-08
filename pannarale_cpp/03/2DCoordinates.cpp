#include <iostream>
#include <cmath>
using namespace std;

class Point {
    private:
        double x, y;

        // regular constructor
        Point(double x1, double x2) {
            x = x1;
            y = x2;
        };

    public:
        // polar(radius, angle)
        static Point Polar(double r, double theta) {
            return Point(r*cos(theta), r*sin(theta));
        }
          
        // cartesian(x, y)
        static Point Cartesian(double x, double y) {
            return Point(x,y);
        }
     
        // utility function to display coordinates
        void display() {
            cout << "x :: " << x <<endl;
            cout << "y :: " << y <<endl;
        }
};
  
  
int main() {
    // Two coordinates
    double x1 = 5.7, x2 = 1.2;

    // Polar coordinates
    Point pp1 = Point::Polar(x1, x2);
    cout << "polar coordinates \n";
    pp1.display();

    // Polar coordinates
    Point pp2 = Point::Polar(x2, x1);
    cout << "polar coordinates \n";
    pp2.display();
      
    // Cartesian coordinates
    Point pr1 = Point::Cartesian(x1, x2);
    cout << "rectangular coordinates \n";
    pr1.display();

    // Cartesian coordinates
    Point pr2 = Point::Cartesian(x2, x1);
    cout << "rectangular coordinates \n";
    pr2.display();

    return 0;
}

#include <iostream>
#include <cmath>
#include "Vector3D.h"

//CONSTRUCTORS
Vector3D::Vector3D(){
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

Vector3D::Vector3D(const double& x, const double& y, const double& z){
    x_ = x;
    y_ = y;
    z_ = z;
}

//SETTERS
void Vector3D::setX(const double& x){x_ = x;}
void Vector3D::setY(const double& y){y_ = y;}
void Vector3D::setZ(const double& z){z_ = z;}

//GETTERS
double Vector3D::X() const {return x_;}
double Vector3D::Y() const {return y_;}
double Vector3D::Z() const {return z_;}

//other getters
double Vector3D::magnitude() const {
    return sqrt(x_*x_ + y_*y_ + z_*z_);
}

double Vector3D::theta() const {
    //particular case: vector in the polar plane (x,y,0)
    if (z_ == 0) {return M_PI/2;}
    else{
        return acos(z_/magnitude());
    }
}

double Vector3D::phi() const {
    //special cases in which arctg(y/x) doesn't exists
    if (x_ == 0 && y_ > 0){return M_PI/2;}
    else if (x_ == 0 && y_ < 0){return - M_PI/2;}
    //atan gives values in the interval [-PI/2;PI/2], so I have to specify whenever add a phase PI
    else if (x_ < 0 && y_ > 0){return atan(y_/x_) + M_PI;}
    else if (x_ < 0 && y_ < 0){return atan(y_/x_) + M_PI;}
    else return atan(y_/x_);
}

//OTHER MEMBER FUNCTIONS
double Vector3D::ScalarProduct(const Vector3D& vec) const {
    return (x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_);
}

Vector3D Vector3D::VectorProduct(const Vector3D& vec) const {
    //three component of the new vector
    double a,b,c;
    a = y_*vec.z_ - z_*vec.y_;
    b = z_*vec.x_ - x_*vec.z_;
    c = x_*vec.y_ - y_*vec.x_;
    return Vector3D(a,b,c);
}

//angle between two vectors -->> Bad function, !
double Vector3D::angle(const Vector3D& vec) const {
    //special case:
    if (magnitude() == 0 || vec.magnitude() == 0){
        std::cout << "La magnitudine di un vettore è 0, non si può definire un angolo!" << std::endl;
        return 0;
    }
    //acos() gives return values betveen 0 and PI.
    return acos(Vector3D::ScalarProduct(vec)/vec.magnitude()/magnitude());
}

//OVERLOAD OPERATORS
Vector3D Vector3D::operator=(const Vector3D& rhs) const {
    return Vector3D(rhs.x_, rhs.y_, rhs.z_);
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const{
	double x = x_ + rhs.x_;
	double y = y_ + rhs.y_;
    double z = z_ + rhs.z_;
	return Vector3D(x,y,z);
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const{
	double x = x_ - rhs.x_;
	double y = y_ - rhs.y_;
    double z = z_ - rhs.z_;
	return Vector3D(x,y,z);
}

Vector3D Vector3D::operator*(const double& rhs) const {
    double x = rhs*x_;
	double y = rhs*y_;
    double z = rhs*z_;
	return Vector3D(x,y,z);
}

Vector3D Vector3D::operator/(const double& rhs) const {
    if(rhs == 0.){
        std::cout << "Errore: non puoi dividere per zero, babbeo." << std::endl;
        return Vector3D(0,0,0);
    }
    double x = x_/rhs;
	double y = y_/rhs;
    double z = z_/rhs;
	return Vector3D(x,y,z);
}
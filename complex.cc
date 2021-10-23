#include <iostream>
#include <cmath>
#include "complex.h"


//constructors
complex::complex(){
	x_ = 0;
	y_ = 0;
}
complex::complex(const double& k){
    x_ = k;
    y_ = 0;
}
complex::complex(const double& x, const double& y){
	x_ = x;
	y_ = y;
}

//setters
void complex::setX(const double& x){x_ = x;}
void complex::setY(const double& y){y_ = y;}

//getters
double complex::re() const {return x_;}
double complex::im() const {return y_;}
double complex::mag() const {return sqrt(x_*x_+y_*y_);}
//this function doesn't work. We have to check whenever we have to add a pi phase or not.
double complex::phase() const {
	if(x_ == 0 && y_ > 0) {return M_PI/2;}
	else if(x_ == 0 && y_ < 0) {return -M_PI/2;}
	else return atan(y_/x_);
}

void complex::print(){
		std::cout << re() << " +i" << im()
		<< " o, in forma complessa, " << mag() << "*exp(i" << phase() << ")" << std::endl;
	}

//overloaded operators
complex complex::operator+(const complex& rhs) const{
	double x = x_ + rhs.x_;
	double y = y_ + rhs.y_;
	return complex(x,y);
}

complex complex::operator-(const complex& rhs) const{
	double x = x_ - rhs.x_;
	double y = y_ - rhs.y_;
	return complex(x,y);
}

complex complex::operator*(const complex& rhs) const{
	double x = x_*rhs.x_ - y_*rhs.y_;
	double y = x_*rhs.y_ + y_*rhs.x_;
	return complex(x,y);
}

complex complex::operator/(const complex& rhs) const{
	double x = x_*rhs.x_ + y_*rhs.y_;
	double y = y_*rhs.x_ - x_*rhs.y_;
	x /= (rhs.mag()*rhs.mag());
	y /= (rhs.mag()*rhs.mag());
	return complex(x,y);
}

//overloaded operators with selfreturn
const complex& complex::operator=(const complex& rhs){
	x_ = rhs.x_;
	y_ = rhs.y_;
	return *this;
}

const complex& complex::operator+=(const complex& rhs){
	x_ += rhs.x_;
	y_ += rhs.y_;
	return *this;
}

const complex& complex::operator-=(const complex& rhs){
	x_ -= rhs.x_;
	y_ -= rhs.y_;
	return *this;
}

//AGGIUSTARE!!!
const complex& complex::operator*=(const complex& rhs){
	x_ = (x_)*(rhs.x_) - (y_)*(rhs.y_);
	y_ = (x_)*(rhs.y_) + (y_)*(rhs.x_);
	return *this;
}

//AGGIUSTARE!!!
const complex& complex::operator/=(const complex& rhs){
    x_ = (x_)*(rhs.x_) + (y_)*(rhs.y_);
	y_ = (y_)*(rhs.x_) - (x_)*(rhs.y_);
	x_ /= (rhs.mag()*rhs.mag());
	y_ /= (rhs.mag()*rhs.mag());
	return *this;
}
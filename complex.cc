#include <iostream>
#include <cmath>
#include "complex.h"

class complex{
	public:

	//constructors
	complex(){
		x_ = 0;
		y_ = 0;
	}
	complex(const double& k){
        x_ = k;
        y_ = 0;
    }
	complex(const double& x, const double& y){
		x_ = x;
		y_ = y;
	}
	
	//setters
	void setX(const double& x){x_ = x;}
	void setY(const double& y){y_ =  y;}

	//getters
	double re() const {return x_;}
    double im() const {return y_;}
    double mag() const {return sqrt(x_*x_+y_*y_);}
	double phase() const {
		if(x_ == 0) return M_PI/2;
		else return atan(y_/x_);
	}

    //operators
    complex operator+(const complex& rhs) const;
    complex operator-(const complex& rhs) const;
    complex operator*(const complex& rhs) const;
    complex operator/(const complex& rhs) const;

    const complex& operator=(const complex& rhs);
    const complex& operator+=(const complex& rhs);
    const complex& operator-=(const complex& rhs);
    const complex& operator*=(const complex& rhs);
    const complex& operator/=(const complex& rhs);

	void print(){
		std::cout << re() << " +i" << im() <<
		std::cout << mag() << "*exp(i" << phase() << ")" << std::endl;
	}

	private:
	double x_;
	double y_;
};

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
	x = x/(rhs.x_*rhs.x_ + rhs.y_*rhs.y_);
	y = y/(rhs.x_*rhs.x_ + rhs.y_*rhs.y_);
	return complex(x,y);
}


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

const complex& complex::operator*=(const complex& rhs){
	x_ = x_*rhs.x_ - y_*rhs.y_;
	y_ = x_*rhs.y_ + y_*rhs.x_;
	return *this;
}

const complex& complex::operator/=(const complex& rhs){
    x_ = x_*rhs.x_ + y_*rhs.y_;
	y_ = y_*rhs.x_ - x_*rhs.y_;
	x_ = x_/(rhs.mag()*rhs.mag());
	y_ = y_/(rhs.mag()*rhs.mag());
	return *this;
}
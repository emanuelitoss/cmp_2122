
#include <iostream>
#include <cmath>

class complex{
	public:

	//constructors
	complex();
	complex(const double&);
	complex(const double&, const double&);
	
	//setters
	void setX(const double&);
	void setY(const double&);

	//getters
	double re() const;
    double im() const;
    double mag() const;
	double phase() const;

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

	void print();

	private:
	double x_;
	double y_;
};
/*
complex complex::operator+(const complex& rhs) const;

complex complex::operator-(const complex& rhs) const;

complex complex::operator*(const complex& rhs) const;

complex complex::operator/(const complex& rhs) const;


const complex& complex::operator=(const complex& rhs);

const complex& complex::operator+=(const complex& rhs);

const complex& complex::operator-=(const complex& rhs);

const complex& complex::operator*=(const complex& rhs);

const complex& complex::operator/=(const complex& rhs);
*/
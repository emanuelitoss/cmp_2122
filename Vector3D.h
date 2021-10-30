#include <iostream>
#include <cmath>

class Vector3D{
	public:

	//constructors
	Vector3D();
	//Vector3D(const double&);
	Vector3D(const double&, const double&, const double&);
	
	//setters
	void setX(const double&);
	void setY(const double&);
	void setZ(const double&);

	//getters
	double X() const;
	double Y() const;
	double Z() const;
    double magnitude() const;
	double theta() const;
	double phi() const;

    //operators
	double angle(const Vector3D& rhs) const;
    double ScalarProduct(const Vector3D& rhs) const;
    Vector3D VectorProduct(const Vector3D& rhs) const;
	
	const Vector3D& operator=(const Vector3D& rhs);
    Vector3D operator+(const Vector3D& rhs) const;
    Vector3D operator-(const Vector3D& rhs) const;
	//Vector3D operator=(const Vector3D& rhs) const;
	
    Vector3D operator*(const double& rhs) const;
    Vector3D operator/(const double& rhs) const;


	void print();

	private:
	double x_;
	double y_;
	double z_;
};
/*
Vector3D Vector3D::angle(const Vector3D& rhs) const;

Vector3D Vector3D::ScalarProduct(const Vector3D& rhs) const;

Vector3D Vector3D::VectorProduct(const Vector3D& rhs) const;

Vector3D Vector3D::operator+(const Vector3D& rhs) const;

Vector3D Vector3D::operator-(const Vector3D& rhs) const;

const Vector3D& Vector3D::operator=(const Vector3D& rhs);

Vector3D Vector3D::operator*(const double& rhs) const;

Vector3D Vector3D::operator/(const double& rhs) const;
*/
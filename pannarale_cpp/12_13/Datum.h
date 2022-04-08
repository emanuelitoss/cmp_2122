#ifndef Datum_h
#define Datum_h
#include <iostream>

class Datum {
  public:
    //Constructors
    Datum();
    Datum(double x, double y);
    Datum(const Datum& datum);

    //Destructor
    ~Datum() { };

    //Getters
    double value() const { return value_; }
    double error() const { return error_; }

    //Setters
    void setValue(double v) { value_ = v; }
    void setError(double e) { error_ = e; }
    static void setTolerance(double val) { tolerance_ = val; };

    //Other methods
    double significance() const;
    void print() const;
    Datum sum( const Datum& rhs ) const;

    //Operator overloading
    Datum operator+(const Datum& rhs) const;
    const Datum& operator+=(const Datum& rhs);
    const Datum& operator=(const Datum& rhs);
    bool operator==(const Datum& rhs) const;
    bool operator<(const Datum& rhs) const;
    Datum operator*(const Datum& rhs) const;
    Datum operator/(const Datum& rhs) const;
    Datum operator*(const double& rhs) const;
    //Will use global functions
    friend Datum operator*(const double& lhs, const Datum& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Datum& rhs);

  private:
    double value_;
    double error_;
    static double tolerance_;
};
#endif

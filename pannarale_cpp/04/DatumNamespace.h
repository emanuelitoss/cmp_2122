// DatumNamespace.h
// header file of the Datum class

#ifndef Datum_h // if Datum_h is not defined, then...
#define Datum_h // ...define the new variable datum_h
namespace rome{
  namespace teaching{
    class Datum {
      public:
        // constructor
        Datum(double val, double error);
    
        // getters
        double value();
        double error();
    
        // setters
        void setValue(double value);
        void setError(double error);
    
        void print();
    
      private:
        double value_;
        double error_;
    };
  } // namespace teaching
} //namespace rome
#endif // end of ifndef block of code


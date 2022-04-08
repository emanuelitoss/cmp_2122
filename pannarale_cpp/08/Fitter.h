#ifndef Fitter_h_
#define Fitter_h_
namespace analysis {
  class Fitter {
    public:
      enum Status { Successful=0, 
                    Failed,
                    Problems };

      Fitter() { };

      Status fit() {
        return Successful;
      }
    private:
  }; // class Fitter
} //namespace
#endif

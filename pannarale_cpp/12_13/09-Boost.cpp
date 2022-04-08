#include "TLorentzVector.h"
#include "TMath.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {

  // Create the B meson 4-momentum in the LAB frame
  TLorentzVector p4_B;
  double m_B = 5.279; // GeV
  double p_B = 0.300; // GeV
  // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
  p4_B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B+m_B*m_B));

  // Create the pion 4-momentum in the B rest frame
  double m_pi = 0.140; // GeV
  double p_pi = 0.100; // GeV
  TLorentzVector p4_pi;
  // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
  p4_pi.SetPxPyPzE(0, p_pi, 0, sqrt(m_pi*m_pi+p_pi*p_pi));

  /*
     Print to screen 4-momenta as we have them
     As a reminder:
     * Hadron colliders measure physical momenta in terms of momentum transverse
       to the beam axis (z-axis); the TRANSVERSE MOMENTUM is denoted by p_T
     * p_x = p_T * cos(phi) 
       p_y = p_T * sin(phi) 
       p_z = m_T * sinh(eta) 
       E = m_T * cosh(eta) 
       where m_T = sqrt(p_T^2 + m^2) is the TRANSVERSE MASS
     * eta is the PSEUDORAPIDITY: eta = -ln[tan(theta/2)]; differences in eta
       are Lorentz invariants under boosts along the longitudinal axis
  */
  cout << "--> LAB p4 B: " << endl;
  p4_B.Print();
  cout << "--> CoM p4 pi*: " << endl;
  p4_pi.Print();

  // The TLorentzVector class provides the Beta() and Gamma() methods to
  // compute the boost parameters: we compare them to their definitions
  cout << "--> boost parameters of B reference frame" << endl;
  cout << "\t beta: " << p4_B.Beta() << "\t"
       << "\t p/E:" << p4_B.P()/p4_B.E() << "\n"
       << "\t gamma: " << p4_B.Gamma() << "\t"
       << "\t E/m: " << p4_B.E()/m_B << "\n"
       << "\t beta*gamma: " << p4_B.Beta()*p4_B.Gamma() << "\t"
       << "\t p/m: " << p_B/m_B
       << endl;

  // Boost parameters of the B frame in the LAB frame can be accessed
  // with the BoostVector method
  cout << "--> boost vector of the B meson" << endl;
  p4_B.BoostVector().Print();

  // Let's boost the pion to the LAB frame
  cout << "--> now boost the pion to LAB" << endl;
  p4_pi.Boost(p4_B.BoostVector());
  cout << "--> LAB p4 pi: " << endl;
  p4_pi.Print();

  // Exit
  return 0;
}

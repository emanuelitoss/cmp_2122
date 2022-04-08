//DatumConst.cpp

#include "DatumConst.h"

int main() {

  Datum d1(-67.03, 32.12 );
  const Datum d2(-67.03, 32.12 );

  d1.print("datum");

  d2.print("const datum");

  return 0;
}

- app1.cpp: use TRandom3 to create data, then fill 1D histograms and save them to pdf
- app2.cpp: similar to app1.cpp but with improved histogram settings
- app3.cpp: similar to app2.cpp but stores data to txt file and creates a figure with 2 panels; uses vector<Datum>

Syntax to compile and link an executable:
    g++ -o app app.cpp `$ROOTSYS/bin/root-config --libs --cflags`

app3.cpp needs the Datum class header and implementation.
You can avoid duplicating Datum.h and Datum.cc with symbolic links:
    ln -s ../Datum.h Datum.h
    ln -s ../Datum.cc Datum.cc
    g++ -o app3 app3.cpp Datum.cc `$ROOTSYS/bin/root-config --libs --cflags`

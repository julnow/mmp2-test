#!/bin/bash

#uruchamianie skryptu dla czastek
#protony
root -q -b "hist1.c(1,1)" 1> mmp2_wyniki.txt
root -q -b "hist1.c(1,-1)" 1>> mmp2_wyniki.txt
root -q -b "hist1.c(1,0)" 1>> mmp2_wyniki.txt
#piony
root -q -b "hist1.c(101,1)" 1>> mmp2_wyniki.txt
root -q -b "hist1.c(101,-1)" 1>> mmp2_wyniki.txt
root -q -b "hist1.c(101,0)" 1>> mmp2_wyniki.txt
#kaony
root -q -b "hist1.c(106,1)" 1>> mmp2_wyniki.txt
root -q -b "hist1.c(106,-1)" 1>> mmp2_wyniki.txt
root -q -b "hist1.c(106,0)" 1>> mmp2_wyniki.txt
#ladunki
root -q -b "hist2.c(1)" 1>> mmp2_wyniki.txt
root -q -b "hist2.c(-1)" 1>> mmp2_wyniki.txt
root -q -b "hist2.c(0)" 1>> mmp2_wyniki.txt

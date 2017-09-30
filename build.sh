#!/bin/bash
mkdir build bin
cd build
cmake ..
cd ..
make -C build diffraction

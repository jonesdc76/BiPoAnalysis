#!/bin/bash
root -b -q .x BiPoPlotter.C+\(0,0,1,1\)
root -b -q .x BiPoPlotter.C+\(0,1,1,0\)
root -b -q .x BiPovsTime.C+\(0,0\)
root -b -q .x BiPovsTime.C+\(0,1\)

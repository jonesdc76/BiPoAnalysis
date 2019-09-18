#!/bin/bash
CLASS=BPsim
sed -i -e 's/TChain \* chain/chain/' ${CLASS}.h
sed -i -e 's/public :/public:\n   TChain         \*chain;    \/\/!TChain/' ${CLASS}.h

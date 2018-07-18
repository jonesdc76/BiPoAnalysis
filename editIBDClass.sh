#!/bin/bash
sed -i -e 's/TChain \* chain/chain/' IBDon.h
sed -i -e 's/public :/public:\
   TChain         \*chain;    \/\/!TChain/' IBDon.h
sed -i -e 's/TChain \* chain/chain/' IBDoff.h
sed -i -e 's/public :/public:\
   TChain         \*chain;    \/\/!TChain/' IBDoff.h

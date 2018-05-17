#!/bin/bash
sed -i -e 's/TChain \* chain/chain/' BP.h
sed -i -e 's/public :/public:\n   TChain         \*chain;    \/\/!TChain/' BP.h

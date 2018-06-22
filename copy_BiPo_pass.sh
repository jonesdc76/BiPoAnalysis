#!/bin/bash
release=Phys_Neutrino_v2 #name of physics release
wright_dir=prospect/data/Analyzed #directory where bipo data exists

scp -r Yale:${wright_dir}/${release} ${BIPO_OUTDIR}/


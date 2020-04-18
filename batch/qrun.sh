#!/bin/sh
#$ -cwd
#$ -j y
#PBS -l cput=48:00:00
#PBS -l walltime=48:00:00
#PBS -q lfi-medium
#PBS -V

export PATH=$PATH:/cvmfs/alice.cern.ch/bin
alienv enter VO_ALICE@AliPhysics::vAN-20181201-1

echo PATH=$PATH
echo LD_LIBRARY_PATH=$LD_LIBRARY_PATH

WDIR=$PBS_O_WORKDIR/job001
mkdir -pv $WDIR
cd $WDIR
echo "Current directory: "`pwd`", hostname "`hostname`
rm -rf *
export PYTHIA8DATA=$ALICE_ROOT/PYTHIA8/pythia8210/xmldoc
time ../../pythia_chic2.exe 10000 >& pythia_chic2.log
ls -al

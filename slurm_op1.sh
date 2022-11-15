#!/bin/bash

usage() {
    echo $0 exeName numThreads numRepeats
}

if [[ $# -ne 3 ]]; then
    usage
    exit -1
fi

ulimit -s unlimited #allow max stacksize
  
EXE=$1
THREADS=$2
REPEATS=$3
X=`basename $EXE`
FILE=${X%%.exe}-`date +%d%b%Y_%H%M%S`.txt
echo best of $REPEATS for executable $EXE on $THREADS threads
echo output file\: $FILE

    export OMP_NUM_THREADS=$THREADS
    echo running on $OMP_NUM_THREADS threads
    for k in `seq 1 $REPEATS`; do
	./${EXE} input_64_512_960.dat kernel_5.dat output_64_512_960x5.dat
    done  > $FILE




#!/bin/bash

for i in 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
do
    rm -rf qrun_tmp.sh
    cat qrun.sh | sed "s|job001|job0${i}|g" > qrun_tmp.sh
    chmod +x qrun_tmp.sh
    qsub qrun_tmp.sh
    sleep 10
    ls -ld job*
done

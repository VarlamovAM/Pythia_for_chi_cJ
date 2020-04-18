#!/bin/bash

for i in 01 02
do
    rm -rf qrun_tmp.sh
    cat qrun.sh | sed "s|job001|job0${i}|g" > qrun_tmp.sh
    chmod +x qrun_tmp.sh
    qsub qrun_tmp.sh
    sleep 10
    ls -ld job*
done

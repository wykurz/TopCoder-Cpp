#!/usr/bin/env bash
function run_make
{
    echo "Make! "`date '+%X'`
    make > blog 2>&1
}
function continue
{
    if python waitfile.py
    then
       return 0
    fi
    return 1
}
run_make
while continue; do
    run_make
done

#!/usr/bin/env bash
function run_make
{
    echo "Make!"
    make > blog 2>&1
}
function continue
{
    echo "Continue!"
    if python waitfile.py
    then
       return 0
    fi
    return 1
}
while continue; do
    run_make
done

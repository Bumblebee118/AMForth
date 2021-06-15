#!/bin/bash

avg_time() {
    local -i n=$1
    local foo real
    shift
    (($# > 0)) || return;
    { read foo real;} < <(
        { time -p for((;n--;)){ "$@" &>/dev/null ;} ;} 2>&1
    )
    echo "$(bc -l <<< "$real / $n;" )"
}

res1=$(avg_time 5 ../cmake-build-release/AMForth gcd.fs)
echo "GCD AMForth Avg: $res1 seconds"
res2=$(avg_time 5 gforth gcd.fs)
echo "GCD Gforth Avg: $res2 seconds"
factor=$( bc -l <<< "$res1 / $res2")
echo "AMForth execution time was $factor times longer"

echo "-----------------"

res1=$(avg_time 5 ../cmake-build-release/AMForth fib_rec.fs)
echo "Fibonacci Recursive AMForth Avg: $res1 seconds"
res2=$(avg_time 5 gforth fib_rec_gforth.fs)
echo "Fibonacci Recursive Gforth Avg: $res2 seconds"
factor=$( bc -l <<< "$res1 / $res2;")
echo "AMForth execution time was $factor times longer"

echo "-----------------"

res1=$(avg_time 5 ../cmake-build-release/AMForth bubblesort.fs)
echo "BubbleSort AMForth Avg: $res1 seconds"
res2=$(avg_time 5 gforth bubblesort.fs)
echo "BubbleSort Gforth Avg: $res2 seconds"
factor=$( bc -l <<< "$res1 / $res2;")
echo "AMForth execution time was $factor times longer"
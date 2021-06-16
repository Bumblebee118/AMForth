#!/bin/bash

avg_time() {
    local -i n=$1
    local foo real
    shift
    (($# > 0)) || return;
    { read foo real;} < <(
        { time -p for((;n--;)){ "$@" &>/dev/null ;} ;} 2>&1
    )
    echo "$(bc -l <<< "scale=3; $real / $n" )"
}

res1=$(avg_time 5 ../cmake-build-release/AMForth gcd.fs)
echo "GCD AMForth Avg: $res1 seconds"
res2=$(avg_time 5 gforth gcd.fs)
echo "GCD Gforth Avg: $res2 seconds"
factor=$( bc -l <<< "scale=3; $res1 / $res2")
echo "AMForth execution time was $factor times longer"

echo "-----------------"

res1=$(avg_time 5 ../cmake-build-release/AMForth fib_rec.fs)
echo "Fibonacci Recursive AMForth Avg: $res1 seconds"
res2=$(avg_time 5 gforth fib_rec_gforth.fs)
echo "Fibonacci Recursive Gforth Avg: $res2 seconds"
factor=$( bc -l <<< "scale=3; $res1 / $res2")
echo "AMForth execution time was $factor times longer"

echo "-----------------"

res1=$(avg_time 5 ../cmake-build-release/AMForth bubble_sort.fs)
echo "BubbleSort AMForth Avg: $res1 seconds"
res2=$(avg_time 5 gforth bubble_sort_orig.fs)
echo "BubbleSort Gforth Avg: $res2 seconds"
factor=$( bc -l <<< "scale=3; $res1 / $res2")
echo "AMForth execution time was $factor times longer"

echo "-----------------"

res1=$(avg_time 5 ../cmake-build-release/AMForth matrix_mult.fs)
echo "Matrix Multiplication AMForth Avg: $res1 seconds"
res2=$(avg_time 5 gforth matrix_mult_orig.fs)
echo "Matrix Multiplication Gforth Avg: $res2 seconds"
factor=$( bc -l <<< "scale=3; $res1 / $res2")
echo "AMForth execution time was $factor times longer"
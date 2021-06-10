: fib dup 2 < if drop 1 else dup 1 - fib swap 2 - fib + then ;
: main 34 fib . ;

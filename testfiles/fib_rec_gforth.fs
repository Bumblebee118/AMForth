: fib dup 2 < if drop 1 else dup 1 - recurse swap 2 - recurse + then ;
: main 34 fib . ;
main
bye

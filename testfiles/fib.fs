: 2dup 1 pick 1 pick ;
variable count
: resetCount 1 count ! ;
: incrCount count @ dup 1 + count ! ;
: printNum rot incrCount . . cr ;
: fib resetCount 1 2 rot 0 do 2dup + printNum loop drop drop ;

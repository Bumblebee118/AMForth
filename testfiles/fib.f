: 2dup 1 pick 1 pick ;
variable count
: resetCount 1 count ! ;
: fib  resetCount 1 2 rot 0 do 2dup + rot count @ dup 1 + count ! . . cr loop drop drop ;

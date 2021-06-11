: mybounds  over + swap ;

1 cells constant cell

variable seed

: initiate-seed 74755 seed ! ;
: random seed @ 1309 * 13849 + 65535 and dup seed ! ;

6000 constant elements

create list elements allot

: initiate-list list elements cells + list do random i ! cell +loop ;

: dump-list list elements cells + list do i @ . cell +loop cr ;

variable index

: reset-index 0 index ! ;

: incr-index index @ 1+ index ! ;

: print-list
  reset-index
  list elements 1- cells mybounds do
    index @ . incr-index
    i @ . cr
  cell +loop
;

: verify-list
  list elements 1- cells mybounds do
    i 2@ > if ." bubble-sort: not sorted" 1 throw then
  cell +loop
;

: bubble
." bubbling..." cr
  1 elements 1 do
    list elements i - cells mybounds do
      j 2@  > if j 2@ swap j 2! then
    cell +loop
  loop
;

: bubble-sort
  initiate-seed
  initiate-list
  bubble
  verify-list
;


: main
	bubble-sort
;

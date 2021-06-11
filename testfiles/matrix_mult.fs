: mybounds  over + swap ;

1 cells constant cell

variable seed

: initiate-seed 74755 seed ! ;
: random seed @ 1309 * 13849 + 65535 and dup seed ! ;

200 constant row-size
row-size cells constant row-byte-size

row-size row-size * constant mat-size
mat-size cells constant mat-byte-size

create ima mat-byte-size allot
create imb mat-byte-size allot
create imr mat-byte-size allot

: initiate-matrix
  mat-byte-size mybounds do
    random dup 120 / 120 * - 60 - i !
  cell +loop
;

: innerproduct
  0 row-size 0 do
    >r over @  over @ * r> + >r
    swap cell+ swap row-byte-size +
    r>
  loop
  >r 2drop r>
;

: main
  initiate-seed
  ima initiate-matrix
  imb initiate-matrix
  imr ima mat-byte-size mybounds do
    imb row-byte-size mybounds do
      i j
       0 row-size 0 do
           >r over @  over @ * r> + >r
           swap cell+ swap row-byte-size +
           r>
         loop
         >r 2drop r>

       over ! cell+
    cell +loop
  row-size cells +loop
  drop
;


: print-matrix
   mat-byte-size mybounds do
        i @ .
   cell +loop
;

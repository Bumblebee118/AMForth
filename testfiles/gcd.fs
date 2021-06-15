: 2dup 1 pick 1 pick ;
: gcd 1 pick 0 = if swap drop . else dup 0 = if drop . else begin 2dup > if 2dup - rot drop swap else 1 pick - then dup 0 = until drop . then then ;
1 12345678 gcd
bye

for (( i = 0; i < 5; i++ )); do
  #time ../cmake-build-release/AMForth < gcd.fs > output.txt
  #time gforth < gcd.fs > output.txt

  time ../cmake-build-release/AMForth < fib_rec.fs > output.txt
  time gforth fib_rec_gforth.fs > output.txt
done
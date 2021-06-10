for (( i = 0; i < 5; i++ )); do
  #time ../cmake-build-release/AMForth < gcd.f > output.txt
  #time gforth < gcd.f > output.txt

  time ../cmake-build-release/AMForth < fib_rec.f > output.txt
  time gforth fib_rec_gforth.f > output.txt
done
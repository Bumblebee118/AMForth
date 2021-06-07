for (( i = 0; i < 5; i++ )); do
  time ../cmake-build-release/AMForth < gcd.f > output.txt
  time gforth < gcd.f > output.txt
done
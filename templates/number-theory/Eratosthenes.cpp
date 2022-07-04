/**
 * @date 2022-07-04
 * @author Delusion88
 * @brief Find prime numbers on [1; lim]
 * 
 * @param lim Upper bound
 * @return vector<int> Primes on the segment [1; lim]
 */
vector<int> sieve(int lim) {
  int sqr = sqrt(lim);
  sqr += 2;
  vector<int> res{2};
  res.reserve(max(10, lim / 25));
  vector<bool> isprime(lim + 1, 1);
  isprime[0] = isprime[1] = 0;
  for(int i = 4; i <= lim; i += 2)
    isprime[i] = 0;
  for(int i = 3; i <= lim; i += 2)
    if(isprime[i]) {
      if(i <= sqr)
        for(int j = i * i; j <= lim; j += i * 2)
          isprime[j] = 0;
      res.push_back(i);
    }
  return res;
}

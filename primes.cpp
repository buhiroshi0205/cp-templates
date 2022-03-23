#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void sieve(ll limit, vector<ll>& result) {
  vector<bool> isprime(limit+1, true);
  isprime[0] = false;
  isprime[1] = false;
  ll maxtest = (int) ceil(sqrt(limit));
  for (ll i = 2; i <= maxtest; i += 1) {
    if (isprime[i]) {
      ll curr = i + i;
      while (curr <= limit) {
        isprime[curr] = false;
        curr += i;
      }
    }
  }
  for (int i = 0; i <= limit; i++) {
    if (isprime[i]) result.push_back(i);
  }
}

ull exp(ull b, ull x, ull m) {
  if (x == 0) return 1;
  if (x == 1) return b % m;
  ull halfexp = exp(b, x/2, m);
  halfexp = (halfexp * halfexp) % m;
  if (x % 2 == 0) {
    return halfexp;
  } else {
    return (halfexp * b) % m;
  }
}

// For 64-bit positive integers, testing the first 12 primes as bases
// is sufficient to catch all the pseudoprimes.
// Complexity: 12*O(log^3(n))
ull firstprimes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
bool miller_rabin(ull n) {
  if (n <= 37) {
    for (int i = 0; i < 12; i++) {
      if (firstprimes[i] == n) return true;
    }
    return false;
  }
  if (n % 2 == 0) return false;

  ull d = n - 1;
  ull s = 0;
  while (d % 2 == 0) {
    s++;
    d /= 2;
  }

  for (int i = 0; i < 12; i++) {
    ull a = firstprimes[i];
    ull x = exp(a,d,n);
    if (x == 1) continue; // probably prime
    bool definitely_composite = true;
    for (int j = 0; j < s; j++) {
      if (x == n - 1) {
        definitely_composite = false;
        break; //probably prime
      }
      x = exp(x,2,n);
    }
    if (definitely_composite) return false;
  }
  return true; // tested all necessary bases, definitely prime
}

ull get_prime() {
  srand(time(NULL));
  ull prime;
  while (true) {
    ull one = 1;
    prime = rand() | (one << 31);
    if (miller_rabin(prime)) break;
  }
}
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll exp(ll b, ll x, ll m) {
  if (x == 0) return 1;
  ll half = exp(b, x/2, m);
  if (x % 2 == 0) return half * half % m;
  else return half * half % m * b % m;
}

ll inverse(ll x, ll m) {
  return exp(x, m-2, m);
}

class Combinatorics {

public:
  ll mod;
  vector<ll> factorial;
  vector<ll> invfactorial;

  Combinatorics(ll limit, ll modulus=1e9+7) {
    mod = modulus;
    factorial.resize(limit+1);
    invfactorial.resize(limit+1);
    factorial[0] = 1;
    invfactorial[0] = 1;
    for (ll i = 1; i <= limit; i++) {
      factorial[i] = factorial[i-1] * i % mod;
      invfactorial[i] = inverse(factorial[i], mod);
    }
  }

  ll P(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;
    return factorial[a] * invfactorial[a-b] % mod;
  }

  ll C(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;
    return factorial[a] * invfactorial[a-b] % mod * invfactorial[b] % mod;
  }

  ll fact(ll a) {
    if (a < 0) return 0;
    return factorial[a];
  }

};
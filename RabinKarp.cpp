#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class RabinKarp {

public:

  ll p;
  int n;
  int b;
  vector<ll> r;
  vector<ll> a;
  vector<ll> reva;

  RabinKarp(string s, ll mod = 999998727899999) {
    vector<int> si(s.size());
    for (int i = 0; i < s.size(); i++) {
      si[i] = s[i];
    }
    b = 256;
    p = mod;
    init(si);
  }

  RabinKarp(vector<int>& s, int base, ll mod = 1e9+7) {
    b = base;
    p = mod;
    init(s);
  }

  void init(vector<int>& s) {
    n = s.size();

    r.resize(n+1);
    a.resize(n+1);
    r[0] = 1;
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
      r[i] = (r[i-1] * b) % p;
      a[i] = (a[i-1] * b + s[i-1]) % p;
    }

    reva.resize(n+1);
    reva[n] = 0;
    for (int i = n-1; i >= 0; i--) {
      reva[i] = (reva[i+1] * b + s[i]) % p;
    }
  }

  // inclusive both ends
  ll hash(int start, int end) {
    ll modded = (a[end+1]-a[start]*r[end+1-start]) % p;
    return (modded + p) % p;
  }

  // inclusive both ends, end >= start
  ll revhash(int start, int end) {
    ll modded = (reva[start]-reva[end+1]*r[end+1-start]) % p;
    return (modded + p) % p;
  }

};

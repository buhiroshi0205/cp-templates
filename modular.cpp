typedef unsigned long long ull;  // 64 bit type

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

ull inverse(ll x, ll m) {
  return exp(x, m-2, m);
}
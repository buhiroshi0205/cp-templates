class Fraction {

public:

  Fraction(ll modnum) {
    mod = modnum;
    p = 1;
    q = 1;
  }

  Fraction(ll modnum, ll p1, ll q1) {
    mod = modnum;
    p = p1;
    q = q1;
  }

  void set(ll p1, ll q1) {
    p = p1 % mod;
    q = q1 % mod;
  }

  pair<ll, ll> get() {
    return make_pair(p, q);
  }

  void multiply(ll a, ll b) {
    p = p * a % mod;
    q = q * b % mod;
  }

  void add(ll a, ll b) {
    ll numerator = (p * b % mod) + (a * q % mod);
    ll denominator = q * b;
    p = numerator % mod;
    q = denominator % mod;
  }

private:

  ll mod;
  ll p;
  ll q;

};
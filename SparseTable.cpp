#include <bits/stdc++.h>
using namespace std;

template <class T>
class SparseTable {
public:

  vector<vector<T>> table;
  function<T(T,T)> f;

  SparseTable(vector<T>& a, function<T(T,T)> cmb) {
    f = cmb;
    int n = a.size();
    int l2 = (int) ceil(log2(n));
    table.resize(l2+1, vector<T>(n));
    for (int i = 0; i < n; i++) {
      table[0][i] = a[i];
    }
    for (int k = 1; k <= l2; k++) {
      for (int i = 0; i <= n-(1<<k); i++) {
        table[k][i] = f(table[k-1][i], table[k-1][i+(1<<(k-1))]);
      }
    }
  }

  // inclusive both ends
  T query(int i, int j) {
    int k = (int) log2(j-i+1);
    return f(table[k][i], table[k][j-(1<<k)+1]);
  }

};
#include <bits/stdc++.h>
using namespace std;

void minsparse_table(vector<int>& a, vector<vector<int>>& sptable) {
  int n = a.size();
  int l2 = (int) ceil(log2(n));
  sptable.resize(l2+1);
  for (int i = 0; i < n; i++) {
    sptable[0].resize(n);
    sptable[0][i] = a[i];
  }
  for (int k = 1; k <= l2; k++) {
    sptable[k].resize(n);
    for (int i = 0; i <= n - (1 << k); i++) {
      sptable[k][i] = min(sptable[k-1][i], sptable[k-1][i + (1 << (k-1))]);
    }
  }
}

void maxsparse_table(vector<int>& a, vector<vector<int>>& sptable) {
  int n = a.size();
  int l2 = (int) ceil(log2(n));
  sptable.resize(l2+1);
  for (int i = 0; i < n; i++) {
    sptable[0].resize(n);
    sptable[0][i] = a[i];
  }
  for (int k = 1; k <= l2; k++) {
    sptable[k].resize(n);
    for (int i = 0; i <= n - (1 << k); i++) {
      sptable[k][i] = max(sptable[k-1][i], sptable[k-1][i + (1 << (k-1))]);
    }
  }
}

int minquery(int i, int j, vector<vector<int>>& sptable) {
  int k = (int) log2(j-i+1);
  return min(sptable[k][i], sptable[k][j - (1 << k) + 1]);
}

int maxquery(int i, int j, vector<vector<int>>& sptable) {
  int k = (int) log2(j-i+1);
  return max(sptable[k][i], sptable[k][j - (1 << k) + 1]);
}
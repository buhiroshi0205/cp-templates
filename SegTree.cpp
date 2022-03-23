#include <bits/stdc++.h>
using namespace std;

template <class T>
class SegTree {
public:

  vector<T> tree;
  function<T(T,T)> combine;

  SegTree(int n, function<T(T,T)> cmb, T identity) {
    int vectorsize = 1 << ((int) ceil(log2(n)) + 1);
    tree.resize(vectorsize, identity);
    combine = cmb;
  }

  T get(int i) {
    return tree[tree.size()/2+i];
  }

  void set(int i, T value) {
    int curridx = tree.size()/2 + i;
    tree[curridx] = value;
    while (curridx > 1) {
      curridx /= 2;
      tree[curridx] = combine(tree[curridx*2], tree[curridx*2+1]);
    }
  }

  T rangequery(int l, int r) {
    T res = tree[0]; // identity
    l += tree.size()/2;
    r += tree.size()/2;
    while (l < r) {
      if (l % 2 == 1) {
        res = combine(res, tree[l]);
        l++;
      }
      l /= 2;
      if (r % 2 == 0) {
        res = combine(res, tree[r]);
        r--;
      }
      r /= 2;
    }
    if (l == r) {
      res = combine(res, tree[l]);
    }
    return res;
  }

};
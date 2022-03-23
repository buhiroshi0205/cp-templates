#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class MaxFlow {

public:

  struct edge {
    int u, v;
    ll cap, flow;
    struct edge *rev = NULL;
    edge(int a, int b, ll c, ll d) {
      u = a; v = b; cap = c, flow = d;
    }
  };

  MaxFlow(vector<int>& layersizes) {
    layerindices.resize(layersizes.size());
    int psum = 2;
    for (int i = 0; i < layersizes.size(); i++) {
      layerindices[i] = psum;
      psum += layersizes[i];
    }
    numnodes = psum;

    g.resize(numnodes);
    dist.resize(numnodes);
    current.resize(numnodes);
  }
  ~MaxFlow() {
    for (int i = 0; i < g.size(); i++) {
      for (int j = 0; j < g[i].size(); j++) {
        delete g[i][j];
      }
    }
  }

  void add_edge(int l1, int i1, int l2, int i2, ll cap) {
    int u = getidx(l1, i1);
    int v = getidx(l2, i2);
    struct edge *forward = new struct edge(u,v,cap,0);
    struct edge *backward = new struct edge(v,u,0,0);
    forward->rev = backward;
    backward->rev = forward;
    g[u].push_back(forward);
    g[v].push_back(backward);
  }

  ll dinic() {
    ll flow = 0;
    while (true) {
      // 1. build layer graph
      fill(dist.begin(), dist.end(), -1);
      dist[0] = 0;
      bfs();
      if (dist[1] == -1) return flow;

      // 2. find blocking flow
      fill(current.begin(), current.end(), 0);
      ll f = blockingflow();
      flow += f;
    }
    return flow;
  }

  int numnodes;
  vector<int> layerindices;
  vector<vector<edge*>> g;
  vector<int> dist;
  vector<int> current;

  int getidx(int l, int i) {
    if (l == -1) return i;
    else return layerindices[l] + i;
  }

  void bfs() {
    deque<int> q;
    q.push_back(0);
    while (!q.empty()) {
      int u = q.front();
      q.pop_front();
      for (int i = 0; i < g[u].size(); i++) {
        struct edge *e = g[u][i];
        if (e->cap - e->flow > 0 && dist[e->v] == -1) {
          dist[e->v] = dist[u] + 1;
          q.push_back(e->v);
        }
      }
    }
  }

  ll blockingflow() {
    ll total = 0;
    while (true) {
      ll f = dfs(0);
      if (f == 0) return total;
      total += f;
      int u = 0;
      while (u != 1) {
        struct edge *e = g[u][current[u]];
        e->flow += f;
        e->rev->flow -= f;
        u = e->v;
      }
    }
  }

  ll dfs(int u) {
    if (u == 1) return LLONG_MAX;
    while (current[u] < g[u].size()) {
      struct edge *e = g[u][current[u]];
      if (dist[e->v] > dist[e->u] && e->cap - e->flow > 0) {
        ll f = dfs(e->v);
        if (f > 0) return min(f, e->cap-e->flow);
      }
      current[u]++;
    }
    return 0;
  }

};
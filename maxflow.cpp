#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class MaxFlow {

public:

  struct edge {
    int u, v;
    ll cap, flow, cost;
    struct edge *rev = NULL;
    edge(int from, int to, ll capacity, ll c) {
      u = from; v = to; cap = capacity; flow = 0; cost = c;
    }
  };

  int n;
  bool hasnegativecost = false;
  vector<vector<edge*>> g;

  MaxFlow(int numnodes) {
    n = numnodes;
    g.resize(n, vector<edge*>());
  }
  ~MaxFlow() {
    for (int i = 0; i < g.size(); i++) {
      for (int j = 0; j < g[i].size(); j++) {
        delete g[i][j];
      }
    }
  }

  edge* add_edge(int u, int v, ll cap) {
    return add_edge_internal(u,v,cap,1);
  }
  edge* add_edge(int u, int v, ll cap, ll cost) {
    if (cost < 0) hasnegativecost = true;
    return add_edge_internal(u,v,cap,cost);
  }
  edge* add_edge_internal(int u, int v, ll cap, ll cost) {
    struct edge *forward = new struct edge(u,v,cap,cost);
    struct edge *backward = new struct edge(v,u,0,-cost);
    forward->rev = backward;
    backward->rev = forward;
    g[u].push_back(forward);
    g[v].push_back(backward);
    return forward;
  }

  ll dinic(int source, int sink) {
    ll flow = 0;
    while (true) {
      // 1. build layer graph
      vector<int> dist(n, -1);
      dist[source] = 0;
      bfs(source, dist);
      if (dist[sink] == -1) return flow;
      // 2. find blocking flow
      ll f = blockingflow(source, sink, dist);
      flow += f;
    }
    return flow;
  }

  void bfs(int source, vector<int>& dist) {
    deque<int> q;
    q.push_back(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop_front();
      for (edge *e : g[u]) {
        if (e->cap - e->flow > 0 && dist[e->v] == -1) {
          dist[e->v] = dist[e->u] + 1;
          q.push_back(e->v);
        }
      }
    }
  }

  ll blockingflow(int source, int sink, vector<int>& dist) {
    vector<int> current(n, 0);
    ll total = 0;
    while (true) {
      ll f = dfs(source, sink, dist, current);
      if (f == 0) return total;
      total += f;
      int u = source;
      while (u != sink) {
        edge *e = g[u][current[u]];
        e->flow += f;
        e->rev->flow -= f;
        u = e->v;
      }
    }
  }

  ll dfs(int u, int sink, vector<int>& dist, vector<int>& current) {
    if (u == sink) return LLONG_MAX;
    while (current[u] < g[u].size()) {
      edge *e = g[u][current[u]];
      if (dist[e->v] > dist[e->u] && e->cap - e->flow > 0) {
        ll f = dfs(e->v, sink, dist, current);
        if (f > 0) return min(f, e->cap-e->flow);
      }
      current[u]++;
    }
    return 0;
  }

  vector<edge*> get_min_cut(int source) {
    vector<bool> reachable(n, false);
    reachabledfs(source, reachable);
    vector<edge*> res;
    for (vector<edge*>& ve : g) {
      for (edge* e : ve) {
        if (reachable[e->u] && !reachable[e->v]) {
          res.push_back(e);
        }
      }
    }
    return res;
  }

  void reachabledfs(int u, vector<bool>& reachable) {
    if (reachable[u]) return;
    reachable[u] = true;
    for (edge* e : g[u]) {
      if (e->cap - e->flow > 0) {
        reachabledfs(e->v, reachable);
      }
    }
  }

  pair<ll,ll> mcmf(int source, int sink) {
    vector<ll> phi(n, 0);
    if (hasnegativecost) {
      bellman_ford(source, phi);
    }

    ll totalflow = 0;
    ll totalcost = 0;
    vector<ll> dist(n);
    vector<edge*> parentedge(n);
    while (true) {
      fill(dist.begin(), dist.end(), LLONG_MAX);
      dijkstra(source, sink, dist, phi, parentedge);
      if (dist[sink] == LLONG_MAX) break;
      // update potentials
      for (int i = 0; i < n; i++) {
        if (dist[i] != LLONG_MAX) phi[i] += dist[i];
      }
      // determine amount of flow to push
      ll minf = LLONG_MAX;
      for (int u = sink; u != source; u = parentedge[u]->u) {
        minf = min(minf, parentedge[u]->cap - parentedge[u]->flow);
      }
      // push flow
      for (int u = sink; u != source; u = parentedge[u]->u) {
        parentedge[u]->flow += minf;
        parentedge[u]->rev->flow -= minf;
        totalcost += parentedge[u]->cost * minf;
      }
      totalflow += minf;
    }

    return make_pair(totalflow, totalcost);
  }

  void bellman_ford(int source, vector<ll>& phi) {
    vector<vector<ll>> dp(n, vector<ll>(n, LLONG_MAX));
    fill(dp[source].begin(), dp[source].end(), 0);
    for (int k = 1; k < n; k++) {
      for (int u = 0; u < n; u++) {
        dp[u][k] = dp[u][k-1];
      }
      for (int u = 0; u < n; u++) {
        for (edge *e : g[u]) {
          if (e->flow < e->cap) dp[e->v][k] = min(dp[e->v][k], dp[u][k-1] + e->cost);
        }
      }
    }
    for (int i = 0; i < n; i++) {
      phi[i] = dp[i][n-1];
    }
  }

  void dijkstra(int source, int sink, vector<ll>& dist, vector<ll>& phi, vector<edge*>& parentedge) {
    vector<bool> visited(n, false);
    dist[source] = 0;
    priority_queue<pair<ll,int>> q;
    q.push(make_pair(0,source));
    while (!q.empty()) {
      pair<ll,int> p = q.top();
      q.pop();
      ll currdist = -p.first;
      int u = p.second;
      if (visited[u]) continue;
      visited[u] = true;
      if (u == sink) return;
      for (edge *e : g[u]) {
        if (e->flow >= e->cap) continue;
        int v = e->v;
        ll newdist = dist[u] + e->cost + phi[u] - phi[v];
        if (newdist < dist[v]) {
          dist[v] = newdist;
          parentedge[v] = e;
          q.push(make_pair(-newdist, v));
        }
      }
    }
  }

};
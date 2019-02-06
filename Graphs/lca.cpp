#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 7;
const int maxl = 21;

int tin[MAXN], tout[MAXN], depth[MAXN], up[MAXN][maxl];
int timer = 0;

void dfs(int u, int last){
  tin[u] = ++timer;
  up[u][0] = last;
  depth[u] = depth[last] + 1;
  for (int i = 1; i < maxl; i++) {
    up[u][i] = up[up[u][i-1]][i-1];
  }
  for (auto v : adj[u]) {
    if (v != last) {
      dfs(v, u);
    }
  }
  tout[u] = ++timer;
}

bool is_ancestor(int u, int v){
  if (tin[u] < tin[v] && tout[u] > tout[v]) return true;
  return false;
}

int lca(int u, int v){
  if (u == v) return u;
  if (is_ancestor(u, v)) return u;
  if (is_ancestor(v, u)) return v;
  for (int i = maxl - 1; i >= 0; i--){
    if (!is_ancestor(up[u][i], v)){
      u = up[u][i];
    }
  }
  return up[u][0];
}

int dist(int u, int v){
  return (depth[u] + depth[v]) - 2 * depth[lca(u,v)];
}

int main() {
  
  return 0;
}

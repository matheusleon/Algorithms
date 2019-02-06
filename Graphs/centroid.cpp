#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 7;

set<int> adj[MAXN];
int parent[MAXN], sz[MAXN];

void dfsSubtree(int u, int p) {
  sz[u] = 1;
  for (auto v : adj[u]) {
    if (v != p) {
      dfsSubtree(v, u);
      sz[u] += sz[v];
    }
  }
}

int getCentroid(int u, int p, int size) {
  for (auto v : adj[u]) {
    if (v != p && sz[v] > size / 2) return getCentroid(v, u, size);
  }
  return u;
}

void decompose(int u, int pctr) {
  dfsSubtree(u, -1);
  int ctr = getCentroid(u, -1, sz[u]); 
  if (pctr == -1) {
    pctr = ctr;
  }
  parent[ctr] = pctr;
  for (auto v : adj[ctr]) {
    adj[v].erase(ctr);
    decompose(v, ctr);
  }
  adj[ctr].clear();
}

int main() {
  
  return 0;
}

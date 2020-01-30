const int MAXN = 1e5 + 7;

set<int> adj[MAXN];
int parent[MAXN], sz[MAXN];

void dfsSubtree(int u, int p) {
  sz[u] = 1;
  for (auto v : adj[u]) {
    if (v != p && !removed[v]) {
      dfsSubtree(v, u);
      sz[u] += sz[v];
    }
  }
}

int getCentroid(int u, int p, int size) {
  for (auto v : adj[u]) {
    if (v != p && !removed[v] && sz[v] * 2 >= size) return getCentroid(v, u, size);
  }
  return u;
}

void setDis(int v, int par, int nv, ll d) {
	dis[v][nv] = d;
	for(auto x : adj[v]) {
		int u = x.first, w = x.second;
		if (u == par || removed[u]) continue;
		setDis(u, v, nv, d + w);
	}
}

void decompose(int u, int p) {
  dfsSubtree(u, -1);
  int ctr = getCentroid(u, -1, sz[u]); 
  if (p == -1) {
    p = ctr;
  }
  parent[ctr] = p;
  removed[ctr] = 1;
  for (auto v : adj[ctr]) {
    if (v != p && !removed[v]) {
      decompose(v, ctr);
    }
  }
}

#include <bits/stdc++.h>

using namespace std;
#define all(foo) foo.begin(), foo.end()
typedef long long ll;
typedef pair<ll, ll> pii;
const int MAXN = 1e5 + 7;
const int maxl = 21;

int tin[MAXN], tout[MAXN], depth[MAXN], up[MAXN][maxl];
int timer = 0;
vector<int> dp[MAXN][maxl];
vector<int> adj[MAXN];
vector<int> ans, ue[MAXN];
priority_queue<int> pq;

int dfs(int u, int p) {
  tin[u] = ++timer;
  depth[u] = depth[p] + 1;
  vector<int> res;
  dp[u][0] = ue[p];
  dp[u][0].resize(min(10, (int) dp[u][0].size()));
  
  up[u][0] = p;
  for (int i = 1; i < maxl; i++) {
    up[u][i] = up[up[u][i-1]][i-1];
  }
  
  for (int i = 1; i < maxl; i++) {
    merge(all(dp[u][i-1]), all(dp[up[u][i-1]][i-1]), back_inserter(dp[u][i]));
    dp[u][i].resize(min(10, (int) dp[u][i].size()));

  }
  for (auto v : adj[u]) {
    if (v != p) {
      dfs(v, u);
    }
  }
  tout[u] = ++timer;
}

bool is_ancestor(int u, int v) {
  if (tin[u] <= tin[v] && tout[u] >= tout[v]) return true;
  return false;
}

int lca(int u, int v) {
  if (u == v) return u;
  if (is_ancestor(u, v)) return u;
  if (is_ancestor(v, u)) return v;
  for (int i = maxl - 1; i >= 0; i--) {
    if (!is_ancestor(up[u][i], v)) {
      u = up[u][i];
    }
  }
  return up[u][0];
}

vector<int> solve(int u, int LCA, int quant) {
  if (u == LCA) return ue[u];
  vector<int> ans = ue[u];
  int h = depth[u] - depth[LCA];
  for (int i = maxl - 1; i >= 0; i--) {
    if (h & (1 << i)) {
      vector<int> res;
      merge(all(ans), all(dp[u][i]), back_inserter(res));
      ans = res;
      ans.resize(min(quant, (int) ans.size()));
      u = up[u][i];
    }
  }
  return ans;
}

int dist(int u, int v) {
  return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

int walk(int u, int k) {
  for (int i = maxl - 1; i >= 0; i--) {
    if ((1 << i) <= k) {
      k -= (1 << i);
      u = up[u][i];
    }
  }
  return u;
}

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d %d",&u, &v);
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= m; i++) {
    int x;
    scanf("%d", &x);
    x--;
    ue[x].push_back(i);
  }
  for (int i = 0; i < n; i++) {
    ue[i].resize(min(10, (int)ue[i].size()));
  }
  dfs(0, 0);
  for (int i = 0; i < q; i++) {
    ans.clear();
    int u, v, a;
    scanf("%d %d %d",&u, &v, &a);
    u--; v--;
    int LCA = lca(u, v);
    if (u == v) {
      ans = ue[u];
    } else {
      if (LCA == u) swap(u, v);
      if (LCA == v) {
        ans = solve(u, v, a);
      }
      else {
        int eita = walk(u, dist(u, LCA) - 1); 
        vector<int> res1 = solve(v, LCA, a);
        vector<int> res2 = solve(u, eita, a);
        merge(all(res1), all(res2), back_inserter(ans));
      }
    }
    ans.resize(min(a, (int) ans.size()));
    cout << ans.size() << ' ';
    for (int i = 0; i < ans.size(); i++) {
      printf("%d ", ans[i]);
    }
    printf("\n");
  }
  return 0;
}

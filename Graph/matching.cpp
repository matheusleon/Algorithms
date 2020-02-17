vector<int> v[MAXN];
int matchA[MAXN], matchB[MAXN];
bool vis[MAXN];

int solve(int u) {
	for(int i = 0; i < v[u].size(); i++) {
		int w = v[u][i];
		if (vis[w]) continue;
		vis[w] = true;
		if(matchB[w] == -1 || solve(matchB[w])) {
			matchB[w] = u;
			matchA[u] = w;
			return 1;
		}
	}
	return 0;
}

int kuhn() {
	memset(matchA, -1, sizeof matchA);
	memset(matchB, -1, sizeof matchB);
	int ans = 0;
	bool found = true;
	while (found) {
		memset(vis, false, sizeof vis);
		found = false;
		for (int i = 0; i < n; i++) {
			if (matchA[i] != -1) continue;
			if (solve(i)) {
				ans++;
				found = true;
			}
		}
	}
	return ans;
}

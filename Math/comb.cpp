ll fexp(ll n, ll p) {
	ll ans = 1;
	while (p) {
		if (p & 1) ans = (ans * n) % MOD;
		n = (n * n) % MOD;
		p >>= 1;
	}
	return ans % MOD;
}

ll inverse(ll n) {
	return fexp(n, MOD - 2);
}

ll comb(ll n, ll k) {
	if (k < 0 || k > n) return 0;
	ll x = (inverse(fat[k]) * inverse(fat[n - k])) % MOD;
	return (fat[n] * x) % MOD;
}

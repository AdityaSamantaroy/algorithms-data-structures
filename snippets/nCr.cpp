
//fac[i] : factorial of i
//inv[i] : modular inverse of fac[i]
vector<ll> fac, inv;
void create_fac(ll n = MAXN) {
	fac.resize(n + 5);
	inv.resize(n + 5);
	fac[0] = 1;
	inv[0] = fpow(fac[0], MOD - 2);
	for (ll i = 1; i <= n; i++) {
		fac[i] = (fac[i - 1] % MOD * i % MOD) % MOD;
		inv[i] = fpow(fac[i], MOD - 2);
	}
}

//nCr
ll binomial_coefficient(ll n, ll r) {
	ll res = 1;
	res = (res * (fac[n] % MOD)) % MOD;
	res = (res * (inv[r] % MOD)) % MOD;
	res = (res * (inv[n - r] % MOD)) % MOD;
	// res = (res, ) % MOD;
	return res;
}

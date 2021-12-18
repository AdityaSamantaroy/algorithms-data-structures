
/**
 *	author:  adityasamantaroy
 *	created: 18-12-2021 16:39:10
**/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define FIO                           \
	freopen("input.txt", "r", stdin); \
	freopen("output.txt", "w", stdout);
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define clr(x) memset(x, 0, sizeof(x))

// debugging start
#ifndef ONLINE_JUDGE
#include "debugging.h"
#define deb(x) cerr << "(" << __LINE__ << ") " << #x << "=" << t << endl
#else
#define deb(x) 42
#endif
// debugging end

const int MOD = 1000000007;
const int INF = 1000000009;
const int MAXN = 1000005;  //300050;

//binary exponentiation
ll fpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = (1LL * res * x) % MOD;
		}
		x = (1LL * x * x) % MOD;
		n >>= 1;
	}
	return (res % MOD);
}

//lp[i]=i => i is prime.
//lp[i]!=i => lp[i] : minimum prime factor of i
//pr[i] : ith prime number (0 indexed)
vector<ll> lp;
vector<ll> pr;
void sieve(ll n = MAXN) {
	lp.resize(n + 1);
	pr.clear();
	for (ll i = 2; i <= n; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (ll j = 0; j < (ll)pr.size() && pr[j] <= lp[i] && i * pr[j] <= n; ++j)
			lp[i * pr[j]] = pr[j];
	}
}

//using eucledian algorithm
ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

ll sceil(ll a, ll b) {
	return (a + b - 1) / b;
}


/* ========== YOUR CODE HERE ========= */
//void solution() {
ll solution() {
	
}

/* ========== YOUR CODE HERE ========= */

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int tt = 1;
	// cin >> tt;
	while (tt--) {
		cout << solution() << endl;
		//        solution();
	}

	return 0;
}

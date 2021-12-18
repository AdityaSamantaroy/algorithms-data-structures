/**
 *	author:  adityasamantaroy
 *	created: 18-12-2021 16:21:55
**/
#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ll long long
#define PI 3.1415926535897932384626
#define endl '\n'
#define FIO                           \
	freopen("input.txt", "r", stdin); \
	freopen("output.txt", "w", stdout);
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define clr(x) memset(x, 0, sizeof(x))
#define tr(it, x) for (auto it = x.begin(); it != x.end(); it++)
#define trr(it, x) for (auto it = x.rbegin(); it != x.rend(); it++)

#define umin(...) min({__VA_ARGS__})
#define umax(...) max({__VA_ARGS__})
#define MAX(v) *max_element(all(v))
#define MIN(v) *min_element(all(v))

typedef pair<ll, ll> pl;
typedef vector<ll> vl;
typedef vector<pl> vpl;
typedef vector<vl> vvl;
const int MOD = 1000000007;
const int INF = 1000000009;
const int MAXN = 1000005;  //300050;

/*debugging */
vector<string> split(const string& s, char c) {
	vector<string> v;
	stringstream ss(s);
	string x;
	while (getline(ss, x, c)) v.emplace_back(x);
	return move(v);
}
template <typename T, typename... Args>
inline string arrStr(T arr, int n) {
	stringstream s;
	s << "[";
	for (int i = 0; i < n - 1; i++) s << arr[i] << ",";
	s << arr[n - 1] << "]";
	return s.str();
}

#ifndef ONLINE_JUDGE
#define debug(args...)                            \
	{                                             \
		__evars_begin(__LINE__);                  \
		__evars(split(#args, ',').begin(), args); \
	}

inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
template <typename T>
inline void __evars_out_var(vector<T> val) { cerr << arrStr(val, val.size()); }
template <typename T>
inline void __evars_out_var(T* val) { cerr << arrStr(val, 10); }
template <typename T>
inline void __evars_out_var(T val) { cerr << val; }
inline void __evars(vector<string>::iterator it) { cerr << endl; }

template <typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
	cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
	__evars_out_var(a);
	cerr << "; ";
	__evars(++it, args...);
}
// #define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif


/* Function to check primality in O(sqrt(n)) */
bool is_prime(ll n) {
	if (n < 2)
		return false;
	for (ll x = 2; x * x <= n; x++) {
		if (n % x == 0)
			return false;
	}
	return true;
}

/* Function to get prime factorization of n in O(sqrt(n))*/
vector<ll> get_prime_factors(ll n) {
	vector<ll> f;
	for (ll x = 2; x * x <= n; x++) {
		while (n % x == 0) {
			f.push_back(x);
			n /= x;
		}
	}
	if (n > 1)
		f.push_back(n);
	return f;
}

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

//using eucledian algorithm
ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
	return a * (b / gcd(a, b));
}

ll sceil(ll a, ll b) {
	return (a + b - 1) / b;
}

//lp[i]=i => i is prime.
//lp[i]≠i => lp[i] : minimum prime factor of i
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

//used for mod_inv function
ll extended_euclidean(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll d = extended_euclidean(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}

//returns the modular inverse of a wrt m
int mod_inv(ll a, ll m) {  //if (a*x) mod m = 1, return x; else return -1;
	ll x, y;
	ll g = extended_euclidean(a, m, x, y);
	if (g != 1) {
		// cout << "No solution!";
		return -1;  // there will be no solution if a is divisible by m
	} else {
		x = (x % m + m) % m;
		return x;
	}
}

/* ========== YOUR CODE HERE ========= */
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// seed_seq seq{
//     (uint64_t)chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
//     (uint64_t)__builtin_ia32_rdtsc(),
//     (uint64_t)(uintptr_t)make_unique<char>().get()};
// mt19937 rng(seq);

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

/**
 *	author:  adityasamantaroy
 *	created: 15-12-2021 14:02:23
 *  verification: https://judge.yosupo.jp/submission/69995 
 *  time: 1.33s
**/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define PI 3.1415926535897932384626
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define clr(x) memset(x, 0, sizeof(x))
const ll MOD = 998244353;
const int INF = 1000000009;

/* ========== YOUR CODE HERE ========= */
struct Vertex {
	ll left, right;
	ll sum = 0;
	ll addProp = 0;
	ll mulProp = 1;
	Vertex *left_child = nullptr, *right_child = nullptr;

	// lb, rb => [0, n) range which this node is responsible for
	Vertex(ll lb, ll rb) {
		left = lb;
		right = rb;
	}

	// push lazy changes to children
	void pushAdd() {
		pushAdd(left, right, addProp);
	}
	// push lazy changes to children
	void pushAdd(ll lq, ll rq, ll& x) {
		if (x) {
			extend();
			pushMul();
			if (left + 1 == right) {
				sum += x;
				sum %= MOD;
				x = 0;
				return;
			}
			left_child->add(lq, rq, x);
			right_child->add(lq, rq, x);
			sum = left_child->sum * left_child->mulProp + (left_child->right - left_child->left) * left_child->addProp + right_child->sum * right_child->mulProp + (right_child->right - right_child->left) * right_child->addProp;
			sum %= MOD;
			x = 0;
		}
	}

	// push lazy changes to children
	void pushMul() {
		pushMul(left, right, mulProp);
	}
	// push lazy changes to children
	void pushMul(ll lq, ll rq, ll& x) {
		if (x != 1) {
			extend();
			if (left + 1 == right) {
				sum *= x;
				sum %= MOD;
				x = 1;
				return;
			}
			left_child->multiply(lq, rq, x);
			right_child->multiply(lq, rq, x);
			sum = left_child->sum * left_child->mulProp + (left_child->right - left_child->left) * left_child->addProp + right_child->sum * right_child->mulProp + (right_child->right - right_child->left) * right_child->addProp;
			sum %= MOD;
			x = 1;
		}
	}

	// create child nodes
	void extend() {
		// if children don't exist and this is not a leaf node
		if (!left_child && left + 1 < right) {
			ll t = (left + right) / 2;
			left_child = new Vertex(left, t);
			right_child = new Vertex(t, right);
		}
	}

	// 0 indexed update incremental
	void add(ll lq, ll rq, ll x) {
		if (max(left, lq) >= min(right, rq))
			return;
		if (lq <= left && right <= rq) {
			addProp += x;
			addProp %= MOD;
			return;
		}
		extend();
		pushAdd(lq, rq, x);
	}

	// 0 indexed multiply
	void multiply(ll lq, ll rq, ll x) {
		if (max(left, lq) >= min(right, rq))
			return;
		if (lq <= left && right <= rq) {
			mulProp *= x;
			addProp *= x;
			mulProp %= MOD;
			addProp %= MOD;
			return;
		}
		extend();
		pushMul();
		pushAdd();
		pushMul(lq, rq, x);
	}

	// 0 indexed update incremental
	void add(ll k, ll x) {
		extend();
		sum += x;
		sum %= MOD;
		if (left_child) {
			if (k < left_child->right)
				left_child->add(k, x);
			else
				right_child->add(k, x);
		}
	}

	//get point sum at mq, 0 indexed
	ll get_sum(ll mq) {
		return get_sum(mq, mq + 1);
	}

	// 0 indexed sum [lq, rq)
	ll get_sum(ll lq, ll rq) {
		if (max(left, lq) >= min(right, rq))
			return 0;
		if (lq <= left && right <= rq) {
			ll sp = sum * mulProp + (right - left) * addProp;
			sp %= MOD;
			return sp;
		}
		extend();
		pushMul();
		pushAdd();
		return (left_child->get_sum(lq, rq) + right_child->get_sum(lq, rq)) % MOD;
	}
};


void solution() {
	// ll solution() {
	ll n;
	cin >> n;

	ll q;
	cin >> q;

	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}

	Vertex root = Vertex(0, n);
	for (int i = 0; i < n; i++) {
		root.add(i, a[i]);
	}

	for (ll i = 0; i < q; i++) {
		ll t = 0;
		cin >> t;

		if (t) {
			ll l, r;
			cin >> l >> r;
			cout << root.get_sum(l, r) % MOD << endl;
		} else {
			ll l, r, b, c;
			cin >> l >> r >> b >> c;
			root.multiply(l, r, b);
			root.add(l, r, c);

			// vector<ll> x;
			// for (int i = 0; i < n; i++) {
			// 	x.push_back(root.get_sum(i));
			// }
			// debug(x);
		}
	}
}
/* ========== YOUR CODE HERE ========= */

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int tt = 1;
	// cin >> tt;
	while (tt--) {
		// cout << solution() << endl;
		solution();
	}

	return 0;
}

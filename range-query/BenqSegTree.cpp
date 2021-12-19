/**
 *  author:  adityasamantaroy
 *  created: 19-12-2021 21:37:12
 *  verification: https://cses.fi/problemset/task/1649/
 *  time: 0.41s
**/

// Range minimum query
// for range sum, all we need to change are T=long long, ID=0, and comb.
#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define INF 1e18

template <class T>
struct Seg {  // comb(ID,b) = b
	const T ID = INF;
	T comb(T a, T b) { return min(a, b); }
	int n;
	vector<T> seg;
	void init(int _n) {
		n = _n;
		seg.assign(2 * n, ID);
	}
	void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
	void upd(int p, T val) {  // set val at position p, 0 indexed
		p++;
		seg[p += n] = val;
		for (p /= 2; p; p /= 2) pull(p);
	}
	T query(int l, int r) {  // min on interval [l, r), 0 indexed
		l++;
		T ra = ID, rb = ID;
		for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if (l & 1)
				ra = comb(ra, seg[l++]);
			if (r & 1)
				rb = comb(seg[--r], rb);
		}
		return comb(ra, rb);
	}
};

int main() {
	int n, q;
	cin >> n >> q;
	Seg<ll> st;
	st.init(n + 1);
	for (int i = 0; i < n; i++) {
		ll a;
		cin >> a;
		st.upd(i, a);
	}
	for (int i = 0; i < q; i++) {
		ll t, a, b;
		cin >> t >> a >> b;
		a--;
		if (t == 1)
			st.upd(a, b);
		else
			cout << st.query(a, b) << "\n";
	}
}

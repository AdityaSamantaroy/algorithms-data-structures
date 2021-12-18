
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
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
typedef long double ld;
typedef long long int lli;
using namespace std;
class complex {
private:
	long double a, b;

public:
	complex() {
		a = b = 0;
	}
	complex(ld a, ld b) {
		this->a = a;
		this->b = b;
	}
	void operator=(ld a) {
		this->a = a;
	}
	void operator=(pair<ld, ld> c) {
		a = c.first, b = c.second;
	}
	void set_val(ld c, ld d) {
		a = c, b = d;
	}
	complex operator+(complex d) {
		complex c;
		c.a = a + d.a;
		c.b = b + d.b;
		return c;
	}
	complex operator+(ld d) {
		complex d1(d, 0);
		return *this + d1;
	}
	complex operator+=(complex d) {
		a = a + d.a;
		b = b + d.b;
		return *this;
	}
	complex operator+=(ld d) {
		complex d1(d, 0);
		return *this += d1;
	}
	complex operator-(complex d) {
		complex c;
		c.a = a - d.a;
		c.b = b - d.b;
		return c;
	}
	complex operator-(ld d) {
		complex d1(d, 0);
		return *this - d1;
	}
	complex operator-=(complex d) {
		a = a - d.a;
		b = b - d.b;
		return *this;
	}
	complex operator-=(ld d) {
		complex d1(d, 0);
		return *this -= d1;
	}

	complex operator*(complex d) {
		complex c;
		c.a = a * d.a - b * d.b;
		c.b = a * d.b + b * d.a;
		return c;
	}
	complex operator*(ld d) {
		complex d1(d, 0);
		return *this * d1;
	}
	complex operator*=(complex d) {
		*this = *this * d;
		return *this;
	}
	complex operator*=(ld d) {
		complex d1(d, 0);
		return *this *= d1;
	}
	complex operator/(complex d) {
		complex c;
		c.a = (a * d.a + b * d.b) / (d.a * d.a + d.b * d.b);
		c.b = (d.a * b - d.b * a) / (d.a * d.a + d.b * d.b);
		return c;
	}
	complex operator/(ld d) {
		complex d1(d, 0);
		return *this / d1;
	}
	complex operator/=(complex d) {
		*this = *this / d;
		return *this; //
	}
	complex operator/=(ld d) {
		complex d1(d, 0);
		return *this /= d1;
	}
	ld R() {
		ld b1 = sqrt(a * a + b * b);
		return b1;
	}
	ld Re() {
		return a;
	}
	void set_Re(ld b) {
		a = b;
	}
	ld Im() {
		return b;
	}
	void set_Im(ld a) {
		b = a;
	}
	ld Arg() {
		ld sm;
		if (a == 0 && b >= 0)
			sm = acos(-1) / (ld)2;
		else if (a == 0)
			sm = ((ld)3 * acos(-1)) / (ld)2;
		else if (a >= 0)
			sm = atan(b / a);
		else
			sm = atan(b / a) + acos(-1);
		return sm;
	}
	complex operator!() {
		complex c(a, -b);
		return c;
	}
	complex operator-() {
		complex c(-a, -b);
		return c;
	}
	complex operator^(lli n) {
		ld a = cos(Arg() * (ld)n), b = sin(Arg() * (ld)n), ret = 1, r = R();
		while (n) {
			if (n & 1LL)
				ret *= r;
			r *= r;
			n >>= 1LL;
		}
		complex c(ret * a, ret * b);
		return c;
	}
};

ostream &operator<<(ostream &c, complex a) {
	if (abs(a.Re()) < 1e-8)
		cout << 0;
	else
		cout << a.Re();
	if (a.Im() < 0)
		cout << "-";
	else
		cout << "+";
	cout << "i";
	if (abs(a.Im()) < 1e-8)
		cout << 0;
	else
		cout << abs(a.Im());
	return c;
}
istream &operator>>(istream &c, complex &l) {
	ld a, b;
	char A, B;
	cin >> a >> A >> B >> b;
	if (A == '-')
		b = -b;
	complex d(a, b);
	l = d;
	return c;
}
ld Re(complex a) {
	return a.Re();
}
ld Im(complex a) {
	return a.Im();
}
complex operator+(ld a, complex b) {
	return b + a;
}
complex operator-(ld a, complex b) {
	return b - a;
}
complex operator*(ld a, complex b) {
	return b * a;
}
complex operator/(ld a, complex b) {
	return b / a;
}
vector<complex> rt(complex A, int n = 2) {
	const ld sm = acos(-1) * (ld)2;
	vector<complex> ret(n);
	ld r = A.R(), c = A.Arg(), a = Re(A), b = Im(A);
	r = pow(r, 1.0 / (ld)n);
	for (int i = 0; i < n; i++) {
		ret[i].set_Re(r * cos(c / (ld)n));
		ret[i].set_Im(r * sin(c / (ld)n));
		c += sm;
	}
	return ret;
}

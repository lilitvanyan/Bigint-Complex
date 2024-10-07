#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#define lli long long int
#define ld long double
#define intt bigint
using namespace std;
const lli mod = 1000000000LL;
class bigint
{
public:
	lli a[4];
	bool sign;
	bigint()
	{
		a[0] = a[1] = a[2] = a[3] = 0;
		sign = false;
	}
	bigint(lli a)
	{
		if (a < 0) sign = true, a = -a;
		this->a[3] = a % mod;
		this->a[2] = a / mod;
	}
	bigint(lli a, lli b)
	{
		if (b < 0 && a < 0) sign = true, a = -a, b = -b;
		else sign = false;
		this->a[3] = b % mod;
		this->a[2] = b / mod;
		this->a[1] = a % mod;
		this->a[0] = a / mod;
	}

	void operator=(lli b)
	{
		if (b < 0) sign = 1, b = -b;
		a[3] = b % mod;
		a[2] = b / mod;
		a[0] = a[1] = 0;
	}
	void operator=(string s)
	{
		if (s[0] == '-') sign = true, s.erase(0, 1);
		else sign = false;
		lli sm = 0;
		for (int i = 0; i < (int)s.length() - 27; i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a[0] = sm / 10LL, sm = 0;
		for (int i = max(0, (int)s.length() - 27); i < (int)s.length() - 18; i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a[1] = sm / 10LL, sm = 0;
		for (int i = max(0, (int)s.length() - 18); i < (int)s.length() - 9; i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a[2] = sm / 10LL, sm = 0;
		for (int i = max(0, (int)s.length() - 9); i < (int)s.length(); i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a[3] = sm / 10LL, sm = 0;
	}
};
const bigint bigint_MAX(mod* mod - 1, mod* mod - 1);
const bigint bigint_MIN(-mod * mod + 1, -mod * mod + 1);


bigint operator-(bigint a)
{
	a.sign ^= 1;
	return a;
}

//hamematutyan
bool operator==(bigint a, bigint b)
{
	if (a.sign != b.sign) return false;
	for (int i = 0; i < 4; i++) if (a.a[i] != b.a[i]) return false;
	return true;
}
bool operator!=(bigint a, bigint b)
{
	if (a.sign != b.sign) return true;
	for (int i = 0; i < 4; i++) if (a.a[i] != b.a[i]) return true;
	return false;
}
bool operator>(bigint a, bigint b)
{
	if (a.sign && !b.sign) return false;
	if (!a.sign && b.sign) return true;
	if (a.sign && b.sign) return -b > -a;
	for (int i = 0; i < 4; i++)
	{
		if (a.a[i] > b.a[i]) return true;
		if (a.a[i] < b.a[i]) return false;
	}
	return false;
}
bool operator<(bigint a, bigint b)
{
	return b > a;
}
bool operator>=(bigint a, bigint b)
{
	return (a > b || a == b);
}
bool operator<=(bigint a, bigint b)
{
	return ((b > a) || (a == b));
}

//hanrahashvakan
bigint operator+(bigint a, bigint b)
{
	bigint c;
	int y;
	if (a.sign == b.sign) {
		c.sign = a.sign;
		for (int i = 0; i < 4; i++)
		{
			c.a[i] = a.a[i] + b.a[i];
		}
		for (int i = 2; i >= 0; i--) c.a[i] += c.a[i + 1] / mod, c.a[i + 1] %= mod;
		c.a[0] %= mod;
		return c;
	}
	if (!a.sign && b.sign)
	{
		b.sign = 0;
		if (a >= b)
		{
			for (int i = 3; i > 0; i--)
			{
				if (a.a[i] >= b.a[i])
				{
					c.a[i] = a.a[i] - b.a[i];
				}
				else {
					lli o = a.a[i];
					int qan = 1;
					int modd = 1;
					while (o / 10 > 0)
					{
						o /= 10;
						qan++;
					}
					for (int i = 0; i < qan; i++)
					{
						modd *= 10LL;
					}
					o = a.a[i] * modd;
					c.a[i] = o - b.a[3];
					a.a[i - 1]--;
				}

			}
			c.a[0] = a.a[0] - b.a[0];
			for (int i = 2; i >= 0; i--) c.a[i] += c.a[i + 1] / mod, c.a[i + 1] %= mod;
			c.a[0] %= mod;
			for (int i = 3; i > 0; i--)
			{
				if (c.a[i] < 0) c.a[i] += mod, c.a[i - 1]--;
			}
			return c;
		}
		else
		{
			for (int i = 3; i > 0; i--)
			{
				if (b.a[i] >= a.a[i])
				{
					c.a[i] = b.a[i] - a.a[i];
				}
				else {
					lli o = b.a[i];
					int qan = 1;
					int modd = 1;
					while (o / 10 > 0)
					{
						o /= 10;
						qan++;
					}
					for (int i = 0; i < qan; i++)
					{
						modd *= 10;
					}
					o = b.a[i] * modd;
					c.a[i] = o - a.a[i];
					b.a[i - 1]--;
				}
			}
			c.a[0] = b.a[0] - a.a[0];
			c.sign = 1;
			b.sign = 1;
			for (int i = 2; i >= 0; i--) c.a[i] += c.a[i + 1] / mod, c.a[i + 1] %= mod;
			c.a[0] %= mod;
			for (int i = 3; i > 0; i--)
			{
				if (c.a[i] < 0) c.a[i] += mod, c.a[i - 1]--;
			}
			return c;
		}

	}
	if (a.sign && !b.sign)
	{
		return b + a;
	}
}
bigint operator+(bigint a, lli b)
{
	bigint c;
	if (b < 0) b = -b, c.sign = true;
	c.a[3] = b % mod, c.a[2] = b / mod;
	return a + c;
}
bigint operator+(lli b, bigint a)
{
	bigint c;
	if (b < 0) b = -b, c.sign = true;
	c.a[3] = b % mod, c.a[2] = b / mod;
	return a + c;
}

bigint operator-(bigint a, bigint b)
{
	return a + (-b);
}
bigint operator-(bigint a, lli b)
{
	bigint c;
	if (b < 0) b = -b, c.sign = true;
	c.a[3] = b % mod, c.a[2] = b / mod;
	return a - c;
}
bigint operator-(lli b, bigint a)
{
	bigint c;
	if (b < 0) b = -b, c.sign = true;
	c.a[3] = b % mod, c.a[2] = b / mod;
	return c - a;
}

bigint operator*(bigint a, lli b)
{
	if (b < 0) a.sign ^= 1, b = -b;
	bigint c = a;
	for (int i = 0; i < 4; i++) a.a[i] = a.a[i] * (b % mod);
	for (int i = 2; i >= 0; i--) a.a[i] += a.a[i + 1] / mod, a.a[i + 1] %= mod;
	a.a[0] %= mod;
	for (int i = 0; i < 3; i++) c.a[i] = c.a[i + 1];
	c.a[3] = 0;
	for (int i = 0; i < 4; i++) c.a[i] = c.a[i] * (b / mod);
	for (int i = 2; i >= 0; i--) c.a[i] += c.a[i + 1] / mod, c.a[i + 1] %= mod;
	c.a[0] %= mod;
	c = c + a;
	return c;
}
bigint operator*(lli b, bigint a)
{
	return a * b;
}
bigint operator*(bigint a, bigint b)
{
	bigint c = a * b.a[3];
	c = c + (a * b.a[2]) * mod;
	c = c + ((a * b.a[1]) * mod) * mod;
	c = c + (((a * b.a[0]) * mod) * mod) * mod;
	c.sign = a.sign ^ b.sign;
	return c;
}

bigint operator/(bigint a, lli b)
{
	if (b < 0) b = -b, a.sign ^= 1;
	for (int i = 0; i < 3; i++)
	{
		a.a[i + 1] = a.a[i + 1] + (a.a[i] % b) * mod;
		a.a[i] /= b;
	}
	a.a[3] /= b;
	for (int i = 2; i >= 0; i--) a.a[i] = a.a[i] + a.a[i + 1] / mod, a.a[i + 1] %= mod;
	a.a[0] %= mod;
	return a;
}
bigint operator/(bigint a, bigint b)
{
	bigint c;
	bool sgn = (a.sign ^ b.sign);

	if (!b.a[0] && !b.a[1])
	{
		lli d = b.a[2] * mod + b.a[3];
		if (b.sign) d = -d;
		return a / d;
	}
	a.sign = b.sign = 0;
	lli l = 0, r = mod * mod;
	while (l <= r)
	{
		lli md = r - (r - l) / 2LL;
		if (md * b <= a) c = md, l = md + 1;
		else r = md - 1;
	}
	c.sign = sgn;
	return c;

}
bigint operator/(lli b, bigint a)
{
	bigint c;
	c.a[3] = b;
	return b / a;
}

bigint operator%(bigint a, bigint b)
{
	return a - (a / b) * b;
}
lli operator%(bigint a, lli b)
{
	lli c = a.a[2] * mod + a.a[3];
	if (a.sign) c = -c;
	return c % b;
}
lli operator%(lli b, bigint a)
{
	if (a.a[0] || a.a[1]) return b;
	lli c = a.a[2] * mod + a.a[3];
	return b % c;
}

//unar
bigint operator--(bigint& a)
{
	a = a - 1;
	return a;
}
bigint operator--(bigint& a, int unused)
{
	bigint c = a;
	a = a - 1;
	return c;
}
bigint operator++(bigint& a)
{
	a = a + 1;
	return a;
}
bigint operator++(bigint& a, int unused)
{
	bigint c = a;
	a = a + 1;
	return c;
}

//veragrman
bigint operator+=(bigint& a, bigint b)
{
	a = a + b;
	return a;
}
bigint operator+=(bigint& a, lli b)
{
	bigint c(b);
	a += b;
	return a;
}
bigint operator-=(bigint& a, bigint b)
{
	a = a - b;
	return a;
}
bigint operator-=(bigint& a, lli b)
{
	bigint c(b);
	a -= c;
	return a;
}
bigint operator*=(bigint& a, bigint b)
{
	a = a * b;
	return a;
}
bigint operator/=(bigint& a, bigint b)
{
	a = a / b;
	return a;
}
bigint operator/=(bigint& a, lli b)
{
	a = a / b;
	return a;
}
lli operator%=(bigint& a, lli b)
{
	a = a % b;
	lli c = a.a[2] * mod + a.a[3];
	return c;
}
lli operator%=(lli& b, bigint a)
{
	b = b % a;
	return b;
}
ostream& operator<<(ostream& c, bigint a)
{
	bool bl = false;
	if (a.sign) cout << "-";
	for (int i = 0; i < 4; i++)
	{
		if (!bl && !a.a[i]) continue;
		lli tas = 10LL;
		if (!bl) cout << a.a[i];
		else for (int j = 0; j < 9; j++) cout << (a.a[i] / (mod / tas)) % 10LL, tas *= 10LL;
		bl = true;
	}
	if (!bl) cout << 0;
	return c;
}
istream& operator>>(istream& c, bigint& a)
{
	string s;
	cin >> s;
	if (s[0] == '-') a.sign = true, s.erase(0, 1);
	else a.sign = false;
	lli sm = 0;
	for (int i = 0; i < (int)s.length() - 27; i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a.a[0] = sm / 10LL, sm = 0;
	for (int i = max(0, (int)s.length() - 27); i < (int)s.length() - 18; i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a.a[1] = sm / 10LL, sm = 0;
	for (int i = max(0, (int)s.length() - 18); i < (int)s.length() - 9; i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a.a[2] = sm / 10LL, sm = 0;
	for (int i = max(0, (int)s.length() - 9); i < (int)s.length(); i++) sm += (lli)(s[i] - '0'), sm *= 10LL; a.a[3] = sm / 10LL, sm = 0;
	return c;
}
//functions
bigint pow(bigint a, lli b)
{
	bigint ret;
	ret = 1;
	while (b)
	{
		if (b & 1LL) ret *= a;
		a *= a;
		b >>= 1LL;
	}
	return ret;
}
bigint sqrt(bigint a)
{
	bigint l, r, x, ans;
	ans = 0;
	l = 0;
	r = mod * mod - 1;
	int sm = 0;
	while (l <= r)
	{
		sm++;
		x = (l + r) / 2;
		if ((x * x) <= a)
		{
			l = (x + 1LL);
			ans = x;
		}
		else
		{
			r = (x - 1LL);
		}
	}
	return ans;
}
bigint abs(bigint a)
{
	a.sign = 0;
	return a;
}
ld log(lli base, bigint a)
{
	ld s = 0;
	for (int i = 0; i < 4; i++)
	{
		s *= (ld)mod;
		s += (ld)a.a[i];
	}
	return log(s) / log(base);
}

string s;
bigint tob(int i1)
{
	string t;
	for (int i = i1; i < s.length(); i++)
	{
		if (s[i] < '0' || s[i] > '9') break;
		t += s[i];
	}
	bigint ret;
	ret = t;
	return ret;
}
bigint rec(int i1)
{
	vector <bigint> a;
	vector <char> c;
	for (int i = i1; i < s.length(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			a.push_back(tob(i));
			while (i < s.length() && s[i] <= '9' && s[i] >= '0') i++;
			i--;
		}
		else if (s[i] == '(')
		{
			a.push_back(rec(i + 1));
			int sm = 1;
			while (sm)
			{
				i++;
				if (s[i] == '(') sm++;
				if (s[i] == ')') sm--;
			}
		}
		else if (s[i] == ')') break;
		else c.push_back(s[i]);
	}
	//for (auto p : a) cout << p << " ";
	//cout << endl;
	//for (auto p : c) cout << p << " ";
	//cout << endl;
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i] == '*')
		{
			a[i + 1] *= a[i];
			a[i] = 0;
		}
		if (c[i] == '/')
		{
			a[i + 1] = a[i] / a[i + 1];
			a[i] = 0;
		}
	}
	bigint ret;
	ret = a[0];
	int nx = 1;
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i] == '+') nx = 1;
		else if (c[i] == '-') nx = -1;
		if (nx == 1) ret += a[i + 1];
		else ret -= a[i + 1];
	}
	return ret;
}
void find_value()
{
	cin >> s;
	cout << rec(0);
}


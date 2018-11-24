#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define ll long long
#define pii pair < int, int >
#define fr first
#define sc second
#define mk make_pair
#define sz(s) (int)s.size()
#define all(s) s.begin(), s.end()
#define OK puts("ok");
#define whatis(x) cerr << #x << " = " << x << endl;
#define pause system("pause");
#define ld long double

const ll N = (int)1e5 + 7;
const int inf = (int)1e9 + 7;
int mod = (int)1e9 + 7;
int n, k, t;
int X[N];

bool make(vector < ld > x, vector < ld > y) {
  if (x[0] < y[0]) return 0;
  int ok = 1;
  pii L, R;
  L = mk(0, 0);
  R = mk(0, 0);
  while (ok) {
    ok = 0;
    while (L.fr + 1 < sz(x) && x[L.fr + 1] >= y[R.sc]) {
      ok = 1;
      if (x[++L.fr] > x[L.sc]) L.sc = L.fr;
    }
    while (R.fr + 1 < sz(y) && y[R.fr + 1] <= x[L.sc]) {
      ok = 1;
      if (y[++R.fr] < y[R.sc]) R.sc = R.fr;
    }
  }
  return L.fr + 1 == sz(x) && R.fr + 1 == sz(y);
}

bool check(int s) {
  vector < ld > x, y;
  for (ll i = k; i >= 0; i--)
    x.pb(X[i] - (ld)2 * s * t * i);
  for (ll i = k; i < n; i++)
    y.pb(X[i] - (ld)2 * s * t * i);
  if (!make(x, y)) return 0;
  reverse(all(x));
  reverse(all(y));
  if (!make(x, y)) return 0;
  return 1;
}

main() {
  cin >> n >> k >> t;
  k--;
  for (ll i = 0; i < n; i++) {
    cin >> X[i];
  }
  int l = 0;
  int r = 1e9;
  while (l < r) {
    ll mid = (l + r) / 2;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l;
}

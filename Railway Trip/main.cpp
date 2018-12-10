#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()

const int MOD = 1000000007;
const ll INF = 1e18;
const int MX = 100001;

template<class T, int SZ> struct RMQ {
    T stor[SZ][32-__builtin_clz(SZ)];

    T comb(T a, T b) {
        return max(a,b);
    }

    void build() {
        FOR(j,1,32-__builtin_clz(SZ)) F0R(i,SZ-(1<<(j-1)))
            stor[i][j] = comb(stor[i][j-1],
                        stor[i+(1<<(j-1))][j-1]);
    }

    T query(int l, int r) {
        int x = 31-__builtin_clz(r-l+1);
        return comb(stor[l][x],stor[r-(1<<x)+1][x]);
    }
};

RMQ<int,MX> R;

int N,K,Q,L[MX];
pi bound[MX][17];
vi tmp[MX];
set<int> S;

pi nex(pi x, int y) {
    return {min(bound[x.f][y].f,bound[x.s][y].f),
            max(bound[x.f][y].s,bound[x.s][y].s)};
}

int get(vi& z, int x) {
    return ub(all(z),x)-z.begin();
}

int dist(int x, int y) {
    if (x == y) return 0;
    int t = min(L[x],L[y]);
    return get(tmp[t],y-1)-get(tmp[t],x)+1;
}

pair<int,pi> tri(int x, int y) {
    int num = 0; pi cur = {x,x};

    F0Rd(i,17) {
        pi CUR = nex(cur,i);
        if (max(L[CUR.f],L[CUR.s]) < y) {
            cur = CUR;
            num ^= 1<<i;
        }
    }
    if (max(L[cur.f],L[cur.s]) < y) {
        cur = nex(cur,0);
        num ++;
    }

    return {num,cur};
}

int solve(int A, int B) {
    int res = R.query(A,B);

    pair<int,pi> a = tri(A,res), b = tri(B,res); // first time you to at least that level

    int ans = a.f+b.f+dist(L[a.s.s] >= res ? a.s.s : a.s.f,L[b.s.f] >= res ? b.s.f : b.s.s);
    /*cout << ans << " " << A << " " << B << "\n";
    cout << res << " " << L[A] << " " << L[B] << "\n";
    cout << a.f << " " << a.s.f << " " << a.s.s << " " << b.f << " " << b.s.f << " " << b.s.s << "\n";
    cout << L[a.s.f] << " " << L[a.s.s] << " " << L[b.s.f] << " " << L[b.s.s] << "\n";*/
    // cout << ans << " " << a.f << " " << a.s.f << " " << a.s.s << " " << b.f << " " << b.s.f << " " << b.s.s << "\n";
    if (res != K) {
        a = tri(A,res+1), b = tri(B,res+1);
        if (a.s.f == b.s.f || a.s.s == b.s.s) ans = min(ans,a.f+b.f);
        else ans = min(ans,a.f+b.f+1);
    }

    return ans;
}

void init() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K >> Q;
    FOR(i,1,N+1) {
        cin >> L[i];
        R.stor[i][0] = L[i];
        tmp[L[i]].pb(i);
    }
    R.build();
    FORd(i,1,K+1) {
        sort(all(tmp[i]));
        for (int j: tmp[i]) S.insert(j);
        for (int j: tmp[i]) {
            auto it = S.find(j);
            bound[j][0].f = (it == S.begin() ? 1 : *prev(it));
            bound[j][0].s = (next(it) == S.end() ? N : *next(it));
        }
    }
    F0R(j,16) FOR(i,1,N+1) bound[i][j+1] = nex(bound[i][j],j);
}

int main() {
    init();
    F0R(i,Q) {
        int A,B; cin >> A >> B;
        if (A > B) swap(A,B);
        cout << solve(A,B)-1 << "\n";
    }
}

/* Look for:
* the exact constraints (multiple sets are too slow for n=10^6 :( )
* special cases (n=1?)
* overflow (ll vs int?)
* array bounds
* if you have no idea just guess the appropriate well-known algo instead of doing nothing :/
*/

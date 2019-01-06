#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
int n;
ll c;
const int N=2e5+5;
const int H=1e6+1;
vector<int> h(N);
struct func{
    int h;
    ll c;
};
ll get(func f,int pos)
{
    return (ll)(pos-f.h)*(pos-f.h)+c+f.c;
}
struct LiChao{
    vector<func> f;
    void init(func fe)
    {
        f.resize(4*H);
        fill(all(f),fe);
    }
    void add(func ne,int l=0,int r=H,int i=1)
    {
        int m=(l+r)>>1;
        bool le=get(ne,l)<get(f[i],l);
        bool mid=get(ne,m)<get(f[i],m);
        if(mid)
            swap(f[i],ne);
        if(r-l==1)
            return;
        if(le!=mid)
            add(ne,l,m,2*i);
        else
            add(ne,m,r,2*i+1);
    }
    ll gett(int pos,int l=0,int r=H,int i=1)
    {
        if(r-l==1)
            return get(f[i],pos);
        int m=(l+r)>>1;
        if(pos<m)
            return min(get(f[i],pos),gett(pos,l,m,2*i));
        return min(get(f[i],pos),gett(pos,m,r,2*i+1));
    }
} st;
int main()
{
    scanf("%i %lld",&n,&c);
    for(int i=0;i<n;i++)
        cin >> h[i];
    func en={h[n-1],0};
    st.init(en);
    for(int i=n-2;i>0;i--)
    {
        func tr={h[i],st.gett(h[i])};
        st.add(tr);
    }
    printf("%lld\n",st.gett(h[0]));
    return 0;
}

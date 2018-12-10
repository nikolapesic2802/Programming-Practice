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
const int N=1e6+5;
vector<int> perm(N);
struct s{
    set<pair<int,int> > inc,dec;
    int inc_delta,dec_delta;
    set<pair<int,int> >::iterator it;
    void reset()
    {
        inc.clear();
        dec.clear();
        inc_delta=0;
        dec_delta=0;
    }
    void insert_inc(int p,int k=1)
    {
        //printf("Dodajem %i u inc!\n",p);
        p-=inc_delta;
        it=inc.lower_bound({p,0});
        if(it==inc.end()||(*it).first!=p)
            inc.insert({p,k});
        else
        {
            int t=(*it).second;
            inc.erase(it);
            inc.insert({p,t+k});
        }
    }
    void insert_dec(int p,int k=1)
    {
        //printf("Dodajem %i u dec!\n",p);
        p-=dec_delta;
        it=dec.lower_bound({p,0});
        if(it==dec.end()||(*it).first!=p)
            dec.insert({p,k});
        else
        {
            int t=(*it).second;
            dec.erase(it);
            dec.insert({p,t+k});
        }
    }
    int get_max()
    {
        int ret=0;
        int cnt=0;
        if(dec.size())
        {
            cnt++;
            it=dec.end();
            it--;
            int v=(*it).first+dec_delta;
            ret=max(ret,v);
        }
        if(inc.size())
        {
            cnt++;
            it=inc.end();
            it--;
            int v=(*it).first+inc_delta;
            ret=max(ret,v);
        }
        assert(cnt!=0);
        return ret;
    }
    void doit()
    {
        if(dec.size())
        {
            it=dec.begin();
            int v=(*it).first+dec_delta;
            if(v<=0)
            {
                int t=(*it).second;
                assert(v==0);
                dec.erase(it);
                insert_inc(0,t);
            }
        }
        if(inc.size())
        {
            it=inc.end();
            it--;
            int v=(*it).first+inc_delta;
            if(v>n/2)
            {
                int t=(*it).second;
                assert(v==n/2+1);
                inc.erase(it);
                insert_dec(n-v,t);
            }
        }
    }
    void increase()
    {
        dec_delta--;
        inc_delta++;
        doit();
    }
    void print()
    {
        /*printf("INC:\n");
        for(auto p:inc)
        {
            for(int i=0;i<p.second;i++)
                printf("%i ",p.first+inc_delta);
        }
        printf("\nDEC:\n");
        for(auto p:dec)
            for(int i=0;i<p.second;i++)
                printf("%i ",p.first+dec_delta);
        printf("\n");*/
    }
} st;
int main()
{
    scanf("%i",&n);
    vector<int> s1,s2;
    for(int i=0;i<n;i++){
        int a;
        scanf("%i",&a);
        a--;
        if(a>=i)
        {
            int d=a-i;
            if(d<=n/2)
            {
                s1.pb(d);
                //st.insert_dec(d);
            }
            else
            {
                s2.pb(n-d);
                //st.insert_inc(n-d);
            }
        }
        else
        {
            int d=i-a;
            if(d<=n/2)
            {
                s2.pb(d);
                //st.insert_inc(d);
            }
            else
            {
                s1.pb(n-d);
                //st.insert_dec(n-d);
            }
        }
    }
    st.reset();
    for(auto p:s1)
        st.insert_inc(p);
    for(auto p:s2)
        st.insert_dec(p);
    st.print();
    st.doit();
    st.print();
    int sol=n;
    for(int i=0;i<n;i++)
    {
        sol=min(sol,st.get_max());
        st.increase();
        st.print();
    }
    st.reset();
    for(auto p:s1)
        st.insert_dec(p);
    for(auto p:s2)
        st.insert_inc(p);
    st.doit();
    for(int i=0;i<n;i++)
    {
        sol=min(sol,st.get_max());
        st.increase();
    }
    printf("%i\n",sol);
    return 0;
}

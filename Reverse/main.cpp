/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2003/reverse.pdf
*/
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
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '[' << a.f << ", " << a.s << ']'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ",";os << a[i];}return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
const int N=9;
vector<int> s(N+1);
vector<pair<int,int> > q;
int n,trN=87,k=2;
void doStep(int a,int b,int c,int d)
{
    trN-=k+1;
    if(s[a]==-1)
        s[a]=trN;
    int uzeo=k+1;
    if(c==-1)
        uzeo=0;
    for(int i=k;i>=0;i--)
    {
        if(i)
            q.pb({a,b});
        for(int j=1;j<i;j++)
            q.pb({b,b});
        if(i<k&&uzeo){
            if(uzeo==k+1)
                q.pb({c,d});
            else
                q.pb({d,d});
            uzeo--;
        }
        for(int j=i+1;j<k&&uzeo;j++)
            q.pb({d,d}),uzeo--;
        if(i==0)
            b=a;
        q.pb({-1,b});
    }
}
void gen()
{
    fill(all(s),-1);
    s[N]=n;
    vector<pair<pair<int,int>,pair<int,int> > > operacije;
    operacije.pb({{8,9},{-1,-1}});
    operacije.pb({{7,9},{6,8}});
    vector<int> chain={8,6};
    for(int i=5;i>=1;i--)
    {
        vector<int> newChain={i};
        for(auto p:chain)
            operacije.pb({{p,9},{newChain.back(),operacije.back().f.f}}),newChain.pb(operacije.back().s.s);
        reverse(all(newChain));
        chain=newChain;
    }
    for(auto p:chain)
        operacije.pb({{p,9},{-1,-1}});
    q.pb({-1,9});
    for(auto p:operacije)
        doStep(p.f.f,p.f.s,p.s.f,p.s.s);
}
int main()
{
	for(int kk=4;kk<7;kk++)
    {
        if(k==7||k==8||k==10||k==11)
            continue;
        string in="reverse.";
        if(kk>9)
            in+='0'+kk/10;
        in+='0'+kk%10;
        in+=".in";
        freopen(in.c_str(),"r",stdin);
        scanf("%i %i",&n,&n);
        string out;
        out+='0'+(kk+1)/10;
        out+='0'+(kk+1)%10;
        out+=".out";
        freopen(out.c_str(),"w",stdout);
        printf("FILE reverse %i\n",kk+1);
        trN=87;k=2;
        while(trN<n)
            trN+=29,k++;
        trN=n;
        q.clear();
        gen();
        for(int i=1;i<=N;i++)
            s[i]=max(s[i],0);
        for(int i=1;i<=N;i++)
            printf("%i ",s[i]);
        printf("\n");
        int m=q.size();
        vector<int> visited(n+1);
        vector<bool> good(m);
        for(int i=0;i<m;i++)
        {
            auto p=q[i];
            if(p.f==-1)
            {
                if(visited[s[p.s]])
                    good[i]=false;
                else
                    good[i]=true,visited[s[p.s]]=1;
            }
            else
                s[p.s]=s[p.f]+1;
        }
        bool dobro;
        for(int i=m-1;i>=0;i--)
        {
            auto p=q[i];
            if(p.f==-1)
                dobro=good[i];
            else
                good[i]=dobro;
        }
        for(int i=0;i<m;i++)
        {
            if(!good[i])
                continue;
            auto p=q[i];
            if(p.f==-1)
                printf("P %i\n",p.s);
            else
                printf("S %i %i\n",p.f,p.s);
        }
    }
    return 0;
}

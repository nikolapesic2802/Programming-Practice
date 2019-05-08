#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

int n;
struct trieNode{
    int kraj,cnt;
    map<int,int> nxt;
};
vector<trieNode> Trie;
map<int,int> empt;
int newNode()
{
    Trie.pb({-1,0,empt});
    return Trie.size()-1;
}
int root;
void add(string s,int pos,int ind,int tr=root)
{
    if(pos==(int)s.size())
    {
        if(Trie[tr].kraj==-1)
            Trie[tr].kraj=ind;
        return;
    }
    int nxt=s[pos]-'a';
    if(Trie[tr].nxt.find(nxt)==Trie[tr].nxt.end()){
        int a=newNode();
        Trie[tr].nxt[nxt]=a;
    }
    add(s,pos+1,ind,Trie[tr].nxt[nxt]);
}
void inc(string s,int pos,int tr=root)
{
    Trie[tr].cnt++;
    if(pos==(int)s.size())
        return;
    int nxt=s[pos]-'a';
    inc(s,pos+1,Trie[tr].nxt[nxt]);
}
int getkraj(string s,int pos,int tr=root)
{
    if(pos==(int)s.size())
    {
        if(Trie[tr].kraj!=-1)
            return Trie[tr].kraj;
        return n;
    }
    int nxt=s[pos]-'a';
    if(Trie[tr].nxt.find(nxt)==Trie[tr].nxt.end())
        return n;
    return getkraj(s,pos+1,Trie[tr].nxt[nxt]);
}
int getcnt(string s,int pos,int tr=root)
{
    int sol=Trie[tr].cnt;
    if(pos==(int)s.size())
        return sol;
    int nxt=s[pos]-'a';
    if(Trie[tr].nxt.find(nxt)==Trie[tr].nxt.end())
        return sol;
    return sol+getcnt(s,pos+1,Trie[tr].nxt[nxt]);
}
int main()
{
    root=newNode();
    freopen("baza.in.10","r",stdin);
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
	cin >> n;
	vector<string> niz(n);
	for(int i=0;i<n;i++)
        cin >> niz[i],add(niz[i],0,i);
    int q;
    cin >> q;
    vector<pair<pair<int,int>,string> > qu(q);
    vector<int> ans(q);
    for(int i=0;i<q;i++)
    {
        cin >> qu[i].s;
        qu[i].f.s=i;
        qu[i].f.f=getkraj(qu[i].s,0);;
    }
    sort(all(qu));
    //cout << qu << endl;
    int tr=0;
    for(auto p:qu)
    {
        while(p.f.f>=tr&&tr<n)
        {
            inc(niz[tr],0);
            tr++;
        }
        ans[p.f.s]=getcnt(p.s,0);
    }
    for(int i=0;i<q;i++)
        printf("%i\n",ans[i]);
    return 0;
}

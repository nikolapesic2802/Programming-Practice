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
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
vector<int> primes;
const int N=1e7;
vector<bool> visited(N);
struct Node{
    int size,val,l,r;
    Node()
    {
        size=1;
        l=r=0;
    }
};
vector<Node> nodes;
int root;
int splay(int position,int tr=root)
{
    //printf("Splayujem %i %i\n",position,tr);
    if(position-nodes[nodes[tr].l].size-1==0)
        return tr;
    if(position<=nodes[nodes[tr].l].size)
    {
        nodes[tr].l=splay(position,nodes[tr].l);
        int ret=nodes[tr].l;
        int b=nodes[nodes[tr].l].r;
        int c=nodes[tr].r;
        nodes[nodes[tr].l].size=nodes[tr].size;
        nodes[tr].size=nodes[b].size+nodes[c].size+1;
        nodes[nodes[tr].l].r=tr;
        nodes[tr].l=b;
        nodes[tr].r=c;
        return ret;
    }
    else
    {
        nodes[tr].r=splay(position-nodes[nodes[tr].l].size-1,nodes[tr].r);
        int ret=nodes[tr].r;
        int b=nodes[nodes[tr].r].l;
        int a=nodes[tr].l;
        nodes[nodes[tr].r].size=nodes[tr].size;
        nodes[tr].size=nodes[a].size+nodes[b].size+1;
        nodes[nodes[tr].r].l=tr;
        nodes[tr].l=a;
        nodes[tr].r=b;
        return ret;
    }
}
int deleted;
int del(int tr=root)
{
    if(nodes[tr].l==0)
    {
        deleted=tr;
        return nodes[tr].r;
    }
    nodes[tr].l=del(nodes[tr].l);
    nodes[tr].size--;
    return tr;
}
void insert(int position,int p,int tr=root)
{
    //printf("Insertujem %i  %i  %i\n",position,p,tr);
    if(position<=nodes[nodes[tr].l].size)
    {
        if(nodes[tr].l==0)
            nodes[tr].l=p;
        else
            insert(position,p,nodes[tr].l);
        nodes[tr].size++;
        return;
    }
    if(nodes[tr].r==0)
        nodes[tr].r=p;
    else
        insert(position-nodes[nodes[tr].l].size-1,p,nodes[tr].r);
    nodes[tr].size++;
    return;
}
vector<int> order;
void get(int tr)
{
    if(tr==0)
        return;
    //printf("Getujem %i\n",tr);
    get(nodes[tr].l);
    order.pb(nodes[tr].val);
    get(nodes[tr].r);
}
void print(int n)
{
    printf("Root:%i\n",root);
    for(int i=1;i<=n;i++)
        printf("%i: Left: %i Right: %i\n",i,nodes[i].l,nodes[i].r);
}
void doit(int times)
{
    if(times==0)
        return;
    root=splay(times,root);
    int newroot=nodes[root].r;
    nodes[root].r=0;
    nodes[root].size=nodes[nodes[root].l].size+1;
    newroot=splay(nodes[newroot].size,newroot);
    nodes[newroot].r=root;
    nodes[newroot].size+=nodes[root].size;
    root=newroot;
}
int main()
{
    int n,k,a;
    scanf("%i %i %i",&n,&k,&a);
	for(int i=2;i<N;i++)
    {
        if(!visited[i])
            primes.pb(i);
        if(primes.size()==k)
            break;
        for(auto p:primes)
        {
            if(i*p>=N)
                break;
            visited[p*i]=1;
            if(i%p==0)
                break;
        }
    }
    nodes.resize(n+1);
    for(int i=1;i<=n;i++)
        nodes[i].val=i;
    nodes[0].size=0;
    root=1;
    for(int i=2;i<=n;i++)
    {
        //print(n);
        insert(i,i,root);
        //print(n);
        root=splay(i,root);
    }
    //print(n);
    for(int i=0;i<k;i++)
    {
        if(i%100==0)
            printf("%i: %i\n",i,primes[i]);
        //print(n);
        root=del(root);
        root=splay(1,root);
        //print(n);
        //print(n);
        nodes[deleted].l=0;
        nodes[deleted].r=0;
        nodes[deleted].size=1;
        int gde=primes[i]%n+1;
        int times=(primes[i]/n)%(n-1);
        doit(times);
        //print(n);
        insert(gde-1,deleted,root);
        //print(n);
        //print(n);
        root=splay(gde,root);
        //print(n);
    }
    //printf("??\n");
    get(root);
    get(root);
    //cout << order;
    //print(n);1
    for(int i=1;i<order.size();i++)
    {
        if(order[i]==a)
        {
            printf("%i %i\n",order[i+1],order[i-1]);
            return 0;
        }
    }
    return 0;
}

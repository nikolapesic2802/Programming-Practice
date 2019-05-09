/*
    -Basic idea:
        -Build a trie on the words.
        -For every query, find the index of the first word that is the same as the query (if there is one)
        -Do the queries offline (sort them by the index of the first word that is the same) and for every query only count the words that have index up to and including the index of the same word.
    -Memory optimizations:
        -Use char[] and cnar* instead of string.
        -Build a trie based only on words that appear in the given words and in the queries.
        -Build a trie that is slower but more memory effective (only storing the next characters that we have, and not even in a map but in a vector)
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()
using namespace std;

int n;
vector<pair<short,vector<pair<char,int> > > > trie;
vector<pair<char,int> > empt;
int cnt=0;
int newNode()
{
    trie.pb({-1,empt});
    cnt++;
    return trie.size()-1;
}
int root;
void construct(char *s,char pos,int tr=root)
{
    if(s[pos]==0)
        return;
    int koji=-1;
    for(auto p:trie[tr].s)
        if(p.f==s[pos])
            koji=p.s;
    if(koji==-1){
        int a=newNode();
        trie[tr].s.pb({s[pos],a});
        koji=a;
    }
    construct(s,pos+1,koji);
}
void add(char* s,char pos,int ind,int tr=root)
{
    if(s[pos]==0)
    {
        if(trie[tr].f==-1)
            trie[tr].f=ind;
        return;
    }
    int koji=-1;
    for(auto p:trie[tr].s)
        if(p.f==s[pos])
            koji=p.s;
    if(koji==-1){
        return;
    }
    add(s,pos+1,ind,koji);
}
void inc(char* s,char pos,int tr=root)
{
    trie[tr].f++;
    if(s[pos]==0)
        return;
    int koji=-1;
    for(auto p:trie[tr].s)
        if(p.f==s[pos])
            koji=p.s;
    if(koji==-1)
        return;
    inc(s,pos+1,koji);
}
int getkraj(char* s,char pos,int tr=root)
{
    if(s[pos]==0)
    {
        if(trie[tr].f!=-1)
            return trie[tr].f;
        return n;
    }
    int koji=-1;
    for(auto p:trie[tr].s)
        if(p.f==s[pos])
            koji=p.s;
    if(koji==-1)
        return n;
    return getkraj(s,pos+1,koji);
}
int getcnt(char* s,char pos,int tr=root)
{
    int sol=trie[tr].f;
    if(s[pos]==0)
        return sol;
    int koji=-1;
    for(auto p:trie[tr].s)
        if(p.f==s[pos])
            koji=p.s;
    if(koji==-1)
        return sol;
    return sol+getcnt(s,pos+1,koji);
}
const int mod=1e9+7;
int main()
{
    root=newNode();
    //freopen("baza.in.10","r",stdin);
	scanf("%i",&n);
	char niz[n][30];
	for(int i=0;i<n;i++)
        scanf("%s",niz[i]);
    vector<int> h;
    for(int i=0;i<n;i++)
    {
        int hh=0;
        for(int j=0;j<30;j++)
        {
            if(niz[i][j]==0)
                break;
            hh=(ll)hh*28%mod;
            hh+=niz[i][j]-'a'+1;
            if(hh>=mod)
                hh-=mod;
            h.pb(hh);
        }
    }
    sort(all(h));
    int q;
    scanf("%i",&q);
    char qq[q][30];
    for(int i=0;i<q;i++)
        scanf("%s",qq[i]);
    char aa[q][30];
    for(int i=0;i<q;i++)
    {
        int hh=0;
        int last=0;
        for(int j=0;j<30;j++)
        {
            if(qq[i][j]==0)
                break;
            hh=(ll)hh*28%mod;
            hh+=qq[i][j]-'a'+1;
            if(hh>=mod)
                hh-=mod;
            int l=0,r=h.size()-1;
            while(l<r)
            {
                int m=(l+r)>>1;
                if(h[m]<hh)
                    l=m+1;
                else
                    r=m;
            }
            if(h[l]==hh)
                last=j+1;
        }
        for(int j=0;j<last;j++)
            aa[i][j]=qq[i][j];
        aa[i][last]=0;
    }
    h.clear();
    for(int i=0;i<q;i++)
        construct(aa[i],0);
    for(int i=0;i<n;i++)
        add(niz[i],0,i);
    vector<pair<pair<short,short>,char*> > qu(q);
    int ans[q];
    for(int i=0;i<q;i++)
    {
        qu[i].s=qq[i];
        qu[i].f.s=i;
        qu[i].f.f=getkraj(qq[i],0);;
    }
    for(auto &p:trie)
        p.f=0;
    sort(all(qu));
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

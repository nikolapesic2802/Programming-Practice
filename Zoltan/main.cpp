/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest3_solutions/solutions.pdf
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;

const int mod=1e9+7;
int add(int a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
    return a;
}
int multi(int a,int b)
{
    ll t=(ll)a*b;
    if(t>mod)
        t%=mod;
    return t;
}
const int N=2e5+5;
vector<int> duzina(N);
vector<int> start(N);
void update(int i,int d,int s)
{
    for(;i<N;i+=i&(-i))
    {
        if(duzina[i]==d)
        {
            start[i]=add(start[i],s);
        }
        if(duzina[i]<d)
        {
            duzina[i]=d;
            start[i]=s;
        }
    }
}
pair<int,int> get(int i)
{
    int d=0;
    int s=0;
    for(;i;i-=i&(-i))
    {
        if(duzina[i]==d)
        {
            s=add(s,start[i]);
        }
        if(duzina[i]>d)
        {
            d=duzina[i];
            s=start[i];
        }
    }
    return make_pair(d,s);
}
vector<int> powers(N);
int main()
{
    powers[0]=1;
    for(int i=1;i<N;i++)
        powers[i]=add(powers[i-1],powers[i-1]);
    int n;
	scanf("%i",&n);
	vector<int> niz,niz1(n);
	for(int i=0;i<n;i++)
        scanf("%i",&niz1[i]);
    vector<int> ss=niz1;
    sort(all(ss));
    ss.erase(unique(all(ss)),ss.end());
    map<int,int> mapa;
    for(int i=0;i<ss.size();i++)
        mapa[ss[i]]=i+1;
    for(int i=0;i<n;i++)
        niz.pb(mapa[niz1[i]]);
    reverse(all(niz));
    vector<pair<int,int> > f,b;
    for(auto p:niz)
    {
        int best;
        int num;
        tie(best,num)=get(p);
        if(best==0)
            num=1;
        best++;
        f.pb({best,num});
        update(p+1,best,num);
    }
    for(int i=0;i<N;i++)
        duzina[i]=0,start[i]=0;
    vector<int> rev;
    for(auto p:niz)
    {
        rev.pb(N-p);
    }
    niz=rev;
    for(auto p:niz)
    {
        int best;
        int num;
        tie(best,num)=get(p);
        if(best==0)
            num=1;
        best++;
        b.pb({best,num});
        update(p+1,best,num);
    }
    int best=0;
    int sum=0;
    for(int i=0;i<n;i++)
    {
        int p=f[i].f+b[i].f-1;
        int num=multi(powers[n-p],multi(f[i].s,b[i].s));
        if(best==p)
            sum=add(sum,num);
        if(best<p)
        {
            best=p;
            sum=num;
        }
    }
    printf("%i %i\n",best,sum);
}

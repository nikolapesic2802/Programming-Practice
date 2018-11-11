#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
const int N=1000050;
const int K=N/4;
const int M=K*62;
int root,go[M][2],tsz,sz[M];
void Insert(int &c, int lvl, ll X)
{
	if(!c) c=++tsz;
	sz[c]++;
	if(lvl<=-1) return;
	Insert(go[c][(X>>lvl)&1],lvl-1,X);
}
ll sum=0;
ll A;
void Get(int c, int lvl, ll X, ll Y)
{
	if(lvl==-1)
	{
		if(A<=Y) sum+=sz[c];
		return;
	}
    int g=((X>>lvl)&1);
    if(A+(((ll)1)<<lvl)-1<=Y) sum+=sz[go[c][g]],A+=((ll)1)<<lvl,Get(go[c][g^1],lvl-1,X,Y);
    else Get(go[c][g],lvl-1,X,Y);
}
void Clear()
{
	while(tsz)
	{
		go[tsz][0]=go[tsz][1]=sz[tsz]=0;
		tsz--;
	}
	root=0;
}
int par[N];
ll dep[N];
void fastscan(ll &number)
{
    bool negative = false;
    register int c;

    number = 0;
    c = getchar();
    if (c=='-')
    {
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
    if (negative)
        number *= -1;
}
void fastscan(int &number)
{
    bool negative = false;
    register int c;

    number = 0;
    c = getchar();
    if (c=='-')
    {
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
    if (negative)
        number *= -1;
}

int main()
{
	int n,i;ll k;
	fastscan(n);
	fastscan(k);
	//scanf("%i %lld",&n,&k);
	for(i=2;i<=n;i++) fastscan(par[i]),fastscan(dep[i]),dep[i]^=dep[par[i]];
	ll top=(((ll)1)<<62)-1,bot=0,mid,ans;
	int a=n/4,b=n*2/4,c=n*3/4;
	if(n<K-100) for(i=1;i<=n;i++) Insert(root,61,dep[i]);
	while(top>=bot)
	{
        mid=top+bot>>1;
        if(n>=K-100)
		{
			sum=0;
			Clear();
			for(i=1;i<=a;i++) Insert(root,61,dep[i]);
			for(i=1;i<=n;i++)
			{
				A=0;
				Get(root,61,dep[i],mid);
			}
			Clear();
			for(i=a+1;i<=b;i++) Insert(root,61,dep[i]);
			for(i=1;i<=n;i++)
			{
				A=0;
				Get(root,61,dep[i],mid);
			}
			Clear();
			for(i=b+1;i<=c;i++) Insert(root,61,dep[i]);
			for(i=1;i<=n;i++)
			{
				A=0;
				Get(root,61,dep[i],mid);
			}
			Clear();
			for(i=c+1;i<=n;i++) Insert(root,61,dep[i]);
			for(i=1;i<=n;i++)
			{
				A=0;
				Get(root,61,dep[i],mid);
			}
		}
		else
		{
			sum=0;
			for(i=1;i<=n;i++)
			{
				A=0;
				Get(root,61,dep[i],mid);
			}
		}
		//printf("%lld %lld\n",mid,sum);
		if(sum>=k) ans=mid,top=mid-1;
		else bot=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}

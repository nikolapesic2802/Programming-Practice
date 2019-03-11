#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;

int power(int n,int k)
{
    int ans=1;
    while(k>0)
    {
        if(k%2==1)
            ans=ans*n;
        n=n*n;
        k=k/2;
    }
    return ans;
}
int N=1e3;
vector<int> visited(N);
int nzd(int a,int b)
{
    if(b==0)
        return a;
    return nzd(b,a%b);
}
int nzs(int a,int b)
{
    return a*b/nzd(a,b);
}
struct pt{
    double x,y;
    pt operator-(pt a){return {x-a.x,y-a.y};}
    pt operator+(pt a){return {x+a.x,y+a.y};}
    pt operator*(double a){return {x*a,y*a};}
    pt operator/(double a){return {x/a,y/a};}
};
bool operator==(pt a,pt b){return a.x==b.x&&a.y==b.y;}
bool operator!=(pt a,pt b){return !(a==b);}
double sq(pt p){return p.x*p.x+p.y*p.y;}
double dist(pt p){return sqrt(sq(p));}
ostream& operator<<(ostream& os,pt p){return os << "(" << p.x << "," << p.y << ")";}

int main()
{
    ///O(N log N)
    int niz[20];
    sort(niz,niz+20);
    reverse(niz,niz+20);
    ///O(log N)
    printf("%i %i\n",nzd(10,5),nzs(10,5));
    ///O(N log N)
    vector<int> prost;
    for(int i=2;i<N;i++)
    {
        if(visited[i])
            continue;
        prost.pb(i);
        for(int j=i;j<N;j+=i)
            visited[j]=1;
    }
    ///O(sqrt(N))
    int n=11;
    vector<int> cinioci;
    for(int i=2;i*i<=n;i++)
    {
        while(n%i==0)
        {
            cinioci.pb(i);
            n/=i;
        }
    }
    if(n!=1)
        cinioci.pb(n);
    ///O(log N)
	printf("%i\n",power(2,3));
    return 0;
}

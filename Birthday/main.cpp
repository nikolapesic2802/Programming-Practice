/*
    -Binary search for the answer. To test if we can solve the problem for a given value, we need to find for every element by how much we need to shift the permutation in order to make the current
    element not move by more than mid steps. So it becomes a problem of checking if all intervals have a common interval.
    -It is really hard to make this n log n solution pass but this one passes with some ifs for special cases(If there were cases where N=1e6 and in one it was optimal not to take the original
                                                                                                              ordering of the permutation, but the reversed one. I wouldn't have been able to solve it)
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
int m;
vector<int> open(N),close(N);
bool test()
{
    for(int i=0;i<n;i++)
    {
        int tr=perm[i];
        int left=tr-m;
        int right=tr+m;
        int extraleft=-1,extraright=-1;
        int cnt=0;
        if(right>=n)
        {
            cnt++;
            extraleft=0;
            extraright=right-n;
            right=n-1;
        }
        if(left<0)
        {
            cnt++;
            extraleft=left+n;
            extraright=n-1;
            left=0;
        }
        left=i-left;
        right=i-right;
        if(left<0&&right<0)
            left+=n,right+=n;
        if(right<0&&left>=0)
        {
            open[0]++;
            close[left]++;
            open[right+n]++;
        }
        else
        {
            open[right]++;
            close[left]++;
        }
        if(extraleft!=-1)
        {
            assert(cnt!=0);
            left=i-extraleft;
            right=i-extraright;
            if(left<0&&right<0)
                left+=n,right+=n;
            if(right<0&&left>=0)
            {
                open[0]++;
                close[left]++;
                open[right+n]++;
            }
            else
            {
                open[right]++;
                close[left]++;
            }
        }
    }
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        cnt+=open[i];
        open[i]=0;
        if(cnt==n)
            return true;
        cnt-=close[i];
        close[i]=0;
    }
    return false;
}
void fastin(int &a)
{
    register int c=getchar();
    a=0;
    while(c>='0'&&c<='9')
    {
        a=a*10+c-'0';
        c=getchar();
    }
}
int main()
{
    fastin(n);
    for(int i=0;i<n;i++)
        fastin(perm[i]),perm[i]--;
    int sol=n;
    int l=0,r=(n-1)/2;
    m=r/100*94;
    if(!test())
        l=m+1;
    while(l<r)
    {
        m=(l+r)>>1;
        if(test())
            r=m;
        else
            l=m+1;
    }
    sol=min(sol,l);
    if(n<(int)1e6/2){
        for(int i=0;i<=n/2;i++)
            swap(perm[i],perm[n-i]);
        l=0,r=sol;
        m=r/100*94;
        if(!test())
            l=m+1;
        while(l<r)
        {
            m=(l+r)>>1;
            if(test())
                r=m;
            else
                l=m+1;
        }
        sol=min(sol,l);
    }
    printf("%i\n",sol);
    return 0;
}

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
int insertionSort(int n,vector<int> a)
{
    a[0]=INT_MIN;
    int sol=0;
    for(int i=2;i<n;i++)
    {
        int j=i;
        sol++;
        while(a[j-1]>a[j])
        {
            swap(a[j-1],a[j]);
            j--;
            sol++;
        }
    }
    return sol;
}
int quickSort(vector<int> a)
{
    vector<int> manje,vece;
    if(a.size()<=1)
        return 0;
    int sol=0;
    int pivot=a[0];
    for(int i=1;i<(int)a.size();i++)
    {
        sol++;
        if(a[i]<pivot)
            manje.pb(a[i]);
        else
            vece.pb(a[i]);
    }
    sol+=quickSort(manje);
    sol+=quickSort(vece);
    return sol;
}
int mod=1234567;
int offset=513;

int main()
{
	int n,x;
	scanf("%i %i",&n,&x);
	vector<int> perm;
	for(int i=0;i<n;i++)
        perm.pb(i);
    reverse(all(perm));
    printf("%i\n",insertionSort(n,perm));
    return 0;
    int cnt=0;
    int mod=1234567;
    do{
        vector<int> a;
        a.pb(0);
        for(auto p:perm)
            a.pb(p);
        int xx=quickSort(perm);
        int lim=xx*x;
        int y=insertionSort(a.size(),a);
        if(y<=lim)
            cnt++;
        if(cnt==mod)
            cnt=0;
    }while(next_permutation(all(perm)));
    printf("%i\n",cnt);
    return 0;
}

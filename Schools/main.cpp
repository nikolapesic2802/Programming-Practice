/*
    -First greedily take the cities with the highest Ai for every music school.
    -Then go through every sport school and see if its better to take a city that hasn't been taken already or to take some city that has been chosen for music and take a new city for music.
    -We can do this by maintaining multisets for already taken and not taken cities.
    -For the case where we take a city that hasn't already been taken, we just need to take a not taken city with the highest value of Bi.
    -For the case where we take a taken city, we find a taken city with the highest value of Bi-Ai lets say it has values (a1,b1) and take a not taken city with the highest value of Ai(a2,b2), we need to add a2-a1+b1 (from this formula we can see why we need a taken city with the highest Bi-Ai) to the solution.
    -For every sports school we choose the better of these 2 cases and update the sets according to what we chose.
    -There are 2 videos by Errichto where he goes over problems similar to this one where we need to sort items with "weird comparators" (in this case Bi-Ai)
    -Part 1 of the video: https://www.youtube.com/watch?v=7hFWrKa6yRM , part 2: https://www.youtube.com/watch?v=gXxu-Cr4b4c , Codeforces blog post: https://codeforces.com/blog/entry/63533
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

int main()
{
    int n,m,s;
    scanf("%i %i %i",&n,&m,&s);
    vector<pair<int,int> > pairs;
    for(int i=0;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        pairs.emplace_back(a,b);
    }
    ll sol=0;
    sort(all(pairs));
    reverse(all(pairs));
    multiset<pair<int,pair<int,int> >,greater<pair<int,pair<int,int> > > > taken,not_taken_a,not_taken_b;
    for(int i=0;i<m;i++)
    {
        pair<int,int> p=pairs[i];
        taken.insert({p.s-p.f,{p.f,p.s}});
        sol+=(ll)p.f;
    }
    for(int i=m;i<n;i++)
    {
        pair<int,int> p=pairs[i];
        not_taken_b.insert({p.s,{p.f,p.s}});
        not_taken_a.insert({p.f,{p.f,p.s}});
    }
    for(int i=0; i<s; i++)
    {
        int o1=(*not_taken_b.begin()).f;
        int o2=(*taken.begin()).s.s-(*taken.begin()).s.f+(*not_taken_a.begin()).f;
        if(o1>=o2)
        {
            sol+=(ll)o1;
            int a=(*not_taken_b.begin()).s.f,b=(*not_taken_b.begin()).s.s;
            not_taken_b.erase(not_taken_b.find({b,{a,b}}));
            not_taken_a.erase(not_taken_a.find({a,{a,b}}));
        }
        else
        {
            sol+=(ll)o2;
            taken.erase(taken.begin());
            int a=(*not_taken_a.begin()).s.f,b=(*not_taken_a.begin()).s.s;
            not_taken_b.erase(not_taken_b.find({b,{a,b}}));
            not_taken_a.erase(not_taken_a.find({a,{a,b}}));
            taken.insert({b-a,{a,b}});
        }
    }
    printf("%lld\n",sol);
    return 0;
}

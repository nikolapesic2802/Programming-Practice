/*
    -When 2 chameleons meet each other, we can look at them not turning 180 degrees but continuing in the same direction, passing by each other:
    --b->  <-a--  ==>  <-(a+b)%k-- --b->, as we can see chameleon b doesn't change his color, so for every chameleon going to the right, we can just ignore all collisions as they don't change his color.
    As for the ones going left, we need to consider every chameleon going right that starts to the left of it, as it will effect its color.
    This can be done in O(n*k) by maintaining an array of size K to tell through which phases a chameleon with direction left will go though.
    We start from the left most chameleon and go to the right, we need to update this array every time we encounter a chameleon going right and use the array to add to the answer for every chameleon going left.
    I also learned that we need to use %Ld (capital L) and not %ld for long doubles, even tho it prints fine on my computer, it doesn't judge the solution as correct when i submit the task.
*/
#include <bits/stdc++.h>

#define ll long long
#define f first
#define s second

using namespace std;

int main()
{
	int n,k,l;
	scanf("%i %i %i",&n,&k,&l);
	vector<pair<int,pair<int,int> > > kam;
	for(int i=0;i<n;i++)
	{
		int d,kk;
		scanf("%i %i",&d,&kk);
		string s;
		cin >> s;
		if(s[0]=='L')
		kam.push_back({d,{kk,0}});
		else
		kam.push_back({d,{kk,1}});
	}
	sort(kam.begin(),kam.end());
	long double colors[k],phase[k];
	for(int i=0;i<k;i++)
        colors[i]=0,phase[i]=0;
	int delta=0,last=-1,poslast,firstpos;
	for(auto p:kam)
	{
		int d=p.f,boja=p.s.f,t=p.s.s;
		if(t==1)
		{
			colors[boja]+=l-d;
			if(last==-1)
                firstpos=d;
			else
			{
				long double dd=(long double)(d-poslast)/2;
				phase[(0-delta+k)%k]+=dd;
			}
			delta+=boja;
			delta%=k;
			last=boja;
			poslast=d;
		}
		else
		{
			if(last==-1)
			{
				colors[boja]+=d;
				continue;
			}
			long double dd=(long double)(d-poslast)/2;
			colors[boja]+=dd;
			dd=(long double)(d-firstpos)/2+firstpos;
			colors[(delta+boja)%k]+=dd;
			for(int i=0;i<k;i++)
			{
				int tr=(i+delta+boja)%k;
				colors[tr]+=phase[i];
			}
		}
	}
	for(int i=0;i<k;i++)
        printf("%.1Lf\n",colors[i]);
	return 0;

}

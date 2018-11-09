#include <bits/stdc++.h>
#include "robots.h"
#define pb push_back
using namespace std;
pair<int,int> maxx=make_pair(INT_MAX,INT_MAX);
int putaway(int a, int b, int t, int x[], int y[], int W[], int S[]) {
    sort(x,x+a);
    sort(y,y+b);
    reverse(y,y+b);
    vector<pair<int,int> > items(t);
    for(int i=0;i<t;i++)
    {
        items[i].first=W[i];
        items[i].second=S[i];
    }
    if(b==0)
    {
        //printf("usao!\n");
        multiset<int> s;
        while(items.size())
        {
            s.insert((items.back()).first);
            items.pop_back();
        }
        multiset<int>::iterator it=s.end();
        it--;
        if(*it>x[a-1])
            return -1;
        for(int res=1;res<=t;res++)
        {
            for(int i=0;i<a;i++)
            {
                it=s.lower_bound(x[i]);
                if(it==s.begin())
                    continue;
                it--;
                s.erase(it);
                if(s.size()==0)
                {
                    return res;
                }
            }
        }
    }
    items.pb(maxx);
    sort(items.begin(),items.end());
    int l=1,r=t+5;
    while(l<r)
    {
        int mid=(l+r)/2;
        //printf("%i\n",mid);
        int j=0;
        int test=true;
        int cnt=0;
        priority_queue<pair<int,int> > s;
        for(int i=0;i<a;i++)
        {
            //printf("Usao za %i\n",x[i]);
            while(items[j].first<x[i])
            {
                //printf("Dodajem %i %i\n",items[j].first,items[j].second);
                s.push({items[j].second,cnt++});
                j++;
            }
            for(int k=0;k<mid;k++)
            {
                if(s.empty())
                    break;
                s.pop();
                //printf("brisem!\n");
            }
        }
        for(;j<t;j++)
            s.push({items[j].second,cnt++});
        for(int i=0;i<b;i++)
        {
            //printf("usao! %i\n",y[i]);
            for(int k=0;k<mid;k++)
            {
                if(s.size()==0)
                {
                    break;
                    break;
                }
                if((s.top().first)<y[i])
                    s.pop();
                else
                {
                    break;
                    break;
                }
            }
        }
        if(s.size()!=0)
            test=false;
        if(test)
        {
            r=mid;
        }
        else
        {
            l=mid+1;
        }
    }
    if(l==t+5)
        return -1;
    return l;
}

#define fail(s, x...) do { \
		fprintf(stderr, s "\n", ## x); \
		exit(1); \
	} while(0)
#define MAX_A 50000
#define MAX_B 50000
#define MAX_T 500000
static int X[MAX_A];
static int Y[MAX_B];
static int W[MAX_T];
static int S[MAX_T];
int main() {
    int A, B, T, i;
	int res;


	//FILE *f = fopen("st5-random-uniform.in", "r");
	FILE *f = fopen("st5-random-highS-cluster.in", "r");
	if (!f)
		fail("Failed to open input file.");

	res = fscanf(f, "%d", &A);
	if (res != 1)
		fail("Failed to read A from input file.");
	if (A < 0 || A > MAX_A)
		fail("A is out of bounds.");

	res = fscanf(f, "%d", &B);
	if (res != 1)
		fail("Failed to read B from input file.");
	if (B < 0 || B > MAX_B)
		fail("B is out of bounds.");

	res = fscanf(f, "%d", &T);
	if (res != 1)
		fail("Failed to read T from input file.");
	if (T < 1 || T > MAX_T)
		fail("T is out of bounds.");

	for (i = 0; i < A; i++) {
		res = fscanf(f, "%d", &X[i]);
		if (res != 1)
		    fail("Failed to read data from input file.");
    }
	for (i = 0; i < B; i++) {
        res = fscanf(f, "%d", &Y[i]);
        if (res != 1)
            fail("Failed to read data from input file.");
    }
	for (i = 0; i < T; i++) {
        res = fscanf(f, "%d%d", &W[i], &S[i]);
        if (res != 2)
            fail("Failed to read data from input file.");
    }
	fclose(f);
	int a=clock();
	int answer = putaway(A, B, T, X, Y, W, S);

	printf("%d %i\n", answer,clock()-a);

	return 0;
}

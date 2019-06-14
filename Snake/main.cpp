/*
    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2008/editorials.pdf
*/
#include <bits/stdc++.h>
#include "snakelib.h"

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";
#define ask(u1,u2) ask_snake(u1,u2,&a1,&a2)

using namespace std;

int main()
{
    int cnt=0;
	char a1,a2;
	int k=get_speed();
	int m=12121;
	int l1,r1,l2,r2;
	int a=m/3,b=2*a;
	ask(a,b);
	cnt++;
	if(a1=='s')
    {
        if(a2=='s')
        {
            l1=0;r1=a;
            l2=b;r2=m;
        }
        if(a2=='f')
        {
            l1=0;r1=a;
            l2=a;r2=b-1;
        }
    }
    if(a1=='f')
    {
        l1=l2=0;
        r1=r2=a-1;
    }
    if(a1=='b')
    {
        if(a2=='s')
        {
            l1=a+1;r1=b;
            l2=b;r2=m;
        }
        if(a2=='b')
        {
            l1=l2=b+1;
            r1=r2=m;
        }
        if(a2=='f')
        {
            l1=l2=a+1;
            r1=r2=b-1;
        }
    }
	while(r1-l1+1>k+1||r2-l2+1>k+1)
    {
        r1=min(r1+k,m);
        r2=min(r2+k,m);
        int m1=(l1+r1)>>1,m2=(l2+r2+1)>>1;
        ask(m1,m2);
        cnt++;
        if(a1=='s')
            r1=m1;
        if(a1=='f')
            r1=m1-1;
        if(a1=='b')
            l1=m1+1;
        if(a2=='s')
            l2=m2;
        if(a2=='f')
            r2=m2-1;
        if(a2=='b')
            l2=m2+1;
    }
    int m1=(l1+r1)>>1,m2=(l2+r2)>>1;
    tell_length(m2-m1+1);
    return 0;
}

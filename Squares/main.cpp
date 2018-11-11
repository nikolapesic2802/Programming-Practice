/*
    - Calculate the diagonals for every (x1,y1) and (x2,y2)
    - Find out how many "bad" diagonals there are between the two points
    - Take the maximum of the two differences, because we can cross both diagonals at once
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

int main()
{

    int a,b,x1,y1,x2,y2;
    scanf("%i %i %i %i %i %i",&a,&b,&x1,&y1,&x2,&y2);
    a*=2;
    b*=2;
    ll cnt1=0,cnt2=0;
    int d1=x1+y1;
    int d2=x2+y2;
    if(d1>d2)
        swap(d1,d2);
    int prva=d1%a;
    if(prva!=0)
    {
        int dd=d1/a;
        if(d1<0)
            dd--;
        dd++;
        int sl=dd*a;
        if(sl>d2)
        {
            d1=d2;
        }
        else
        {
            cnt1++;
            d1=sl;
        }
    }
    else
        cnt1++;
    ll dif=(ll)d2-d1;
    cnt1+=(ll)dif/a;
    d1=x1-y1;
    d2=x2-y2;
    if(d1>d2)
        swap(d1,d2);
    prva=d1%b;
    if(prva!=0)
    {
        int dd=d1/b;
        if(d1<0)
            dd--;
        dd++;
        int sl=dd*b;
        //printf("%i\n",sl);
        if(sl>d2)
        {
            d1=d2;
        }
        else
        {
            cnt2++;
            d1=sl;
        }
    }
    else
        cnt2++;
    dif=(ll)d2-d1;
    cnt2+=(ll)dif/b;
    printf("%lld\n",max(cnt1,cnt2));
    return 0;
}

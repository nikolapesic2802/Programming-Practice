#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back

const int N=1e6+5;
vector<int> lo(N),hi(N);
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
    int n;
    //scanf("%i",&n);
    fastscan(n);
    for(int i=0;i<n;i++)
        fastscan(lo[i]),fastscan(hi[i]);
        //scanf("%i %i",&lo[i],&hi[i]);
    multiset<int,greater<int> > mins;
    int res=1;
    int s=0;
    mins.insert(lo[0]);
    for(int i=1;i<n;i++)
    {
        while(mins.size()&&*mins.begin()>hi[i])
        {
            mins.erase(mins.find(lo[s]));
            s++;
        }
        mins.insert(lo[i]);
        res=max(res,i-s+1);
    }
    printf("%i\n",res);

    return 0;
}

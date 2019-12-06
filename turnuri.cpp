/*
    -For every element we need to calculate the first and second element that are bigger than it to the left.
    -To do this we can use the algorithm for finding the first element bigger than it (convex hull optimization) but add a second queue for the second bigger element.
    -Without any input optimizations and using vector, it gets AC in 436ms.
    -With the input optimization and vector it gets AC in 108ms.
    -With the input optimization and using arrays instead of vector, it gets AC in 78ms. (code at the bottom)
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define f first
#define s second

using namespace std;

class InParser {
private:
	FILE *fin;
	char *buff;
	int sp;

	char read_ch() {
		++sp;
		if (sp == 4096) {
			sp = 0;
			fread(buff, 1, 4096, fin);
		}
		return buff[sp];
	}

public:
	InParser(const char* nume) {
		fin = fopen(nume, "r");
		buff = new char[4096]();
		sp = 4095;
	}

	InParser& operator >> (int &n) {
		char c;
		while (!isdigit(c = read_ch()));
        n = c - '0';
		while (isdigit(c = read_ch()))
			n = 10 * n + c - '0';
		return *this;
	}

	InParser& operator >> (long long &n) {
		char c;
		while (!isdigit(c = read_ch()));
        n = c - '0';
		while (isdigit(c = read_ch()))
			n = 10 * n + c - '0';
		return *this;
	}
}f("turnuri.in");
ofstream g("turnuri.out");

int main()
{
    int n;
    ll ans=0;
    f >> n;
    vector<pair<int,int> > l1,l2,temp;
    l1.pb({-1,INT_MAX});
    l2.pb({-1,INT_MAX});
    for(int i=0;i<n;i++){
        int p;
        f >> p;
        while(l1.back().s<=p)
            temp.pb(l1.back()),l1.pop_back();
        while(l2.back().s<=p)
            l2.pop_back();
        int a=l1.back().f;
        if(a==-1)
            ans+=(ll)(n-2)*i;
        else{
            int d=i-a;
            ans+=(ll)(n-1-d)*d+(ll)(d-1)*(d-1);
            a=max(l1[l1.size()-2].f,l2.back().f);
            if(a==-1)
                ans+=i-1;
            else
                ans+=i-a-1;
        }
        while(temp.size())
            l2.pb(temp.back()),temp.pop_back();
        l1.pb({i,p});
    }
    g << ans;
    return 0;
}

/*Code with arrays instead of vector
const int N=1e6;
int l1f[N],l1s[N],l2f[N],l2s[N],tf[N],ts[N],l1,l2,t;
int main()
{
    int n;
    ll ans=0;
    f >> n;
    l1f[l1]=-1;
    l1s[l1]=INT_MAX;
    l2f[l1]=-1;
    l2s[l1]=INT_MAX;
    for(int i=0;i<n;i++){
        int p;
        f >> p;
        while(l1s[l1]<=p)
            tf[t]=l1f[l1],ts[t++]=l1s[l1],l1--;
        while(l2s[l2]<=p)
            l2--;
        int a=l1f[l1];
        if(a==-1)
            ans+=(ll)(n-2)*i;
        else{
            int d=i-a;
            ans+=(ll)(n-1-d)*d+(ll)(d-1)*(d-1);
            a=max(l1f[l1-1],l2f[l2]);
            if(a==-1)
                ans+=i-1;
            else
                ans+=i-a-1;
        }
        while(t)
            l2f[++l2]=tf[--t],l2s[l2]=ts[t];
        l1f[++l1]=i;
        l1s[l1]=p;
    }
    g << ans;
    return 0;
}*/


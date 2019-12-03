#include <bits/stdc++.h>
#define pb push_back
using namespace std;
int main()
{
	int n,a;
	scanf("%i",&n);
	vector<int> in(n+1),stk,sol,nov;
	for(int i=0;i<2*n;i++){
        scanf("%i",&a);
        if(in[a]){
            while(stk.back()!=a)
                sol.pb(stk.size()),nov.pb(stk.back()),stk.pop_back();
            stk.pop_back();
            while(nov.size())
                stk.pb(nov.back()),nov.pop_back();
        }
        else
            stk.pb(a),in[a]=1;
	}
	printf("%i\n",sol.size());
	for(auto p:sol)
        printf("%i\n",p);
    return 0;
}

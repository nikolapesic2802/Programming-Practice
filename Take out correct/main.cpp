#include <bits/stdc++.h>
#define fi first
#define se second
#define lo long long
#define inf 1000000009
#define md 1000000007
#define li 1000005
#define mp make_pair
#define pb push_back
using namespace std;
int n,k,cev,bas1,bas2,c;
char s[li];
vector<int> v,p;
vector< vector<int> > ans;
int main(){
	scanf("%d %d",&n,&k);
	scanf("%s",s+1);
	p.pb(0);
	for(int i=1;i<=n;i++){
		v.pb(i);
		if(s[i]=='c'){
			c++;
			p.pb(0);
		}
		else p[c]++;
		if(c && p[c]+p[c-1]>=k){
			vector<int> T;
			for(int i=0;i<k+1;i++){
				T.pb(v.back());
				v.pop_back();
			}
			reverse(T.begin(),T.end());
			ans.pb(T);
			int X=p[c--];
			p.pop_back();
			p[c]-=k-X;
		}
	}
	for(int i=(int)ans.size()-1;i>=0;i--){
		for(int j=0;j<(int)ans[i].size();j++){
			printf("%d ",ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}

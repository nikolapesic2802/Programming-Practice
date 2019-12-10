/*
    -We can split the circle into sections such that an elf at the beginning of the section can be transfered to the end.
    -Calculate these sections using DSU.
    -For each section, we can do a greedy algorithm
    -Go through the section in order, keep a set of elves available (their strengths), and for every dwarf, assign the elf with the lowest strength from the set such that its larger than the dwarfs strength and increase the answer by 1,
    -If such elf doesn't exits, assign the dwarf with the lowers strength and don't increase the answer.
*/
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int N=5e5+5;
vector<int> par(N),siz(N),p(N),v(N);
vector<vector<int> > pwrs(N);
int find(int tr){return tr==par[tr]?tr:par[tr]=find(par[tr]);}
void merge(int a,int b){
    a=find(a);
    b=find(b);
    if(a==b)
        return;
    siz[a]+=siz[b];
    par[b]=a;
}
int main()
{
    iota(par.begin(),par.end(),0);
	int n,a;
	scanf("%i",&n);
	for(int i=0;i<n;i++)
        scanf("%i",&a),a--,siz[a]++,pwrs[a].pb(i);
    for(int i=0;i<n;i++)
        scanf("%i",&p[i]);
    for(int i=0;i<n;i++)
        scanf("%i",&v[i]);
    for(int i=0;i<n;i++){
        if(find(i)!=i)
            continue;
        for(int j=1;j<siz[i];j++)
            merge(i,(i+j)%n);
    }
    int ans=0;
    for(int i=0;i<n;i++)
        if(find(i)==i)
        {
            set<int> st;
            for(int j=0;j<siz[i];j++){
                for(auto p:pwrs[(i+j)%n])
                    st.insert(v[p]);
                auto it=st.lower_bound(p[(i+j)%n]);
                if(it==st.end())
                    st.erase(st.begin());
                else
                    ans++,st.erase(it);
            }
        }
    printf("%i\n",ans);
    return 0;
}

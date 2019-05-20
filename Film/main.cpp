#include <bits/stdc++.h>

#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()

using namespace std;

int k;
struct cvor{
    vector<int> nxt;
    vector<int> ends;
    int fail;
    cvor(){nxt.resize(k,-1);}
};
vector<cvor> aho;
int newNode()
{
    cvor a;
    aho.pb(a);
    return aho.size()-1;
}
int root;
void addString(string s,int ind,int pos=0,int tr=root)
{
    if(pos==(int)s.size())
    {
        aho[tr].ends.pb(ind);
        return;
    }
    int sl=s[pos]-'a';
    if(aho[tr].nxt[sl]==-1)
        aho[tr].nxt[sl]=newNode();
    addString(s,ind,pos+1,aho[tr].nxt[sl]);
}
void buildBackEdges()
{
    aho[root].fail=root;
    queue<int> q;
    for(int i=0;i<k;i++)
        if(aho[root].nxt[i]!=-1)
            aho[aho[root].nxt[i]].fail=root,q.push(aho[root].nxt[i]);
    while(q.size())
    {
        int cur=q.front();
        int fail=aho[cur].fail;
        q.pop();
        for(int i=0;i<k;i++)
        {
            if(aho[cur].nxt[i]==-1)
                continue;
            int tr=fail;
            while(true)
            {
                if(aho[tr].nxt[i]!=-1)
                {
                    tr=aho[tr].nxt[i];
                    break;
                }
                if(tr==root)
                    break;
                tr=aho[tr].fail;
            }
            aho[aho[cur].nxt[i]].fail=tr;
            for(auto p:aho[tr].ends)
                aho[aho[cur].nxt[i]].ends.pb(p);
            q.push(aho[cur].nxt[i]);
        }
    }
}
int visited[200][1<<14],n;
char uzmi[200][1<<14];
pair<int,int> par[200][1<<14],start={-1,-1};
void bfs()
{
    queue<pair<int,int> > q;
    q.push({0,0});
    visited[0][0]=1;
    while(q.size())
    {
        int tr=q.front().f,mask=q.front().s;
        if(mask==((1<<n)-1))
        {
            start={tr,mask};
            return;
        }
        q.pop();
        for(int i=0;i<k;i++)
        {
            int sl=tr;
            while(true)
            {
                if(aho[sl].nxt[i]!=-1)
                {
                    int nm=mask;
                    bool moze=true;
                    for(auto p:aho[aho[sl].nxt[i]].ends)
                        if(mask&(1<<p))
                            moze=false;
                        else
                            nm|=1<<p;
                    if(moze)
                    {
                        if(visited[aho[sl].nxt[i]][nm]==0)
                        {
                            visited[aho[sl].nxt[i]][nm]=1;
                            par[aho[sl].nxt[i]][nm]={tr,mask};
                            uzmi[aho[sl].nxt[i]][nm]='a'+i;
                            q.push({aho[sl].nxt[i],nm});
                        }
                    }
                    break;
                }
                if(sl==root)
                {
                    if(visited[root][mask]==0)
                    {
                        visited[root][mask]=1;
                        par[root][mask]={tr,mask};
                        uzmi[root][mask]='a'+i;
                        q.push({root,mask});
                    }
                    break;
                }
                sl=aho[sl].fail;
            }
        }
    }
}
int Resi(int N, int K, int* L, char** A, char* S) {
    k=K;
    n=N;
    root=newNode();
	vector<string> a(n);
	vector<int> l(n);
	for(int i=1;i<=n;i++)
        for(int j=1;j<=L[i];j++)
            if(A[i][j]-'a'+1>k)
                return -1;
	for(int i=1;i<=n;i++)
        for(int j=1;j<=L[i];j++)
            a[i-1]+=A[i][j];
    for(int i=0;i<n;i++)
        l[i]=a[i].size(),addString(a[i],i);
    buildBackEdges();
    bfs();
    if(start==make_pair(-1,-1))
        return -1;
    string s;
    while(start!=make_pair(0,0))
    {
        s+=uzmi[start.f][start.s];
        start=par[start.f][start.s];
    }
    reverse(all(s));
    for(int i=0;i<(int)s.size();i++)
        S[i+1]=s[i];
    return s.size();
}
int main() {
    freopen("in.txt","r",stdin);
	int N, K;
	cin >> N >> K;
	char** A = new char*[N+1];
	int* L = new int[N+1];
	char* S = new char[65536];
	for (int i=1; i<=N; i++) {
		string s;
		cin >> s;
		A[i] = new char[s.size() + 2];
		copy(s.begin(), s.end(), A[i]+1);
		A[i][s.size() + 1] = 0;
		L[i] = s.size();
	}
	int res = Resi(N, K, L, A, S);
	cout << res << '\n';
	if (res >= 0) {
		for (int i=1; i<=res; i++)
			cout << S[i];
		cout << '\n';
	}
	for (int i=1; i<=N; i++)
		delete[] A[i];
	delete[] A;
	delete[] L;
	delete[] S;
}

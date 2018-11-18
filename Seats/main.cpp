#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
int N;
struct segTree{
    vector<int> ones,tri;
    vector<int> sum;
    vector<pair<int,int> > minn;
    vector<int> num;
    void set(int i,int l,int r)
    {
        //minn[i]=make_pair(0,0);
        num[i]=r-l+1;
        if(l==r)
            return;
        int m=(l+r)>>1;
        set(2*i,l,m);
        set(2*i+1,m+1,r);
    }
    void init()
    {
        ones.resize(4*N);
        tri.resize(4*N);
        minn.resize(4*N);
        num.resize(4*N);
        set(1,0,N-1);
    }
    void prop(int i)
    {
        if(ones[i]!=0){
        ones[2*i]+=ones[i];
        minn[2*i].first+=ones[i];
        ones[2*i+1]+=ones[i];
        minn[2*i+1].first+=ones[i];
        ones[i]=0;
        }
        if(tri[i]!=0){
        tri[2*i]+=tri[i];
        minn[2*i].second+=tri[i];
        tri[2*i+1]+=tri[i];
        minn[2*i+1].second+=tri[i];
        tri[i]=0;
        }
    }
    void update(int i)
    {
        if(minn[2*i]==minn[2*i+1])
        {
            minn[i]=minn[2*i];
            num[i]=num[2*i]+num[2*i+1];
            return;
        }
        if(minn[2*i]<minn[2*i+1])
        {
            minn[i]=minn[2*i];
            num[i]=num[2*i];
            return;
        }
        if(minn[2*i]>minn[2*i+1])
        {
            minn[i]=minn[2*i+1];
            num[i]=num[2*i+1];
        }
    }
    void update_all(int i=1,int l=0,int r=N-1)
    {
        if(l==r){
            minn[i].first+=ones[i];
            minn[i].second+=tri[i];
            //printf("%i: %i %i\n",l,minn[i].first,minn[i].second);
            return;
        }
        int m=(l+r)>>1;
        ones[2*i]+=ones[i];
        ones[2*i+1]+=ones[i];
        ones[i]=0;
        tri[2*i]+=tri[i];
        tri[2*i+1]+=tri[i];
        tri[i]=0;
        update_all(2*i,l,m);
        update_all(2*i+1,m+1,r);
        update(i);
    }
    void no_updates(int qs,int qe,int x,int sta,int i=1,int l=0,int r=N-1)
    {
        if(qe<qs)
            return;
        if(r<qs||l>qe)
            return;
        if(qs<=l&&r<=qe)
        {
            //printf("Dodajem %i %i od %i do %i %i\n",x,sta,l,r,i);
            if(sta==0){
                ones[i]+=x;
                //minn[i].first+=x;
            }
            else{
                tri[i]+=x;
                //minn[i].second+=x;
            }
            return;
        }
        int m=(l+r)>>1;
        no_updates(qs,qe,x,sta,2*i,l,m);
        no_updates(qs,qe,x,sta,2*i+1,m+1,r);
    }
    void add(int qs,int qe,int x,int sta,int i=1,int l=0,int r=N-1)
    {
        if(qe<qs)
            return;
        if(r<qs||l>qe)
            return;
        if(qs<=l&&r<=qe)
        {
            if(sta==0){
                ones[i]+=x;
                minn[i].first+=x;
            }
            else{
                tri[i]+=x;
                minn[i].second+=x;
            }
            return;
        }
        int m=(l+r)>>1;
        prop(i);
        add(qs,qe,x,sta,2*i,l,m);
        add(qs,qe,x,sta,2*i+1,m+1,r);
        update(i);
    }
    int get()
    {
        //printf("%i %i\n",minn[1].first,minn[1].second);
        if(minn[1]==make_pair(4,0))
            return num[1];
        return 0;
    }
} ST;
vector<vector<int> > mat;
int h,w;
bool inside(int x,int y)
{
    if(x>=0&&x<h&&y>=0&&y<w)
        return true;
    return false;
}
void update(int x,int y,int z)
{
    vector<int> val;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++){
            if(inside(x+i,y+j))
                val.pb(mat[x+i][y+j]);
            else
                val.pb(N);
        }
    sort(val.begin(),val.end());
    ST.add(val[0],val[1]-1,z,0);
    ST.add(val[2],val[3]-1,z,1);
}
void update2(int x,int y,int z)
{
    vector<int> val;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++){
            if(inside(x+i,y+j))
                val.pb(mat[x+i][y+j]);
            else
                val.pb(N);
        }
    sort(val.begin(),val.end());
    ST.no_updates(val[0],val[1]-1,z,0);
    ST.no_updates(val[2],val[3]-1,z,1);
}
vector<int> r,c;
vector<bool> sol;
void give_initial_chart(int H, int W, std::vector<int> R, std::vector<int> C) {
    h=H;
    w=W;
    sol.resize(H*W);
    mat.resize(H);
    for(int i=0;i<H;i++)
        mat[i].resize(W);
    N=H*W;
    ST.init();
    for(int i=0;i<H*W;i++){
        mat[R[i]][C[i]]=i;
        r.pb(R[i]);
        c.pb(C[i]);
    }
    for(int i=-1;i<H;i++)
        for(int j=-1;j<W;j++)
            update2(i,j,1);
    ST.update_all();
    //printf("%i\n",ST.get());
}
int swap_seats(int a, int b) {
    for(int i=-1;i<=0;i++)
        for(int j=-1;j<=0;j++)
            update(r[a]+i,c[a]+j,-1);
    for(int i=-1;i<=0;i++)
        for(int j=-1;j<=0;j++)
            update(r[b]+i,c[b]+j,-1);
    swap(mat[r[a]][c[a]],mat[r[b]][c[b]]);
    swap(r[a],r[b]);
    swap(c[a],c[b]);
    for(int i=-1;i<=0;i++)
        for(int j=-1;j<=0;j++)
            update(r[a]+i,c[a]+j,1);
    for(int i=-1;i<=0;i++)
        for(int j=-1;j<=0;j++)
            update(r[b]+i,c[b]+j,1);
    return ST.get();
}

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const gp_hash_table<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

int main()
{
    int cnt=0;
    for(int i=1;i<=20;i++){
        string s;
        if(i>9)
            s+='1';
        s+='0'+i%10;
        string o=s+".out";
        s+=".in";
        FILE* in=fopen(s.c_str(),"r");
        FILE* out=fopen(o.c_str(),"r");
        int sol;
        fscanf(out,"%i",&sol);
        FILE* myin=fopen("~in","w");
        int n,c;
        fscanf(in,"%i %i",&n,&c);
        fprintf(myin,"%i %i\n",n,c);
        while(c--)
        {
            int e;
            fscanf(in,"%i",&e);
            int f,l;
            fscanf(in,"%i %i",&f,&l);
            fprintf(myin,"%i %i %i",e,f,l);
            for(int i=0;i<f+l;i++)
                fscanf(in,"%i",&e),fprintf(myin," %i",e);
            fprintf(myin,"\n");
        }
        fclose(in);
        fclose(out);
        fclose(myin);
        int ti=clock();
        system("main.exe");
        ti=clock()-ti;
        in=fopen("~out","r");
        int sol1;
        fscanf(in,"%i",&sol1);
        printf("Test %i: Time: %i ",i,ti);
        if(sol1==sol)
            printf("Correct!\n"),cnt++;
        else
            printf("Incorrect!\n");
        fclose(in);
    }
    printf("%i!!\n",cnt*5);
    return 0;
}

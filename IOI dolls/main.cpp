/*
    -We will build one big switch to which all the nodes will connect.
    -The first time we enter the switch, we should leave at node a[0], the second time at node a[1], and so on for the whole array, plus we should finish the tour by exiting to node 0 the last time.
    -The 2*n switches solution is pretty easy to come up with, which is just to make a binary tree of switches and assign the corresponding output to the corresponding switch.
    -The optimization to n+log n requires us to group all the empty nodes(nodes which lead back to the switch itself) to as little outputs as possible.
*/
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}

void answer(std::vector<int> C, std::vector<int> X, std::vector<int> Y);
struct node{
    int x,y;
    node(){x=-1;y=-1;}
};
const int NMAX=6e5+5;
vector<node> graf(NMAX);
vector<int> flipped(NMAX);
vector<int> skips;
int stigao;
void markskips(vector<int> poz,int koliko)
{
    if(koliko==0)
        return;
    vector<int> levo,desno;
    for(int i=0;i<(int)poz.size();i++)
        if(i%2)
            desno.pb(poz[i]);
        else
            levo.pb(poz[i]);
    if((int)levo.size()<=koliko)
        for(auto p:levo)
            skips[p]=1;
    else
        markskips(levo,koliko);
    if((int)levo.size()<koliko)
        markskips(desno,koliko-(int)levo.size());
}
void build(int tr,vector<int> izlazi,int skip,int sta)
{
    int ukupno=izlazi.size()+skip;
    assert(ukupno%2==0);
    if(ukupno==2)
    {
        if(skip)
        {
            assert(skip==1);
            graf[tr].x=sta;
            graf[tr].y=izlazi[0];
        }
        else
        {
            graf[tr].x=izlazi[0];
            graf[tr].y=izlazi[1];
        }
        return;
    }
    if(skip>=ukupno/2)
    {
        graf[tr].x=sta;
        graf[tr].y=stigao;
        stigao++;
        build(graf[tr].y,izlazi,skip-ukupno/2,sta);
        return;
    }
    skips.resize(ukupno);
    fill(all(skips),0);
    vector<int> pozicije;
    for(int i=0;i<ukupno;i++)
        pozicije.pb(i);
    markskips(pozicije,skip);
    vector<int> levo,desno;
    int trr=0;
    for(int i=0;i<ukupno;i++)
    {
        if(i%2)
            desno.pb(izlazi[trr++]),assert(!skips[i]);
        else
            if(!skips[i])
                levo.pb(izlazi[trr++]);
    }
    graf[tr].x=stigao;
    stigao++;
    build(graf[tr].x,levo,skip,sta);
    graf[tr].y=stigao;
    stigao++;
    build(graf[tr].y,desno,0,sta);
}

void create_circuit(int m, vector<int> a)
{
    a.pb(0);
    stigao=m+1;
    for(int i=0;i<=m;i++)
        graf[i].x=stigao;
    stigao++;
    int sz=2;
    while(sz<(int)a.size())
        sz*=2;
    build(stigao-1,a,sz-a.size(),stigao-1);
    vector<int> A,X,Y;
    for(int i=0;i<=m;i++)
        if(graf[i].x>m)
            A.pb(m-graf[i].x);
        else
            A.pb(graf[i].x);
    for(int i=m+1;i<stigao;i++)
    {
        if(graf[i].x>m)
            X.pb(m-graf[i].x);
        else
            X.pb(graf[i].x);
        if(graf[i].y>m)
            Y.pb(m-graf[i].y);
        else
            Y.pb(graf[i].y);
    }
    answer(A,X,Y);
}

constexpr int P_MAX = 20000000;
constexpr int S_MAX = 400000;

int M, N;
std::vector<int> A;

bool answered;
int S;
std::vector<int> IC, IX, IY;

int read_int() {
  int x;
  if (scanf("%d", &x) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  return x;
}

void wrong_answer(const char *MSG) {
  printf("Wrong Answer: %s\n", MSG);
  exit(0);
}

void simulate() {
  if (S > S_MAX) {
    char str[50];
    sprintf(str, "over %d switches", S_MAX);
    wrong_answer(str);
  }
  for (int i = 0; i <= M; ++i) {
    if (!(-S <= IC[i] && IC[i] <= M)) {
      wrong_answer("wrong serial number");
    }
  }
  for (int j = 1; j <= S; ++j) {
    if (!(-S <= IX[j - 1] && IX[j - 1] <= M)) {
      wrong_answer("wrong serial number");
    }
    if (!(-S <= IY[j - 1] && IY[j - 1] <= M)) {
      wrong_answer("wrong serial number");
    }
  }

  int P = 0;
  std::vector<bool> state(S + 1, false);
  int pos = IC[0];
  int k = 0;
  FILE *file_log = fopen("log.txt", "w");
  fprintf(file_log, "0\n");
  for (;;) {
    fprintf(file_log, "%d\n", pos);
    if (pos < 0) {
      if (++P > P_MAX) {
        fclose(file_log);
        char str[50];
        sprintf(str, "over %d inversions", P_MAX);
        wrong_answer(str);
      }
      state[-pos] = !state[-pos];
      pos = state[-pos] ? IX[-(1 + pos)] : IY[-(1 + pos)];
    } else {
      if (pos == 0) {
        break;
      }
      if (k >= N) {
        fclose(file_log);
        wrong_answer("wrong motion");
      }
      if (pos != A[k++]) {
        fclose(file_log);
        wrong_answer("wrong motion");
      }
      pos = IC[pos];
    }
  }
  fclose(file_log);
  if (k != N) {
    wrong_answer("wrong motion");
  }
  for (int j = 1; j <= S; ++j) {
    if (state[j]) {
      wrong_answer("state 'Y'");
    }
  }
  printf("Accepted: %d %d\n", S, P);
}

  // namespace

void answer(std::vector<int> C, std::vector<int> X, std::vector<int> Y) {
  if (answered) {
    wrong_answer("answered not exactly once");
  }
  answered = true;
  // check if input format is correct
  if ((int)C.size() != M + 1) {
    wrong_answer("wrong array length");
  }
  if (X.size() != Y.size()) {
    wrong_answer("wrong array length");
  }
  S = X.size();
  IC = C;
  IX = X;
  IY = Y;
}

int main() {
freopen("in.txt","r",stdin);
  M = read_int();
  N = read_int();
  A.resize(N);
  for (int k = 0; k < N; ++k) {
    A[k] = read_int();
  }

  answered = false;
  create_circuit(M, A);
  if (!answered) {
    wrong_answer("answered not exactly once");
  }
  FILE *file_out = fopen("out.txt", "w");
  fprintf(file_out, "%d\n", S);
  for (int i = 0; i <= M; ++i) {
    fprintf(file_out, "%d\n", IC[i]);
  }
  for (int j = 1; j <= S; ++j) {
    fprintf(file_out, "%d %d\n", IX[j - 1], IY[j - 1]);
  }
  fclose(file_out);
  simulate();
  return 0;
}

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back

#define MAX_K 40
#define MAX_N 150


using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set; ///find_by_order(),order_of_key()


static int Q, N, K, A[MAX_N], P[MAX_K];
static long long X;
static int min_wa = MAX_K + 1;

#include "Annalib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 150;

static int possivel[MAXN],resposta[MAXN];

void Anna( int N, long long X, int K, int P[] ){

	memset(possivel,1,sizeof(possivel));
	memset(resposta,0,sizeof(resposta));
	possivel[N] = 0;

	for(int i = 0;i<K;i++) possivel[P[i]] = 0;

	deque<int> digitos;
	while(X != 0){
		digitos.push_back(X % 2);
		X /= 2;
	}
	for(int i = 0;i<100;i++) digitos.push_back(0);

	for(int i = 0;i+2<N;i+=3){
		int nao_pode = (possivel[i] + 2*possivel[i+1] + 4*possivel[i+2]) ^ 7;
		int best_qtd = 0,mascara = 0;
		if(!(nao_pode & 4) && digitos[0] == 1){
			best_qtd = 1;
			mascara = 4;
		}
		if(!(nao_pode & 2) && digitos[0] == 0){
			best_qtd = 1;
			mascara = 2;
		}
		if(!(nao_pode & 3) && digitos[0] == 1){
			best_qtd = 1;
			mascara = 3;
		}
		if(!(nao_pode & 6) && digitos[0] == 1 && digitos[1] == 0){
			best_qtd = 2;
			mascara = 6;
		}
		if(!(nao_pode & 1) && digitos[0] == 0 && digitos[1] == 0){
			best_qtd = 2;
			mascara = 1;
		}
		if(!(nao_pode & 5) && digitos[0] == 0 && digitos[1] == 1){
			best_qtd = 2;
			mascara = 5;
		}
		if(!(nao_pode & 7) && digitos[0] == 1 && digitos[1] == 1){
			best_qtd = 2;
			mascara = 7;
		}
		for(int j = 0;j<best_qtd;j++) digitos.pop_front();
		resposta[i] = (mascara & 1) != 0;
		resposta[i+1] = (mascara & 2) != 0;
		resposta[i+2] = (mascara & 4) != 0;
	}

	for(int i = 0;i<N;i++){
		Set( i, resposta[i] );
	}

}

#include "Brunolib.h"
#include <bits/stdc++.h>
using namespace std;

long long Bruno( int N, int A[] ){

	vector<int> digitos;
	long long ans = 0;

	for(int i = 0;i+2<N;i+=3){
		int numero = A[i] + 2*A[i+1] + 4*A[i+2];
		if(numero == 0) continue;
		if(numero == 4 || numero == 6 || numero == 3 || numero == 7){
			digitos.push_back(1);
			if(numero == 7) digitos.push_back(1);
			else if(numero == 6) digitos.push_back(0);
		}
		else{
			digitos.push_back(0);
			if(numero == 1) digitos.push_back(0);
			else if(numero == 5) digitos.push_back(1);
		}
	}

	while(!digitos.empty() && digitos.back() == 0){
		digitos.pop_back();
	}
	for(int i = 0;i<digitos.size();i++){
		if(digitos[i]) ans += (1LL << i);
	}

	return ans;

}

void WrongAnswer( int e ){
  fprintf( stderr, "Wrong Answer [%d]\n", e );
  exit( 0 );
}

void Set( int pos, int bit ){
  if( !( 0 <= pos && pos < N ) ){
    WrongAnswer( 1 );
  }
  if( A[pos] != -1 ){
    WrongAnswer( 2 );
  }
  if( !( bit == 0 || bit == 1 ) ){
    WrongAnswer( 3 );
  }
  A[pos] = bit;
}

int main( int argc, char** argv ){
  int i, query_cnt;
  long long ans;

  //scanf( "%d", &Q );
  Q=1;
  for( query_cnt = 0; query_cnt < Q; query_cnt++ ){
    //scanf( "%d %lld %d", &N, &X, &K );
    N=150;X=16;K=0;
    for( i = 0; i < K; i++ ){
      scanf( "%d", &P[i] );
    }

    for( i = 0; i < N; i++ ){
      A[i] = -1;
    }

    Anna( N, X, K, P );

    for( i = 0; i < N; i++ ){
      if( A[i] == -1 ){
        WrongAnswer( 4 );
      }
    }

    for( i = 0; i < K; i++ ){
      A[ P[i] ] = 0;
    }

    ans = Bruno( N, A );

    if( ans != X ){
      if( K < min_wa ){
        min_wa = K;
      }
    }
  }

  if( min_wa == 1 ){
    if( K < min_wa ){
      min_wa = K;
    }
  }

  fprintf( stderr, "Accepted\n" );
  fprintf( stderr, "L* = %d\n", min_wa - 1 );

  return 0;
}

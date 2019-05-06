#include "doll.h"

void create_circuit(int M, std::vector<int> A) {
  int N = A.size();
  std::vector<int> C(M + 1);
  C[0] = -1;
  for (int i = 1; i <= M; ++i) {
    C[i] = 1;
  }
  std::vector<int> X(N), Y(N);
  for (int k = 0; k < N; ++k) {
    X[k] = Y[k] = A[k];
  }
  answer(C, X, Y);
}

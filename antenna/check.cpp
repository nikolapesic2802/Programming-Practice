
/*
  CEOI 2006
  Competition Day #1
  Task ANTENNA
  Output correctness checker
*/

#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
   if ( argc <= 3 ) {
      fprintf( stderr, "usage: check input-file official-output-file your-output-file\n" );
      return 2;
   }

   FILE
      *fin  = fopen(argv[1], "rt"),
      *foff = fopen(argv[2], "rt"),
      *fout = fopen(argv[3], "rt");

   if ( fin == NULL ) {
      fprintf( stderr, "Error opening input file (\"%s\") for reading!\n", argv[1] );
      return 2;
   }

   if ( foff == NULL ) {
      fprintf( stderr, "Error opening official output file (\"%s\") for reading!\n", argv[2] );
      return 2;
   }

   if ( fout == NULL ) {
      fprintf( stderr, "Error opening your output file (\"%s\") for reading!\n", argv[3] );
      return 1;
   }

   int N, K;
   static int px[1000], py[1000];

   if ( fscanf(fin, "%d%d", &N, &K) != 2 ) {
      fprintf( stderr, "Error reading input (N, K)!\n" );
      return 2;
   }

   for ( int i=0; i<N; ++i ) {
      if ( fscanf(fin, "%d%d", &px[i], &py[i]) != 2 ) {
         fprintf( stderr, "Error reading input (i-th point)!\n", i+1 );
         return 2;
      }
   }

   double R, Roff, x, y;
   if ( fscanf(foff, "%lf", &Roff) != 1 ) {
      fprintf( stderr, "Error reading official output!\n" );
      return 2;
   }

   if ( fscanf(fout, "%lf%lf%lf", &R, &x, &y) != 3 ) {
      fprintf( stderr, "Error reading your output!\n");
      return 2;
   }

   if ( R-Roff > 0.0001+1e-12 ) {
      printf( "Radius too large (%.6f, expected %.6f).\n", R, Roff );
      return 1;
   }

   R += 0.0002;

   int covered = 0;
   for ( int i=0; i<N; ++i ) {
      if ( (x-px[i])*(x-px[i]) + (y-py[i])*(y-py[i]) <= R*R+1e-12 )
         ++covered;
   }
   if ( covered < K ) {
      printf( "Covered only %d households (%d required).\n", covered, K );
      return 1;
   }

   printf( "Correct!\n" );
   return 0;
}

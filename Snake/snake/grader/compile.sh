g++ -O2 gslib_io.cpp gslib1.cpp mt19937ar.c -o gslib1
g++ -O2 gslib_io.cpp gslib2.cpp mt19937ar.c -o gslib2
fpc snakelib.pas

#g++ snake.cpp gslib_iface.c -o snake
#gcc -std=c99 snake.c gslib_iface.c -o snake
fpc snake.pas

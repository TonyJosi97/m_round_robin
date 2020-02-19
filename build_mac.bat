gcc main.c -o main.o -c
gcc cbuffer/circular_bfr.c -o circular_bfr.o -c
gcc rrobin/round_robin.c -o round_robin.o -c
gcc -o rrobin.o main.o circular_bfr.o round_robin.o
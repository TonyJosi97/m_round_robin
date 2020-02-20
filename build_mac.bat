gcc main.c -o main.o -c -pedantic -Wall -Wextra -Wconversion
gcc cbuffer/circular_bfr.c -o circular_bfr.o -c -pedantic -Wall -Wextra -Wconversion
gcc rrobin/round_robin.c -o round_robin.o -c -pedantic -Wall -Wextra -Wconversion
gcc -o rrobin.o main.o circular_bfr.o round_robin.o -pedantic -Wall -Wextra -Wconversion
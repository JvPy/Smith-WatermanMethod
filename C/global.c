#include <stdio.h>
#include <time.h>
#include <string.h>

#define match 1
#define mismatch 0
#define gap -1

clock_t begin;
clock_t end;
double timeE;

end = clock();
timeE = (double)(end - begin) / CLOCKS_PER_SEC;
printf("\nTempo de execucao: %.3f segundos.\nFIM DO PROCESSO.\n\n", timeE);
return 0;

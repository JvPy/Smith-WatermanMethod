#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define match 1
#define mismatch 0
#define gap -1

clock_t begin;
clock_t end;
double timeE;

int main(void){
  int i, j, k;         //Conters
  int score, a, b, c;   //Score

  char str1[261], str2[326];          //DNA strings
  char *T_Score, *T_backtrack; //Matrix - Score and backtrack

  FILE *fastaFile;

  puts("Score:\n");
  printf("Match: %i  Mismatch: %i  Gap: %i.\n\n", match, mismatch, gap);
  begin = clock();

  fastaFile=fopen ("gen.fasta","r");  /* o arquivo se chama exemplo.bin e está localizado no diretório corrente */
  if (!fastaFile)
    printf ("Erro na abertura do arquivo.");
  else
    printf("Fasta aberto\n");

  char line [61]; /* or other suitable maximum line size */
  i = 0;
  while(fgets(line, sizeof line, fastaFile) != NULL){ /* read a line */
    // printf("Linha: %i ", i);
    //fputs ( line, stdout ); /* write the line */
    if(line[0] != '>'){
      if(i == 1){
        printf("S1 ");
        printf("%li\t", strlen(line));
        fputs(line, stdout);
        strcat(str1, line);
      }
      if(i == 2){
        printf("S2 ");
        printf("%li\t", strlen(line));
        fputs(line, stdout);
        strcat(str2, line);
      }
    } else {
      printf("Sequencia %i: \n", i);
      i++;
    }
  }

  puts("");
  printf("STR1:\n%s\n\n", str1);
  printf("STR2:\n%s\n\n", str2);



  end = clock();
  timeE = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao: %.3f segundos.\nFIM DO PROCESSO.\n\n", timeE);
  return 0;
}

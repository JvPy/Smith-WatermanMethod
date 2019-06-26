#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define match 5
#define mismatch -3
#define gap -4

#define backtrackMatch -5
#define backtrackMismatch 3
#define backtrackGap 4

// #define linha 262
// #define coluna 327
#define linha 5
#define coluna 7

clock_t begin;
clock_t end;
double timeE;

int main(void){
  int i, j, k;         //Conters
  int score, a, b, c;   //Score

  // char str1[linha] = {0}, str2[coluna] = {0};          //DNA strings
   char tScore[linha][coluna];        //Matrix - Score and backtrack

  char str1[5] = { 'A','C','G','C','\0'};
  char str2[7] = { 'G','A','C','T','A','C','\0'};

  FILE *fastaFile;

  puts("Score:\n");
  printf("Match: %i  Mismatch: %i  Gap: %i.\n\n", match, mismatch, gap);
  begin = clock();

  // fastaFile=fopen ("gen.fasta","r");
  // if (!fastaFile)
  //   printf ("Erro na abertura do arquivo.");
  // else
  //   printf("Fasta aberto\n");
  //
  // char line [128];
  // i = 0;
  // while(fgets(line, sizeof line, fastaFile) != NULL){
  //
  //   if(line[0] != '>'){
  //     if(i == 1){
  //       printf("S1 ");
  //       printf("%li\t", strlen(line));
  //       fputs(line, stdout);
  //       strcat(str1, line);
  //     }
  //     if(i == 2){
  //       printf("str2 ");
  //       printf("%li\t", strlen(line));
  //       fputs(line, stdout);
  //       strcat(str2, line);
  //     }
  //   } else {
  //     i++;
  //   }
  // }

  puts("");
  printf("STR1:\n%s\n\n", str1);
  printf("STR2:\n%s\n\n", str2);

  //Metodo
  //Similaridade
  tScore[0][0] = 0;

	for(i = 0; i < linha-1; i++)
		tScore[i][0] = i * gap;

	for(j = 0; j < coluna-1; j++)
		tScore[0][j] = j * gap;

  for(i = 1; i < linha-1; i++){
    for(j = 1; j < coluna-1; j++){

      score = str1[i-1] == str2[j-1] ? match : mismatch;

			a = tScore[i-1][j-1] + score;
			b = tScore[i-1][j] + gap;
			c = tScore[i][j-1] + gap;

      if(a >= b && a >= c)
        tScore[i][j] = a;
      else if(b > a && b >= c)
        tScore[i][j] = b;
      else
        tScore[i][j] = c;
    }
  }

  printf("i: %d, j: %d\n\n", i, j);

  k = linha >= coluna ? linha : coluna;

  // for(j = 0; j < coluna-1; j++)
  //   printf("\t%c", str2[j]);
  // puts("");
  // for(i = 0; i < linha-1; i++){
  //   printf("%c\t", str1[i]);
  //   for(j = 0; j < coluna-1; j++){
  //     printf("%d\t", tScore[i][j]);
  //   }
  //   puts("");
  // }


  while(i > 0 || j > 0){
    score = str1[i-1] == str2[j-1] ? backtrackMatch : backtrackMismatch;

    a = tScore[i-1][j-1] + score;
    b = tScore[i-1][j] + backtrackGap;
    c = tScore[i][j-1] + backtrackGap;

    printf("i: %d, j: %d\n\n", i, j);
    if(a <= b && a <= c){
      printf("Match\t\t|%c\t%c|\n", str1[i], str2[j]);
      i--;
      j--;
    } else if(b < a && b <= c){
      printf("Gap Linha\t|%c\t-|\n", str1[i-2]);
      j--;
    } else {
      printf("Gap Coluna\t|-\t%c|\n", str2[j-2]);
      i--;
    }
  }

  end = clock();
  timeE = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao: %.3f segundos.\nFIM DO PROCESSO.\n\n", timeE);
  return 0;
}

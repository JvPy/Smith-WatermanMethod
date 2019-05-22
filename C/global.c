#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define match 5
#define mismatch -3
#define gap -4

#define linha 262
#define coluna 327

clock_t begin;
clock_t end;
double timeE;

// Tarefinha:
// S1: gaattcagtta
// S2: ggatcga
//
// Considerando
// Match 5
// Mismatch -3
// Gap -4

int main(void){
  int i, j, k;         //Conters
  int score, a, b, c;   //Score

  char str1[linha] = {0}, str2[coluna] = {0};          //DNA strings
  // char str2[coluna] = {'g','g','a','t','c','a','g'};
  // char s1[linha] = {'g','a','a','t','t','c','a','g','t','t','a'};
  char T_Score[linha][coluna], T_backtrack[linha][coluna];        //Matrix - Score and backtrack

  FILE *fastaFile;

  puts("Score:\n");
  printf("Match: %i  Mismatch: %i  Gap: %i.\n\n", match, mismatch, gap);
  begin = clock();

  fastaFile=fopen ("gen.fasta","r");
  if (!fastaFile)
    printf ("Erro na abertura do arquivo.");
  else
    printf("Fasta aberto\n");

  char line [128];
  i = 0;
  while(fgets(line, sizeof line, fastaFile) != NULL){

    if(line[0] != '>'){
      if(i == 1){
        printf("S1 ");
        printf("%li\t", strlen(line));
        fputs(line, stdout);
        strcat(str1, line);
      }
      if(i == 2){
        printf("str2 ");
        printf("%li\t", strlen(line));
        fputs(line, stdout);
        strcat(str2, line);
      }
    } else {
      i++;
    }
  }

  puts("");
  printf("STR1:\n%s\n\n", str1);
  printf("STR2:\n%s\n\n", str2);
  //Metodo
  //Similaraty
  for(i = 0; i < linha; i++)
    T_Score[i][0] = i * gap;

  for(j = 1; j < coluna; j++)
    T_Score[0][j] = j * gap;

  for(i = 1; i < linha; i++){
    for(j = 1; j < coluna; j++){

      if(str1[i-1] == str2[j-1])
        score = match;
      else
        score = mismatch;

      a = T_Score[i-1][j-1] + score;
      b = T_Score[i-1][j] + gap;
      c = T_Score[i][j-1] + gap;

      if(a >= b && a >= c){
        T_Score[i][j] = a;
        T_backtrack[i][j] = 'd';
      } else if(b > a && b >= c){
        T_Score[i][j] = T_Score[i-1][j] + gap;
        T_backtrack[i][j] = 'u';
      } else {
        T_Score[i][j] = T_Score[i][j-1] + gap;
        T_backtrack[i][j] = 'l';
      }
    }
  }

  for(i = 0; i < linha; i++)
    T_backtrack[i][0] = 'u';

  for(j = 1; j < coluna; j++)
    T_backtrack[0][j] = 'l';

  T_backtrack[0][0] = '.';

  //backtrack
  i = strlen(str1)-1;
  j = strlen(str2)-1;

  if(linha >= coluna)
    k = linha;
  else
    k = coluna;

  while(k >= 0){
    printf("%ix%i\t%c\t", i, j, T_backtrack[i][j]);
    if(T_backtrack[i][j] == 'd'){
      printf("|%c\t%c|\n", str2[j-1], str1[i-1]);
      i--;
      j--;
      k--;
    } else if(T_backtrack[i][j] == 'l'){
      printf("|%c\t-|\n", str2[j-1]);
      j--;
      k--;
    } else if(T_backtrack[i][j] == 'u'){
      printf("|-\t%c|\n", str1[i-1]);
      i--;
      k--;
    } else if(T_backtrack[i][j] == '.'){
      break;
    }

    if(j < 0)
      break;
  }
  // return 0;

  end = clock();
  timeE = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao: %.3f segundos.\nFIM DO PROCESSO.\n\n", timeE);
  return 0;
}

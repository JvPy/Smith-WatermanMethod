#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define match 5
#define mismatch -3
#define gap -4

#define backtrackMatch -match
#define backtrackMismatch -(mismatch)
#define backtrackGap -(gap)

// #define linha 1880
// #define coluna 2806
#define linha 561
#define coluna 563
// #define linha 189
// #define coluna 191
// static const int linha = 1879;
// static const int coluna = 2805;

clock_t begin;
clock_t end;
double timeE;

int i, j, k;         //Conters
int score, a, b, c;   //Score
unsigned int x,y;

char str1[linha], str2[coluna];          //DNA strings
int tScore[linha][coluna];        //Matrix - Score and backtrack

FILE *fastaFile;

int main(){
  puts("[*] Score:\n");
  printf("[*] Match: %i  Mismatch: %i  Gap: %i.\n", match, mismatch, gap);
  printf("[*] backtrackMatch: %i  backtrackMismatch: %i  backtrackGap: %i.\n\n", backtrackMatch, backtrackMismatch, backtrackGap);
  begin = clock();

  fastaFile=fopen ("files/2.fasta","r");
  if (!fastaFile)
    printf ("[-] Erro na abertura do arquivo.\n");
  else
    printf("[+] Fasta aberto!\n");

  char line [128];
  i = 0;
  while(fgets(line, sizeof line, fastaFile) != NULL){

    if(line[0] != '>'){
      if(i == 1){
        x += strlen(line);
        strcat(str1, line);
      }
      if(i == 2){
        y += strlen(line);
        strcat(str2, line);
      }
    } else {
      i++;
    }
  }

  printf("\nSTR1:%d\tSTR2:%d\n\n", x, y);

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

  while(i > 0 && j > 0){
    score = str1[i-1] == str2[j-1] ? backtrackMatch : backtrackMismatch;

    a = tScore[i-1][j-1] + score;
    b = tScore[i-1][j] + backtrackGap;
    c = tScore[i][j-1] + backtrackGap;

    if(a <= b && a <= c){
      printf("Diagonal\t|%c\t%c|\t", str1[i], str2[j]);
      i--;
      j--;
    } else if(b < a && b <= c){
      printf("Gap Linha\t|%c\t-|\t", str1[i-1]);
      j--;
    } else {
      printf("Gap Coluna\t|-\t%c|\t", str2[j-1]);
      i--;
    }
    printf("i: %d, j: %d\n", i, j);
  }

  printf("\nPontuacao: %d\n", x);

  end = clock();
  timeE = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\n[*] Tempo de execucao: %.3f segundos.\nFIM DO PROCESSO.\n\n", timeE);
  return 0;
}

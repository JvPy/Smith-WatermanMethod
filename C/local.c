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

// #define linha 1879
// #define coluna 2805
// #define linha 560
// #define coluna 562
#define linha 188
#define coluna 190

clock_t begin;
clock_t end;
double timeE;

int main(void){
  int i, j, k;                            //Conters
  int iStart, jStart, kStart, valueStart; //Startpoint
  int score, a, b, c;                     //Score
  unsigned int x,y;

  char str1[linha] = {0}, str2[coluna] = {0};          //DNA strings
  char tScore[linha][coluna];                          //Matrix - Score and backtrack

  FILE *fastaFile;

  puts("[*] Score:\n");
  printf("[*] Match: %i  Mismatch: %i  Gap: %i.\n", match, mismatch, gap);
  printf("[*] backtrackMatch: %i  backtrackMismatch: %i  backtrackGap: %i.\n\n", backtrackMatch, backtrackMismatch, backtrackGap);
  begin = clock();

  fastaFile=fopen ("files/3.fasta","r");
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

			a = tScore[i-1][j-1] + score > 0 ? tScore[i-1][j-1] + score : 0;
			b = tScore[i-1][j] + gap > 0 ? tScore[i-1][j] + gap > 0 : 0;
			c = tScore[i][j-1] + gap > 0 ? tScore[i][j-1] + gap > 0 : 0;

      if(a >= b && a >= c)
        tScore[i][j] = a;
      else if(b > a && b >= c)
        tScore[i][j] = b;
      else
        tScore[i][j] = c;
    }
  }

	valueStart = tScore[0][0];

  for(i = 0; i < linha-1; i++){
    for(j = 0; j < coluna-1; j++){
			if(tScore[i][j] > valueStart){
				valueStart = tScore[i][j];
				iStart = i;
				jStart = j;
			}
    }
  }

	printf("[*] Valor inicial: %d;\n[*] iStart: %d;\n[*] jStart %d;\n\n", valueStart, iStart, jStart);

  while(iStart > 0 && jStart > 0){
    score = str1[iStart-1] == str2[jStart-1] ? backtrackMatch : backtrackMismatch;

    a = tScore[iStart-1][jStart-1] + score;
    b = tScore[iStart-1][jStart] + backtrackGap;
    c = tScore[iStart][jStart-1] + backtrackGap;

    if(a <= b && a <= c){
      printf("Diagonal\t\t|%c\t%c|\t", str1[iStart], str2[jStart]);
      iStart--;
      jStart--;
    } else if(b < a && b <= c){
      printf("Gap Linha\t|%c\t-|\t", str1[iStart-2]);
      jStart--;
    } else {
      printf("Gap Coluna\t|-\t%c|\t", str2[jStart-2]);
      iStart--;
    }
    printf("iStart: %d, jStart: %d\n", iStart, jStart);
  }

  end = clock();
  timeE = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\n[*] Tempo de execucao: %.3f segundos.\nFIM DO PROCESSO.\n\n", timeE);
  return 0;
}

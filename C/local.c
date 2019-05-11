#include <stdio.h>
#include <time.h>
#include <string.h>

#define match 1
#define mismatch 0
#define gap -1

clock_t begin;
clock_t end;
double timeE;

int main(void){
	//Contadores
	int i;
	int j;
	int k;

	//Pontuacao
	int score;
	int a;
	int b;
	int c;

	//Fitas de DNA
	char str1[5] = { 'A','C','G','C','\0'};
	char str2[7] = { 'G','A','C','T','A','C','\0'};
	char tabela[6][8];
	char direcao[6][8];

	int m = strlen(str1)+1;		//Linha
	int n = strlen(str2)+1; 	//Coluna

	puts("Score:\n");
	printf("Match: %i  Mismatch: %i  Gap: %i.\n\n", match, mismatch, gap);

	begin = clock();
	
	//Similaridade
	for(i = 0; i < m; i++)
		tabela[i][0] = i * gap;

	for(j = 1; j < n; j++)
		tabela[0][j] = j * gap;

	for(i = 1; i < m; i++){
		for(j = 1; j < n; j++){
			//Definir score
			if(str1[i-1] == str2[j-1])
				score = match;
				else 
					score = mismatch;
			a = tabela[i-1][j-1] + score;
			b = tabela[i-1][j] + gap;
			c = tabela[i][j-1] + gap;
			
			//Definir MAX
			//Max pela diagonal
			if( a >= b && a >= c) {
				tabela[i][j] = a;	
				direcao[i][j] = 'd';
			//Max por cima
			} else if( b > a && b >= c ) {
				tabela[i][j] = tabela[i-1][j] + gap;
				direcao[i][j] = 'u';
			//Max pela esquerda
			} else {
				tabela[i][j] = tabela[i][j-1] + gap;
				direcao[i][j] = 'l';
			}
		}
	}

	puts("\n");
	
	//Print da tabela
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			printf("%i\t", tabela[i][j]);
		}
		puts("\n");
	} 
	
	puts("\n");

	//print da  matriz Backtrack
	for(i = 0; i < m; i++)
		direcao[i][0] = 'u';
	for(j = 1; j < n; j++)
		direcao[0][j] = 'l';

	direcao[0][0] = '.';

	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			printf("%c\t", direcao[i][j]);
		}
		puts("\n");
	}

	//Backtrack
	i = strlen(str1);
	j = strlen(str2);
	if(n >= m)
		k = n;
	else
		k = m;

	while(k >= 0){
		printf("%ix%i\t%c\t", i, j, direcao[i][j]);
		if(direcao[i][j] == 'd'){
			printf("|%c\t%c|\n", str2[j-1], str1[i-1]);
			i--; 
			j--;
			k--;
		}else if(direcao[i][j] == 'l'){
			printf("|%c\t-|\n", str2[j-1]);
			j--;
			k--;
		} else if(direcao[i][j] == 'u'){
			printf("|-\t%c|\n", str1[i-1]);
			i--;
			k--;
		} else if(direcao[i][j] == '.')
			break;
		if(j < 0){
			printf("break pois j == 0\n");
			break;
		}
	}

	puts("\n");

	end = clock();
	timeE = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTempo de execucao: %.3f segundos.\nFIM DO PROCESSO.\n\n", timeE);
	return 0;
}
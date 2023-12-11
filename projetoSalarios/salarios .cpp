/* Projeto de calculo de salarios
Grupo composto por: Gustavo Hideki Takeuchi, Joao V L Marchette, Vinicius Kazuo Takeuchi */

#include<stdio.h>
#include<stdlib.h>

void trocarPosicoes(double *a, double *b) 
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

void ordenarVetores(double *vetor, int tamanho) 
{
    int i, j;
    for (i = 0; i < tamanho - 1; i++) 
	{
        for (j = 0; j < tamanho - i - 1; j++) 
		{
            if (vetor[j] > vetor[j + 1]) 
			{
                trocarPosicoes(&vetor[j], &vetor[j + 1]);
            }
        }
    }
}

int main() 
{
	FILE *arqSalarios; // Declaração do ponteiro para o arquivo de entrada
	FILE *arqCalculos; // Declaração do ponteiro para o arquivo de saída
	int tam; // Variável para armazenar o tamanho dos vetores
	double *salBruto; 
	double *aliqINSS; 
	double *impostoINSS; 
	double *aliqIR; 
	double *impostoIR; 
	double *salLiquido; 
	int i; 
	double auxiliarSalario; 
	  
	printf("Projeto de calculo de salarios\n");
	printf("Grupo composto por: Gustavo Hideki Takeuchi, Joao V L Marchette, Vinicius Kazuo Takeuchi\n");
	printf("ILP-501 Fatec SP"); 

	arqSalarios = fopen("SALARIO.txt", "r"); // Abre o arquivo de entrada
	if (arqSalarios == NULL) 
	{
	    fprintf(stderr, "Erro ao abrir o arquivo CALCULOS.TXT\n");
	    return 1;
	}
	  
	tam = 0; // Inicializa o tamanho dos vetores !!NÃO REMOVER!!
	salBruto = NULL; // Inicializa o vetor de salários brutos !!NÃO REMOVER!!
	  
	while (fscanf(arqSalarios, "%lf\n", &auxiliarSalario) != EOF ) 
	{ 
		tam++; 
	    salBruto = (double *)realloc(salBruto, sizeof(double) * tam);
		salBruto[tam-1] = auxiliarSalario;                  
	}
	fclose(arqSalarios); 
	
	// Ordena os salários brutos
	ordenarVetores(salBruto, tam);
	
	aliqINSS = (double *)malloc(sizeof(double) * tam); 
	impostoINSS = (double *)malloc(sizeof(double) * tam); 
	aliqIR = (double *)malloc(sizeof(double) * tam); 
	impostoIR = (double *)malloc(sizeof(double) * tam); 
	salLiquido = (double *)malloc(sizeof(double) * tam); 
  
	for(i = 0; i < tam; i++) 
	{
		if (salBruto[i] <= 1751.81) 
		{
		  aliqINSS[i] = 0.08;
		} 
		else if (salBruto[i] >= 1751.82 && salBruto[i] <= 2919.72) 
		{
		  aliqINSS[i] = 0.09;
		} 
		else if (salBruto[i] >= 2919.73 && salBruto[i] <= 5839.45) 
		{
		  aliqINSS[i] = 0.11;
		} 
		else if (salBruto[i] >= 5839.46) 
		{
		  aliqINSS[i] = 0.0;
		} 
		else 
		{
		  aliqINSS[i] = 0.0;
		}
		
		impostoINSS[i] = salBruto[i] * aliqINSS[i];
		
		double baseIR = salBruto[i] - impostoINSS[i];
		
		double deducaoIR=0.0;
		if (baseIR <= 1903.98) 
		{
		  aliqIR[i] = 0.0;
		} 
		else if (baseIR >= 1903.99 && baseIR <= 2826.65) 
		{
		  aliqIR[i] = 0.075;
		  deducaoIR = 142.80;
		} 
		else if (baseIR >= 2826.66 && baseIR <= 3751.05) 
		{
		  aliqIR[i] = 0.15;
		  deducaoIR = 354.80;
		} 
		else if (baseIR >= 3751.06 && baseIR <= 4664.68) 
		{
		  aliqIR[i] = 0.225;
		  deducaoIR = 636.13;
		} 
		else if (baseIR > 4664.69) 
		{
		  aliqIR[i] = 0.275;
		  deducaoIR = 869.36;
		}
		
		impostoIR[i] = (salBruto[i] - impostoINSS[i]) * aliqIR[i] - deducaoIR;
		
		if (impostoIR[i] < 10.0) 
		{
		  impostoIR[i] = 0.0;
		}
		salLiquido[i] = salBruto[i] - impostoINSS[i] - impostoIR[i]; // Calcula o salário líquido
	}
  
	arqCalculos = fopen("CALCULOS.TXT", "w"); // Abre o arquivo de saída
	if (arqCalculos == NULL) 
	{
	    fprintf(stderr, "Erro ao abrir o arquivo CALCULOS.TXT\n");
	    return 1;
	}
	fprintf(arqCalculos, "%-14s%-20s%-15s%-15s%-12s%-15s%-15s\n", "Bruto", "AliqINSS", "ValINSS", "BaseIR", "AliqIR", "ValIR", "Liquido");
	
	for (i = 0; i < tam; i++) 
	{
	    fprintf(arqCalculos, "%-14.2lf%-20.2lf%-15.2lf%-15.2lf%-12.2lf%-15.2lf%-15.2lf\n",
    salBruto[i], aliqINSS[i] * 100, impostoINSS[i], salBruto[i] - impostoINSS[i], aliqIR[i] * 100, impostoIR[i], salLiquido[i]);

	}
	fclose(arqCalculos); 
	
    free(salBruto);
    free(impostoINSS);
    free(impostoIR);
    free(salLiquido);
  
  printf("\n\nFim do Programa\n");
  return 0;
}


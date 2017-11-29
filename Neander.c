#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


int ler_arquivo(FILE *neandertxt, char MatrizI[][4], int Vetor[], char Stexto[], int *endereco_memoria)
{
  int i = 0, j = 0;
  char temp[10], temp1[2], temp2[2], temp3[2], temp4[2], texto[1];

  strcpy(temp1, "0");
  strcpy(temp2, "0");
  strcpy(temp3, "0");
  strcpy(temp4, "0");

  neandertxt = fopen("Neander.txt", "r");
  if (!neandertxt){
    printf("N�o foi possivel abrir o arquivo\n");

    return 1;
  }

  while (!feof(neandertxt))
  {
    if (i > 256){
      printf("ERRO: Este micro, disp�e de 256 posi��es de mem�ria, contudo � impossivel continuar...!\n");
      return 1;
    }

    fgets(Stexto, 10, neandertxt);

    MatrizI[i][0] = Stexto[0];
    MatrizI[i][1] = Stexto[1];
    MatrizI[i][2] = Stexto[2];
    MatrizI[i][3] = '\0';

    temp4[0] = Stexto[2];

    if (!strcmp(temp4, " "))
      j=3;
    else
      j=4;

    temp1[0] = Stexto[j];
    temp2[0] = Stexto[j+1];
    temp3[0] = Stexto[j+2];

    strcpy(temp, temp1);
    strcat(temp, temp2);
    strcat(temp, temp3);

    Vetor[i] = atoi (temp);

    i++;
  }

  *endereco_memoria = i;

  fclose(neandertxt);
  return 0;
}

int simulador(char MatrizI[][4], int Vetor[], int *RI, int *PC, int *AC, int *endereco_memoria)
{
  if (!strcmp(MatrizI[*PC],"NOP") || !strcmp(MatrizI[*PC],"STA") || !strcmp(MatrizI[*PC],"LDA")||
  !strcmp(MatrizI[*PC],"ADD")|| !strcmp(MatrizI[*PC],"OR ")|| !strcmp(MatrizI[*PC],"AND")||
  !strcmp(MatrizI[*PC],"NOT") || !strcmp(MatrizI[*PC],"JMP") || !strcmp(MatrizI[*PC],"HLT") ||
  (Vetor[*PC] >= -127 & Vetor[*PC] <= 128))
  {
    if (!strcmp(MatrizI[*PC] , "HLT"))
    {
      printf("\nFIM DA SIMULA��O COM A INSTRU��O HALT\n");
      printf("PC = %d\n", *PC);
      printf("AC = %d\n", *AC);
      printf("MEM�RIA UTILIZADA = %d Endere�os\n", *endereco_memoria);
      return 1;
    } else if (!strcmp(MatrizI[*PC] , "NOP"))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      printf("� A CPU enviou o conte�do do PC (%d) que no caso � endere�o da pr�xima instru��o via BE, para o REM.\n", *PC);
      printf("� A MP l� o REM e retorna para o RDM o conte�do deste endere�o via BD. Logo depois o dado (%s %d) � transferido para o RI.\n", MatrizI[*PC], Vetor[*PC]);
      printf("� O RI passa a instru��o para o UC.\n");
      printf("� A UC decodifica a instru��o.\n");
      printf("� Como se trata de NOP, nada � executado.\n");
      *PC += 1;
      printf("� Por fim o PC � incrementado:Logo PC = %d", *PC);
    } else if (!strcmp(MatrizI[*PC] , "STA"))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      MatrizI[Vetor[*PC]][0] = *AC;
      printf("� A CPU enviou o conte�do do PC (%d) que no caso � endere�o da pr�xima instru��o via BE, para o REM.\n", *PC);
      printf("� A MP l� o REM e retorna para o RDM o conte�do deste endere�o via BD. Logo depois o dado (%s %d) � transferido para o RI.\n", MatrizI[*PC], Vetor[*PC]);
      printf("� O RI passa a instru��o para o UC.\n");
      printf("� A UC decodifica a instru��o.\n");
      printf("� Como se trata de STA (Armazena AC), a MP recebe um comando de grava��o onde s�o passados endere�o (%d) e dado (%d) a ser gravado, que no caso � o dado do AC.\n", Vetor[*PC], *AC);
      *PC += 1;
      printf("� Por fim o PC � incrementado: Logo PC = %d", *PC);
      if (*endereco_memoria < Vetor[*PC]){
        *endereco_memoria += 1;
      }
    }else if (!strcmp(MatrizI[*PC] , "LDA"))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      *AC = atoi (MatrizI[Vetor[*PC]]);
      printf("� A CPU enviou o conte�do do PC (%d) que no caso � endere�o da pr�xima instru��o via BE, para o REM.\n", *PC);
      printf("� A MP l� o REM e retorna para o RDM o conte�do deste endere�o via BD. Logo depois o dado (%s %d) � transferido para o RI.\n", MatrizI[*PC], Vetor[*PC]);
      printf("� O RI passa a instru��o para o UC.\n");
      printf("� A UC decodifica a instru��o.\n");
      printf("� Como se trata de LDA (Carrega AC), a UC passa para ULA a realiza��o da opera��o IGUAL:\n");
      printf("  - � realizada uma busca na MP no endere�o (%d), retornado o dado (%d)\n", Vetor[*PC], atoi (MatrizI[Vetor[*PC]]));
      printf("  - O resultado (%d) desta opera��o � enviado para o AC.\n", *AC);
      if (*AC < 0){
        printf("  - Como o resultado (%d) desta opera��o � negativo a flag N � ativada.\n", *AC);

      }else {
        printf("  - Como o resultado (%d) desta opera��o � positivo a flag Z � ativada.\n", *AC);
      }
      *PC += 1;
      printf("� Por fim o PC � incrementado: PC = %d", *PC);
    }else if(!strcmp(MatrizI[*PC] , "ADD"))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      *AC += atoi (MatrizI[Vetor[*PC]]);
      printf("� A CPU enviou o conte�do do PC (%d) que no caso � endere�o da pr�xima instru��o via BE, para o REM.\n", *PC);
      printf("� A MP l� o REM e retorna para o RDM o conte�do deste endere�o via BD. Logo depois o dado (%s %d) � transferido para o RI.\n", MatrizI[*PC], Vetor[*PC]);
      printf("� O RI passa a instru��o para o UC.\n");
      printf("� A UC decodifica a instru��o.\n");
      printf("� Como se trata de ADD (Soma ao AC), a UC passa para ULA a realiza��o da opera��o SOMA:\n");
      printf("  - Esta recebe o dado do AC, e logo ap�s � realizada uma busca na MP no endere�o (%d), retornado o dado (%d), e somado-o ao dado do AC;\n", Vetor[*PC], MatrizI[*PC]);
      printf("  - O resultado (%d) desta opera��o � enviado para o AC.\n", *AC);
      if (*AC < 0)
        printf("  - Como o resultado (%d) desta opera��o � negativo a flag N � ativada.\n", *AC);
      else
        printf("  - Como o resultado (%d) desta opera��o � positivo a flag Z � ativada.\n", *AC);

      *PC += 1;
      printf("� Por fim o PC � incrementado: PC = %d\n", *PC);
    }else if(!strcmp(MatrizI[*PC] , "OR "))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      *PC += 1;
      printf("� Incrementa o PC: ");
      printf("PC = %d", *PC);
    }else if(!strcmp(MatrizI[*PC] , "AND"))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      printf("� Compara AC com Valor da Memoria no Endere�o: %d\n", Vetor[*PC]);
      if (MatrizI[Vetor[*PC]][0] == *AC)
      {
        printf("  - AC igual ao Valor da Mem�ria no Endere�o %d\n", Vetor[*PC]);
        *PC = 5;
        printf("�Incrementa o PC: ");
        printf("PC = %d", *PC);
      }else
      {
        printf("  - AC diferente ao Valor da Mem�ria no Endere�o %d\n", Vetor[*PC]);
        *PC += 1;
        printf("�Incrementa o PC: ");
        printf("PC = %d", *PC);
      }
    }else if(!strcmp(MatrizI[*PC] , "NOT"))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      *PC += 1;
      printf("� Incrementa o PC: ");
      printf("� PC = %d", *PC);
    }else if(!strcmp(MatrizI[*PC] , "JMP"))
    {
      printf("\n%s %d\n", MatrizI[*PC], Vetor[*PC]);
      printf("� Pula para instru��o da linha de comandos %d.\n", Vetor[*PC]);
      *PC = Vetor[*PC];
      printf("PC = %d", *PC);
    }
    printf("\n");
  } else
  {
    if (Vetor[*PC] < -127 & Vetor[*PC] > 128)
    {
      printf("ERRO: Este micro, s� pode realizar contas com n�meros > -126 e < 129\n");
    } else {
      printf("ERRO: Fim das instru��es, sem serem finalizadas com HALT\n");
    }
    return 1;
  }
  return 0;
}


int main ()
{
  setlocale(LC_ALL, "Portuguese");
  FILE *neandertxt;
  char MatrizI[256][4], Stexto[9];
  int Vetor[256], RI = 0, PC = 0, AC = 0, retorno = 0, endereco_memoria = 0;

  printf("-------------------------------------------------------------------\n");
  printf("                          Bem-Vindo                                \n");
  printf("                             ao                                    \n");
  printf("                           Neander                                 \n");
  printf("-------------------------------------------------------------------\n\n");

  printf("         Pressione a tecla ENTER para iniciar a simula��o\n");
  fgetc(stdin);

  retorno = ler_arquivo(&neandertxt, &MatrizI, &Vetor, &Stexto, &endereco_memoria);

  if (retorno == 1){
    return 0;
  }
  while (simulador(&MatrizI, &Vetor, &RI, &PC, &AC, &endereco_memoria) != 1) {
    printf("         Pressione a tecla ENTER para iniciar a simula��o\n");
    fgetc(stdin);
  }
}

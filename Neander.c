#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


int leitura(FILE *neandertxt, char Nome_Instrucao[][4], int Numero[], char txt[], int *endereco_memoria)
{
  int i = 0, j = 0;
  char aux[10], aux1[2], aux2[2], aux3[2], aux4[2], texto[1];

  strcpy(aux1, "0");
  strcpy(aux2, "0");
  strcpy(aux3, "0");
  strcpy(aux4, "0");

  neandertxt = fopen("Neander.txt", "r");
  if (!neandertxt){
    printf("N�o foi possivel abrir o arquivo\n");

    return 1;
  }

  while (!feof(neandertxt))
  {
    fgets(txt, 10, neandertxt);

    Nome_Instrucao[i][0] = txt[0];
    Nome_Instrucao[i][1] = txt[1];
    Nome_Instrucao[i][2] = txt[2];
    Nome_Instrucao[i][3] = '\0';

    aux4[0] = txt[2];

    if (!strcmp(aux4, " "))
      j=3;
    else
      j=4;

    aux1[0] = txt[j];
    aux2[0] = txt[j+1];
    aux3[0] = txt[j+2];

    strcpy(aux, aux1);
    strcat(aux, aux2);
    strcat(aux, aux3);

    Numero[i] = atoi (aux);

    i++;
  }

  *endereco_memoria = i;

  fclose(neandertxt);
  return 0;
}

int teste(char Nome_Instrucao[][4], int Numero[], int *RI, int *PC, int *AC, int *endereco_memoria)
{
  if (!strcmp(Nome_Instrucao[*PC],"NOP") || !strcmp(Nome_Instrucao[*PC],"STA") || !strcmp(Nome_Instrucao[*PC],"LDA")||
  !strcmp(Nome_Instrucao[*PC],"ADD")|| !strcmp(Nome_Instrucao[*PC],"OR ")|| !strcmp(Nome_Instrucao[*PC],"AND")||
  !strcmp(Nome_Instrucao[*PC],"NOT") || !strcmp(Nome_Instrucao[*PC],"JMP") || !strcmp(Nome_Instrucao[*PC],"HLT") ||
  (Numero[*PC] >= -127 & Numero[*PC] <= 128))
  {
    if (!strcmp(Nome_Instrucao[*PC] , "HLT"))
    {
      printf("\nFIM DA SIMULA��O COM A INSTRU��O HALT\n");
      printf("PC = %d\n", *PC);
      printf("AC = %d\n", *AC);
      printf("MEM�RIA UTILIZADA = %d Endere�os\n", *endereco_memoria);
      return 1;
    }
    else if (!strcmp(Nome_Instrucao[*PC] , "NOP"))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      printf("Busca de Instru��o:\n");
      printf(" --> A CPU envia o conte�do do PC (%d) para o REM.\n", *PC);
      printf(" --> A Mem�ria Principal l� o REM e retorna para o RDM o conte�do do endere�o.\n");
      printf(" --> Tranfere-se o dado (%s %d) para o RI.\n", Nome_Instrucao[*PC], Numero[*PC]);
      printf(" --> O RI passa a instru��o para a Unidade de Controle.\n");
      printf(" --> Ocorre a decodifica��o da instru��o pela Unidade de Controle.\n");
      printf("Execu��o:\n");
      printf(" --> Nenhuma execu��o.\n");
      *PC += 1;
      printf(" --> PC parte para pr�xima instru��o, ent�o PC = %d.", *PC);
    }
    else if (!strcmp(Nome_Instrucao[*PC] , "STA"))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      Nome_Instrucao[Numero[*PC]][0] = *AC;
      printf("Busca de Instru��o:\n");
      printf(" --> A CPU envia o conte�do do PC (%d) para o REM.\n", *PC);
      printf(" --> A Mem�ria Principal l� o REM e retorna para o RDM o conte�do deste endere�o.");
      printf(" --> O dado (%s %d) � transferido para o RI.\n", Nome_Instrucao[*PC], Numero[*PC]);
      printf(" --> O RI passa a instru��o para o Unidade de Controle.\n");
      printf(" --> A Unidade de Controle decodifica a instru��o.\n");
      printf("Execu��o:\n");
      printf(" --> A Mem�ria Principal recebe um comando para gravar o dado do AC onde s�o passados o endere�o (%d) e o dado (%d) a ser gravado.\n", Numero[*PC], *AC);
      *PC += 1;
      printf(" --> PC parte para pr�xima instru��o, ent�o PC = %d.", *PC);
      if (*endereco_memoria < Numero[*PC]){
        *endereco_memoria += 1;
      }
    }
    else if (!strcmp(Nome_Instrucao[*PC] , "LDA"))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      *AC = atoi (Nome_Instrucao[Numero[*PC]]);
      printf("Busca de Instru��o:\n");
      printf(" --> A CPU envia o conte�do do PC (%d) para o REM.\n", *PC);
      printf(" --> A Mem�ria Principal l� o REM e retorna para o RDM o conte�do do endere�o.\n");
      printf(" --> O dado (%s %d) � transferido para o RI.\n", Nome_Instrucao[*PC], Numero[*PC]);
      printf(" --> O RI passa a instru��o para a Unidade de Controle.\n");
      printf(" --> A Unidade de Controle decodifica a instru��o.\n");
      printf("Execu��o:\n");
      printf(" --> A Unidade de Controle passa para ULA a realiza��o da opera��o IGUALDADE.\n");
      printf(" --> � realizada uma busca na Mem�ria Principal no endere�o (%d), retornando o dado (%d).\n", Numero[*PC], atoi (Nome_Instrucao[Numero[*PC]]));
      printf(" --> O resultado (%d) da opera��o � enviado para o AC.\n", *AC);
      if (*AC < 0)
      printf(" -->  Como o resultado (%d) da opera��o � negativo a flag N � ativada.\n", *AC);
      else
      {
      printf(" --> Como o resultado (%d) da opera��o � positivo a flag Z � ativada.\n", *AC);
      }
      *PC += 1;
      printf(" --> PC parte para pr�xima instru��o, ent�o PC = %d.", *PC);
    }
    else if(!strcmp(Nome_Instrucao[*PC] , "ADD"))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      *AC += atoi (Nome_Instrucao[Numero[*PC]]);
      printf("Busca de Instru��o:\n");
      printf(" --> A CPU enviou o conte�do do PC (%d) para o REM.\n", *PC);
      printf(" --> A Mem�ria Principal l� o REM e retorna para o RDM o conte�do do endere�o.\n");
      printf(" --> O dado (%s %d) � transferido para o RI.\n", Nome_Instrucao[*PC], Numero[*PC]);
      printf(" --> O RI passa a instru��o para a Unidade de Controle.\n");
      printf(" --> A Unidade de Controle decodifica a instru��o.\n");
      printf("Execu��o:\n");
      printf(" --> A Unidade de Controle passa para ULA a realiza��o da opera��o SOMA.\n");
      printf(" --> A ULA recebe o dado do AC e realiza uma busca na Mem�ria Principal no endere�o (%d), retornando o dado (%d), e somando ao dado do AC.\n", Numero[*PC], Nome_Instrucao[*PC]);
      printf(" --> O resultado (%d) da opera��o � enviado para o AC.\n", *AC);
      if (*AC < 0)
        printf(" --> Como o resultado (%d) da opera��o � negativo a flag N � ativada.\n", *AC);
      else
        printf(" --> Como o resultado (%d) da opera��o � positivo a flag Z � ativada.\n", *AC);

      *PC += 1;
      printf(" --> PC parte para pr�xima instru��o, ent�o PC = %d.", *PC);
    }
    else if(!strcmp(Nome_Instrucao[*PC] , "OR "))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      *PC += 1;
      printf(" --> PC = %d", *PC);
    }
    else if(!strcmp(Nome_Instrucao[*PC] , "AND"))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      printf("Busca de Instru��o:\n");
      printf(" --> Compara AC com Valor da Memoria no Endere�o: %d\n", Numero[*PC]);
      if (Nome_Instrucao[Numero[*PC]][0] == *AC)
      {
      printf(" --> AC igual ao Valor da Mem�ria no Endere�o %d\n", Numero[*PC]);
        *PC = 5;
        printf(" --> PC = %d", *PC);
      }
      else
      {
      printf(" --> AC diferente ao Valor da Mem�ria no Endere�o %d\n", Numero[*PC]);
        *PC += 1;
        printf(" --> PC = %d", *PC);
      }
    }
    else if(!strcmp(Nome_Instrucao[*PC] , "NOT"))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      *PC += 1;
      printf(" --> PC = %d", *PC);
    }
    else if(!strcmp(Nome_Instrucao[*PC] , "JMP"))
    {
      printf("\n%s %d\n", Nome_Instrucao[*PC], Numero[*PC]);
      printf(" --> Pula para instru��o da linha de comandos %d.\n", Numero[*PC]);
      *PC = Numero[*PC];
      printf(" --> PC = %d", *PC);
    }
    printf("\n");
  }
  else
  {
    if (Numero[*PC] < -127 & Numero[*PC] > 128)
      printf("ERRO: Este micro, s� pode realizar contas com n�meros > -126 e < 129\n");
    else {
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
  char Nome_Instrucao[100][4], txt[9];
  int Numero[100], RI = 0, PC = 0, AC = 0, retorno = 0, endereco_memoria = 0;

  printf("-------------------------------------------------------------------\n");
  printf("                          Bem-Vindo                                \n");
  printf("                             ao                                    \n");
  printf("                           Neander                                 \n");
  printf("-------------------------------------------------------------------\n\n");

  printf("                Pressione qualquer tecla\n");
  fgetc(stdin);

  retorno = leitura(&neandertxt, &Nome_Instrucao, &Numero, &txt, &endereco_memoria);

  if (retorno == 1){
    return 0;
  }
  while (teste(&Nome_Instrucao, &Numero, &RI, &PC, &AC, &endereco_memoria) != 1) {
    printf("                Pressione qualquer tecla\n");
    fgetc(stdin);
  }
}

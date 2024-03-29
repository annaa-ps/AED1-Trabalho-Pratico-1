//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

/*Sistema de Processos */
#include<stdlib.h>
#include <stdio.h>
#include<string.h>

typedef struct no{
  char nome[50];
  float tempoExecucao; 
  struct no*proximo;
}No;

typedef struct {
  No *inicio;
  No *fim;
  No *processosRemovidos; //Lista para armazenar os processos removidos
  int tam; 
}Fila;

//Função para criar a fila
void criar_fila(Fila *fila){
  fila->inicio = NULL;
  fila->fim = NULL; 
  fila->tam = 0;
}

//Função para inserir um elemento na fila
void inserirFila(Fila *fila, char nome[], float tempoExecucao){
  No *novo = (No*)malloc(sizeof(No));

  if(novo){
    strcpy(novo->nome, nome);
    novo->tempoExecucao = tempoExecucao;
    novo->proximo = NULL;

    if(fila->inicio == NULL){
      fila->inicio = novo;
      fila->fim = novo;
    }else{
      fila->fim->proximo = novo; 
      fila->fim = novo; 
    }
    fila->tam++;
  }else{
    printf("\nErro ao alocar memoria!\n");
  }
}

//Função para remover um elemento da fila
No* removerFila(Fila *fila){
  No *remover = NULL;
  if(fila->inicio){
    remover = fila->inicio;
    fila->inicio = remover->proximo;
    fila->tam--;

    //Adiciona o processo removido para a fila de processos que já foram executados 
    remover->proximo = fila->processosRemovidos;
    fila->processosRemovidos = remover; 
  }else{
    printf("\n\tFila Vazia!\n");
  }
  return remover;
}

//Função  para imprimir os dados do processo 
void imprimir_processo(No *processo){
    printf("----------------------------------------");
    printf("\nNome: [%s]\n", processo->nome); 
    printf("Tempo de Execucao: [%.2f]\n", processo->tempoExecucao);
    printf("----------------------------------------\n");
}

//Função para imprimir a fila
void imprimir(Fila *fila){
  No *aux = fila->inicio;
  printf("\n\t\tFILA\t\n");
  while(aux){
    imprimir_processo(aux);
    aux = aux->proximo;
  }
  printf("\t\tFIM FILA\n");
}

//Função para calcular o tempo médio de execução dos processos que estão esperando para serem executados
float calcularTempoMedio(Fila *fila){
  No *aux = fila->inicio;
  int qtdeProcessos = 0;
  float tempoTotal = 0;


  while(aux){
    tempoTotal += aux->tempoExecucao;
    qtdeProcessos++;
    aux = aux->proximo;
  }

  if(qtdeProcessos == 0){
    printf("\nNenhum processo na fila\n");
    return 0;
  }

  return tempoTotal / qtdeProcessos; 
}

//Função para calcular o tempo médio de execução dos processos que já foram executados (já saíram da lista)
float calcularTempoExecutados(No *processosRemovidos){
  No *aux = processosRemovidos;
  int qtdeProcessos = 0;
  float tempoTotal = 0; 

  while (aux){
    tempoTotal += aux->tempoExecucao;
    qtdeProcessos++;
    aux = aux->proximo;
  }

  if(qtdeProcessos == 0){
    printf("\nNenhum processo foi executado ainda!\n"); 
    return 0;
  }
  return tempoTotal / qtdeProcessos; 
}


int main(){
  No *remover; 
  Fila fila; 
  char nome[50];
  int qtdeProcessos, i, opcao; 
  float tempoMedio, tempoExecucao, tempoMedioExecutados; 

  //Criando a fila 
  criar_fila(&fila);
  do{
    printf("\n---------------------------------MENU DE OPCOES---------------------------------\n");
    printf("\t1 - Adicionar Processos\n\t2 - Remover Processos\n\t3 - Calcular Tempo Medio\n\t4 - Calcular Tempo Medio dos Processos ja Executados\n\t5 - Imprimir lista de Procesos\n");
    printf("----------------------------------------------------------------------------------\n");
    scanf("%d", &opcao);
    getchar();

    switch(opcao){
      case 1:
        printf("\nInforme a quantidade de processos para a simulacao:\n");
        scanf("%d", &qtdeProcessos);
        //Lendo os dados do usuário
        for(i = 0; i < qtdeProcessos; i++){
          printf("\nInforme o nome do %d processo:\n", i+1);
          scanf("%s", nome);
          printf("Informe o tempo de execucao do  %d processo:\n", i+1);
          scanf("%f", &tempoExecucao); 

          //Inserindo os dados na fila
          inserirFila(&fila, nome, tempoExecucao); 
        }
        break;
      case 2:
        remover = removerFila(&fila);
        if(remover != NULL){
          printf("\n---------------------------------------");
          printf("\nProcesso removido:\n");
          imprimir_processo(remover); 
          printf("\n"); 
          free(remover);
        }else{
          printf("\nSem produto cadastrado para remover!\n");
        }
        break;

      case 3:
        tempoMedio = calcularTempoMedio(&fila);
        printf("\n-------------------------------------------");
        printf("\nTempo medio de execucao: %.2f\n", tempoMedio);
        printf("-------------------------------------------");
        printf("\n");
        break;
      case 4:
        tempoMedioExecutados = calcularTempoExecutados(fila.processosRemovidos);
        printf("-------------------------------------------------------------------------");
        printf("\nTempo medio de execucao dos processos que ja foram executados: %.2f\n", tempoMedioExecutados);
        printf("-------------------------------------------------------------------------");
        printf("\n"); 
        break;
      case 5:
        imprimir(&fila); 
        break;
      default: 
        if(opcao != 0){
          printf("\nOpcao invalida!\n");
        }
            break; 
        }
    }while(opcao !=0);
    return 0;
}

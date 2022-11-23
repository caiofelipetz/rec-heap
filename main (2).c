
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>



#define Tamanho 50
#define TamanhoMax 52

int hash(char key[]){
  
  int string_size = strlen(key);
  unsigned int valor = 0;

  for (int i=0 ; i<string_size ; i++){
    valor += key[i] * (i*i);
  }

  return valor % Tamanho;

}

struct heap_max {
  struct no *vetor;
  int size;
  int last;
};

struct no {

  int indice;
  char senha[TamanhoMax];

};

int center(int indice) {
  return(indice - 1)/2; 
}

int left(int indice) {
  return indice*2+1; 
}

int right(int indice) {
  return indice*2+2;
}

bool empty(struct heap_max *heap) {

  if (heap->last == -1) {
    return true;
  }
  
  return false;
  
}

bool verificaIndice(struct heap_max *heap,int indice) {
  if ( (indice >= 0) && (indice <= heap->size) ) {
    return true;}
  return false;
  
}

bool verificaFolha(struct heap_max *heap, int indice) {

  if ( (indice > center(heap->last)) && (indice <= heap->last) ) {
    return true;}
  return false;
}

int verificaMaiorIndice(struct heap_max *heap, int center, int direita,int esquerda) {

  if (heap->vetor[center].indice > heap->vetor[esquerda].indice) {
    if (verificaIndice(heap, direita) == true) {
      if (heap->vetor[center].indice < heap->vetor[direita].indice) {
        return direita;
      }
    }

    return center;

  } 
    
  else {
    if (verificaIndice(heap, direita) == true) {
      if (heap->vetor[esquerda].indice < heap->vetor[direita].indice) {
        return direita;
      }
    }

    return esquerda;
    
  }
  
}

void heapify_max(struct heap_max *heap, int indice) {

  if (verificaFolha(heap, indice) || !verificaIndice(heap, indice)) {
    return;
  }

  int maior_indice = verificaMaiorIndice(heap, indice, left(indice), right(indice));

  if (maior_indice != indice) {
    struct no aux = heap->vetor[indice];
    heap->vetor[indice] = heap->vetor[maior_indice];
    heap->vetor[maior_indice] = aux;

    heapify_max(heap, maior_indice);

  }
  
}

bool buscar(struct heap_max *heap, char senha []) {

  int indice = hash(senha);
  
  for (int i=0 ; i <= heap->last ; i++) {
    if (heap->vetor[i].indice == indice) {
      printf("\n\tO valor digitado se encontra no índice %d!\n",i);
      return true;
    }
  }

  return false;

}

struct heap_max *inserir(struct heap_max *heap, char senha[]) {

  int indice = hash(senha);

  if(buscar(heap,senha) == false){
    if (heap->last >= (heap->size)) {
      printf("O heap esta cheio!\n");
      return heap;
    }
  
    heap->last += 1;
    struct no novo;
    novo.indice = indice;
    strcat(novo.senha,senha);
    heap->vetor[heap->last] = novo;
  
    int i = heap->last;
    while ( (heap->vetor[center(i)].indice < heap->vetor[i].indice) && (i > 0) ) {
      struct no aux = heap->vetor[i];
      heap->vetor[i] = heap->vetor[center(i)];
      heap->vetor[center(i)] = aux;
      i = center(i);
    }
    return heap;
  }
  return heap;  
  
}

bool remove_heap(struct heap_max *heap) {

  if (empty(heap) == true) {
    return false;  
  }

  else {
    heap->vetor[0] = heap->vetor[heap->last];
    heap->vetor[heap->last].indice = 0;
    memset(heap->vetor[heap->last].senha, 0, TamanhoMax);
    heap->last -= 1;

    heapify_max(heap, 0);
  }

  return true;
  
}

void print(struct heap_max *heap){

  for(int i=0 ; i<Tamanho ; i++){
    if((int)strlen(heap->vetor[i].senha)>0){
      printf("Senha %d: %s",i,heap->vetor[i].senha);
    }
      
    else{
       printf("Senha %d: %s\n",i,heap->vetor[i].senha);
    }
  }

}

void verificacao(char senha[]){
  fgets(senha,TamanhoMax,stdin);
  if(strlen(senha)<50){
  }
  setbuf(stdin,NULL);
  while( (strlen(senha)>50) || (strlen(senha)<10) ){
    printf("\nsenha deve ser maior que 10 caracteres e menor que 50\n");
    if(strlen(senha)>50){
      setbuf(stdin,NULL);
    }
    printf("\nsenha: ");
    fgets(senha,TamanhoMax,stdin);
  }
}

int main(){

  int opcao, retorno, tabela[Tamanho];
  char senha[TamanhoMax];
  struct heap_max *heap;
  heap = (struct heap_max *)malloc(sizeof(struct heap_max));
  heap->vetor = (struct no *)calloc(Tamanho, sizeof(struct no));
  heap->size = Tamanho;
  heap->last = -1;

  do{
    printf("\nSair - 0\nInserir - 1\nBuscar - 2\nExcluir - 3\nPrintar - 4\n>");
    scanf("%d", &opcao);
    getchar();


    switch(opcao){
    case 0:
      break;

    case 1:

      printf("\nsenha: ");
      verificacao(senha);
      heap = inserir(heap, senha);
      break;

    case 2:

      verificacao(senha);
      if(buscar(heap,senha) == false){
        printf("\nValor digitado nao encontrado\n");
      }
      break;

    case 3:
  
      if (remove_heap(heap)) {
        printf("\n raiz do heap excluida\n");
        }
      else{
        printf("\nheap empty\n");}
      break;

    case 4:

      print(heap);
      break;
    default:
      printf(" ");
    }

  }

  while(opcao != 0);

  return 0;


}
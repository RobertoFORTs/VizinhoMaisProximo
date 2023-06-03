#include "vizinhoProximo.h"
#include <stdio.h>
#include <stdlib.h>


int main(){

  tree *kd_arvore;
  kd_arvore = malloc(sizeof(tree));
  kd_build(kd_arvore, compare_cidade, printNode_cidade, compareListaMelhoresCidade, new_cidade);

  FILE *arq;
  char linha[300];

  
  arq = fopen("municipios.txt", "r");
  

  if (arq == NULL) {
      printf("Something went wrong with file\n");
  }
  int i;
  
  int cont  = 0;
  while (cont< 10) {
      cidade *aux = malloc(sizeof(cidade));
      
      // fscanf(arq, "%d,%[^,],%[^,],%[^,],%[^,],%f,%f,%[^,],%[^,],%[^,],%[^,\n]", &i, aux.address, aux.categories, aux.city, aux.country, &aux.latitude, &aux.longitude, aux.name, aux.postalCode, aux.province, aux.websites);
      fscanf(arq, "%d, %[^,], %f, %f, %d, %d, %d, %d, %[^,\n]", &aux->cod_ibge, aux->nome, &aux->latitude, &aux->longitude, &aux->capital, &aux->cod_uf, &aux->cod_siafi, &aux->ddd, aux->fuso_hor);
      kd_insert(kd_arvore, aux);
      cont++;
      
  }
  printf("\n");
  printKDTree(kd_arvore, kd_arvore->printNode);

  
  int k = 1;
  int *tamAtual;
  int *duplicate;
  int value1= 0;
  int value2= 0;
  tamAtual = &value1;
  duplicate = &value2;
  node **listaMelhores = malloc(sizeof(node*));
  node *candidato = malloc(sizeof(node));
  cidade* cidadeCandidate = malloc(sizeof(cidade));
  cidadeCandidate->latitude = -19.1551;
  cidadeCandidate->longitude = -45.4444;
  candidato->pdata = cidadeCandidate;
  
  searchNeighbors(kd_arvore,listaMelhores,k,tamAtual, candidato, kd_arvore->root, duplicate);
  printf("AHHHHHHHHH");
  cont = 0;
  while (cont<k){
    cidade *cidadeProxima;
    cidadeProxima = (cidade*)listaMelhores[cont]->pdata;
    printf("Cidade(s) Próxima(s): %s", cidadeProxima->nome);

    cont++;
  }
 

  fclose(arq);
  
 
//   deleteTree(kd_arvore);
  return 0;
}
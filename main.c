#include "vizinhoProximo.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
  tree *kd_arvore;
  kd_arvore = malloc(sizeof(tree));
  kd_build(kd_arvore, compare);
  kd_insert(kd_arvore, new_node(NULL, 2,3));
  kd_insert(kd_arvore, new_node(NULL, 8,2));
  kd_insert(kd_arvore, new_node(NULL, 10,11));
  kd_insert(kd_arvore, new_node(NULL, 20,15));
  kd_insert(kd_arvore, new_node(NULL, 6,7));
  kd_insert(kd_arvore, new_node(NULL, 9,12));
  kd_insert(kd_arvore, new_node(NULL, 19,4));
  kd_insert(kd_arvore, new_node(NULL, 1,6));
  kd_insert(kd_arvore, new_node(NULL, 13,14));
  printKDTree(kd_arvore);

  float location[2];
  location[0] = 10;
  location[1] = 12;
  node **listaMelhores;
  listaMelhores = malloc(sizeof(node*));
  int *tamanhoListaMelhores;
  int aux = 0;
  tamanhoListaMelhores = &aux;
  searchNextNeighbor(kd_arvore->root, location, 1, 0, listaMelhores, tamanhoListaMelhores);
  printf("\n\n\n - %f - \n\n\n ", *listaMelhores[0]);
  deleteTree(kd_arvore);
  printKDTree(kd_arvore); //apenas para verificar se a arvore foi apagada corretamente
  printf("\n FIMM!!");
  
  return 0;
}
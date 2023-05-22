#include "vizinhoProximo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int compare(const void* coordinate, const void *candidate){
  float* a = (float*)coordinate;
  float* b = (float*)candidate;
  if (*b < *a){
    return -1;
  }
  return 0;
}

void kd_build(tree *ptree, int (*compara)(const void *a, const void *b)){
  
  ptree->root = NULL;
  ptree->compara = compara;
}

node* new_node(void* data, int x, int y){
  node* output = malloc(sizeof(node));
  output->data = data;
  output->coordinate[0] = x;
  output->coordinate[1] = y;
  return output;
}

void kd_insert(tree *ptree, node *new_node){
  node **ppNode;
  node *pNode;
  node *parentTemp;
  ppNode = &(ptree->root);
  parentTemp = *ppNode;
  pNode = *ppNode;
  int depth = 0;

  while (pNode != NULL){
    
    if (depth%2==0){
      if (ptree->compara(&(pNode->coordinate[0]), &(new_node->coordinate[0])) < 0){
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->left);
        pNode = *ppNode;
      }
      else{
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->right);
        pNode = *ppNode;
      }
    }
    else{
      if (ptree->compara(&(pNode->coordinate[1]), &(new_node->coordinate[1])) < 0){
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->left);
        pNode = *ppNode;
      }
      else{
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->right);
        pNode = *ppNode;
      }
    }

    depth++;
  }
  if ((*ppNode == NULL)){
    (*ppNode) = new_node;
    (*ppNode)->parent = (node*)parentTemp;
    (*ppNode)->left = NULL;
    (*ppNode)->right = NULL;
  }
}

void printKDTree(tree * treeObj){
  node* root = treeObj->root;
  if (root == NULL){
    return;
  }
  else printNode(root); 
}

void printNode(node * nodeObj){

  if(nodeObj->left) {
    printNode((node*)nodeObj->left);
  }

  printf("[%.2f, %.2f] \n", nodeObj->coordinate[0], nodeObj->coordinate[1]);
  
  if(nodeObj->right) {
    printNode((node*)nodeObj->right);
  }

}

void deleteNodes(node *actual){

  if (actual == NULL){
    return;
  }

  deleteNodes((node*)actual->left);
  deleteNodes((node*)actual->right);

  free(actual);
}

void deleteTree(tree *kd_tree){

  deleteNodes((node*)kd_tree->root);
  kd_tree->compara = NULL;
  kd_tree->root=NULL;
  
}

float distance(const void* coordinate, const void* neighbor){
   float *a, *b;
   a = (float*)coordinate;
   b = (float*)neighbor;

  return sqrt( pow(b[0]-a[0], 2) + pow(b[1]-a[1], 2) );
}

float* globalLocation;

int compareListaMelhores(const void* A, const void *B){
  node* a = (node*)A;
  node* b = (node*)B;
  if (distance(b->coordinate, globalLocation) < distance(a->coordinate, globalLocation)){
    return -1;
  }
  return 0;
}



void insereListaMelhores(node** listaMelhores, int K, int* tamAtual, node* candidato, float* location){
  listaMelhores[(*tamAtual)++] = candidato;
  globalLocation = location;
  qsort(listaMelhores, *tamAtual, sizeof(float) * 2, compareListaMelhores);
  if(*tamAtual == K + 1) {
    (*tamAtual)--;
  }
}

void searchNextNeighbor(node* current_node, float* location, int numberOfNeighbors, int depth, node** listaMelhores, int* tamAtualLista){
  
  int currentAxis = depth % 2 == 0 ? 0 : 1;
  int foiDireita;
  
  // if(current_node->left == NULL && current_node->right == NULL){
  //   insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
  //   return;
  // }
  // else if (location[currentAxis] < current_node->coordinate[currentAxis] && current_node->left == NULL){
  //   insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
  //   return;
  // }
  // else if (location[currentAxis] >= current_node->coordinate[currentAxis] && current_node->right == NULL){
  //   insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
  //   return;
  // }

  if (current_node ==  NULL){ //para de percorrer árvore e subárvores
    printf("Encontrei um no folha \n");
    return;
  }

  if (depth%2==0){ //percorre árvore
    if ( (float)location[0] < current_node->coordinate[0] ){ 
      printf("fui pra esquerda 0\n");
      foiDireita = 0;
      searchNextNeighbor(current_node->left, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
    }
    else{
      foiDireita = 1;
      printf("fui pra direita 0\n");
      searchNextNeighbor(current_node->right, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
    }
  }
  else{
    if ( (float)location[1] < current_node->coordinate[1] ){
      foiDireita = 0;
      printf("fui pra esquerda 1\n");
      searchNextNeighbor(current_node->left, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
    }
    else{
      foiDireita = 1;
      printf("fui pra direita 1\n");
      searchNextNeighbor(current_node->right, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
    }
  }

  node* aux = listaMelhores[*tamAtualLista-1];
  
  if (*tamAtualLista == numberOfNeighbors){
    if( fabs(current_node->coordinate[currentAxis] - location[currentAxis]) < distance(location, aux->coordinate) ){ //verifica raio do circulo
      printf("Estou satisfeito com a função!!\n");
      return;
    }
    else{
        if (distance(location, aux->coordinate) > distance(location, current_node->coordinate)){
          printf("Troquei na lista cheia\n");
          insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location); //troca novo pior entre melhores
        }
        if(foiDireita){ //vai percorrer outra subárvore até satisfazer o primeiro if dps da verificação do tamanho da lista
          printf("Após ter retornado ao pai, percorrerei a próxima subárvore à esquerda\n");
          searchNextNeighbor(current_node->left, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
        }
        else{
          printf("Após ter retornado ao pai, percorrerei a próxima subárvore à direita\n");
          searchNextNeighbor(current_node->right, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
        }
      printf("Já percorri a subárvore agr retornarei ao pai\n");
      return; //terminou de percorrer a subárvore ele deve retornar para o próximo pai caso ainda n tenha satisfeito a situação do primeiro if
    
      }
  }
  
  else{ //enquanto não preencher a lista com o número de vizinhos mais próximos, vai adicionando seus antecessores e retorna para o nó anterior
    printf("Eu sou o batman");
    insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
    printf("Após eu encontrar o nó na primeira descida na árvore, adicionei na lista e retornei ao próximo pai\n");
    return;
  }

}


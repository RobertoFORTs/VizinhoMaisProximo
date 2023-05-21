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
  listaMelhores[*tamAtual++] = candidato;
  globalLocation = location;
  qsort(listaMelhores, *tamAtual, sizeof(float) * 2, compareListaMelhores);
  if(*tamAtual == K + 1) {
    *tamAtual--;
  }
}

void searchNextNeighbor(node* current_node, float* location, int numberOfNeighbors, int depth, node** listaMelhores, int* tamAtualLista){
  
  int currentAxis = depth % 2 == 0 ? 0 : 1;
  int foiDireita;

  if(current_node->left == NULL && current_node->right == NULL){
    insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
    return;
  }
  else if (location[currentAxis] < current_node->coordinate[currentAxis] && current_node->left == NULL){
    insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
    return;
  }
  else if (location[currentAxis] >= current_node->coordinate[currentAxis] && current_node->right == NULL){
    insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
    return;
  }

   if (depth%2==0){
      if ( (float)location[0] < current_node->coordinate[0] ){ 
        foiDireita = 0;
        searchNextNeighbor(current_node->left, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
      }
      else{
        foiDireita = 1;
        searchNextNeighbor(current_node->right, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
      }
    }
    else{
      if ( (float)location[1] < current_node->coordinate[1] ){
        foiDireita = 0;
        searchNextNeighbor(current_node->left, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
      }
      else{
        foiDireita = 1;
        searchNextNeighbor(current_node->right, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
      }
    }

    

    node* aux = listaMelhores[*tamAtualLista-1];
    if( fabs(current_node->coordinate[currentAxis] - location[currentAxis]) < distance(location, aux->coordinate) ){
      return;
    }
    else{
      if (tamAtualLista == numberOfNeighbors){
        if (distance(location, aux->coordinate) > distance(location, current_node->coordinate)){
          insereListaMelhores(listaMelhores, numberOfNeighbors, tamAtualLista, current_node, location);
          return;
        }
      }
    }

    if(foiDireita){
      searchNextNeighbor(current_node->left, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
    }
    else{
      searchNextNeighbor(current_node->right, location, numberOfNeighbors, depth + 1, listaMelhores, tamAtualLista);
    }
}


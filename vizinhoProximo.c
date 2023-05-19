#include "vizinhoProximo.h"
#include <stdlib.h>
#include <stdio.h>

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
  ppNode = &(ptree->root);
  pNode = *ppNode;
  int depth = 0;

  while (pNode != NULL){
    
    if (depth%2==0){
      if (ptree->compara(&(pNode->coordinate[0]), &(new_node->coordinate[0])) < 0){
        ppNode = (node**)&(pNode->left);
        pNode = *ppNode;
      }
      else{
        ppNode = (node**)&(pNode->right);
        pNode = *ppNode;
      }
    }
    else{
      if (ptree->compara(&(pNode->coordinate[1]), &(new_node->coordinate[1])) < 0){
        ppNode = (node**)&(pNode->left);
        pNode = *ppNode;
      }
      else{
        ppNode = (node**)&(pNode->right);
        pNode = *ppNode;
      }
    }

    depth++;
  }
  if ((*ppNode == NULL)){
    (*ppNode) = new_node;
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

void deleteTree(tree *raiz){

  if (raiz->root == NULL){
    printf( " Arvore vazia!!😂😂😂😂😂😂\n");
    return;
  }
  int cont = 1;
  if (cont != 1){
    raiz->root = (node *)(raiz->root->left);
    raiz = (tree *)(raiz->root);
  }
  else{
    raiz = (tree *)(raiz->root);
  }
  deleteTree(raiz);  

  raiz->root = (node *)(raiz->root->right);
  raiz = (tree *)(raiz->root);

  deleteTree(raiz);

  free(raiz->root);  
}

node* searchNextNeighbor(node* root, const void* location, int numberOfNeighbors){
  
}
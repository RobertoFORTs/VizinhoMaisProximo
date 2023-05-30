#include "vizinhoProximo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int compare_restaurant(const void* coordinate, const void *candidate, int depth){
  restaurant* a = (restaurant*)coordinate;
  restaurant* b = (restaurant*)candidate;

  if (depth%2 ==0){
    if ((b)->x < (a)->x){
    return -1;
  }
  return 0;
  }
  else{
    if ((b)->y < (a)->x){
      return -1;
    }
    return 0;
  }
}
int compare_cidade(const void* coordinate, const void *candidate, int depth){
  cidade* a = (cidade*)coordinate;
  cidade* b = (cidade*)candidate;

  if (depth%2 ==0){
    if (b->x < a->x){
    return -1;
  }
  return 0;
  }
  else{
    if (b->y < a->x){
      return -1;
    }
    return 0;
  }
}
void kd_build(tree *ptree, int (*compara)(const void *a, const void *b, int depth), void (*printNode)(void *node)){
  
  ptree->root = NULL;
  ptree->compara = compara;
  ptree->printNode = printNode;
}

restaurant *new_restaurant(int x, int y){
  restaurant *output = malloc(sizeof(restaurant));
  output->x = x;
  output->y = y;
  return output;
}

cidade *new_cidade(int x, int y){
  cidade *output = malloc(sizeof(cidade));
  output->x = x;
  output->y = y;
  return output;
}

node* new_node(void* data){ 
  node* output = malloc(sizeof(node));
  output->pdata = data; 
  return output;
}

void kd_insert(tree *ptree, void *new_node_data){
  node **ppNode;
  node *pNode;
  node *parentTemp;
  ppNode = &(ptree->root);
  parentTemp = *ppNode;
  pNode = *ppNode;
  int depth = 0;
  int aux;

  while (pNode != NULL){
    
    if (ptree->compara(pNode->pdata, new_node_data, depth) == -1){
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->left);
        pNode = *ppNode;
      }
    else{
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->right);
        pNode = *ppNode;
      }

    depth++;
  }
  if ((*ppNode == NULL)){
    (*ppNode) = new_node(new_node_data);
    (*ppNode)->parent = (node*)parentTemp;
    (*ppNode)->left = NULL;
    (*ppNode)->right = NULL;
  }
}

node* sucessores(node *pnodeAtual){
  
  if (pnodeAtual->left == NULL && pnodeAtual->right == NULL){
    return pnodeAtual->parent;
  }

  if (pnodeAtual->left ==  NULL){
    pnodeAtual = (node*)pnodeAtual->right;
    while (pnodeAtual->left!=NULL){
      pnodeAtual = (node*)pnodeAtual->left;
    }
    return pnodeAtual; //será o sucessor no caso de ser um node no início ou meio da árvore
  }
  else{
    pnodeAtual = (node*)pnodeAtual->left;
    while (pnodeAtual->right!=NULL){
      pnodeAtual = (node*)pnodeAtual->right;
    }
    return pnodeAtual; //será o sucessor no caso de ser um node no início ou meio da árvore

  }
}

node *predecessor(node *pnodeAtual, int depth){


    if(pnodeAtual->left != NULL){
      pnodeAtual = pnodeAtual->left;
      while (pnodeAtual->right != NULL){
        pnodeAtual = pnodeAtual->right;
      }

      return pnodeAtual;
    }

      node* parent = pnodeAtual->parent;

      while (parent != NULL && no == parent->left){
        no = parent;
        parent = parent->parent;
      }

    return parent;
  

    
}

void printKDTree(const void *treeObj, void (*printNode)(void *nodeObj)){
  tree *arv = (tree*)treeObj;
  node* root = arv->root;
  if (root == NULL){
    return;
  }
  else printNode(root); 
}

void printNode_restaurant(void *nodeObj){
  node *nodeAux = (node*)nodeObj;
  restaurant *aux = (restaurant*)nodeAux->pdata;
  if(nodeAux->left) {
    printNode_restaurant((node*)nodeAux->left);
  }

  printf("[%d, %d] \n", aux->x, aux->y);
  
  if(nodeAux->right) {
    printNode_restaurant((node*)nodeAux->right);
  }

}

void printNode_cidade(void *nodeObj){
  node *nodeAux = (node*)nodeObj;
  cidade *aux = (cidade*)&(nodeAux->pdata);
  if(nodeAux->left) {
    printNode_cidade((node*)nodeAux->left);
  }

  printf("[%d, %d] \n", aux->x, aux->y);
  
  if(nodeAux->right) {
    printNode_cidade((node*)nodeAux->right);
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

// int compareListaMelhores(const void* A, const void *B){
//   node* a = (node*)A;
//   node* b = (node*)B;
//   if (distance(b->coordinate, globalLocation) < distance(a->coordinate, globalLocation)){
//     return -1;
//   }

//   if (distance(b->coordinate, globalLocation) > distance(a->coordinate, globalLocation)){
//     return 1;
//   }

//   return 0;
// }



// void insereListaMelhores(node** listaMelhores, int K, int* tamAtual, node* candidato, float* location){
//   listaMelhores[(*tamAtual)++] = candidato;
//   globalLocation = location;
//   qsort(listaMelhores, *tamAtual, sizeof(node*) * 2, compareListaMelhores);
//   if(*tamAtual == K + 1) {
//     (*tamAtual)--;
//   }
// }

// void searchNextNeighbor(){


// }


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
  node* nodeAdd = (node*)new_node_data;

  while (pNode != NULL){
    
    if (ptree->compara(pNode->pdata, nodeAdd->pdata, depth) == -1){
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
    (*ppNode) = new_node(nodeAdd->pdata);
    (*ppNode)->parent = (node*)parentTemp;
    (*ppNode)->left = NULL;
    (*ppNode)->right = NULL;
  }
}

node* sucessores(node *pnodeAtual, int* duplicate){
  
  if ((pnodeAtual->left == NULL && pnodeAtual->right == NULL) || *duplicate == 2){
    *duplicate = 1;
    return pnodeAtual->parent;
  }

  if (pnodeAtual->left ==  NULL){
    if (*duplicate == 1){
      *duplicate = 2;
      pnodeAtual = (node*)pnodeAtual->left;
      while (pnodeAtual->right!=NULL){
        pnodeAtual = (node*)pnodeAtual->right;
      } 
      return pnodeAtual;
    }
    pnodeAtual = (node*)pnodeAtual->right;
    while (pnodeAtual->left!=NULL){
      pnodeAtual = (node*)pnodeAtual->left;
    }
    return pnodeAtual; //será o sucessor no caso de ser um node no início ou meio da árvore
  }
  else{
    if (*duplicate == 1){
      *duplicate = 2;
      pnodeAtual = (node*)pnodeAtual->right;
      while (pnodeAtual->left!=NULL){
        pnodeAtual = (node*)pnodeAtual->left;
      }
      return pnodeAtual; 
    }
    pnodeAtual = (node*)pnodeAtual->left;
    while (pnodeAtual->right!=NULL){
      pnodeAtual = (node*)pnodeAtual->right;
    }
    return pnodeAtual; //será o sucessor no caso de ser um node no início ou meio da árvore

  }
}

node *predecessor(node *pnodeAtual){


    if(pnodeAtual->left != NULL){
      pnodeAtual = pnodeAtual->left;
      while (pnodeAtual->right != NULL){
        pnodeAtual = pnodeAtual->right;
      }

      return pnodeAtual;
    }

      node* parent = pnodeAtual->parent;

      while (parent != NULL && pnodeAtual == parent->left){
        pnodeAtual = parent;
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

//  int compareListaMelhores(const void* A, const void *B){
//    node* a = (node*)A;
//    node* b = (node*)B;
//    if (distance(b->coordinate, globalLocation) < distance(a->coordinate, globalLocation)){
//      return -1;
//    }

//    if (distance(b->coordinate, globalLocation) > distance(a->coordinate, globalLocation)){
//      return 1;
//    }

//    return 0;
//  }


// void insereListaMelhores(node** listaMelhores, int K, int* tamAtual, node* candidato, float* location){
//   listaMelhores[(*tamAtual)++] = candidato;
//   globalLocation = location;
//   qsort(listaMelhores, *tamAtual, sizeof(node*) * 2, compareListaMelhores);
//   if(*tamAtual == K + 1) {
//     (*tamAtual)--;
//   }
// }

//Para funcionar, devemos INSERIR por ÚLTIMO o nó q desejamos procurar
int searchNeighbohrs(tree *ptree, node **listaMelhores, int k, int* tamAtual, node* candidato, node *pnodeAtual, int *duplicate){
  int depth = 0;
  if (*tamAtual == k){ //condição de parada
    return;
  }

  if (*tamAtual > 1){
    //procurar por sucessores do "paiAtual" e adicionar na listaMelhores
    pnodeAtual = sucessores(pnodeAtual, duplicate);
    insereListaMelhores(pnodeAtual);
    return searchNextNeighbor(ptree, listaMelhores, k, tamAtual, candidato, pnodeAtual, duplicate);
  }

  if (candidato == pnodeAtual){
    insereListaMelhores(predecessor(pnodeAtual, duplicate));   
    insereListaMelhores(sucessores(pnodeAtual), duplicate);
    duplicate = 1;
    return searchNeighbohrs(ptree, listaMelhores, k, tamAtual, candidato, pnodeAtual->parent, duplicate); //recursivamente searchNextNeighbors com o nó pai e o duplicate atualizado  
  }

  while (candidato!=pnodeAtual){
    //percorrer árvore até achar o nó que se procura
    if (ptree->compara(pnodeAtual->pdata, candidato->pdata, depth) == -1){
        pnodeAtual = pnodeAtual->left;
      }
    else{
        pnodeAtual = pnodeAtual->right;
      }
    depth++;
  }
  if (candidato!=pnodeAtual){
    return 0; //candidato então não existe na lista, logo não será possível continuar a busca
  }
  return searchNeighbohrs(ptree, listaMelhores, k, tamAtual, candidato, pnodeAtual, duplicate);
}



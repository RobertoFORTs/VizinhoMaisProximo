#include "vizinhoProximo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

node *globalLocation;

int compare_restaurant(const void* coordinate, const void *candidate, int depth){
  restaurant* a = (restaurant*)coordinate;
  restaurant* b = (restaurant*)candidate;

  if (b->latitude == a->latitude && b->longitude == a->longitude){
    return 0;
  }

  if (depth%2 ==0){
    if ((b)->latitude < (a)->latitude){
    return -1;
  }
  return 1;
  }
  else{
    if ((b)->longitude < (a)->longitude){
      return -1;
    }
    return 1;
  }
}
int compare_cidade(const void* coordinate, const void *candidate, int depth){
  cidade* a = (cidade*)coordinate;
  cidade* b = (cidade*)candidate;

   if (b->latitude == a->latitude && b->longitude == a->longitude){
    return 0;
  }

  if (depth%2 ==0){
    if ((b)->latitude < (a)->latitude){
    return -1;
  }
  return 1;
  }
  else{
    if ((b)->longitude < (a)->longitude){
      return -1;
    }
    return 1;
  }
}

void kd_build(tree *ptree, int (*compara)(const void *a, const void *b, int depth), void (*printNode)(void *node), int (*compareListaMelhores)(const void* A, const void *B), node* (*new_node)(const void *data)){
  
  ptree->root = NULL;
  ptree->compara = compara;
  ptree->printNode = printNode;
  ptree->compareListaMelhores = compareListaMelhores;
  ptree->new_node = new_node;
}

node* new_restaurant(const void *data){
  node *output = malloc(sizeof(node));
  output->pdata = data;
  return output;
}

node* new_cidade(const void *data){
  node *output = malloc(sizeof(node));
  output->pdata = (cidade*)data;
  return output;
}

node* new_node(const void* data);

void kd_insert(tree *ptree, void *new_node_data){
  node **ppNode;
  node *pNode;
  node *parentTemp;
  ppNode = &(ptree->root);
  parentTemp = *ppNode;
  pNode = *ppNode;
  int depth = 0;

  while (pNode != NULL){
    
    if (ptree->compara(pNode->pdata, new_node_data, depth) == -1){
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->left);
        pNode = *ppNode;
      }
    else if (ptree->compara(pNode->pdata, new_node_data, depth) == 1){
        parentTemp = *ppNode;
        ppNode = (node**)&(pNode->right);
        pNode = *ppNode;
      }
    else{
      return; //só vai retornar e não irá inserir na árvore caso exista um nó igual a esse presente
    }

    depth++;
  }
  if ((*ppNode == NULL)){
    (*ppNode) = (node*)ptree->new_node(new_node_data);
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

  printf("[%f, %f] \n", aux->latitude, aux->longitude);
  
  if(nodeAux->right) {
    printNode_restaurant((node*)nodeAux->right);
  }

}

void printNode_cidade(void *nodeObj){
  node *nodeAux = (node*)nodeObj;
  cidade *aux = (cidade*)(nodeAux->pdata);
  if(nodeAux->left) {
    printNode_cidade((node*)nodeAux->left);
  }

  printf("[%f, %f] \n", aux->latitude, aux->longitude);
  
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

float distanceCidade(const void* coordinate, const void* neighbor){
  cidade *a, *b;
  a = (cidade*) coordinate;
  b = (cidade*) neighbor;
  return sqrt( pow(b->latitude - a->latitude, 2) + pow(b->longitude - a->longitude, 2) );
}

 float distanceRestaurante(const void* coordinate, const void* neighbor){
   restaurant *a, *b;
   a = (restaurant*) coordinate;
   b = (restaurant*) neighbor;
   return sqrt( pow(b->latitude - a->latitude, 2) + pow(b->longitude - a->longitude, 2) );}

int compareListaMelhores(const void* A, const void *B);
  
int compareListaMelhoresRestaurante(const void* A, const void *B){
  node* a = (node*)A;
  node* b = (node*)B;
  if (distanceRestaurante(b->pdata, globalLocation->pdata) < distanceRestaurante(a->pdata, globalLocation->pdata)){
    return -1;
  }

  if (distanceRestaurante(b->pdata, globalLocation->pdata) > distanceRestaurante(a->pdata, globalLocation->pdata)){
    return 1;
  }

  return 0;
}

int compareListaMelhoresCidade(const void* A, const void *B){
  node* a = (node*)A;
  node* b = (node*)B;
  if (distanceCidade(b->pdata, globalLocation->pdata) < distanceCidade(a->pdata, globalLocation->pdata)){
    return -1;
  }

  if (distanceCidade(b->pdata, globalLocation->pdata) > distanceCidade(a->pdata, globalLocation->pdata)){
    return 1;
  }

  return 0;
}

 void insereListaMelhores(tree *ptree, node** listaMelhores, int K, int* tamAtual, node* candidato, node* location){
   listaMelhores[(*tamAtual)++] = candidato;
   globalLocation = location;
   qsort(listaMelhores, *tamAtual, sizeof(node*) * 2, ptree->compareListaMelhores);
   if(*tamAtual == K + 1) {
     (*tamAtual)--;
   }
 }

//Para funcionar, devemos INSERIR por ÚLTIMO o nó q desejamos procurar
void searchNeighbors(tree *ptree, node **listaMelhores, int k, int* tamAtual, node* location, node *pnodeAtual, int *duplicate){
  int depth = 0;
  if (*tamAtual == k){ //condição de parada
    return;
  }

  if (*tamAtual > 1){
    //procurar por sucessores do "paiAtual" e adicionar na listaMelhores
    pnodeAtual = sucessores(pnodeAtual, duplicate);
    insereListaMelhores(ptree, listaMelhores, k, tamAtual, pnodeAtual, location);
    return searchNeighbors(ptree, listaMelhores, k, tamAtual, location, pnodeAtual, duplicate);
  }

  if (ptree->compara(pnodeAtual->pdata, location->pdata, depth) == 0){
    insereListaMelhores(ptree, listaMelhores, k, tamAtual, predecessor(pnodeAtual), location);   
    insereListaMelhores(ptree, listaMelhores, k, tamAtual, sucessores(pnodeAtual, duplicate), location);
    duplicate = 1;
    return searchNeighbors(ptree, listaMelhores, k, tamAtual, location, pnodeAtual->parent, duplicate); //recursivamente searchNeighborss com o nó pai e o duplicate atualizado  
  }

  while (pnodeAtual != NULL){
    //percorrer árvore até achar o nó que se procura
    if (ptree->compara(pnodeAtual->pdata, location->pdata, depth) == -1){
        pnodeAtual = pnodeAtual->left;
      }
    else if (ptree->compara(pnodeAtual->pdata, location->pdata, depth) == 1){
        pnodeAtual = pnodeAtual->right;
      }
    else{
      //achou igual
      return searchNeighbors(ptree, listaMelhores, k, tamAtual, location, pnodeAtual, duplicate);
    }
    depth++;
  }
}

// void menu(){
//   int op = -1;
//   while (op != 5){
    
//     printf("------------- Search Next Neighbor -------------\n");
//     printf("1 - build Tree(s)\n");
//     printf("2 - Insert data on tree(s)\n");
//     printf("3 - Search Neighbor(s)\n");
//     printf("4 - Delete tree\n");
//     printf("5 - Stop program\n");

//     int y = scanf("%d", &op);

//     if (op == 1){
//       kd_build();
//       printf("succesfully built the tree!\n");
//     }

//     if (op ==2){
//       printf("Please inform the data:\n");

//     }

//     if(op == 3){
//       printf("Inform the locality(Name) That you want to search for its next neighbors:\n");
      
//       char[50] name;
//       scanf(" %s", name);
//       //searchNode by name

//     }
//     if(op == 4){
//       deleteTree();
//       printf("Tree deleted\n");
//     }
//     if(op == 5){
//       printf("Stopped!\n");
//       break;
//     }
//     }
// }


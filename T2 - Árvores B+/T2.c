#include <stdio.h>
#include <stdlib.h>
#define MAX_CHILDREN 3

typedef struct node {
    int key1;
    int key2;
    int overflow;
    int isLeaf;
    struct node* pointers[MAX_CHILDREN];
    struct node* parent;
    struct node* pOverflow;
} Node;

Node* createNode(int isLeaf);
Node* insertLeaf(Node* leaf, int n);
Node* splitLeaf(Node* childNode, Node* parentNode);
Node* insert(Node* bPlusTree, int n);
Node* removeNode(Node* bPlusTree, int n);
Node* fixNodes(Node* tree);
Node* getFromLeft(Node* tree, int pIndex);
Node* getFromRight(Node* tree, int pIndex);
Node* concRight(Node* tree);
Node* search(Node* bPlusTree, int n);
void checkParent(Node* parentNode);
void printNode(Node* node);
void printTree(Node* bPlusTree);

int main(void) {
    int nums1[] = { 15, 20, 5, 30, 25, 10, 35, 1, 40, 50 }; 
    Node* bPlusTree = createNode(1);
    
    printf("Case 1:\n");

    for (int i = 0; i < 10; i++) {
        printf("\nInserting %d into the tree...\n", nums1[i]);
        bPlusTree = insert(bPlusTree, nums1[i]);
        printf("\nTree currently:\n");
        printTree(bPlusTree);
        printf("-------------------------------------------------------------------------------\n");
    }

    printf("\nFinal Tree after insertions:\n");
    printTree(bPlusTree);

    printf("\nCase 2:\n");

    int buscaNum = 7;  
    Node* busca = search(bPlusTree, buscaNum);
    if (busca == NULL) {
        printf("\n\nKey %d not found :(\n", buscaNum);
    }
    else {
        printf("\n\nNode of the desired key %d:\n", buscaNum);
        printNode(busca);
    }

    buscaNum = 100; 
    busca = search(bPlusTree, buscaNum);
    if (busca == NULL) {
        printf("\n\nKey %d not found :(\n", buscaNum);
    }
    else {
        printf("\n\nNode of the desired key %d:\n", buscaNum);
        printNode(busca);
    }

    buscaNum = 25; 
    busca = search(bPlusTree, buscaNum);
    if (busca == NULL) {
        printf("\n\nKey %d not found :(\n", buscaNum);
    }
    else {
        printf("\n\nNode of the desired key %d:\n", buscaNum);
        printNode(busca);
    }

    printf("\nCase 3:\n");

    printf("\nTree before deletion:\n");
    printTree(bPlusTree);

    printf("\nTree after deletion of key %d:\n", 20);
    removeNode(bPlusTree, 20);
    printTree(bPlusTree);

    printf("\nTree after deletion of key %d:\n", 30);
    removeNode(bPlusTree, 30);
    printTree(bPlusTree);

    printf("\nTree after deletion of key %d:\n", 10);
    removeNode(bPlusTree, 10);
    printTree(bPlusTree);

    printf("\nTree after deletion of key %d:\n", 1);
    removeNode(bPlusTree, 1);
    printTree(bPlusTree);

    printf("\nCase 4:\n");

    printf("\nAttempting to delete key %d that is not in the tree:\n", 100);
    removeNode(bPlusTree, 100);

    printf("\nAttempting to delete key %d that is not in the tree:\n", -5);
    removeNode(bPlusTree, -5);

    printf("\nFinal Tree after deletions:\n");
    printTree(bPlusTree);

    int nums5[] = { 15, 20, 5, 30, 25, 10, 35, 1, 40, 50, 60, 55 }; 
    bPlusTree = createNode(1); 

    printf("\nCase 5:\n");

    for (int i = 0; i < 12; i++) {
        printf("Inserting %d into the tree...\n", nums5[i]);
        bPlusTree = insert(bPlusTree, nums5[i]);
        printf("\nTree currently:\n");
        printTree(bPlusTree);
        printf("-------------------------------------------------------------------------------\n");
    }

    printf("\nFinal Tree after insertions:\n");
    printTree(bPlusTree);

    int nums6[] = { 15, 20, 5, 30, 25, 10, 35, 1, 40, 50, 60, 55 }; 
    bPlusTree = createNode(1); 

    printf("\nCase 6:\n");

    for (int i = 0; i < 12; i++) {
        printf("Inserting %d into the tree...\n", nums6[i]);
        bPlusTree = insert(bPlusTree, nums6[i]);
        printf("\nTree currently:\n");
        printTree(bPlusTree);
        printf("-------------------------------------------------------------------------------\n");
    }

    printf("\nFinal Tree after insertions:\n");
    printTree(bPlusTree);

    int buscaNum6 = 25;
    Node* busca6 = search(bPlusTree, buscaNum6);
    if (busca6 == NULL) {
        printf("\n\nKey %d not found :(\n", buscaNum6);
    }
    else {
        printf("\n\nNode of the desired key %d:\n", buscaNum6);
        printNode(busca6);
    }

    buscaNum6 = 100; 
    busca6 = search(bPlusTree, buscaNum6);
    if (busca6 == NULL) {
        printf("\n\nKey %d not found :(\n", buscaNum6);
    }
    else {
        printf("\n\nNode of the desired key %d:\n", buscaNum6);
        printNode(busca6);
    }

    printf("\nTree before deletion:\n");
    printTree(bPlusTree);

    printf("\nTree after deletion of key %d:\n", 20);
    removeNode(bPlusTree, 20);
    printTree(bPlusTree);

    printf("\nTree after deletion of key %d:\n", 5);
    removeNode(bPlusTree, 5);
    printTree(bPlusTree);

    printf("\nTree after deletion of key %d:\n", 40);
    removeNode(bPlusTree, 40);
    printTree(bPlusTree);

    printf("\nAttempting to delete key %d that is not in the tree:\n", 100);
    removeNode(bPlusTree, 100);

    printf("\nAttempting to delete key %d that is not in the tree:\n", -5);
    removeNode(bPlusTree, -5);

    printf("\nFinal Tree after deletions:\n");
    printTree(bPlusTree);

    return 0;
}

Node* createNode(int isLeaf) {
    Node* root = (Node*)malloc(sizeof(Node));

    if (root == NULL) {
        printf("error: memorry allocation");
        exit(1);
    }
    
    root->key1 = -1;
    root->key2 = -1;
    root->overflow = -1;
    for(int i = 0; i < MAX_CHILDREN; i++) root->pointers[i] = NULL;
    root->parent = NULL;
    root->pOverflow = NULL;
    root->isLeaf = isLeaf;
    return root;
}

Node* insertLeaf(Node* leaf, int n) {
    if (leaf->key1 == -1) leaf->key1 = n;
    else if (leaf->key2 == -1) {
        if (n > leaf->key1) {
            leaf->key2 = n;
        }
        else {
            int aux = leaf->key1;
            leaf->key1 = n;
            leaf->key2 = aux;
        }
    }
    else {
        if (n > leaf->key2) leaf->overflow = n;
        else if (n > leaf->key1) {
            int aux = leaf->key2;
            leaf->key2 = n;
            leaf->overflow = aux;
        }
        else {
            int aux = leaf->key1;
            int auxaux = leaf->key2;
            leaf->key1 = n;
            leaf->key2 = aux;
            leaf->overflow = auxaux;
        }
    }
    return leaf;
}

Node* splitLeaf(Node* childNode, Node* parentNode) {
    int isLeaf = childNode->isLeaf;

    if (parentNode == NULL) parentNode = createNode(0);

    if (parentNode->key1 == -1) {
        parentNode->key1 = childNode->key2;

        Node* newNode = createNode(isLeaf);
        if (isLeaf) {
            newNode->key1 = childNode->key2;
            newNode->key2 = childNode->overflow;
        }
        else newNode->key1 = childNode->overflow;

        newNode->pointers[0] = childNode->pointers[2];
        newNode->pointers[1] = childNode->pOverflow;
        newNode->parent = parentNode;

        parentNode->pointers[1] = newNode;

        childNode->key2 = -1;
        childNode->overflow = -1;
        childNode->pointers[2] = NULL;
        childNode->pOverflow = NULL;
        childNode->parent = parentNode;

        parentNode->pointers[0] = childNode;
    }
    else if (parentNode->key2 == -1) {
        if (childNode->key2 > parentNode->key1) {
            parentNode->key2 = childNode->key2;

            Node* newNode = createNode(isLeaf);

            if (isLeaf) {
                newNode->key1 = childNode->key2;
                newNode->key2 = childNode->overflow;
                newNode->parent = parentNode;
                parentNode->pointers[2] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                childNode->parent = parentNode;
                parentNode->pointers[1] = childNode;
            }
            else {
                newNode->key1 = childNode->overflow;
                newNode->pointers[0] = childNode->pointers[2];
                newNode->pointers[1] = childNode->pOverflow;
                newNode->parent = parentNode;
                parentNode->pointers[2] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                childNode->pointers[2] = NULL;
                childNode->pOverflow = NULL;
                childNode->parent = parentNode;
                parentNode->pointers[1] = childNode;
            }
        }
        else {
            parentNode->key2 = parentNode->key1;
            parentNode->key1 = childNode->key2;

            parentNode->pointers[2] = parentNode->pointers[1];
            Node* newNode = createNode(isLeaf);

            if (isLeaf) {
                newNode->key1 = childNode->key2;
                newNode->key2 = childNode->overflow;
                newNode->parent = parentNode;
                parentNode->pointers[1] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                childNode->parent = parentNode;
                parentNode->pointers[0] = childNode;
            }
            else {
                newNode->key1 = childNode->overflow;
                newNode->pointers[0] = childNode->pointers[2];
                newNode->pointers[1] = childNode->pOverflow;
                newNode->parent = parentNode;
                parentNode->pointers[1] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                childNode->pointers[2] = NULL;
                childNode->pOverflow = NULL;
                childNode->parent = parentNode;
                parentNode->pointers[0] = childNode;
            }
        }
    }
    else if (parentNode->overflow == -1) {
        if (childNode->key2 < parentNode->key1) {
            parentNode->overflow = parentNode->key2;
            parentNode->key2 = parentNode->key1;
            parentNode->key1 = childNode->key2;

            parentNode->pOverflow = parentNode->pointers[2];
            parentNode->pointers[2] = parentNode->pointers[1];

            Node* newNode = createNode(isLeaf);

            if (isLeaf) {
                newNode->key1 = childNode->key2;
                newNode->key2 = childNode->overflow;
                parentNode->pointers[1] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                parentNode->pointers[0] = childNode;

                newNode->parent = parentNode->pointers[1];
                childNode->parent = parentNode->pointers[1];
            }
            else {
                newNode->key1 = childNode->overflow;
                newNode->pointers[0] = childNode->pointers[2];
                newNode->pointers[1] = childNode->pOverflow;
                parentNode->pointers[1] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                childNode->pointers[2] = NULL;
                childNode->pOverflow = NULL;
                parentNode->pointers[0] = childNode;

                newNode->parent = parentNode->pointers[1];
                childNode->parent = parentNode->pointers[1];
            }
        }
        else if (childNode->key2 < parentNode->key2) {
            parentNode->overflow = parentNode->key2;
            parentNode->key2 = childNode->key2;

            parentNode->pOverflow = parentNode->pointers[2];
            Node* newNode = createNode(isLeaf);

            if (isLeaf) {
                newNode->key1 = childNode->key2;
                newNode->key2 = childNode->overflow;
                parentNode->pointers[2] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                parentNode->pointers[1] = childNode;

                newNode->parent = parentNode->pointers[1];
                childNode->parent = parentNode->pointers[1];
            }
            else {
                newNode->key1 = childNode->overflow;
                newNode->pointers[0] = childNode->pointers[2];
                newNode->pointers[1] = childNode->pOverflow;
                parentNode->pointers[2] = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                childNode->pointers[2] = NULL;
                childNode->pOverflow = NULL;
                parentNode->pointers[1] = childNode;

                newNode->parent = parentNode->pointers[1];
                childNode->parent = parentNode->pointers[1];
            }
        }
        else {
            parentNode->overflow = childNode->key2;

            Node* newNode = createNode(isLeaf);

            if (isLeaf) {
                newNode->key1 = childNode->key2;
                newNode->key2 = childNode->overflow;
                parentNode->pOverflow = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                parentNode->pointers[2] = childNode;

                newNode->parent = parentNode->pointers[1];
                childNode->parent = parentNode->pointers[1];
            }
            else {
                newNode->key1 = childNode->overflow;
                newNode->pointers[0] = childNode->pointers[2];
                newNode->pointers[1] = childNode->pOverflow;
                parentNode->pOverflow = newNode;

                childNode->key2 = -1;
                childNode->overflow = -1;
                childNode->pointers[2] = NULL;
                childNode->pOverflow = NULL;
                parentNode->pointers[2] = childNode;

                newNode->parent = parentNode->pointers[1];
                childNode->parent = parentNode->pointers[1];
            }
        }
    }
    return parentNode;
}

Node* insert(Node* bPlusTree, int n) {
    Node* currentNode = bPlusTree;

    while (!currentNode->isLeaf) {
        if (n < currentNode->key1) currentNode = currentNode->pointers[0];
        else if (n < currentNode->key2 || currentNode->key2 == -1) currentNode = currentNode->pointers[1];
        else currentNode = currentNode->pointers[2];
    }
    currentNode = insertLeaf(currentNode, n);

    if (currentNode->overflow == -1) return bPlusTree;

    while (currentNode != bPlusTree) {
        if (currentNode->overflow != -1) currentNode->parent = splitLeaf(currentNode, currentNode->parent);
        currentNode = currentNode->parent;
    }

    if (currentNode->overflow != -1) {
        currentNode->parent = splitLeaf(currentNode, currentNode->parent);
        currentNode = currentNode->parent;
    }

    checkParent(currentNode);
    return currentNode;
}

void checkParent(Node* parentNode) {
    if (parentNode == NULL) return;
    Node* LeftNode = parentNode->pointers[0];
    Node* midNode = parentNode->pointers[1];
    Node* rightNode = parentNode->pointers[2];

    if (LeftNode != NULL) {
        LeftNode->parent = parentNode;
        checkParent(LeftNode);
    }

    if (midNode != NULL) {
        midNode->parent = parentNode;
        checkParent(midNode);
    }

    if (rightNode != NULL) {
        rightNode->parent = parentNode;
        checkParent(rightNode);
    }
}

Node* removeNode(Node* bPlusTree, int n) {
    int aux;
    Node* auxTree = bPlusTree;
    Node* buffTree;
    while (1) {
        if (auxTree->isLeaf && (auxTree->key1 == n)) {
            if (auxTree->key2 != -1) {
                auxTree->key1 = auxTree->key2;
                aux = auxTree->key1;
                auxTree->key2 = -1;
                while (auxTree->parent) {
                    auxTree = auxTree->parent;
                    if (auxTree->key1 == n) {
                        auxTree->key1 = aux;
                    }
                    else if (auxTree->key2 == n) {
                        auxTree->key2 = aux;
                    }
                }
            }
            else {
                if (!auxTree->parent) {
                    return NULL;
                }
                auxTree = auxTree->parent;
                if (n < auxTree->key1) {
                    if (auxTree->pointers[1]->key2 != -1) {
                        aux = auxTree->pointers[1]->key1;
                        auxTree->pointers[1]->key1 = auxTree->pointers[1]->key2;
                        auxTree->pointers[1]->key2 = -1;
                        auxTree->key1 = auxTree->pointers[1]->key1;
                        auxTree->pointers[0]->key1 = aux;
                        while (auxTree->parent) {
                            auxTree = auxTree->parent;
                            if (auxTree->key1 == n) {
                                auxTree->key1 = aux;
                            }
                            else if (auxTree->key2 == n) {
                                auxTree->key2 = aux;
                            }
                        }
                    }
                    else {
                        if (auxTree->key2 != -1) {
                            free(auxTree->pointers[0]);
                            auxTree->key1 = auxTree->key2;
                            auxTree->key2 = -1;
                            auxTree->pointers[0] = auxTree->pointers[1];
                            auxTree->pointers[1] = auxTree->pointers[2];
                            auxTree->pointers[2] = NULL;
                            aux = auxTree->pointers[0]->key1;
                            while (auxTree->parent) {
                                auxTree = auxTree->parent;
                                if (auxTree->key1 == n) {
                                    auxTree->key1 = aux;
                                }
                                else if (auxTree->key2 == n) {
                                    auxTree->key2 = aux;
                                }
                            }
                        }
                        else {
                            if (!auxTree->parent) {
                                free(auxTree->pointers[0]);
                                free(auxTree->pointers[1]);
                                auxTree->pointers[0] = NULL;
                                auxTree->pointers[1] = NULL;
                                auxTree->isLeaf = 1;
                            }
                            else if (n < auxTree->parent->key1) {
                                if (auxTree->parent->key2 != -1) {
                                    if (auxTree->parent->pointers[1]->key2 != -1) {
                                        free(auxTree->pointers[0]);
                                        auxTree->pointers[0] = auxTree->pointers[1];
                                        auxTree->pointers[1] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->key1 = auxTree->parent->key1;
                                        auxTree->parent->key1 = auxTree->parent->pointers[1]->key1;
                                        auxTree->parent->pointers[1]->key1 = auxTree->parent->pointers[1]->key2;
                                        auxTree->parent->pointers[1]->key2 = -1;
                                        auxTree->parent->pointers[1]->pointers[0] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->parent->pointers[1]->pointers[1] = auxTree->parent->pointers[1]->pointers[2];
                                        auxTree->parent->pointers[1]->pointers[2] = NULL;
                                        aux = auxTree->pointers[0]->key1;
                                        while (auxTree->parent) {
                                            auxTree = auxTree->parent;
                                            if (auxTree->key1 == n) {
                                                auxTree->key1 = aux;
                                            }
                                            else if (auxTree->key2 == n) {
                                                auxTree->key2 = aux;
                                            }
                                        }
                                    }
                                    else {
                                        free(auxTree->pointers[0]);
                                        auxTree->pointers[0] = auxTree->pointers[1];
                                        auxTree->pointers[1] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->key2 = auxTree->pointers[2]->key1;
                                        auxTree->parent->key1 = auxTree->parent->key2;
                                        auxTree->parent->key2 = -1;
                                        free(auxTree->parent->pointers[1]);
                                        auxTree->parent->pointers[1] = auxTree->parent->pointers[2];
                                        auxTree->parent->pointers[2] = NULL;
                                        aux = auxTree->pointers[0]->key1;
                                        while (auxTree->parent) {
                                            auxTree = auxTree->parent;
                                            if (auxTree->key1 == n) {
                                                auxTree->key1 = aux;
                                            }
                                            else if (auxTree->key2 == n) {
                                                auxTree->key2 = aux;
                                            }
                                        }
                                    }
                                }
                                else {
                                    if (auxTree->parent->pointers[1]->key2 != -1) {
                                        free(auxTree->pointers[0]);
                                        auxTree->pointers[0] = auxTree->pointers[1];
                                        auxTree->pointers[1] = auxTree->parent->pointers[0]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->parent->key1 = auxTree->parent->pointers[1]->key1;
                                        auxTree->parent->pointers[1]->key1 = auxTree->parent->pointers[1]->key2;
                                        auxTree->parent->pointers[1]->key2 = -1;
                                        auxTree->parent->pointers[1]->pointers[0] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->parent->pointers[1]->pointers[1] = auxTree->parent->pointers[1]->pointers[2];
                                        auxTree->parent->pointers[1]->pointers[2] = NULL;
                                        aux = auxTree->pointers[0]->key1;
                                        while (auxTree->parent) {
                                            auxTree = auxTree->parent;
                                            if (auxTree->key1 == n) {
                                                auxTree->key1 = aux;
                                            }
                                            else if (auxTree->key2 == n) {
                                                auxTree->key2 = aux;
                                            }
                                        }
                                    }
                                    else {
                                        free(auxTree->pointers[0]);
                                        auxTree->pointers[0] = auxTree->pointers[1];
                                        auxTree->pointers[1] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->key2 = auxTree->pointers[2]->key1;
                                        auxTree->parent->key1 = -1;
                                        aux = auxTree->pointers[0]->key1;
                                        free(auxTree->parent->pointers[1]);
                                        buffTree = auxTree;
                                        while (buffTree->parent) {
                                            buffTree = buffTree->parent;
                                            if (buffTree->key1 == n) {
                                                buffTree->key1 = aux;
                                            }
                                            else if (buffTree->key2 == n) {
                                                buffTree->key2 = aux;
                                            }
                                        }
                                        fixNodes(auxTree->parent);
                                    }
                                }
                            }
                            else if (auxTree->parent->key2 == -1 || n < auxTree->parent->key2) {
                                if (auxTree->parent->key2 != -1) {
                                    if (auxTree->parent->pointers[0]->key2 != -1) {
                                        free(auxTree->pointers[0]);
                                        auxTree->pointers[0] = auxTree->parent->pointers[0]->pointers[2];
                                        auxTree->pointers[0]->parent = auxTree;
                                        auxTree->parent->key1 = auxTree->pointers[0]->key1;
                                        auxTree->parent->pointers[0]->key2 = -1;
                                        auxTree->parent->pointers[0]->pointers[2] = NULL;
                                    }
                                    else if (auxTree->parent->pointers[2]->key2 != -1) {
                                        free(auxTree->pointers[0]);
                                        auxTree->pointers[0] = auxTree->pointers[1];
                                        auxTree->pointers[1] = auxTree->parent->pointers[2]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->parent->key1 = auxTree->pointers[0]->key1;
                                        auxTree->parent->key2 = auxTree->parent->pointers[2]->key1;
                                        auxTree->parent->pointers[2]->key1 = auxTree->parent->pointers[2]->key2;
                                        auxTree->parent->pointers[2]->key2 = -1;
                                        auxTree->parent->pointers[2]->pointers[0] = auxTree->parent->pointers[2]->pointers[1];
                                        auxTree->parent->pointers[2]->pointers[1] = auxTree->parent->pointers[2]->pointers[2];
                                        auxTree->parent->pointers[2]->pointers[2] = NULL;
                                    }
                                    else {
                                        free(auxTree->pointers[0]);
                                        auxTree = auxTree->parent->pointers[0];
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key2 = auxTree->parent->pointers[1]->key1;
                                        auxTree->parent->key1 = auxTree->parent->key2;
                                        auxTree->parent->key2 = -1;
                                        free(auxTree->parent->pointers[1]);
                                        auxTree->parent->pointers[1] = auxTree->parent->pointers[2];
                                        auxTree->parent->pointers[2] = NULL;
                                    }
                                }
                                else {
                                    if (auxTree->parent->pointers[0]->key2 != -1) {
                                        free(auxTree->pointers[0]);
                                        auxTree->pointers[0] = auxTree->parent->pointers[0]->pointers[2];
                                        auxTree->pointers[0]->parent = auxTree;
                                        auxTree->parent->key1 = auxTree->pointers[0]->key1;
                                        auxTree->parent->pointers[0]->key2 = -1;
                                        auxTree->parent->pointers[0]->pointers[2] = NULL;
                                    }
                                    else {
                                        free(auxTree->pointers[0]);
                                        auxTree = auxTree->parent->pointers[0];
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key2 = auxTree->pointers[2]->key1;
                                        auxTree->parent->key1 = -1;
                                        free(auxTree->parent->pointers[1]);
                                        fixNodes(auxTree->parent);
                                    }
                                }
                            }
                            else if (n >= auxTree->parent->key2) {
                                if (auxTree->parent->pointers[1]->key2 != -1) {
                                    free(auxTree->pointers[0]);
                                    auxTree->pointers[0] = auxTree->parent->pointers[1]->pointers[2];
                                    auxTree->pointers[0]->parent = auxTree;
                                    auxTree->parent->key2 = auxTree->pointers[0]->key1;
                                    auxTree->parent->pointers[1]->key2 = -1;
                                    auxTree->parent->pointers[1]->pointers[2] = NULL;
                                }
                                else {
                                    free(auxTree->pointers[0]);
                                    auxTree = auxTree->parent->pointers[1];
                                    auxTree->pointers[2] = auxTree->parent->pointers[2]->pointers[1];
                                    auxTree->pointers[2]->parent = auxTree;
                                    auxTree->key2 = auxTree->pointers[2]->key1;
                                    auxTree->parent->key2 = -1;
                                    free(auxTree->parent->pointers[2]);
                                    auxTree->parent->pointers[2] = NULL;
                                }
                            }
                        }
                    }
                }
                else if (n == auxTree->key1) {
                    if (auxTree->pointers[0]->key2 != -1) {
                        aux = auxTree->pointers[0]->key2;
                        auxTree->pointers[0]->key2 = -1;
                        auxTree->key1 = aux;
                        auxTree->pointers[1]->key1 = aux;
                        while (auxTree->parent) {
                            auxTree = auxTree->parent;
                            if (auxTree->key1 == n) {
                                auxTree->key1 = aux;
                            }
                            else if (auxTree->key2 == n) {
                                auxTree->key2 = aux;
                            }
                        }
                    }
                    else if ((auxTree->pointers[2]) && (auxTree->pointers[2]->key2 != -1)) {
                        aux = auxTree->pointers[2]->key1;
                        auxTree->pointers[2]->key1 = auxTree->pointers[2]->key2;
                        auxTree->pointers[2]->key2 = -1;
                        auxTree->key2 = auxTree->pointers[2]->key1;
                        auxTree->pointers[1]->key1 = aux;
                        auxTree->key1 = aux;
                        while (auxTree->parent) {
                            auxTree = auxTree->parent;
                            if (auxTree->key1 == n) {
                                auxTree->key1 = aux;
                            }
                            else if (auxTree->key2 == n) {
                                auxTree->key2 = aux;
                            }
                        }
                    }
                    else {
                        if (auxTree->pointers[2]) {
                            free(auxTree->pointers[1]);
                            auxTree->pointers[1] = auxTree->pointers[2];
                            auxTree->pointers[2] = NULL;
                            auxTree->key1 = auxTree->pointers[1]->key1;
                            auxTree->key2 = -1;
                        }
                        else {
                            if (!auxTree->parent) {
                                aux = auxTree->pointers[0]->key1;
                                free(auxTree->pointers[0]);
                                free(auxTree->pointers[1]);
                                auxTree->key1 = aux;
                                auxTree->pointers[0] = NULL;
                                auxTree->pointers[1] = NULL;
                                auxTree->isLeaf = 1;
                            }
                            else if (n < auxTree->parent->key1) {
                                if (auxTree->parent->key2 != -1) {
                                    if (auxTree->parent->pointers[1]->key2 != -1) {
                                        free(auxTree->pointers[1]);
                                        auxTree->pointers[1] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->parent->key1 = auxTree->parent->pointers[1]->key1;
                                        auxTree->parent->pointers[1]->key1 = auxTree->parent->pointers[1]->key2;
                                        auxTree->parent->pointers[1]->key2 = -1;
                                        auxTree->parent->pointers[1]->pointers[0] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->parent->pointers[1]->pointers[1] = auxTree->parent->pointers[1]->pointers[2];
                                        auxTree->parent->pointers[1]->pointers[2] = NULL;
                                    }
                                    else {
                                        free(auxTree->pointers[1]);
                                        auxTree->pointers[1] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->key2 = auxTree->pointers[2]->key1;
                                        auxTree->parent->key1 = auxTree->parent->key2;
                                        auxTree->parent->key2 = -1;
                                        free(auxTree->parent->pointers[1]);
                                        auxTree->parent->pointers[1] = auxTree->parent->pointers[2];
                                        auxTree->parent->pointers[2] = NULL;
                                    }
                                }
                                else {
                                    if (auxTree->parent->pointers[1]->key2 != -1) {
                                        free(auxTree->pointers[1]);
                                        auxTree->pointers[1] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->parent->key1 = auxTree->parent->pointers[1]->key1;
                                        auxTree->parent->pointers[1]->key1 = auxTree->parent->pointers[1]->key2;
                                        auxTree->parent->pointers[1]->key2 = -1;
                                        auxTree->parent->pointers[1]->pointers[0] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->parent->pointers[1]->pointers[1] = auxTree->parent->pointers[1]->pointers[2];
                                        auxTree->parent->pointers[1]->pointers[2] = NULL;
                                    }
                                    else {
                                        free(auxTree->pointers[1]);
                                        auxTree->pointers[1] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[1];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->key2 = auxTree->pointers[2]->key1;
                                        auxTree->parent->key1 = -1;
                                        free(auxTree->parent->pointers[1]);
                                        fixNodes(auxTree->parent);
                                    }
                                }
                            }
                            else if (n < auxTree->parent->key2 || auxTree->parent->key2 == -1) {
                                if (auxTree->parent->key2 != -1) {
                                    if (auxTree->parent->pointers[0]->key2 != -1) {
                                        free(auxTree->pointers[1]);
                                        auxTree->pointers[1] = auxTree->pointers[0];
                                        auxTree->pointers[0] = auxTree->parent->pointers[0]->pointers[2];
                                        auxTree->pointers[0]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->parent->key1 = auxTree->pointers[0]->key1;
                                        auxTree->parent->pointers[0]->key2 = -1;
                                        auxTree->parent->pointers[0]->pointers[2] = NULL;
                                    }
                                    else if (auxTree->parent->pointers[2]->key2 != -1) {
                                        free(auxTree->pointers[1]);
                                        auxTree->pointers[1] = auxTree->parent->pointers[2]->pointers[0];
                                        auxTree->pointers[1]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->parent->key2 = auxTree->parent->pointers[2]->key1;
                                        auxTree->parent->pointers[2]->key1 = auxTree->parent->pointers[2]->key2;
                                        auxTree->parent->pointers[2]->key2 = -1;
                                        auxTree->parent->pointers[2]->pointers[0] = auxTree->parent->pointers[2]->pointers[1];
                                        auxTree->parent->pointers[2]->pointers[1] = auxTree->parent->pointers[2]->pointers[2];
                                        auxTree->parent->pointers[2]->pointers[2] = NULL;
                                    }
                                    else {
                                        free(auxTree->pointers[1]);
                                        auxTree = auxTree->parent->pointers[0];
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key2 = auxTree->pointers[2]->key1;
                                        auxTree->parent->key1 = auxTree->parent->key2;
                                        auxTree->parent->key2 = -1;
                                        free(auxTree->parent->pointers[1]);
                                        auxTree->parent->pointers[1] = auxTree->parent->pointers[2];
                                        auxTree->parent->pointers[2] = NULL;
                                    }
                                }
                                else {
                                    if (auxTree->parent->pointers[0]->key2 != -1) {
                                        free(auxTree->pointers[1]);
                                        auxTree->pointers[1] = auxTree->pointers[0];
                                        auxTree->pointers[0] = auxTree->parent->pointers[0]->pointers[2];
                                        auxTree->pointers[0]->parent = auxTree;
                                        auxTree->key1 = auxTree->pointers[1]->key1;
                                        auxTree->parent->key1 = auxTree->pointers[0]->key1;
                                        auxTree->parent->pointers[0]->key2 = -1;
                                        auxTree->parent->pointers[0]->pointers[2] = NULL;
                                    }
                                    else {
                                        free(auxTree->pointers[1]);
                                        auxTree = auxTree->parent->pointers[0];
                                        auxTree->pointers[2] = auxTree->parent->pointers[1]->pointers[0];
                                        auxTree->pointers[2]->parent = auxTree;
                                        auxTree->key2 = auxTree->pointers[2]->key1;
                                        auxTree->parent->key1 = -1;
                                        free(auxTree->parent->pointers[1]);
                                        fixNodes(auxTree->parent);
                                    }
                                }
                            }
                            else if (n >= auxTree->parent->key2) {
                                if (auxTree->parent->pointers[1]->key2 != -1) {
                                    free(auxTree->pointers[1]);
                                    auxTree->pointers[1] = auxTree->pointers[0];
                                    auxTree->pointers[0] = auxTree->parent->pointers[1]->pointers[2];
                                    auxTree->pointers[0]->parent = auxTree;
                                    auxTree->key1 = auxTree->pointers[1]->key1;
                                    auxTree->parent->key2 = auxTree->pointers[0]->key1;
                                    auxTree->parent->pointers[1]->key2 = -1;
                                    auxTree->parent->pointers[1]->pointers[2] = NULL;
                                }
                                else {
                                    free(auxTree->pointers[1]);
                                    auxTree = auxTree->parent->pointers[1];
                                    auxTree->pointers[2] = auxTree->parent->pointers[2]->pointers[0];
                                    auxTree->pointers[2]->parent = auxTree;
                                    auxTree->key2 = auxTree->pointers[2]->key1;
                                    auxTree->parent->key2 = -1;
                                    free(auxTree->parent->pointers[2]);
                                    auxTree->parent->pointers[2] = NULL;
                                }
                            }
                        }
                    }
                }
                else if (n == auxTree->key2) {
                    if (auxTree->pointers[1]->key2 != -1) {
                        aux = auxTree->pointers[1]->key2;
                        auxTree->pointers[1]->key2 = -1;
                        auxTree->key2 = aux;
                        auxTree->pointers[2]->key1 = aux;
                    }
                    else {
                        auxTree->key2 = -1;
                        free(auxTree->pointers[2]);
                        auxTree->pointers[2] = NULL;
                    }
                }
            }
            break;
        }
        else if (auxTree->isLeaf && (auxTree->key2 == n)) {
            auxTree->key2 = -1;
            break;
        }
        else if (n < auxTree->key1) {
            if (!auxTree->pointers[0]) {
                printf("Key not found :(\n");
                return bPlusTree;
            }
            auxTree = auxTree->pointers[0];
        }
        else if ((n < auxTree->key2) || (auxTree->key2 == -1)) {
            if (!auxTree->pointers[1]) {
                printf("Key not found :(\n");
                return bPlusTree;
            }
            auxTree = auxTree->pointers[1];
        }
        else {
            if (!auxTree->pointers[2]) {
                printf("Key not found :(\n");
                return bPlusTree;
            }
            auxTree = auxTree->pointers[2];
        }
    }

    return bPlusTree;
}

Node* fixNodes(Node* tree) {
    Node* auxTree;
    Node* parentTree = tree->parent;
    if (tree->parent == NULL) {
        if (tree->pointers[0] != NULL) {
            auxTree = tree->pointers[0];
            tree->key1 = auxTree->key1;
            tree->key2 = auxTree->key2;
            tree->pointers[0] = auxTree->pointers[0];
            tree->pointers[0]->parent = tree;
            tree->pointers[1] = auxTree->pointers[1];
            tree->pointers[1]->parent = tree;
            tree->pointers[2] = auxTree->pointers[2];
            tree->pointers[2]->parent = tree;
            free(auxTree);
            return tree;
        }
    }
    int pIndex;
    Node* childArray[MAX_CHILDREN] = { parentTree->pointers[0], parentTree->pointers[1], parentTree->pointers[2] };
    int childKey1, childKey2;
    int parentKey;
    if (tree->key1 == -1) {
        parentTree = tree->parent;
        for (pIndex = 0; childArray[pIndex] != tree; pIndex++);

        if (childArray[pIndex - 1] && childArray[pIndex - 1]->key2 == -1) childKey1 = 1;
        else childKey1 = 2;

        if (childArray[pIndex + 1] && childArray[pIndex + 1]->key2 == -1) childKey2 = 1;
        else childKey2 = 2;

        if (parentTree->key2 == -1) parentKey = 1;
        else parentKey = 2;

        if (pIndex > 0 && childKey1 > 1) {
            getFromLeft(tree, pIndex);
        }
        else if (pIndex < parentKey && childKey2 > 1) {
            getFromRight(tree, pIndex);
        }
        else if (pIndex == 0) {
            Node* nextNode = concRight(tree);
            fixNodes(nextNode->parent);
        }
        else {
            Node* nextNode = concRight(childArray[pIndex - 1]);
            fixNodes(nextNode->parent);
        }
    }
    return tree;
}

Node* getFromLeft(Node* tree, int pIndex) {
    Node* treeArray[MAX_CHILDREN] = { tree->pointers[0], tree->pointers[1], tree->pointers[2] };
    Node* parentTree = tree->parent;
    Node* parentArray[MAX_CHILDREN] = { parentTree->pointers[0], parentTree->pointers[1], parentTree->pointers[2] };
    int treeNumKeys;
    int treeKeys[2] = { tree->key1, tree->key2 };
    int parentKey[2] = { parentTree->key1, parentTree->key2 };
    int rmlNumKeys;

    if (tree->key1 == -1) treeNumKeys = 0;
    else if (tree->key2 == -1) treeNumKeys = 1;
    else treeNumKeys = 2;

    for (int i = treeNumKeys - 1; i > 0; i--) {
        treeKeys[i] = treeKeys[i - 1];
    }

    Node* left = parentArray[pIndex - 1];
    Node* rmlArray[MAX_CHILDREN] = { left->pointers[0], left->pointers[1], left->pointers[2] };
    int rmlKeys[2] = { left->key1, left->key2 };

    if (left->key2 == -1) rmlNumKeys = 1;
    else rmlNumKeys = 2;

    treeKeys[0] = parentKey[pIndex - 1];
    parentKey[pIndex - 1] = rmlKeys[rmlNumKeys - 1];
    rmlKeys[rmlNumKeys - 1] = -1;
    treeNumKeys += 1;

    for (int i = treeNumKeys; i > 0; i--) {
        if (i == 1) tree->pointers[1] = tree->pointers[0];
        if (i == 2) tree->pointers[2] = tree->pointers[1];
        treeArray[i] = treeArray[i - 1];
    }

    tree->pointers[0] = rmlArray[rmlNumKeys];
    rmlArray[rmlNumKeys] = NULL;
    if (rmlNumKeys == 2) left->pointers[2] = NULL;
    if (rmlNumKeys == 1) left->pointers[1] = NULL;
    if (rmlNumKeys == 0) left->pointers[0] = NULL;
    tree->pointers[0]->parent = tree;

    tree->key1 = treeKeys[0];
    tree->key2 = treeKeys[1];
    parentTree->key1 = parentKey[0];
    parentTree->key2 = parentKey[1];
    left->key1 = rmlKeys[0];
    left->key2 = rmlKeys[1];

    return tree;
}

Node* getFromRight(Node* tree, int pIndex) {
    Node* treeArray[MAX_CHILDREN] = { tree->pointers[0], tree->pointers[1], tree->pointers[2] };
    Node* parentTree = tree->parent;
    Node* parentArray[MAX_CHILDREN] = { parentTree->pointers[0], parentTree->pointers[1], parentTree->pointers[2] };
    int treeNumKeys;
    int treeKeys[2] = { tree->key1, tree->key2 };
    int parentKey[2] = { parentTree->key1, parentTree->key2 };
    int rmlNumKeys;

    if (tree->key1 == -1) treeNumKeys = 0;
    else if (tree->key2 == -1) treeNumKeys = 1;
    else treeNumKeys = 2;

    Node* right = parentArray[pIndex + 1];
    Node* rmlArray[MAX_CHILDREN] = { right->pointers[0], right->pointers[1], right->pointers[2] };
    int rmlKeys[2] = { right->key1, right->key2 };

    if (right->key1 == -1) rmlNumKeys = 0;
    else if (right->key2 == -1) rmlNumKeys = 1;
    else rmlNumKeys = 2;

    treeKeys[treeNumKeys] = parentKey[pIndex];
    parentKey[pIndex] = rmlKeys[0];
    rmlKeys[0] = -1;
    treeNumKeys += 1;
    treeArray[treeNumKeys] = rmlArray[0];
    if (treeNumKeys == 0) tree->pointers[0] = rmlArray[0];
    if (treeNumKeys == 1) tree->pointers[1] = rmlArray[0];
    if (treeNumKeys == 2) tree->pointers[2] = rmlArray[0];
    treeArray[treeNumKeys]->parent = tree;
    rmlArray[0] = NULL;
    right->pointers[0] = NULL;

    for (int i = 1; i < rmlNumKeys + 1; i++) {
        if (i == 1) {
            right->pointers[0] = right->pointers[1];
            right->pointers[1] = NULL;
        }
        if (i == 2) {
            right->pointers[1] = right->pointers[2];
            right->pointers[2] = NULL;
        }
        rmlArray[i - 1] = rmlArray[i];
        rmlArray[i] = NULL;
    }

    for (int i = 0; i < rmlNumKeys; i++) {
        rmlKeys[i - 1] = rmlKeys[i];
        rmlKeys[i] = -1;
    }

    tree->key1 = treeKeys[0];
    tree->key2 = treeKeys[1];
    parentTree->key1 = parentKey[0];
    parentTree->key2 = parentKey[1];
    right->key1 = rmlKeys[0];
    right->key2 = rmlKeys[1];

    return tree;
}

Node* concRight(Node* tree) {
    Node* parentTree = tree->parent;
    Node* parentArray[MAX_CHILDREN] = { parentTree->pointers[0], parentTree->pointers[1], parentTree->pointers[2] };
    Node* treeArray[MAX_CHILDREN] = { tree->pointers[0], tree->pointers[1], tree->pointers[2] };
    int parentKey[2] = { parentTree->key1, parentTree->key2 };
    int treeKeys[2] = { tree->key1, tree->key2 };
    int pIndex = 0;
    int treeNumKeys;
    int parentNumKeys;
    int rightNum;

    if (tree->key1 == -1) treeNumKeys = 0;
    else if (tree->key2 == -1) treeNumKeys = 1;
    else treeNumKeys = 2;

    if (parentTree->key1 == -1) parentNumKeys = 0;
    else if (parentTree->key2 == -1) parentNumKeys = 1;
    else parentNumKeys = 2;

    for (pIndex = 0; parentArray[pIndex] != tree; pIndex++);

    Node* right = parentArray[pIndex + 1];
    Node* rightArray[MAX_CHILDREN] = { right->pointers[0], right->pointers[1], right->pointers[2] };
    int rightKeys[2] = { right->key1, right->key2 };

    if (right->key1 == -1) rightNum = 0;
    else if (right->key2 == -1) rightNum = 1;
    else rightNum = 2;

    treeKeys[treeNumKeys] = parentKey[pIndex];
    parentKey[pIndex] = -1;

    for (int i = 0; i < rightNum; i++) {
        int endIndex = treeNumKeys + 1 + i;
        treeKeys[endIndex] = rightKeys[i];
    }

    for (int i = 0; i <= rightNum; i++) {
        if (treeNumKeys + 1 + i == 1) {
            tree->pointers[1] = rightArray[i];
            tree->pointers[1]->parent = tree;
        }
        else if (treeNumKeys + 1 + i == 2) {
            tree->pointers[2] = rightArray[i];
            tree->pointers[2]->parent = tree;
        }
        treeArray[treeNumKeys + 1 + i] = rightArray[i];
        treeArray[treeNumKeys + 1 + i]->parent = tree;
    }

    for (int i = pIndex + 1; i < parentNumKeys; i++) {
        if (i == 1) {
            parentTree->pointers[1] = parentTree->pointers[2];
        }
        parentArray[i] = parentArray[i + 1];
        parentKey[i - 1] = parentKey[i];
        parentKey[i] = -1;
    }
    free(right);
    tree->key1 = treeKeys[0];
    tree->key2 = treeKeys[1];
    parentTree->key1 = parentKey[0];
    parentTree->key2 = parentKey[1];

    return tree;
}

Node* search(Node* bPlusTree, int n) {
    while (!bPlusTree->isLeaf) {
        if (n < bPlusTree->key1) {
            bPlusTree = bPlusTree->pointers[0];
        }
        else if (n < bPlusTree->key2 || bPlusTree->key2 == -1) {
            bPlusTree = bPlusTree->pointers[1];
        }
        else {
            bPlusTree = bPlusTree->pointers[2];
        }
    }
    if (bPlusTree->key1 == n || bPlusTree->key2 == n) {
        return bPlusTree;
    }
    else {
        return NULL;
    }
}

void printNode(Node* node) {
    printf("%p -> node: %d, %d | ptr1 = %p, ptr2 = %p, ptr3 = %p\n",
        node, node->key1, node->key2, node->pointers[0], node->pointers[1], node->pointers[2]);
}

void printTree(Node* bPlusTree) {
    if (bPlusTree == NULL) return;
    printNode(bPlusTree);

    if (!bPlusTree->isLeaf) {
        for(int i = 0; i < MAX_CHILDREN; i++) printTree(bPlusTree->pointers[i]);
    }
}
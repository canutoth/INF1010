#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 100

typedef struct Node {
    int key, level, height;
    struct Node* left, * right, * parent;
} Node;

Node* newNode(int key);
void insert(Node** nodes, int key, int* index);
int height(Node* node);
void printLevel(Node* root, int level);
void printTree(Node* root);

int main() {
    Node* nodes[100] = {NULL};

    int index = 0;


    int keys[] = { 10, 5, 15, 3, 7, 13, 20, 1, 4, 6 };
    ;
    int n = sizeof(keys) / sizeof(keys[0]);
    if (n > MAX_NODES) {
        printf("Error: The number of keys exceeds the maximum allowed limit of %d.\n", MAX_NODES);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        insert(nodes, keys[i], &index);
    }

    printf("binary tree by level:\n\n");
    printTree(nodes[0]);

    return 0;
}

Node* newNode(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));

    if (temp == NULL) {
        printf("Error: Memory Allocation.\n");
        exit(1);
    }

    temp->parent = NULL;
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

void insert(Node** nodes, int key, int* index) {
    Node* temp = newNode(key);

    if (nodes[0] == NULL) {
        nodes[0] = temp;
        temp->level = 0;
        return;
    }

    while (nodes[*index]->left != NULL && nodes[*index]->right != NULL) {
        (*index)++;
    }
      
    if (nodes[*index]->left == NULL) {
        nodes[*index]->left = temp;
    }
    else if (nodes[*index]->right == NULL) {
        nodes[*index]->right = temp;
    }

    int next_free_spot = *index;
    temp->parent = nodes[*index];
    temp->level = temp->parent->level+1;
    
    while (nodes[next_free_spot] != NULL) {
        next_free_spot++;
    }

    nodes[next_free_spot] = temp;

}

int height(Node* node) {
    if (node == NULL) return 0;
    int left_height = height(node->left);
    int right_height = height(node->right);
    node->height = (left_height > right_height ? left_height : right_height);
    return node->height + 1;
}

void printLevel(Node* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        printf("Node: %d\nAdress: %p\nHeight: %d\nLevel: %d\n", root->key, (void*)root, root->height, root->level);

        //printf("Address: %p\t", (void*)root);

        if (root->parent == NULL)
            printf("Root (no parent)\n");
        else
            printf("Parent: %d (Address: %p)\n", root->parent->key, (void*)root->parent);

        if (root->left != NULL)
            printf("Left Child: %d (Address: %p)\n", root->left->key, (void*)root->left);
        else
            printf("Left Child: NULL\n");

        if (root->right != NULL)
            printf("Right Child: %d (Address: %p)\n\n", root->right->key, (void*)root->right);
        else
            printf("Right Child: NULL\n\n");

        printf("\n");
    }
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}


void printTree(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
        printf("\n");
    }
}
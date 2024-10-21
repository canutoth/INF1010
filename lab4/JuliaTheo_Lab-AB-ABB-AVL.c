#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int num_subtrees;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int key);
Node* insert(Node* root, int key);
int calculate_subtrees(Node* root);
void print_tree(Node* root);
int is_bst(Node* root, Node* min_node, Node* max_node);
int height(Node* node);
int is_avl(Node* root);

int main() {
    //int keys[] = { 15, 17, 3, 5, 2, 20, 25, 13, 10, 16 }; // not avl test
    int keys[] = { 15, 3, 20, 2, 10, 17, 25, 5, 13, 16 }; //(avl test)
    int n = sizeof(keys) / sizeof(keys[0]);

    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    printf("Initial tree:\n\n");
    print_tree(root);

    printf("\nCalculating the number of nodes in the subtrees...\n");
    calculate_subtrees(root);

    printf("\nResulting tree:\n");
    print_tree(root);

    if (is_bst(root, NULL, NULL)) {
        printf("\nThis tree is a BST.\n");
        if (is_avl(root)) {
            printf("The tree is an AVL tree.\n");
        } else {
            printf("The tree is NOT an AVL tree.\n");
        }
    } else {
        printf("\nThis tree is NOT a BST.\n");
        printf("The tree is NOT an AVL tree.\n");
    }

    return 0;
}

Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("ERROR: Memory Allocation\n");
        exit(1);
    }
    node->key = key;
    node->num_subtrees = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

int calculate_subtrees(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left_count = calculate_subtrees(root->left);
    int right_count = calculate_subtrees(root->right);
    root->num_subtrees = left_count + right_count;
    return left_count + right_count + 1;
}

void print_tree(Node* root) {
    if (root != NULL) {
        print_tree(root->left);
        printf("Key: %d\nNumber of nodes on subtrees: %d\nAddress: %p\n", root->key, root->num_subtrees, (void*)root);
        if (root->left != NULL)
            printf("Left Child: %d (Address: %p)\n", root->left->key, (void*)root->left);
        else
            printf("Left Child: NULL\n");

        if (root->right != NULL)
            printf("Right Child: %d (Address: %p)\n\n", root->right->key, (void*)root->right);
        else
            printf("Right Child: NULL\n\n");
        print_tree(root->right);
    }
}

int is_bst(Node* root, Node* min_node, Node* max_node) {
    if (root == NULL) {
        return 1;
    }
    if (min_node != NULL && root->key <= min_node->key) {
        return 0;
    }
    if (max_node != NULL && root->key >= max_node->key) {
        return 0;
    }
    return is_bst(root->left, min_node, root) && is_bst(root->right, root, max_node);
}

int height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = height(node->left);
    int right_height = height(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

int is_avl(Node* root) {
    if (root == NULL) {
        return 1;
    }

    int left_height = height(root->left);
    int right_height = height(root->right);
    int balance_factor = left_height - right_height;

    if (balance_factor > 1 || balance_factor < -1) {
        return 0;
    }

    return is_avl(root->left) && is_avl(root->right);
}
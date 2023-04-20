#include <stdio.h>
#include <stdlib.h>
typedef struct NODE_s *NODE;
typedef struct NODE_s {
    NODE left;
    NODE right;
    void *data;
    int key;
}NODE_t[1];
typedef struct {
    NODE root;
}BST_t[1], *BST;
BST bst_init(){
    BST tree =(BST)malloc(sizeof(BST_t));
    tree->root = NULL;
    return tree;
}
NODE bst_init_node(int key, void*data){
    NODE node = (NODE)malloc(sizeof(NODE_t));
    node->left = NULL;
    node->right =NULL;
    node->key=key;
    node->data =data;
    return node;
}
int bst_insert( BST tree, int key, void *data){
    if(tree == NULL){
        printf("Error: The tree is not initialized\n");
    }
    else if(tree->root == NULL){
        tree->root = bst_init_node(key, data);
    }
    else{
        NODE node = tree->root;
        while (node !=NULL){
            if(key < node->key){
                if(node->left != NULL) {
                    node = node->left;
                }
                else{
                    node->left = bst_init_node(key,data);
                    node = NULL;
                }
            }
            else if(key > node->key){
                if(node->right !=NULL){
                    node = node->right;
                }
                else{
                    node->right= bst_init_node(key,data);
                    node = NULL;
                }
            }
            else{
                printf("Error: Duplicate key entry ! No action is done. \n");
                node = NULL;
                return -1;
            }
        }
    }
    return 1;
}

NODE bst_insert_rec1(NODE node, int key, void *data){
    if(node == NULL){
        node = bst_init_node(key, data);
    }
    else{
        if(key < node->key){
            node->left = bst_insert_rec1(node->left, key, data);
        }
        else if(key > node->key){
            node->right = bst_insert_rec1(node->right, key, data);
        }
        else{
            printf("ERROR: Duplicate key!!!\n");
        }
    }
    return node;
}
void print_tree(NODE node, int l) {
    if(node != NULL){
        print_tree(node->right, l+1);
        for (int i = 0; i < l; i++){
            printf("    ");
        }
        printf("%d",node->key);
        printf("\n");
        print_tree(node->left, l+1);
    }
}

void LeftRotation(NODE parent,NODE child,NODE grandparent,BST tree){
    parent->right=child->left;
    child->left=parent;
    if(parent==tree->root){
        tree->root=child;
    }
    else{
        grandparent->left=child;
    }
}

void make_backbone(NODE root,BST tree){//LEFT ROTASYON ICIN
    NODE grandparent = root;
    NODE parent = root;
    int counter=1;
    while(parent != NULL){
        NODE child = parent->right; //RİGHT ROTASYON İCİN BUNU LEFT YAP
        if(child!=NULL){
            LeftRotation(parent,child,grandparent,tree);
            printf("in Step %d Backbone Process:\n",counter++);
            print_tree(tree->root,1);
            parent = child;
        }
        else{
            grandparent= parent;
            parent=parent->left; // RİGHT ROTASYON İCİN BUNU RİGHT YAP
        }
    }
}

int main(){

    BST tree1 = bst_init();
    int Tree_arr[20]={27, 31, 74, 56, 86, 48, 8, 53, 7, 22, 85, 44, 63, 80, 49, 34, 84, 87, 5, 24};
    for (int i = 0; i < 20; i++) {
        tree1->root=bst_insert_rec1(tree1->root, Tree_arr[i], NULL);
    }
    printf("Before Processes Our Tree:\n");
    print_tree(tree1->root,0);
    make_backbone(tree1->root,tree1);
    printf("\n \t \t \t \t  Backbone COMPLETED !\n");

}

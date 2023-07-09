#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
	int prodID;
	char prodName[20];
	int prodQty;
	float prodPrice;
}Product;

typedef struct node{
	Product data;
	struct node *left;
	struct node *right;
} NodeType, *NodePtr, BST, *BSTPtr;

//Add element to the BST based on the product ID
BST *addElement(BST *list, int item, char *name;);//using recursive method
void insertBST(BSTPtr *list, int item, char *name);//using iterative method

//Delete element in the BST based on the product ID
void removeElement(BST **list, int prodID);// using iterative method
BST *deleteElement(BST *list, int prodID);//using recursive method

//Display BST all in recursive method
void inorderBST(BST *list);
void preorderBST(BST *list);
void postorderBST(BST *list);

//Other functions
BST *newBST();
void initBST(BST **list);
bool isEmpty(BST *list);
Product createProduct(int id,char *name, int qty, float price);
//use the following format {<id> | <prodName>} replacing angular brackets with data
void displayProduct(Product prod); 
BST *max(BST *list);
BST *min(BST *list);
bool isMember(BST *list, int prodID);

int main(int argc, char *argv[]) {
	BSTPtr bst = NULL;
    initBST(&bst);

    // Add elements to the BST
    bst = addElement(bst, 50, "Product 1");
    bst = addElement(bst, 30, "Product 2");
    bst = addElement(bst, 70, "Product 3");
    bst = addElement(bst, 20, "Product 4");
    bst = addElement(bst, 40, "Product 5");
    bst = addElement(bst, 60, "Product 6");
    bst = addElement(bst, 80, "Product 7");


    // Display the BST
    printf("Inorder traversal: ");
    inorderBST(bst);

    printf("Preorder traversal: ");
    preorderBST(bst);

    printf("Postorder traversal: ");
    postorderBST(bst);

    // Remove an element from the BST
    int prodID = 30;
    removeElement(&bst, prodID);
    printf("After removing element with prodID %d:\n", prodID);
    printf("Inorder traversal: ");
    inorderBST(bst);

    // Check if an element is present in the BST
    int searchID = 60;
    if (isMember(bst, searchID)) {
        printf("Element with prodID %d is present in the BST.\n", searchID);
    } else {
        printf("Element with prodID %d is not found in the BST.\n", searchID);
    }

	// Add an element using insertBST
	int newProdID = 90;
    char *newProdName = "Product 8";
    insertBST(&bst, newProdID, newProdName);
    printf("After inserting element with prodID %d and prodName %s:\n", newProdID, newProdName);
    printf("Inorder traversal: ");
    inorderBST(bst);

	return 0;
}
/*-------------Add element to the BST based on the product ID---------------*/
//Only insert and add element ang naay malloc
BST *addElement(BST *list, int item, char *name) {
	//using recursive method
    if (isEmpty(list)) {
        list = (BST *)malloc(sizeof(BST));
        list->data.prodID = item;
        strncpy(list->data.prodName, name, 20); // Copy the name to prodName field
        list->left = NULL;
        list->right = NULL;
    } else if (item < list->data.prodID) {
        list->left = addElement(list->left, item, name);
    } else if (item > list->data.prodID) {
        list->right = addElement(list->right, item, name);
    }

    return list;
}
void insertBST(BSTPtr *list, int item, char *name){
	//using iterative method
	BSTPtr newNode = (BSTPtr)malloc(sizeof(NodeType));
    newNode->data.prodID = item;
    strncpy(newNode->data.prodName, name, 20); // Copy the name to prodName field
    newNode->left = NULL;
    newNode->right = NULL;

    if (*list == NULL) {
        *list = newNode;
        return;
    }

    BSTPtr curr = *list;
    BSTPtr parent = NULL;

    while (curr != NULL) {
        parent = curr;

        if (item < curr->data.prodID) {
            curr = curr->left;
        } else if (item > curr->data.prodID) {
            curr = curr->right;
        } else {
            // Handle duplicates (if necessary)
            free(newNode); // Free the allocated memory for newNode
            return;
        }
    }

    if (item < parent->data.prodID) {
        parent->left = newNode;
    } else if (item > parent->data.prodID) {
        parent->right = newNode;
    }
}

/*-------------Delete element in the BST based on the product ID---------------*/
void removeElement(BST **list, int prodID){
	// using iterative method | uses loops
	if (*list == NULL)
        return;

    BSTPtr curr = *list;
    BSTPtr parent = NULL;

    // Find the node to be deleted
    while (curr != NULL && curr->data.prodID != prodID) {
        parent = curr;
        if (prodID < curr->data.prodID)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (curr == NULL)
        return; // Element not found

    // Case 1: Node to be deleted has no children
    if (curr->left == NULL && curr->right == NULL) {
        if (parent == NULL) {
            // Deleting the root node
            *list = NULL;
        } else if (parent->left == curr) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }

        free(curr);
    }
    // Case 2: Node to be deleted has one child
    else if (curr->left == NULL) {
        if (parent == NULL) {
            // Deleting the root node
            *list = curr->right;
        } else if (parent->left == curr) {
            parent->left = curr->right;
        } else {
            parent->right = curr->right;
        }

        free(curr);
    } else if (curr->right == NULL) {
        if (parent == NULL) {
            // Deleting the root node
            *list = curr->left;
        } else if (parent->left == curr) {
            parent->left = curr->left;
        } else {
            parent->right = curr->left;
        }

        free(curr);
    }
    // Case 3: Node to be deleted has two children
    else {
        BSTPtr successor = curr->right;
        BSTPtr succParent = curr;

        // Find the inorder successor (smallest node in the right subtree)
        while (successor->left != NULL) {
            succParent = successor;
            successor = successor->left;
        }

        // Replace the node's data with the successor's data
        curr->data = successor->data;

        // Delete the successor node (successor will have at most one right child)
        if (succParent->left == successor)
            succParent->left = successor->right;
        else
            succParent->right = successor->right;

        free(successor);
    }
}

BST *deleteElement(BST *list, int prodID){
	//using recursive method | calls it self
	if (list == NULL)
        return list;

    if (prodID < list->data.prodID) {
        list->left = deleteElement(list->left, prodID);
    } else if (prodID > list->data.prodID) {
        list->right = deleteElement(list->right, prodID);
    } else {
        if (list->left == NULL && list->right == NULL) {
            free(list);
            list = NULL;
        } else if (list->left == NULL) {
            BST *temp = list;
            list = list->right;
            free(temp);
        } else if (list->right == NULL) {
            BST *temp = list;
            list = list->left;
            free(temp);
        } else {
            BST *temp = min(list->right);
            list->data.prodID = temp->data.prodID;
            list->right = deleteElement(list->right, temp->data.prodID);
        }
    }

    return list;
}


/*---------Display BST all in recursive method (Using stack and Queues)----------*/
void inorderBST(BST *list) {
    if (list == NULL)
        return;

    inorderBST(list->left);
    displayProduct(list->data);
    inorderBST(list->right);
}

void preorderBST(BST *list) {
    if (list == NULL)
        return;

    displayProduct(list->data);
    preorderBST(list->left);
    preorderBST(list->right);
}

void postorderBST(BST *list) {
    if (list == NULL)
        return;

    postorderBST(list->left);
    postorderBST(list->right);
    displayProduct(list->data);
}

/*-------------Other Functions---------------*/
BST *newBST(){	
    return NULL;
}
void initBST(BST **list){
	*list = NULL;
}
bool isEmpty(BST *list){
	return list == NULL;
}
Product createProduct(int id,char *name, int qty, float price){
	Product prod;
    prod.prodID = id;
    strncpy(prod.prodName, name,20);
    prod.prodQty = qty;
    prod.prodPrice = price;
    return prod;
}
void displayProduct(Product prod){
	//use the following format {<id> | <prodName>} replacing angular brackets with data
	printf("{%d | %s}\n", prod.prodID, prod.prodName);
}
BST *max(BST *list){ //entire node | Predecessor getting average for 
	if (list == NULL)
        return NULL;

    while (list->right != NULL)
        list = list->right;

    return list;
}
BST *min(BST *list){
	if (list == NULL)
        return NULL;

    while (list->left != NULL)
        list = list->left;

    return list;
}
bool isMember(BST *list, int prodID){
	if (list == NULL)
        return false;

    if (list->data.prodID == prodID)
        return true;
    else if (prodID < list->data.prodID)
        return isMember(list->left, prodID);
    else
        return isMember(list->right, prodID);
}

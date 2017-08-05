// C program to demonstrate insert operation in binary search tree
#include<stdio.h>
#include<stdlib.h>

//Build struct for linked list;
typedef struct node
{
	int key;
	struct node *left, *right, *parent;
}node_data;

//Initiallize functions;
void menu(node_data *root);
void enter_node(node_data *root, int key);
void printTree(node_data *root);
node_data *serch(node_data *root, int k);
node_data *maxNode(node_data *root);
node_data *minNode(node_data *root);
void deleteNode(node_data *node);
void freeTreeRec(node_data* node);

void main()
{
	//Initiallize variables;
	node_data *root;
	root = (node_data*)malloc(sizeof(node_data));
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->key = -1;
	menu(root);

	printf("Press any key to close the program");
	getch();

	//Free all pointers;
	freeTreeRec(root);
}

//menu for user;
void menu(node_data *root)
{

	char input = 'z';
	int Nkey = 0, k = 0;

	//for min and max function;
	node_data *saveMin;
	node_data *saveMax;

	//for remove node function;
	node_data *node_to_remove;

	while (input != 'q')
	{
		printf("What you want to do?\n");
		printf("a) Enter a node to tree\n");
		printf("b) Print tree\n");
		printf("c) Search if some key is in list\n");
		printf("d) Search min and max\n");
		printf("e) To remove node\n");
		printf("q) Exit\n");
		fflush(stdin);
		scanf("%c", &input);

		switch (input)
		{
		case 'a':
			printf("Please enter a number that you want to insert to the tree\n");
			scanf("%d", &Nkey);
			enter_node(root, Nkey);
			break;
		case 'b':
			printTree(root);
			printf("Press any key to continue\n");
			getch();	//to hold the program
			break;
		case 'c':
			printf("Enter the key you want to search\n");
			scanf("%d", &k);
			if (serch(root, k) == NULL)
			{
				printf("This key is not in the tree\n");
			}
			else
			{
				printf("This key is in the tree\n");
			}
			printf("Press any key to continue\n");
			getch();
			break;
		case 'd':
			saveMin = maxNode(root);
			saveMax = minNode(root);
			printf("The minimum key is: %d \n", saveMin->key);
			printf("The maximum key is: %d \n", saveMax->key);
			printf("Press any key\n");
			getch();	//To hold the screen
			break;
		case 'e':
			printf("Enter the key you want to remove\n");
			scanf("%d", &k);
			node_to_remove = serch(root, k);
			if (node_to_remove == NULL)
			{
				printf("This key is not in the tree\n");
				printf("Press any key to continue\n");
				getch();
			}
			else
			{
				deleteNode(node_to_remove);
				printf("This key removed\n");
				getch();
			}
			break;
		default:
			break;
		}
		system("cls");	//Clear the screen
	}
}

//This function free all the node in the tree. 
//The order call postorder
void freeTreeRec(node_data* node)
{
	if (node == NULL){	//Base case
		return;
	}
	freeTreeRec(node->left);
	freeTreeRec(node->right);
	free(node);
}

//Enter new node to the tree.
/*
We get the root of the tree and the new value we want to enter.
here it's one of the places you want to change if you will use this data structure
*/
void enter_node(node_data *root, int Nkey)
{
	node_data *par = NULL, *save_node = root;

	//I chose to use -1 as a flag to check if this node is all ready initiallized in the tree
	if (root->key == -1)
	{
		root->key = Nkey;
		return;
	}

	//Serch the right place for this node;
	while (root != NULL){
		save_node = root;
		if (Nkey < save_node->key){ root = root->left; }//If the new key is greater than the current key, the then we need to go left.
		else if (Nkey >= root->key){ root = root->right; }
	}

	//Create node;
	if (Nkey >= save_node->key)
	{
		//Here we find that the new key is smaller than the leaf so we connecting it to his right 
		save_node->right = (node_data*)malloc(sizeof(node_data));
		save_node->right->left = NULL;
		save_node->right->right = NULL;
		save_node->right->parent = save_node;
		save_node->right->key = Nkey;
	}

	//create node;
	else if (Nkey < save_node->key)
	{
		save_node->left = (node_data*)malloc(sizeof(node_data));
		save_node->left->left = NULL;
		save_node->left->right = NULL;
		save_node->left->parent = save_node;
		save_node->left->key = Nkey;
	}
}

//preorder
//node left right
void printTree(node_data *root)
{
	if (root == NULL)
	{
		return;
	}
	//check if tree empty;
	if (root->key == -1)
	{
		printf("the tree is empty\n");
		return;
	}
	//print;
	printf("%d\n", root->key);
	printTree(root->left);
	printTree(root->right);
}

//search for some node;
node_data *serch(node_data *root, int k)
{
	node_data* node = root;
	//by logic of bst;
	while (node != NULL)
	{
		if (k < node->key)
		{
			node = node->left;
		}
		else if (k > node->key)
		{
			node = node->right;
		}
		else if (k == node->key)
		{
			return node;
		}
	}
	//if not fuond;
	return NULL;
}

//Search max;
//By logic of bst;
node_data *maxNode(node_data *root)
{
	node_data *save_node;
	node_data *curr = root;
	while (curr != NULL)
	{
		save_node = curr;
		curr = curr->right;
	}
	return save_node;
}

//Search min;
node_data *minNode(node_data *root)
{
	node_data *save_node, *curr = root;
	while (curr != NULL)
	{
		save_node = curr;
		curr = curr->left;
	}
	return save_node;
}

//This function deleting node from tree; /*** This function need to be refactored ****/
void deleteNode(node_data *node)
{
	//Pointers to work with;
	node_data* node_parent = node->parent;
	node_data* temp;
	node_data* save_node = node;
	int save_key = -1;

	//If tree empty;
	if (node->parent == NULL && node->left == NULL && node->right == NULL)
	{
		node->key = -1;
		printf("the tree is empty\n");
		return;
	}
	//If there are two sons;
	if (node->left == NULL && node->right == NULL){
		//If its the right or left;
		if (node->parent->left == node){
			node->parent->left = NULL;
		}
		if (node->parent->right == node){
			node->parent->right = NULL;
		}
		//Free memory;
		free(node);
		return;
	}
	//If the node has no left child
	if (node->left == NULL && node->right != NULL){
		//If is the root;
		if (node->parent != NULL){
			node->parent->right = node->right;
			node->right->parent = node->parent;
			free(node);
			return;
		}
		//If not the root;
		else{
			save_node = save_node->right;
			while (save_node->left != NULL){
				save_node = save_node->left;
			}
			//Check the sons before connect new node;
			if (save_node->right == NULL){
				save_key = save_node->key;
				save_node->parent->left = NULL;
				free(save_node);
				node->key = save_key;
				return;
			}
			if (save_node->right != NULL){
				node->right->left = save_node->right;
				save_node->right->parent = node->right;
				node->key = save_node->key;
				free(save_node);
			}
			return;
		}
	}
	//If we run out of right;
	if (node->left != NULL && node->right == NULL){
		//If is the root;
		if (node->parent != NULL){
			node->parent->left = node->left;
			node->left->parent = node->parent;
			free(node);
			return;
		}
		//If it's not the root;
		else
		{
			while (save_node->left != NULL){
				save_node = save_node->left;
			}
			//Check the sons before connect new node;
			if (save_node->right == NULL)
			{
				save_key = save_node->key;
				save_node->parent->left = NULL;
				free(save_node);
				node->key = save_key;
				return;
			}
			if (save_node->right != NULL){
				while (save_node->right != NULL){
					save_node = save_node->right;
				}
				save_key = save_node->key;
				save_node->parent->right = save_node->left;
				free(save_node);
				node->key = save_key;
			}
			return;
		}
	}


	//If the node have two childrens
	if (node->left != NULL && node->right != NULL)
	{
		save_node = save_node->right;

		while (save_node->left != NULL){
			save_node = save_node->left;
		}
		if (save_node->right == NULL){
			save_key = save_node->key;
			save_node->parent->left = NULL;
			free(save_node);
			node->key = save_key;
			return;
		}

		if (save_node->right != NULL){
			node->right->left = save_node->right;
			save_node->right->parent = node->right;
			node->key = save_node->key;
			free(save_node);
		}
		return;
	}
}
#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node *root = NULL;
struct Node *previous = NULL;
struct Node *current = NULL;
void insert(int value);  //insert a node in the binary tree
void preorder_traversal(struct Node* root);
struct Node* deletion(struct Node* root, int value);
int height(struct Node *node);
int array[] = {30,20,40,10,25,35,45,5,15};
int preorder[9];
int j = -1;

int main()
{
	int i;
    for (i=0; i < 9; i++)
    {
        insert(array[i]);
    }
    root = deletion(root, 45);
    int hgt = height(root);
    int nodeData = 25;
    
    printf("The height of the tree is %d\n\n",hgt);
    printf("Level of node with data %d is %d\n\n", nodeData, getLevel(root, nodeData, 1));
    
    preorder_traversal(root);
    for(i = 0;i < 9;i++)
    {
    	
		printf("%d\t",preorder[i]);
	}

}

void insert(int value)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;

    if(root == NULL)
    {
        root = temp;
    }
    else
    {
    	current = root;
    	while(current != NULL)
    	{
    		if(value < current->data)
    		{
    			previous = current;
    			current = current->left;
			}
			else
			{
				previous = current;
				current = current->right;
			}
		}
		if(value < previous->data)
		{
			previous->left = temp;
		}
		else
		{
			previous->right = temp;
		}
	}

}
void preorder_traversal(struct Node* Root) {
    if(Root == NULL)
        return;
    else {
    	++j;
    	preorder[j] = Root->data;
        preorder_traversal(Root->left);
        preorder_traversal(Root->right);
    }
}
struct Node* minimum(struct Node* node)
{
    struct Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct Node* deletion(struct Node* root, int value)
{

    if (root == NULL) return root;

    if (value < root->data)
        root->left = deletion(root->left, value);

    else if (value > root->data)
        root->right = deletion(root->right, value);

    else
    {

        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }


        struct Node* temp = minimum(root->right);

        root->data = temp->data;

        root->right = deletion(root->right, temp->data);
    }
    return root;
}
int height(struct Node *node)
{
    if (node == NULL)
        return 0;
    else
    {
        int lDepth = height(node->left);
        int rDepth = height(node->right);
        if(lDepth > rDepth)
        	return lDepth + 1;
        else
        	return rDepth + 1;
    }
}
int getLevel(struct Node *node, int data, int level) {
    if (node == NULL)
        return 0;
    if (node->data == data)
        return level;
    int downlevel = getLevel(node->left, data, level+1);
    if (downlevel != 0)
        return downlevel;
    downlevel = getLevel(node->right, data, level+1);
    return downlevel;
}
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
     
#define N 100

//Binary search tree 
typedef struct nodebst
{
  int data;
  struct nodebst *right,*left;
}bst;
 
//AVL tree
typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
}avl;

//function declaration of bst
bst* insert(int val,bst* root);
bst* delete(int ,bst*);
bst* minbst(bst* root);
void preOrderbst(bst *root);

//function declaration of avl
int height(avl *start);
int max(int a, int b);
avl* newNode(int key);
int getBalance(avl *start);
avl *rightRotate(avl *y);
avl *leftRotate(avl *x);
avl* insertNode(avl* node, int key);
avl* minavl(avl* root);
avl* deleteNode(avl* root, int key);
void preOrderavl(avl *root);

//main function

int main()
{
	clock_t start, end;
    double timebstinsertion;
    double timebstdeletion;
	double timeavlinsertion;
	double timeavldeletion;
	int choice=1,val;
    
	bst* rootbst=NULL;
	avl* rootavl=NULL; 
	
	printf("Enter your choice:\n1.Insertion\n2.Deletion\n3.exit");
	scanf("%d",&choice);
	do
	{
		switch(choice)
		{
			case 1:
			{
				printf("Enter the element to be inserted");
				scanf("%d",&val);
				
				//time for bst insertion
				start = clock();
				rootbst = insert(val,rootbst);
				end = clock();
				timebstinsertion = ((double) (end - start)) / CLOCKS_PER_SEC;
				
				//print bst in preorder way
				preOrderbst(rootbst);
				
				//time for avl insertion
				start = clock();
				rootavl = insertNode(rootavl,val);
				end = clock();
				timeavlinsertion = ((double) (end - start)) / CLOCKS_PER_SEC;
				
				//print avl in preorder way
				preOrderavl(rootavl);
				
				printf("Time taken for BST insertion is %f ",timebstinsertion);
				printf("Time taken for AVL insertion is %f ",timeavlinsertion);
				
				break;
			}
			case 2:
			{
				printf("Enter the element to be Deleted");
				scanf("%d",&val);
				
				//time for bst insertion
				start = clock();
				rootbst = delete(val,rootbst);
				end = clock();
				timebstdeletion = ((double) (end - start)) / CLOCKS_PER_SEC;
				
				//print bst in preorder way
				preOrderbst(rootbst);
				
				//time for avl insertion
				start = clock();
				rootavl = deleteNode(rootavl,val);
				end = clock();
				timeavldeletion = ((double) (end - start)) / CLOCKS_PER_SEC;
				
				//print avl in preorder way
				preOrderavl(rootavl);
				
				printf("Time taken for BST insertion is %f ",timebstinsertion);
				printf("Time taken for AVL insertion is %f ",timeavlinsertion);
				
				break;
			}
			default:
				printf("invalid choice");
				exit(0);
					
		}
		printf("Enter your choice:\n1.Insertion\n2.Deletion\n3.exit");
		scanf("%d",&choice);
	}while(choice);
}

//Insertion function for bst
bst* insert(int val,bst* root)
{
  //insertSteps++;
  if(root==NULL)
  {
    bst* new_node=(bst*)malloc(sizeof(N));
    new_node->data=val;
    new_node->left=NULL;
    new_node->right=NULL;
    root=new_node;
  }
  else
  {
    if(val > root->data)
      root->right=insert(val,root->right);
    else if(val < root->data)
      root->left=insert(val,root->left);
  }
  return root;
}

//Deletion function in bst
bst* delete(int val,bst* root)
{
  //deleteSteps++;
  if(root==NULL)
    return NULL;
  else if(root->data > val)
    root->left = delete(val,root->left);
  else if(root->data < val)
    root->right = delete(val,root->right);
  else
  {
    if(root->left==NULL)
    {
      bst* temp=root->right;
      free(root);
      return temp;
    }
    else if(root->right==NULL)
    {
      bst* temp=root->left;
      free(root);
      return temp;
    }
    else if(root->right!=NULL && root->left!=NULL)
    {
      bst* temp=minbst(root->right);
      root->data=temp->data;
      root->right=delete(temp->data,root->right);
    }
    return root;
  }
}

//find min element in a bst
bst* minbst(bst* root)
{
  bst* temp;
  temp=minbst(root->left);
  return temp;
}

//preorder traversal bst
void preOrderbst(bst *root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preOrderbst(root->left);
        preOrderbst(root->right);
    }
}

// A utility function to get height of the AVL tree
int height(avl *start)
{
    if (start == NULL)
        return 0;
    return start->height;
}

//max among two elements 
int max(int a, int b)
{
    return (a > b)? a : b;
}

//create a new node in AVL tree and initializes left & right pointers to NULL
avl* newNode(int key)
{
    avl* node = (avl*)malloc(sizeof(avl));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

// Get Balance factor of node N
int getBalance(avl *start)
{
    if (start == NULL)
        return 0;
    return height(start->left) - height(start->right);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
avl *rightRotate(avl *y)
{
    avl *x = y->left;
    avl *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
avl *leftRotate(avl *x)
{
    avl *y = x->right;
    avl *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

//Insertion function in avl tree
avl* insertNode(avl* node, int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left  = insertNode(node->left, key);
    else
        node->right = insertNode(node->right, key);

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

//minimum element in avl tree
avl* minavl(avl* root)
{
  avl* temp;
  temp=minavl(root->left);
  return temp;
}

//Deletion fumction in avl tree
avl* deleteNode(avl* root, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;

            // No child case
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            avl* temp = minavl(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrderavl(avl *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrderavl(root->left);
        preOrderavl(root->right);
    }
}


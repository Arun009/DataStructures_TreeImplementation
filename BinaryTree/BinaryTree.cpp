#include "BinaryTree.h"



BinaryTree::BinaryTree()					// Constructor
{
	root = nullptr;							// Initialize root node to nullptr while creating the object
}


BinaryTree::~BinaryTree()					// Destructor
{
	destroyTree(root);						// Recursive funstion to delete all the nodes of the tree
}

/*The function destroy_tree goes to the bottom of each part of the tree, that is, searching while there is a non-null node, 
deletes that leaf, and then it works its way back up. The function deletes the leftmost node, 
then the right child node from the leftmost node's parent node, then it deletes the parent node, 
then works its way back to deleting the other child node of the parent of the node it just deleted, 
and it continues this deletion working its way up to the node of the tree upon which delete_tree was originally called.*/
void BinaryTree::destroyTree(node *leaf)	// Recursive function that will delete all nodes of the tree
{											// The function recursively destroy the tree, node by node, from the bottom up
	if (leaf != nullptr)					// Check is the node passed is null
	{
		destroyTree(leaf->left);			// Calling the function recursively to traverse through the left nodes
		destroyTree(leaf->right);			// Calling the function recursively to traverse through the right nodes
		delete leaf;						// Delete the leaf once you reach an end
	}
}

/*This public version of the insert function takes care of the case where the root has not been initialized by allocating the memory for it and 
setting both child nodes to NULL and setting the node_value to the value to be inserted. 
If the root node already exists, insert is called with the root node as the initial node of the function, and the recursive insert function takes over.*/
void BinaryTree::insert(int value)
{
	if (root == nullptr)				// If root is nullptr
	{
		root = new node;				// Create new node and set it as root
		root->node_value = value;		// Set the value of the root node
		root->left = nullptr;			// Set the left and right pointers to nullptr
		root->right = nullptr;
	}
	else								// If tree already contains nodes
		insert(value, root);			// Call the recursive insert function with value to be inserted and root as parameters		
}

/*This recursive insert function searches, moving down the tree of children nodes, following the prescribed rules, 
left for a lower value to be inserted and right for a greater value, 
until it finds an empty node which it creates using the 'new' keyword and initializes with the key value while setting the new node's child node pointers to NULL. 
After creating the new node, the insert function will no longer call itself.*/
void BinaryTree::insert(int value, node *leaf)
{
	if (value < leaf->node_value)			// Check if the value to be inserted is less than the value in the leaf
	{
		if (leaf->left != nullptr)			// If there are nodes to the left of the leaf node
			insert(value, leaf->left);		// Call the recursive function with value and the node pointed by left as the parameters
		else								// If there are no nodes to the left of the leaf node
		{
			leaf->left = new node;			// Create new node at the left of the leaf node	
			leaf->left->node_value = value;	// Set the value to the node_value of the newly created node
			leaf->left->left = nullptr;		// Set the left and right of the newly created node to nullptr
			leaf->left->right = nullptr;
		}
	}
	else if (value >= leaf->node_value)		// Check if the value to be inserted is greater than the value in the leaf
	{
		if (leaf->right != nullptr)			// If there are nodes to the right of the leaf node
			insert(value, leaf->right);		// Call the recursive function with value and the node pointed by right as the parameters
		else								// If there are no nodes to the right of the leaf node
		{
			leaf->right = new node;			// Create new node at the right of the leaf node	
			leaf->right->node_value = value;// Set the value to the node_value of the newly created node
			leaf->right->left = nullptr;	// Set the left and right of the newly created node to nullptr
			leaf->right->right = nullptr;
		}
	}
}

/*The public version of the search function is used to set off the search recursion at the root node, 
keeping it from being necessary for the user to have access to the root node.*/
node* BinaryTree::search(int data)
{
	return search(data, root);
}

/*This search function recursively moves down the tree until it either reaches a node with a key value equal to the value 
for which the function is searching or until the function reaches an uninitialized node, 
meaning that the value being searched for is not stored in the binary tree. 
It returns a pointer to the node to the previous instance of the function which called it, 
handing the pointer back up to the search function accessible outside the class.*/
node* BinaryTree::search(int data, node *leaf)
{
	if (leaf != nullptr)				// Check if the leaf is not null
	{
		if (data == leaf->node_value)	// Check if the data equals the node_value of the leaf
			return leaf;				// If yes, return the leaf
		if (data < leaf->node_value)	// Check if the data is less than the node_value of the leaf
			search(data, leaf->left);	// If yes call the resursive search function with data and the node at the left of the leaf as the parameters
		else							// Check if the data is greater than or equal to the node_value of the leaf
			search(data, leaf->right);	// Call the recursive search function with the data and the node at the right of the leaf as the parameters
	}
	else
		return nullptr;					// If searched data not in the tree, return null
}

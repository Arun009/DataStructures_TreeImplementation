#include <iostream>
using namespace std;
#include "BinaryTree.h"



BinaryTree::BinaryTree()					// Constructor
{
	root = nullptr;							// Initialize root node to nullptr while creating the object
}


BinaryTree::~BinaryTree()					// Destructor
{
	destroyTree(root);						// Calls the Recursive funstion to delete all the nodes of the tree
}

/*
	Consider this example tree for reference

					10
				   /  \
				 6     14
				/ \    / \
			   5   8  11  18
*/

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

void BinaryTree::display()					// Displays the tree using Preorder, Inorder and Postorder Traversals techniques. 
{
	cout << "Preorder Traversal" << endl;
	cout << "------------------" << endl;
	preorderTraversal(root);
	cout << endl << endl;

	cout << "Inorder Traversal" << endl;
	cout << "-----------------" << endl;
	inorderTraversal(root);
	cout << endl << endl;

	cout << "Postorder Traversal" << endl;
	cout << "-------------------" << endl;
	postorderTraversal(root);
	cout << endl << endl;
}

/* Traverses from the root node while displaying the node value first while traversing, and then moves to the left subtree, 
displays the node value, moves to the next left subtree and on until there are no more nodes in the left subtree, the method then traverses to the right subtree
This will display the earlier mentioned tree in the below form:
10 6 5 8 14 11 18
*/
void BinaryTree::preorderTraversal(node *leaf)
{
	if (root == nullptr)
		cout << "Nothing to Display";
	else {
		if (leaf != nullptr)
		{
			cout << leaf->node_value << " ";		// Display the node value first
			preorderTraversal(leaf->left);			// Traverse the tree to the left recursively
			preorderTraversal(leaf->right);			// Traverse the tree to the right recursively
		}
	}
}

/* Traverses the tree in such a way that left most node value is displayed, its parent and then the node to the right
This will display the earlier mentioned tree in the below form:
5 6 8 10 11 14 18
*/
void BinaryTree::inorderTraversal(node *leaf)
{
	if (root == nullptr)
		cout << "Nothing to Display";
	else {
		if (leaf != nullptr)
		{
			inorderTraversal(leaf->left);			// Traverse the tree to the left recursively
			cout << leaf->node_value << " ";		// Display the node value
			inorderTraversal(leaf->right);			// // Traverse the tree to the right recursively
		}
	}
}

/* Traverses the tree in such a way that the left and right nodes of the leftmost parent is diplayed first, then its parent node and so on upto the root node
This will display the earlier mentioned tree in the below form:
5 8 6 11 18 14 10
*/
void BinaryTree::postorderTraversal(node *leaf)
{
	if (root == nullptr)
		cout << "Nothing to Display";
	else {
		if (leaf != nullptr)
		{
			postorderTraversal(leaf->left);			// Traverse the tree to the left recursively
			postorderTraversal(leaf->right);		// Traverse the tree to the right recursively
			cout << leaf->node_value << " ";		// Display the node value
		}
	}
}

void BinaryTree::destroy()		// To manually destroy the tree
{
	destroyTree(root);			// Calls the recursive function that deletes all the nodes in the tree
}

void BinaryTree::deleteValue(int value)		// To manually delete a node from the tree
{
	deleteValue(value, root);				// Calls the function that deletes the node from the tree
}


/*Deletion is the most complex in a binary tree. The algorithm for deletion is as follows:
1. Read the data to be deleted.
2. Find the node where the data exist. Lets call it leaf node.
	If node not found, print "node not found" and exit
3. If the node to be deleted has no subtree
	* Assign the parents left or right node with null whichever points to the node
	* Delete the node that contains the data item
4. If the node to be deleted has only one subtree
	* Move its child node up to take its place
	* Delete the node that contains the data item
5. If the node to be deleted has two subtrees
	* Set the information of node to be deleted by the information of leftmost node of right most subtree of the node to be deleted.
*/
void BinaryTree::deleteValue(int value, node *leaf)				// To manually delete a node from the tree
{
	node *deleteNode;											// Pointer to the node which is to be deleted
	node *parent = root;										// We need a pointer to the parent of the leaf node which is to be deleted,
																// because we need to set the parents left and right properly if one of its child is deleted.
	if (root == nullptr)
		cout << "Tree is empty" << endl;
	else {														
		while (leaf != nullptr && leaf->node_value != value)	// This while loop traverses the tree until leaf points to the node that is to be deleted
		{
			parent = leaf;										// After the execution of while loop, parent will be pointing to the parent node of the leaf 
			if (value < leaf->node_value)						// and leaf will be pointing to the node to be deleted.
				leaf = leaf->left;
			else
				leaf = leaf->right;
		}
	}

	deleteNode = leaf;											// Point the deleteNode to the leaf node for deletion at the end of this method.

	if (leaf == nullptr)
		cout << "Node does not exist in the tree" << endl;
	else if(leaf == root)										// Case where leaf or the node to be deleted is the root
	{
		if (leaf->left == nullptr && leaf->right == nullptr)	// If the leaf node does not have any child nodes (only one node in the whole tree)
		{
			root = nullptr;										// Set the root to nullptr
		}
		else if (leaf->left == nullptr)							// If the leaf have no left subtree
		{
			root = leaf->right;									// Set the root to the child node at the right subtree
		}
		else if (leaf->right == nullptr)						// If the leaf have no right subtree
		{
			root = leaf->left;									// Set the root to the child node at the left subtree
		}
		else													// If the leaf has both left and right sub trees
		{
			node *temp = leaf->right;							// We need to traverse to the left most node of the right most subtree of the node to be deleted, point temp to the right subtree
			while (temp->left != nullptr)						// Then traverse to the left most node
			{
				leaf = temp;									// After the execution of while loop, leaf points to the parent of the left most node (with respect to the right child node of the node to be deleted)
				temp = temp->left;								// temp points to the left most node (with respect to the right child node of the node to be deleted)
																// The above two happens only if there is a left subtree for the right child of the node to be deleted
			}													// If there is no left subtree for the child of the node to be deleted temp will be equal to leaf->right
			if (temp != leaf->right)							// For the cases where there is a left subtree for the right child of the node to be deleted
			{
				leaf->left = temp->right;						// We set the parent, leaf->left to point to the left most (temp) nodes right (with respect to the right child node of the node to be deleted)
				temp->right = root->right;						// We set the temp (or left most node : with respect to the right child node of the node to be deleted) nodes right to point to the roots right as temp will be the new root
			}
			temp->left = root->left;							// We set the temp (or left most node : with respect to the right child node of the node to be deleted) nodes left to point to the roots left
			root = temp;										// Finally set temp as root
		}
	}
	else														// If the node to be deleted is any other node other than root
	{
		if (leaf->left == nullptr && leaf->right == nullptr)	// If the leaf node does not have any child nodes
		{
			if (parent->left == leaf)							// If the leaf node is the left child of the parent node
				parent->left = nullptr;							// Set the left of parent to nullptr
			else												// Else
				parent->right = nullptr;						// Set the right of parent to nullptr
			leaf = nullptr;
		}
		else if (leaf->left == nullptr)							// If leaf node does not have left subtree
		{
			if (parent->left == leaf)							// If the leaf node is the left child of the parent node
				parent->left = leaf->right;						// Set the left of parent to leafs right
			else												// Else
				parent->right = leaf->right;					// Set the right of parent to leafs right
		}
		else if (leaf->right == nullptr)						// If leaf node does not have right subtree (same like above if)
		{
			if (parent->left == leaf)
				parent->left = leaf->left;
			else
				parent->right = leaf->left;
		}
		else													// If the leaf node have both left and right subtrees
		{
			node *toBeDeletedNode = leaf;						// Set the information of node to be deleted by the information of leftmost node of right most subtree of the node to be deleted. 
			node *temp = leaf->right;							// Same as like we did for root node with both subtrees.
			while (temp->left != nullptr)
			{
				leaf = temp;
				temp = temp->left;
			}
			if (temp != leaf->right)
			{
				leaf->left = temp->right;
				temp->right = toBeDeletedNode->right;
			}
			temp->left = toBeDeletedNode->left;
			if (parent->left == toBeDeletedNode)				// We also need to set the parents left and right accordingly
				parent->left = temp;
			else
				parent->right = temp;
			toBeDeletedNode = temp;
		}
	}
	delete deleteNode;											// Finally delete the node
}
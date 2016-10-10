#pragma once

struct node
{
	int node_value;
	node *left;
	node *right;
};

class BinaryTree
{
private:
	node *root;
	void insert(int value, node *leaf);
	node* search(int data, node *leaf);
	void destroyTree(node *leaf);
public:
	BinaryTree();
	~BinaryTree();
	void insert(int value);
	node* search(int data);
};


#include <iostream>
using namespace std;
#include "BinaryTree.h"

int main() {
	cout << "Binary Tree Implementation" << endl;
	cout << "==========================" << endl;

	int value;
	BinaryTree btree;
	node *leafNode = nullptr;
	int choice = -1;
	do
	{
		cout << "1. Insert" << endl;
		cout << "2. Search" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Display" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;
		if (choice > 5 || choice < 1)
			cout << "Invalid Choice" << endl;

		switch (choice)
		{
			case 1:
				cout << "Enter the value to be inserted" << endl;
				cin >> value;
				btree.insert(value);
				break;

			case 2:
				cout << "Enter the value to be searched" << endl;
				cin >> value;
				leafNode = btree.search(value);
				if (leafNode == nullptr)
					cout << "Value does not exist in the Tree" << endl;
				else
					cout << leafNode->node_value << " exists in the Tree" << endl;
				break;

			case 3:
				cout << "Enter the value to be deleted" << endl;
				cin >> value;
				btree.deleteValue(value);
				break;

			case 4:
				btree.display();
				break;

			case 5:
				btree.destroy();
				exit(0);
		}
	} while (choice != 6);

	getchar();
	return 0;
}
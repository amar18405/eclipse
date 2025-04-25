#include <iostream>

using namespace std;

class avl_node
{
	string word, meaning;
	avl_node *left, *right;

public:
	avl_node()
	{
		left = NULL;
		right = NULL;
	}

	friend class avl_tree;
};

class avl_tree
{
	avl_node *root;

public:
	avl_tree()
	{
		root = NULL;
	}

	int height(avl_node *);
	int diff(avl_node *);
	avl_node *ll_rotation(avl_node *);
	avl_node *rr_rotation(avl_node *);
	avl_node *lr_rotation(avl_node *);
	avl_node *rl_rotation(avl_node *);
	avl_node *balance(avl_node *);
	void insert();
	avl_node *insert(avl_node *, avl_node *);
	void preorder();
	void preorder(avl_node *);
	void inorder();
	void inorder(avl_node *);
	void postorder();
	void postorder(avl_node *);
};

int avl_tree::height(avl_node *temp)
{
	int h = 0;
	if (temp != NULL) {
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

int avl_tree::diff(avl_node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

avl_node *avl_tree::ll_rotation(avl_node *parent)
{
	avl_node *temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

avl_node *avl_tree::rr_rotation(avl_node *parent)
{
	avl_node *temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

avl_node *avl_tree::lr_rotation(avl_node *parent)
{
	avl_node *temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

avl_node *avl_tree::rl_rotation(avl_node *parent)
{
	avl_node *temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

avl_node *avl_tree::balance(avl_node *temp)
{
	int bal_factor = diff(temp);
	cout << "The balance factor of " << temp->word << " is " << bal_factor << "." << endl;
	if (bal_factor > 1) {
		if (diff(temp->left) > 0) {
			temp = ll_rotation(temp);
			cout << "LL rotation has taken place." << endl;
		} else {
			temp = lr_rotation(temp);
			cout << "LR rotation has taken place." << endl;
		}
	} else if (bal_factor < -1) {
		if (diff(temp->right) > 0) {
			temp = rl_rotation(temp);
			cout << "RL rotation has taken place." << endl;
		} else {
			temp = rr_rotation(temp);
			cout << "RR rotation has taken place." << endl;
		}
	}
	return temp;
}

void avl_tree::insert()
{
	char ch;
	do {
		avl_node *temp = new avl_node;
		cout << endl
			 << "Enter new word: ";
		cin >> temp->word;
		cout << "Enter meaning: ";
		cin >> temp->meaning;

		root = insert(root, temp);

		cout << endl
			 << "Do you want to insert another node? (Y/n): ";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}

avl_node *avl_tree::insert(avl_node *root, avl_node *temp)
{
	if (root == NULL) {
		root = new avl_node;
		root->word = temp->word;
		root->meaning = temp->meaning;
		cout << "Word added successfully." << endl
			 << endl;
		return root;
	} else if (temp->word < root->word) {
		root->left = insert(root->left, temp);
		root = balance(root);
	} else if (temp->word > root->word) {
		root->right = insert(root->right, temp);
		root = balance(root);
	} else {
		cout << endl
			 << "Word already exists." << endl;
	}
	return root;
}

void avl_tree::preorder()
{
	cout << endl
		 << "Preorder traversal:" << endl
		 << endl;
	preorder(root);
}

void avl_tree::preorder(avl_node *root)
{
	if (root != NULL) {
		cout << root->word << ":\t" << root->meaning << endl;
		preorder(root->left);
		preorder(root->right);
	}
}

void avl_tree::inorder()
{
	cout << endl
		 << "Inorder traversal:" << endl
		 << endl;
	inorder(root);
}

void avl_tree::inorder(avl_node *root)
{
	if (root != NULL) {
		inorder(root->left);
		cout << root->word << ":\t" << root->meaning << endl;
		inorder(root->right);
	}
}

void avl_tree::postorder()
{
	cout << endl
		 << "Postorder traversal:" << endl
		 << endl;
	postorder(root);
}

void avl_tree::postorder(avl_node *root)
{
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		cout << root->word << ":\t" << root->meaning << endl;
	}
}

int main()
{
	avl_tree tree;
	int choice;
	while (true) {
		cout << endl
			 << "Choose an operation:" << endl
			 << "1. Insert a node" << endl
			 << "2. Preorder traversal" << endl
			 << "3. Inorder traversal" << endl
			 << "4. Postorder traversal" << endl
			 << "5. Exit" << endl
			 << endl
			 << "Your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			tree.insert();
			break;

		case 2:
			tree.preorder();
			break;

		case 3:
			tree.inorder();
			break;

		case 4:
			tree.postorder();
			break;

		case 5:
			cout << endl
				 << "Exiting..." << endl
				 << endl;
			return 0;

		default:
			cout << endl
				 << "Invalid input! Try again." << endl
				 << endl;
		}
	}
}
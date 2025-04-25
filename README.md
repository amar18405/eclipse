#include <iostream>
#define MAX 10

using namespace std;

class user
{
	long long mobile;
	string name;
	double bill_amt;
	
public:
	user()
	{
		mobile = 1234567890;
		name = "john doe";
		bill_amt = 0;
	}
	
	friend class record;
};

user b[MAX];

class record
{
	user u[MAX];
	
public:
    int size;

	record()
    {
        size = 0;
    }
	
	void accept();
	void display();
	void adjust(int, int);
	void heapsort();
	int partition(int, int);
	void quicksort(int, int);
	void linsearch(long long);
	void binsearch(long long);
	int bin_rec(int, int, long long);
	void binsearch(int, int, long long);
};

void record::accept()
{
	user temp;
	char choice = 'y';
	while ((choice == 'y' || choice == 'Y') && (size < MAX)) {
		cout << endl
			 << "Enter details for user " << size + 1 << ":" << endl
			 << "Enter mobile number: ";
		cin >> temp.mobile;
		cout << "Enter name: ";
		cin >> temp.name;
		cout << "Enter bill amount: ";
		cin >> temp.bill_amt;
		u[size++] = temp;
		
		cout << endl
			 << "Number of users: " << size << endl
			 << endl;
        
        if (size >= MAX) {
            cout << "Maximum number of users reached. You cannot add more." << endl;
            break;
        }

		cout << "Do you want to add more users? (Y/n): ";
		cin >> choice;
	}
}

void record::display()
{
	cout << endl
		 << "User records:" << endl
		 << endl
		 << "Name\tMobile\t\tBill Amount" << endl;
	for (int i = 0; i < size; i++) {
		cout << u[i].name << "\t" << u[i].mobile << "\t" << u[i].bill_amt << endl;
	}
	cout << endl;
}

void record::adjust(int n, int i)
{
	while ((2 * i + 1) <= n) {
		int j = 2 * i + 1;
		if (((j + 1) <= n) && (u[j + 1].bill_amt > u[j].bill_amt))
			j++;
		if (u[i].bill_amt >= u[j].bill_amt)
			break;
		else {
			user temp = u[i];
			u[i] = u[j];
			u[j] = temp;
			i = j;
		}
	}
}

void record::heapsort()
{
	int n = size, pass = 1;
	for (int i = (n / 2) - 1; i >= 0; i--)
		adjust(n - 1, i);
		
	while (n > 0) {
		cout << endl
			 << "Values after " << pass++ << "th pass: ";
		for (int i = 0; i < size; i++)
			cout << u[i].bill_amt << "\t";
		cout << endl;
		user t = u[0];
		u[0] = u[n - 1];
		u[n - 1] = t;
		n--;
		adjust(n - 1, 0);
	}

    cout << endl
         << "User records have been sorted." << endl
         << endl;
}

int record::partition(int p, int r)
{
	int i = p - 1;
	user temp, x = u[r];
	for (int j = p; j < r; j++)
		if (u[j].mobile <= x.mobile) {
			temp = u[++i];
			u[i] = u[j];
			u[j] = temp;
		}
	temp = u[++i];
	u[i] = u[r];
	u[r] = temp;
	return i;
}


void record::quicksort(int p, int r)
{
	if (p < r) {
		int q = partition(p, r);
		cout << endl
			 << "Pivot element: " << u[q].mobile << endl
			 << "Values after partitioning: ";
		for (int i = 0; i < size; i++)
			cout << u[i].mobile << "\t";
		quicksort(p, q - 1);
		quicksort(q + 1, r);
	}
}

void record::linsearch(long long key)
{
	int i;
	for (i = 0; i < size; i++) {
		if (u[i].mobile == key)
		{
			cout << endl
				 << "Details found:" << endl
				 << endl
				 << "Mobile number: " << u[i].mobile << endl
				 << "Name: " << u[i].name << endl
				 << "Bill amount: " << u[i].bill_amt << endl;
			break;
		}
	}
	
	if (i >= size)
		cout << endl
			 << "No data found for given mobile number." << endl;
}

void record::binsearch(long long key)
{
	int lo = 0, hi = size, mid;
	while (lo <= hi) {
		mid = (lo + hi) / 2;
		if (u[mid].mobile == key) {
			cout << endl
				 << "Details found:" << endl
				 << endl
				 << "Mobile number: " << u[mid].mobile << endl
				 << "Name: " << u[mid].name << endl
				 << "Bill amount: " << u[mid].bill_amt << endl;
			return;
		} else if (key < u[mid].mobile)
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	cout << endl
		 << "Data not found for given mobile number." << endl;
}

int record::bin_rec(int lo, int hi, long long key)
{
	if (lo <= hi)
	{
		int mid = (lo + hi) / 2;
		if (u[mid].mobile == key)
			return mid;
		else if (key < u[mid].mobile)
			return bin_rec(lo, mid - 1, key);
		else
			return bin_rec(mid + 1, hi, key);
	}
	return -1;
}

void record::binsearch(int lo, int hi, long long key)
{
	int pos = bin_rec(lo, hi, key);
	if (pos != -1)
		cout << endl
			 << "Details found:" << endl
			 << endl
			 << "Mobile number: " << u[pos].mobile << endl
			 << "Name: " << u[pos].name << endl
			 << "Bill amount: " << u[pos].bill_amt << endl;
	else
		cout << endl
			 << "Data not found for given mobile number." << endl;
}

int main()
{
	record r;
	int choice;
	long long key;
	cout << endl
		 << "Start by adding records:" << endl;
	r.accept();
	r.display();
	
	while (true) {
		cout << endl
			 << "Select operation:" << endl
			 << "1 - Heap Sort (ascending bill amount)" << endl
			 << "2 - Quick Sort (ascending mobile number)" << endl
			 << "3 - Linear Search" << endl
			 << "4 - Non-recursive Binary Search" << endl
			 << "5 - Recursive Binary Search" << endl
			 << "6 - Exit" << endl
			 << endl
			 << "Your choice: ";
		cin >> choice;
		
		switch (choice) {
		case 1:
			r.heapsort();
			r.display();
			break;
			
		case 2:
			r.quicksort(0, r.size - 1);
			r.display();
			break;
			
		case 3:
			cout << endl
				 << "Enter mobile number to search: ";
			cin >> key;
			r.linsearch(key);
			break;
			
		case 4:
			cout << endl
				 << "Enter mobile number to search: ";
			cin >> key;
			r.binsearch(key);
			break;
			
		case 5:
			cout << endl
				 << "Enter mobile number to search: ";
			cin >> key;
			r.binsearch(0, r.size - 1, key);
			break;
			
		case 6:
			cout << endl
				 << "You have chosen to exit." << endl
				 << "Bye bye." << endl
				 << endl;
			return 0;
			
		default:
			cout << endl
				 << "Invalid choice! Try again." << endl;
		}
	}
}


-----------------------------------------------------------------------------------------------------------------------------------

#include <iostream>

using namespace std;

class gnode
{
	int id;
	string name;
	gnode *next;
	friend class graph;
	friend class stack;
	friend class queue;
};

class graph
{
	gnode *head[20];
	int n;
	int visited[20];
	
public:
	graph()
	{
		n = 0;
		char choice;
		
		do {
			cout << endl
				 << "Enter name for user " << n << ": ";
			head[n] = new gnode();
			cin >> head[n]->name;
			head[n]->id = n;
			head[n]->next = NULL;
			n++;
			
			if (n >= 20) {
				cout << endl
					 << "Maximum limit reached! You cannot add more users." << endl;
				break;
			}
			
			cout << endl
				 << "Do you want to add another user? (Y/n): ";
			cin >> choice;
		} while (choice == 'Y' || choice == 'y');
	}
	
	void create_adj_list();
	void display();
	void dfs();
	void dfs_r(int);
	void dfs(int);
	void bfs(int);
};

class stack
{
	int stk[20];
	int top;
	
public:
	stack()
	{
		top = -1;
	}
	
	int isempty();
	void push(int);
	int pop();
	friend class graph;
};

class queue
{
	int arr[20];
	int front;
	int rear;
	
public:
	queue()
	{
		front = -1;
		rear = -1;
	}
	
	int isempty();
	void insert(int);
	int del();
	friend class graph;
};

void graph::create_adj_list()
{
	int v;
	char ch;
	for (int i = 0; i < n; i++) {
		gnode *temp = head[i];
		do {
			cout << endl
				 << "Enter user id for connection of (" << head[i]->id << ", " << head[i]->name << "): ";
			cin >> v;
			if (v == i)
				cout << endl
					 << "Self loops are not allowed!" << endl;
			else {
				gnode *curr = new gnode();
				curr->next = NULL;
				curr->id = v;
				curr->name = head[v]->name;
				temp->next = curr;
				temp = temp->next;
			}
			
			cout << endl
				 << "Do you want to add another connection for " << head[i]->name << "? (Y/n): ";
			cin >> ch;
		} while (ch == 'Y' || ch == 'y');
	}
}

void graph::display()
{
	cout << endl
		 << "Displaying adjacency lists for each node:" << endl;
	for (int i = 0; i < n; i++) {
		gnode *curr = head[i];
		cout << endl
			 << "Connections of user (" << curr->id << 	", " << curr->name << "):\t";
		curr = curr->next;
		if (curr != NULL)
			while (curr != NULL) {
				cout << "(" << curr->id << ", " << curr->name << ")";
				if (curr->next != NULL)
					cout << ", ";
				else
					cout << ";";
				curr = curr->next;
			}
		else
			cout << "No connections.";
	}
	cout << endl
		 << endl;
}

void graph::dfs()
{
	int v;
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	cout << endl
		 << "Enter starting user id: ";
	cin >> v;
	cout << endl
		 << "Depth first traversal starting at (" << v << ", " << head[v]->name << "):" << endl;
	dfs_r(v);
	cout << endl
		 << endl;
}

void graph::dfs_r(int v)
{
	cout << "(" << v << ", " << head[v]->name << ")\t";
	visited[v] = 1;
	gnode *temp = head[v]->next;
	while (temp != NULL) {
		if (!visited[temp->id])
			dfs_r(temp->id);
		temp = temp->next;
	}
}

int stack::isempty()
{
	return top == -1;
}

void stack::push(int item)
{
	if (top == 19) {
		cout << endl
			 << "Stack overflow" << endl;
		return;
	}
	stk[++top] = item;
}

int stack::pop()
{
	if (isempty()) {
		cout << endl
			 << "Stack underflow" << endl;
		return -1;
	}
	
	return stk[top--];
}

int queue::isempty()
{
	return rear == front;
}

void queue::insert(int item)
{
	if (rear == 19) {
		cout << endl
			 << "Queue overflow" << endl;
		return;
	}
	arr[++rear] = item;
}

int queue::del()
{
	if (isempty()) {
		cout << endl
			 << "Queue underflow" << endl;
		return -1;
	}
	return arr[++front];
}

void graph::dfs(int v)
{
	stack s;
	cout << endl
		 << "Depth first traversal starting at (" << v << ", " << head[v]->name << "):" << endl;
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	
	s.push(v);
	visited[v] = 1;
	while (!s.isempty()) {
		v = s.pop();
		cout << "(" << v << ", " << head[v]->name << ")\t";
		for (gnode *temp = head[v]->next; temp != NULL; temp = temp->next)
			if (!visited[temp->id]) {
				s.push(temp->id);
				visited[temp->id] = 1;
			}
	}
	cout << endl;
}

void graph::bfs(int v)
{
	queue q;
	cout << endl
		 << "Breadth first traversal strting at (" << v << ", " << head[v]->name << "):" << endl;
	for (int i = 0; i < n; i++)
		visited[i] = 0;
		
	q.insert(v);
	visited[v] = 1;
	while (!q.isempty()) {
		v = q.del();
		cout << "(" << v << ", " << head[v]->name << ")\t";
		for (gnode *temp = head[v]->next; temp != NULL; temp = temp->next)
			if (!visited[temp->id]) {
				q.insert(temp->id);
				visited[temp->id] = 1;
			}
	}
	cout << endl;
}

int main()
{
	cout << endl
		 << "Start by adding users: " << endl;
	graph g;
	cout << endl
		 << "Add connections: " << endl;
	g.create_adj_list();
	
	int choice;
	int v;
	while (true) {
		cout << endl
			 << "Choose an operation:" << endl
			 << "1 - Display adjacency list" << endl
			 << "2 - Depth First Traversal (Recursive)" << endl
			 << "3 - Depth First Traversal (Non - Recursive)" << endl
			 << "4 - Breadth First Traversal" << endl
			 << "5 - Exit" << endl
			 << endl
			 << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			g.display();
			break;
		case 2:
			g.dfs();
			break;
		case 3:
			cout << endl
				 << "Enter starting user id: ";
			cin >> v;
			g.dfs(v);
			break;
		case 4:
			cout << endl
				 << "Enter starting user id: ";
			cin >> v;
			g.bfs(v);
			break;
		case 5:
			cout << endl
				 << "You have chosen to exit. Bye-bye." << endl
				 << endl;
			return 0;
		default:
			cout << endl
				 << "Invalid choice! Try again." << endl;
		}
	}
}

---------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>

using namespace std;

class graph
{
	int cost[20][20];
	int tcities;
	
public:
	graph()
	{
		cout << endl
			 << "Enter the number of cities: ";
		cin >> tcities;
		char choice;
		
		for (int i = 0; i < tcities; i++)
			for (int j = 0; j < tcities; j++)
				cost[i][j] = 999;
	}
	
	void create_adj_matrix();
	void display();
	int prims(int);
};

void graph::create_adj_matrix()
{
	char choice;
	for (int i = 0; i < tcities; i++)
		for (int j = 0; j < tcities; j++)
			if (i != j && cost[i][j] == 999) {
				cout << endl
					 << "Is there a connection between city " << i << " and " << j << "? (Y/n): ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y') {
					cout << "Enter the cost of connection: ";
					cin >> cost[i][j];
					cost[j][i] = cost[i][j];
				}
			}
}

void graph::display()
{
	cout << endl
		 << "Cost adjaceny matrix for the cities: " << endl;
	
	for (int i = 0; i < tcities; i++) {
		for (int j = 0; j < tcities; j++) {
			if (cost[i][j] != 999)
				cout << "\t" << cost[i][j];
			else
				cout << "\t999";
		}
		cout << endl;
	}
	cout << endl;
}

int graph::prims(int start_v)
{
	int st[tcities - 1][3];
	int nearest[tcities];
	int mincost = 0;
	int r = 0;
	int j = 0;
	
	nearest[start_v] = -1;
	for (int i = 0; i < tcities; i++)
		if (i != start_v)
			nearest[i] = start_v;
			
	for (int i = 1; i < tcities; i++) {
		int min = 999;
		for (int k = 0; k < tcities; k++)
			if ((nearest[k] != -1) && (cost[k][nearest[k]] < min)) {
				j = k;
				min = cost[k][nearest[k]];
			}
		st[r][0] = nearest[j];
		st[r][1] = j;
		st[r][2] = min;
		r++;
		
		mincost += cost[j][nearest[j]];
		nearest[j] = -1;
		
		for (int k = 0; k < tcities; k++)
			if ((nearest[k] != -1) && (cost[k][nearest[k]] > cost[k][j]))
				nearest[k] = j;
	}
	
	cout << endl
		 << "Minimum cost spanning tree:" << endl;
	for (int x = 0; x < tcities - 1; x++){
		for (int y = 0; y < 3; y++)
			cout << "\t" << st[x][y];
		cout << endl;
	}
	return mincost;
}


int main()
{
	graph city;
	city.create_adj_matrix();
	city.display();
	char choice;
	do {
		int v;
		cout << endl
			 << "Enter the starting vertex for minimum cost: ";
		cin >> v;
		int mincost = city.prims(v);
		cout << endl
			 << "Minimum cost calculated using Prim's algorithm = " << mincost << endl
			 << endl
			 << "Do you want to run Prim's algorithm again? (Y/n): ";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
	cout << endl
		 << "Exiting..." << endl
		 << endl;
	return 0;
}

------------------------------------------------------------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>

using namespace std;

class sack
{
	int cap;
	int n;
	int value[20];
	int weight[20];
	int b[25][25];
	bool selected[20];
    int totprofit;
	
public:
	sack()
	{
        totprofit = 0;
		cout << endl
			 << "Enter capacity of knapsack: ";
		cin >> cap;
		cout << "Enter number of item: ";
		cin >> n;
		
		for (int i = 0; i < n; i++) {
			cout << endl
				 << "Enter profit value of item " << i << ": ";
			cin >> value[i];
			cout << "Enter weight of item " << i << ": ";
			cin >> weight[i];
		}
	}
	
	void knapsack()
	{
		for (int w = 0; w <= cap; w++)
			b[0][w] = 0;
		for (int i = 1; i <= n; i++)
			b[i][0] = 0;
			
		for (int i = 1; i <= n; i++)
			for (int w = 1; w <= cap; w++) {
				b[i][w] = ((weight[i - 1] <= w) && (value[i - 1] + b[i - 1][w - weight[i - 1]] > b[i - 1][w])) ? (value[i - 1] + b[i - 1][w - weight[i - 1]]) : b[i - 1][w];
                // if ((weight[i - 1] <= w) && (value[i - 1] + b[i - 1][w - weight[i - 1]] > b[i - 1][w]))
                //     b[i][w] = value[i - 1] + b[i - 1][w - weight[i - 1]];
                // else
                //     b[i][w] = b[i - 1][w];
            }
	}
	
	void find_items()
	{
		int i = n, k = cap;
		while (i >= 0 && k >= 0) {
			if (b[i][k] != b[i - 1][k]) {
				selected[i - 1] = true;
				k -= weight[i - 1];
			} else {
				selected[i - 1] = false;
			}
			i--;
		}

        for (int j = 0; j < n; j++)
            if (selected[j])
                totprofit += value[j];
	}
	
	void display()
	{
		cout << endl
			 << "Table: " << endl;
		for (int i = 0; i <= n; i++) {
			for (int w = 0; w <= cap; w++)
				cout << b[i][w] << '\t';
			cout << endl;
		}

        cout << endl
             << "Selected array:\t";
        for (int i = 0; i < n; i++)
            if (selected[i])
                cout << "\t1";
            else
                cout << "\t0";
		
		cout << endl
             << endl
			 << "Selected items:\t";
		for (int i = 0; i < n; i++)
			if (selected[i])
				cout << '\t' << i;

        cout << endl
             << endl
             << "Total profit:\t" << totprofit << endl
             << endl;
	}
};

int main()
{
	sack s;
	s.knapsack();
	s.find_items();
	s.display();
	return 0;
}

----------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <cmath>

using namespace std;

class queens
{
	int n;
	int *x;
	int count;
	
public:
	queens()
	{
		cout << endl
			 << "Enter number of queens: ";
		cin >> n;
		count = 0;
		x = new int[n];
		cout << endl;
	}
	
	void nqueen(int);
	bool place(int, int);
	void printcount();
	void display();
};

void queens::nqueen(int k)
{
	for (int i = 1; i <= n; i++)
		if (place(k, i)) {
			x[k] = i;
			if (k == n) display();
			else nqueen(k + 1);
		}
}

bool queens::place(int k, int i)
{
	for (int j = 1; j < k; j++)
		if (x[j] == i || abs(x[j] - i) == abs(j - k))
			return false;
	return true;
}

void queens::display()
{
	count++;
	cout << endl
		 << "Solution " << count << ":" << endl;
	for (int i = 1; i <= n; i++) {
		cout << '\t';
		for (int j = 1; j <= n; j++) {
			if (x[i] == j)
				cout << "Q ";
			else
				cout << ". ";
		}
		cout << endl;
	}
	cout << endl;
}

void queens::printcount()
{
	cout << endl
		 << "Number of solutions: " << count << endl
		 << endl;
}

int main()
{
	queens q;
	q.nqueen(1);
	q.printcount();
	return 0;
}
------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>

using namespace std;

#define MAX 10

class record
{
	int roll, marks;
	string name;
	
public:

	friend class student;
};

class hashing
{
	int roll, pos;
	
public:
	hashing()
	{
		roll = -1;
		pos = -1;
	}
	
	friend class student;
};

class student
{
	record rec;
	hashing h[MAX];
	int s, relt;
	
public:
	student()
	{
		s = sizeof(record);
		for (int i = 0; i < MAX; i++) {
			h[i].roll = -1;
			h[i].pos = -1;
		}
		relt = 0;
	}
	
	void create_wor();
	void create_wr();
	void modify();
	void retrieve();
	void display();
	void displayall();
};

void student::create_wor()
{
	char choice;
	fstream f;
	f.open("student.txt", ios::binary | ios::out | ios::app);
	int loc;
	
	do {
		cout << endl
			 << "Enter details for new student:" << endl
			 << endl
			 << "Enter roll no.: ";
		cin >> rec.roll;
		cout << "Enter name: ";
		cin >> rec.name;
		cout << "Enter marks: ";
		cin >> rec.marks;
		
		loc = rec.roll % MAX;
		
		while (h[loc].roll != -1) {
			loc = (loc + 1) % MAX;
			if (loc == rec.roll % MAX) {
				cout << endl
					 << "Hash table is full!" << endl;
				return;
			}
		}
		
		h[loc].roll = rec.roll;
		h[loc].pos = relt;
		
		f.seekg(relt * s, ios::beg);
		f.write((char*)&rec, s);
		relt++;
		
		cout << endl
			 << "Do you wish to add another record? (Y/n): ";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
	
	f.close();
	displayall();
}

void student::create_wr()
{
	char choice;
	int loc, nloc;
	hashing temp;
	fstream f;
	f.open("student.txt", ios::binary | ios::out | ios::app);
	do {
		cout << endl
			 << "Enter details for new student:" << endl
			 << endl
			 << "Enter roll no.: ";
		cin >> rec.roll;
		cout << "Enter name: ";
		cin >> rec.name;
		cout << "Enter marks: ";
		cin >> rec.marks;
		
		loc = rec.roll % MAX;
		
		if(h[loc].roll == -1) {
			h[loc].roll = rec.roll;
			h[loc].pos = relt;
			f.seekg(relt * s, ios::beg);
			f.write((char*)&rec, s);
			relt++;
		} else {
			temp.roll = rec.roll;
			temp.pos = relt;
			f.seekg(relt * s, ios::beg);
			f.write((char*)&rec, s);
			relt++;
			
			if (loc != h[loc].roll % MAX) {
				temp.roll = h[loc].roll;
				temp.pos = h[loc].pos;
				h[loc].roll = rec.roll;
				h[loc].pos = relt - 1;
			}
			
			nloc = (loc + 1) % MAX;
			
			while (nloc != loc) {
				if (h[nloc].roll == -1) {
					h[nloc].roll = temp.roll;
					h[nloc].pos = temp.pos;
					break;
				}
				nloc = (nloc + 1) % MAX;
			}
		}
		
		cout << endl
			 << "Do you wish to add more records? (Y/n): ";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
	f.close();
}

void student::display()
{
	cout << rec.roll << "\t\t" << rec.name << "\t" << rec.marks << endl;
}

void student::displayall()
{
	cout << endl
		 << "Displaying Hash Table:" << endl
		 << endl
		 << "Index\tRoll no.\tPosition in file" << endl;
	for (int i = 0; i < MAX; i++)
		cout << i << "\t" << h[i].roll << "\t\t" << h[i].pos << endl;
	
	cout << endl
		 << "Records in order of insertion:" << endl
		 << endl
		 << "Roll no.\tname\tMarks" << endl;
	fstream f;
	f.open("student.txt", ios::binary | ios::in);
	
	for (int i = 0; i < relt; i++) {
		f.seekg(i * s, ios::beg);
		f.read((char*)&rec, s);
		display();
	}
	
	f.close();
}

void student::retrieve()
{
	fstream f;
	f.open("student.txt", ios::binary | ios::in);
	
	cout << endl
		 << "Enter the roll no. of the student you want to search: ";
	cin >> rec.roll;
	
	int loc = rec.roll % MAX, i;
	
	for (i = 0; i < MAX; i++) {
		if (h[loc].roll == rec.roll) {
			int p = h[loc].pos * s;
			f.seekg(p, ios::beg);
			f.read((char*)&rec, s);
			display();
			break;
		} else
			loc = (loc + 1) % MAX;
	}
	
	if (i == MAX)
		cout << endl
			 << "Record not found!" << endl;
	f.close();
}

void student::modify()
{
	fstream f;
	f.open("student.txt", ios::binary | ios::in | ios::out);
	cout << endl
		 << "Enter the roll no of the student whose details you want to change: ";
	cin >> rec.roll;
	
	int loc = rec.roll % MAX, i;
	
	for (i = 0; i < MAX; i++) {
		if (h[loc].roll == rec.roll) {
			int p = h[loc].pos * s;
			f.seekg(p, ios::beg);
			f.read((char*)&rec, s);
			display();
			
			cout << endl
				 << "Enter the new name: ";
			cin >> rec.name;
			cout << "Enter the new marks: ";
			cin >> rec.marks;
			
			p = h[loc].pos * s;
			f.seekg(p, ios::beg);
			f.write((char*)&rec, s);
			break;
		} else
			loc = (loc + 1) % MAX;
	}
	
	if (i == MAX)
		cout << endl
			 << "Record not found!" << endl;
	f.close();
}

int main()
{
	student stu;
	int choice;
	
	do {
		cout << endl
			 << "Choose an operation:" << endl
			 << "1. Insert without Replacement" << endl
			 << "2. Insert with Replacement" << endl
			 << "3. Display" << endl
			 << "4. Retrieve" << endl
			 << "5. Modify" << endl
			 << "6. Exit" << endl
			 << endl
			 << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			stu.create_wor();
			break;
		case 2:
			stu.create_wr();
			break;
		case 3:
			stu.displayall();
			break;
		case 4:
			stu.retrieve();
			break;
		case 5:
			stu.modify();
			break;
		case 6:
			cout << endl
				 << "Exiting the program..." << endl
				 << endl;
			break;
		default:
			cout << endl
				 << "Invalid choice! Try again." << endl
				 << endl;
		}
	} while (choice != 6);
	return 0;
}
--------------------------------------------------------------------------------------------------------------------------------------


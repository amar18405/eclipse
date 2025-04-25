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
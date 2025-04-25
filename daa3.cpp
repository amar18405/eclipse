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
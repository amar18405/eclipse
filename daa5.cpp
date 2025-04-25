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
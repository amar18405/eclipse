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
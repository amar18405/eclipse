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
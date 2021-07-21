#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
void myopen(ifstream& fin, const char* fname, const int n = ios_base::in);
void myopen(ofstream& fout, const char* fname, const int n = ios_base::out | ios_base::trunc);



class ListIterator;

class List
{
protected:
	friend ListIterator;

	struct Node
	{
		int value;
		Node* next;
	}  *list;

public:
	typedef ListIterator  Iterator;
	List() : list(NULL) { ; }


	void Push(int value)       //функция которая добавляет элементы
	{
		Node* node = new Node;
		node->value = value;
		node->next = list;

		list = node;
	}


	int Pop()
	{
		Node* node = list;
		list = list->next;

		int value = node->value;
		delete node;

		return value;
	}


	bool Empty() const
	{
		return (list == NULL);
	}

	void Clean()
	{
		while (Empty() == false)
		{
			Pop();
		}
	}
};

class ListIterator
{
protected:
	typename List::Node* node;

public:
	ListIterator(const List& list) : node(list.list) { ; }

	bool End()
	{
		return (node == NULL);
	}

	ListIterator& operator ++ ()
	{
		node = node->next;

		return *this;
	}

	int operator * ()
	{
		return node->value;
	}
};


ostream& operator << (ostream& os, const List& list)
{
	for (typename List::Iterator it = list; !it.End(); ++it)
	{
		os << *it << " ";
	}

	return os;
}


int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	List list1;


	cout << "Ведите количество элементов списка list1: n= ";
	int n=50;
	cout << n << endl;
	
	int *A=new int[n];

	ifstream fin;
	myopen(fin, "List1.txt");
	for (int i = 0; i < n; ++i)
	{
		fin >> A[i];
		list1.Push(A[i]);
	}
	delete[] A;
	fin.close();
 	cout << "list1: " << list1 << endl;


	List list2;
	ofstream fout;
	myopen(fout, "List2.txt");
	int max = 0, index = 1;
	for (List::Iterator it = list1; !it.End(); ++it)
	{
		if (max < *it)
		{
			list2.Clean();
			max = *it;
		}
		if (max == *it)
		{
			if(index>7)
				fout << index << " ";
			
			list2.Push(index);
		}
		index++;
	}
	fout.close();
	cout << endl;
	cout << "Выводятся максимальные элементы списка: ";
	cout << max << endl;

	cout << "list2 состот из порядковых номеров максимальных элементов из list1 " << endl;
	cout << "list2: " << list2 << endl;

	system("pause");
	return 0;
}

void myopen(ifstream& fin, const char* fname, const int n) {
	fin.open(fname, n);

	if (!fin.is_open()) {
		cout << "Ошибка открытия файла " << fname << endl;
		system("pause"); exit(1);
	}
}
void myopen(ofstream& fout, const char* fname, const int n) {
	fout.open(fname, n);
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла " << fname << endl;
		system("pause"); exit(1);
	}
}

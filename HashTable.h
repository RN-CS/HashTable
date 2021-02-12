// HashTable.h
// define node class
// Node will have key and value and next
// key : string
// value : T (generic)
// next : Node<T>*
#include<iostream>
#include<string>
using namespace std;

template<typename T>
class Node {
public:
	string key;
	T value;
	Node<T>*next;
	Node(string key, T val)
	{
		this->key = key;
		value = val;
		next = NULL;
	}
	~Node()
	{
		//recursive delete
		if (next != NULL)
		{
			delete next;
		}
	}

};

// What are the things that we need to store in hashTable class
// Data member => Pointer to table array and table is array of Node<T>* so we need a pointer to an array of pointers
// Node<T>**
// current size of hash Table
// Total Capcity
//
template <typename T>
class HashTable
{
	Node<T>** table; // pointer to an array of Node<T>*
	int current_size;
	int table_size;

	int hashFun(string key)
	{
		int idx = 0;
		int p = 1;
		for (int i = 0; i < key.length(); i++)
		{
			idx = idx + (key[i] * p) % table_size;
			idx = idx % table_size;
			p = (p * 27) % table_size;
		}
		return idx;
	}


	void rehash()
	{

		Node<T>**oldTable = table;
		int oldTableSize = table_size;
		table_size = 2 * table_size;      // next prime number can also be generated but for simplicity and because of lazyness, i am just double it
		table = new Node<T>*[table_size];
		for (int i = 0; i < table_size; i++)
		{
			table[i] = NULL;
		}
		current_size = 0;
		// shift element from oldTable to table

		for (int i = 0; i < oldTableSize; i++)
		{
			Node<T>*temp = oldTable[i];
			while (temp != NULL)
			{
				insert(temp->key, temp->value);

				temp = temp->next;
			}
			// Delete linked list present at oldTable[i] to check presence check oldTable[i]!=NULL
			if (oldTable[i] != NULL)
			{
				delete oldTable[i];
			}
		}

		// Now delete oldTable
		// Delete Table array of
		// oldTable is pointer to oldTable array

		delete [] oldTable;

	}



public:

	HashTable(int ts = 10)
	{
		{
			table_size = ts;
			table = new Node<T>*[table_size];   // table will be array of node object
			current_size = 0;
			// Initailize each pointer to null inially table is not pointing to anywhere; and does not have a linked list associated with it
			for (int i = 0; i < table_size; i++)
			{
				table[i] = NULL;
			}
		}
	}
	// Insert
	void insert(string key, T value)
	{
		//..table[hash(key)] = value;
		// send key to hash function and get idx and tabe[idx] = Node(key,value);


		// get idx
		int idx = hashFun(key);

		// Now create a node
		Node<T>*NewNode = new Node<T>(key, value);

		// insert at the head of table[idx]-
		// Like table[idx]->next = NewNode;
		NewNode->next = table[idx];
		table[idx] = NewNode;

		current_size++;
		// Rehashing

		// To avoid frequent rehash use bigger table size;


		float load_factor = current_size / (float)table_size;
		cout << load_factor << endl;

		if (load_factor > 0.75)
		{
			// do Rehashing
			// cout << "yes" << endl;

			cout << key << "\n";

			rehash();

		}

	}



	T* search(string key)
	{
		// returns the address of value associated with key if it happens to present otherwise NULL
		// We can not return -1 in case of absentee becoz we do not know datatype of T
		// But we can return NULL
		// And NULL is pointer so we have to return address of value if it happens to presnet

		// First get hash of key
		int idx = hashFun(key);
		Node<T>*temp = table[idx];
		while (temp != NULL)
		{

			if (temp->key == key)
			{
				return &temp->value;
			}

			temp = temp->next;

		}

		// if not present return NULL
		return NULL;

	}



	void print()
	{
		for (int i = 0; i < table_size; i++)
		{
			cout << "Bucket " << i << "->";

			Node<T>*tm = table[i];
			while (tm != NULL)
			{
				cout << "(" << tm->key << ": " << tm->value << ")" << "-> ";
				// cout << tm->key << "->";
				tm = tm->next;
			}
			cout << "\n";

		}
		return ;
	}

	int get_size()
	{
		return current_size;
	}

	bool isEmpty()
	{
		return current_size == 0;
	}


	void erase(string key)
	{
		int idx = hashFun(key);
		Node<T>* temp = table[idx];
		Node<T>*prev = NULL;

		while (temp != NULL)
		{
			if (temp->key == key)
			{
				if (prev)
				{

					prev->next = temp->next;
				}
				else
				{
					table[idx] = temp->next;
				}
				current_size--;
				temp->next = NULL;
				delete temp;
				return ;
			}
			prev = temp;
			temp = temp->next;
		}

		return;
	}


	// void erase(string key)
	// {
// int idx = hashFun(key);
// 		Node<T>* temp = table[idx];
// 		Node<T>* prev = NULL;

// 		while (temp != NULL) {
// 			if (temp->key == key) {
// 				if (prev) {
// 					prev->next = temp->next;
// 				}
// 				else {
//
// 				}
// 				temp->next = NULL;
// 				delete temp;
// 				return ;
// 			}
// 			prev = temp;
// 			temp = temp->next;
// 		}

	// }

	// ~HashTable();

};
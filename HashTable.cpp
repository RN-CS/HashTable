// HashTable.cpp
#include<iostream>
#include<string>
#include"HashTable.h"

using namespace std;

int main()
{
	HashTable<int> price_menu;

	price_menu.insert("Burger", 120);
	price_menu.insert("Pepsi", 12);
	price_menu.insert("BurgerPizza", 150);
	price_menu.insert("Noodles", 50);
	price_menu.insert("Doke", 40);
	price_menu.insert("Coke", 34);
	price_menu.insert("Samosa", 10);
	price_menu.insert("Samosa", 11);
	price_menu.insert("Samosa", 112);
	price_menu.insert("Coke", 113);
	price_menu.insert("Jalebi", 42);
	price_menu.insert("Rasmalai", 110);
	price_menu.insert("GulabJamun", 55);
	price_menu.insert("GulabJamun", 40);


	int* price = price_menu.search("Coke");

	if (price == NULL)
	{
		cout << "Not found";
	}
	else
	{
		cout << "Price is " << *price << endl;
	}

	price_menu.erase("Rasmalai");
	price_menu.erase("Coke");
	price_menu.erase("Coke");
	price_menu.erase("Samosa");

	price_menu.erase("Toke");

	price_menu.print();

	cout << endl << price_menu.get_size();
	return 0;
}


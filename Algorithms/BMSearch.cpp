#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int getTab(int*tab, string &substr, string &str, int j)
{
	for (int i = substr.length() - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (substr[i] != str[j])
		{ // если символа в подстроке нет - сдвиг на длину подстроки
			return tab[str[j]];
		}
	}

	return 0;
}

void bmSearch(string str, string substr)
{
	
	int *tabs = new int[256];
	for (int i = 0; i < 256; i++)
		tabs[i] = substr.length();
	for (int i = 0; i < substr.length() - 1; i++)
	{
		tabs[substr[i]] = substr.length() - i - 1; // создание хешмапы сдвигов
	}

	int tab;
	bool occur = false;

	for (int j = substr.length() - 1; j < str.length();)
	{
		tab = getTab(tabs, substr, str, j); // смещение подстроки
		if (tab == 0)
		{
			cout << "Found occurrence of a substring with shift = " << (j - substr.length() + 1) << endl;
			occur = true;
			j++;
		}
		else
			cout << "Shift = " << tab << endl;
		j += tab;
	}

	if (!occur) // если не было вхождения
		cout << "No substring occurrence" << endl;
	delete[]tabs;
}

void main() {

	int restartProg = 1;
	while (restartProg == 1)
	{
		string substr, str;

		cout << "Enter the string: " << endl;
		cin >> str;
		cout << "Enter the substring: " << endl;
		cin >> substr;

		bmSearch(str, substr);

		cout << "Press 1 to continue" << endl;
		cin >> restartProg;
	}
}

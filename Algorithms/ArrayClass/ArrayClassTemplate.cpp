#include "ClassTemplate.h"
#include <ctime>

void main()
{
	Array <int> mas1(5);
	mas1.Scan(5);
	mas1.Print();

	Array<int> mas2(mas1);
	cout << mas2 << endl;
	if (mas1 == mas2)
		cout << "They are equal" << endl;
	else cout << "They are not equal" << endl;
	mas1 += 6;
	cout << mas1 << endl;
	if (mas1 == mas2)
		cout << "They are equal" << endl;
	else cout << "They are not equal" << endl;
	Array <char> mas3(4);
	mas3.Scan(4);
	cout << mas3 << endl;
	mas3.DelPosEq(0);
	cout << mas3 << endl;
	Array <char> mas4 = mas3.DelPosNew(mas3.GetN() - 1);
	cout << mas4 << endl;
	mas3 -= 1;
	cout << mas3 << endl;
	if (mas3 == mas4)
		cout << "They are equal" << endl;
	else cout << "They are not equal" << endl;

	Array <float> mas5(5);
	mas3.Scan(5);
	cout << mas5 << endl;
	Array <float> mas6(mas5);
	mas6 -= mas5[4];
	cout << mas6 << endl;
	cout << "Min: " << mas5.Min() << ", min index: " << mas5.FindKey(mas5.Min()) << endl;
	cout << "Max: " << mas5.Max() << ", max index: " << mas5.FindKey(mas5.Max()) << endl;
	mas5.Sort();
	cout << "Sorted: " << mas5 << endl;

	Array <float> mas7 = mas5 + mas6;
	cout << mas7 << endl;

	if (mas7.FindKey(1.1) != -1)
		cout << "1 is in array" << endl;
	else
		cout << "1 is not in array" << endl;

	if (mas7.FindKey(10.1) != -1)
		cout << "10 is in array" << endl;
	else
		cout << "10 is not in array" << endl;

	Array <float> mas8 = mas7 - 10.1;
	cout << mas8 << endl;
	if (mas7 == mas8)
		cout << "They are equal" << endl;
	else cout << "They are not equal" << endl;
}
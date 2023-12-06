#include<iostream>
#include "../include/circle.h"
#include "../include/device.h"
#include "../include/imgReader.h"


using namespace std;

int main()
{
	Circle c(3);
	cout << "Area=" << c.Area() << endl;
	printf("hello world \n");
	getLeftSpace("C:\\");
	getSystemStorageUsed();
	getBatteryPower();
	imgReader();
	return 0;
}
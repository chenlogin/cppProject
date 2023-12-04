#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<string>
#include<tchar.h>
#include"device.h"

using namespace std;

//��ѡ���̿ռ�
void getLeftSpace(string path) {
	string str_disk_name = path;
	DWORD64 qwFreeBytesToCaller = 0;
	DWORD64 qwTotalBytes = 0;
	DWORD64 qwFreeBytes = 0;
	///ʹ��GetDiskFreeSpaceEx��ȡ������Ϣ����ӡ���
	BOOL bResult = GetDiskFreeSpaceExA(str_disk_name.c_str(),
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);
	/// ��ȡ�ɹ�
	if (bResult)
	{
		printf("ʹ��GetDiskFreeSpaceEx��ȡ���̿ռ���Ϣ\n");

		cout << "��ѡ����ʣ��ռ�:" + to_string(qwFreeBytesToCaller / (1024 * 1024 * 1024)) + "G" << endl;
		cout << "��ѡ����ʣ��ռ�:" + to_string(qwFreeBytes / (1024 * 1024 * 1024)) + "G" << endl;
		cout << "��ѡ����������:" + to_string(qwTotalBytes / (1024 * 1024 * 1024)) + "G" << endl;
	}
	else {
		cout << "read fail" << endl;
	}
}

//���Դ����ܿռ�
std::string getSystemStorageUsed()
{
	long long all_Free = 0;
	long long all_Total = 0;
	long long used = 0;
	DWORD dwSize = MAX_PATH;
	TCHAR szLogicalDrives[MAX_PATH] = { 0 };

	DWORD dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);

	if (dwResult > 0 && dwResult <= MAX_PATH)
	{
		TCHAR* szSingleDrive = szLogicalDrives;

		while (*szSingleDrive)
		{
			uint64_t available, total, free;
			if (GetDiskFreeSpaceEx(szSingleDrive, (ULARGE_INTEGER*)&available, (ULARGE_INTEGER*)&total, (ULARGE_INTEGER*)&free))
			{
				uint64_t Total, Available, Free;
				Total = total >> 20;
				Available = available >> 20;
				Free = free >> 20;

				all_Total += Total;   //��
				all_Free += Free;   //ʣ��
			}
			// ��ȡ��һ������������ʼ��ַ
			szSingleDrive += _tcslen(szSingleDrive) + 1;
		}
	}
	used = (all_Total - all_Free) * 1024 * 1024;
	cout << "�����ܿռ�:" + to_string(all_Total / 1024) + "G" << endl;
	cout << "����ʣ��ռ�:" + to_string(all_Free / 1024) + "G" << endl;
	return std::to_string(used);
}

//��ص���
std::string getBatteryPower() {
	LPSYSTEM_POWER_STATUS power = new _SYSTEM_POWER_STATUS();
	int ret = GetSystemPowerStatus(power);
	int percent = (int)power->BatteryLifePercent;
	delete power;
	if (ret == 0) //��ʾ��ȡʧ��
		return "0%";
	cout << "��ص�����" + to_string(percent) + "%" << endl;
	return std::to_string(percent);
}
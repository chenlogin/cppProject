#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<string>
#include<tchar.h>
#include"device.h"

using namespace std;

//所选磁盘空间
void getLeftSpace(string path) {
	string str_disk_name = path;
	DWORD64 qwFreeBytesToCaller = 0;
	DWORD64 qwTotalBytes = 0;
	DWORD64 qwFreeBytes = 0;
	///使用GetDiskFreeSpaceEx获取磁盘信息并打印结果
	BOOL bResult = GetDiskFreeSpaceExA(str_disk_name.c_str(),
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);
	/// 读取成功
	if (bResult)
	{
		printf("使用GetDiskFreeSpaceEx获取磁盘空间信息\n");

		cout << "所选磁盘剩余空间:" + to_string(qwFreeBytesToCaller / (1024 * 1024 * 1024)) + "G" << endl;
		cout << "所选磁盘剩余空间:" + to_string(qwFreeBytes / (1024 * 1024 * 1024)) + "G" << endl;
		cout << "所选磁盘总容量:" + to_string(qwTotalBytes / (1024 * 1024 * 1024)) + "G" << endl;
	}
	else {
		cout << "read fail" << endl;
	}
}

//电脑磁盘总空间
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

				all_Total += Total;   //总
				all_Free += Free;   //剩余
			}
			// 获取下一个驱动器号起始地址
			szSingleDrive += _tcslen(szSingleDrive) + 1;
		}
	}
	used = (all_Total - all_Free) * 1024 * 1024;
	cout << "电脑总空间:" + to_string(all_Total / 1024) + "G" << endl;
	cout << "电脑剩余空间:" + to_string(all_Free / 1024) + "G" << endl;
	return std::to_string(used);
}

//电池电量
std::string getBatteryPower() {
	LPSYSTEM_POWER_STATUS power = new _SYSTEM_POWER_STATUS();
	int ret = GetSystemPowerStatus(power);
	int percent = (int)power->BatteryLifePercent;
	delete power;
	if (ret == 0) //表示获取失败
		return "0%";
	cout << "电池电量：" + to_string(percent) + "%" << endl;
	return std::to_string(percent);
}
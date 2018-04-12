#pragma once
#include <iostream>
#include <string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

class URI
{
public:
	URI();
	~URI();
	// http://students.iitk.ac.in/programmingclub/course/lectures/

	// Link nạp ban đầu
	char url[1024];			// http://students.iitk.ac.in/programmingclub/course/lectures/

							// Host của server
	char hostname[256];		// students.iitk.ac.in

							// Đường dẫn path tới folder hoặc thư mục
	char pathname[512];		// /programmingclub/course/lectures/

							// Tên folder, file con
	char itemname[256];		// lectures

							// Lưu preFolder name
	char pre_ItemName[256];
	bool isFile;		// if (isFile = true: File else Folder)

						// Gán url và preName vào cấu trúc
	void setURL(char url[1024], char pre_ItemName[256]);

	// Thực hiện định dạng từ url theo các trường của cấu trúc
	bool separateURL();

	// Nếu tên Item có chứa %20 thì thay bằng ' '
	void makeBeautyItemName();
};



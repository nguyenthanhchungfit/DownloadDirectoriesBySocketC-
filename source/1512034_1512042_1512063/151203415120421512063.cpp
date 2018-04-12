// 151203415120421512063.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyHTTP.h"


// Hàm này thực hiện việc kết nối tới server và tải file về máy tính
void get_FileAndFolder(QueueURI& uris, int port, int versionHTTP);


int main(int argc, char *argv[])
{
	char mssv[30];
	char link[1024];
	int versionHTTP = 0;

	/*strcpy_s(link, "");
	strcpy_s(link, "http://students.iitk.ac.in/programmingclub/course/lectures/");
	strcpy_s(mssv, "1512034_1512042_1512063_");
	versionHTTP = 1;*/

	if (argc != 3)
	{
		cout << "Khong du tham so" << endl;
		return 1;
	}
	strcpy_s(mssv, argv[0]);
	strcat(mssv, "_");
	strcpy_s(link, argv[1]);

	// 1: HTTP1.1 ; 0: HTTP 1.0
	if (strcmpi(argv[2], "--http1.0") == 0)
	{
		versionHTTP = 0;
	}
	else if (strcmpi(argv[2], "--http1.1") == 0)
	{
		versionHTTP = 1;
	}


	// Chương trình dùng tham số dòng lệnh chạy chương trình argv[0]: mssv  argv[1]: Link  argv[2]: versionHTTP

	// Ý tưởng của chương trình là sẽ nạp các link download vào 1 hàng đợi, khi nào hàng đợi hết 
	// phần tử thì dừng chương trình, ngược lại thì mỗi khi đọc dữ liệu từ server nếu nhận được
	// là folder thì sẽ lấy hết các link sub item trong folder nạp vào hàng đợi, nếu là file thì thực hiện
	// download file bình thường, và lấy link này ra khỏi hàng đợi


	QueueURI uris;			// Hàng đợi lưu trữ các link
	URI uri;				// CTDL URI lưu trữ link ban đầu chương trình nạp vào
	uri.setURL(link, mssv);
	uri.separateURL();
	uris.enQueue(uri);

	while (!uris.isEmpty())
	{
		get_FileAndFolder(uris, 80, versionHTTP);
	}

    return 0;
}


void get_FileAndFolder(QueueURI& uris, int port, int versionHTTP)
{
	// Lấy link ra khỏi hàng đợi uris
	URI uri;
	uris.deQueue(uri);


	MyHTTP http(uri, port);		// Khai báo đối tượng MyHTTP
	WSAData a;

	// Initialize winsock
	WSAStartup(MAKEWORD(2, 2), &a);		// Khởi tạo winsock

	if (http.Create(AF_INET, SOCK_STREAM, IPPROTO_TCP))		// Khởi tạo MyHTTP
	{
		// Connect tới Server
		if (http.Connect())
		{
			char messageGet[1024];			// Lưu trữ chuỗi REQUEST từ máy client
			http.makeRequest(messageGet, versionHTTP);		// Thực hiện format chuỗi REQUEST theo version và URI ban đầu
			http.Send(messageGet);		// Gửi chuỗi REQUEST tới Server
			char header[65535];
			http.GetHeader(header, sizeof(header));	// Lấy header RESPONSE từ Server


			if (http.isValidResponse(header, versionHTTP))	// Kiểm tra gói header RESPONSE có được không
			{
				bool hasChunked = false;
				if (versionHTTP == 1)
				{
					hasChunked = http.hasChunkedEncoding(header);	// Kiểm tra gói có ChunkedEncoding không?
				}
				cout << "Header ok!" << endl;
				http.writeData(uris, versionHTTP, hasChunked);		// Thực hiện việc lưu trữ file
			}
			else
			{
				cout << "Link Is Not OK" << endl;
			}
		}
		else
		{
			cout << "connect failed" << endl;
		}
		http.Close();
	}
	else
	{
		cout << "Init failed";
	}

	WSACleanup();
}



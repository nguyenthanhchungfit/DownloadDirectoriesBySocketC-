1/ Môi trường cài đặt: Visual Studio 2017 Community
2/ Lưu ý khi biên dịch và chạy mã nguồn.
	a/ Mode "DEBUG"
	Chuột phải vào Property của Project
		+ Configuration Properties -> General ->  Use of MFC (chọn UMFC in a Shared DLL)
		+ C/C++ -> SDL checks (chọn No (/sdl)).
	b/ Mode "RELEASE"
	Chuột phải vào Property của Project
		+ Configuration Properties -> General ->  Use of MFC (chọn UMFC in a Shared DLL)
		+ C/C++ -> SDL checks (chọn No (/sdl)).
		+ C/C++ -> Optimization. Optimization:Disable. Phần Enable Intrinsic Functions:No
		+ C/C++ -> Code Generation. Enable Minimal Rebuild :Yes(/Gm). 
		Basic Runtime Checks:Both (/RTC1, equiv. to /RTCsu) (/RTC1). 
		Runtime Library: Multi-Thread Dll(/MD).  
		Enable Function-Level 	Linking:Yes
			 
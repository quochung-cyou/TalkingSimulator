#pragma once
#include "IncludeHeader.h"
using namespace std;


class Quiz {
public:
	wchar_t question[1000];
	wchar_t ans1[1000];
	wchar_t ans2[1000];
	wchar_t ans3[1000];
	wchar_t ans4[1000];

	int cong_tutin = 0;
	int cong_code = 0;
	int cong_daicuong = 0;

	int correctAns = 0;
	Quiz(wchar_t question[], wchar_t ans1[], wchar_t ans2[], wchar_t ans3[], wchar_t ans4[], int cong_tutin, int cong_code, int cong_daicuong, int correctAns);


};
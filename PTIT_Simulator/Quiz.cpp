#include "Quiz.h"

Quiz::Quiz(wchar_t question[], wchar_t ans1[], wchar_t ans2[], wchar_t ans3[], wchar_t ans4[], int cong_tutin, int cong_code, int cong_daicuong, int correctAns) {
	wcscpy_s(this->question, question);
	wcscpy_s(this->ans1, ans1);
	wcscpy_s(this->ans2, ans2);
	wcscpy_s(this->ans3, ans3);
	wcscpy_s(this->ans4, ans4);
	this->cong_tutin = cong_tutin;
	this->cong_code = cong_code;
	this->cong_daicuong = cong_daicuong;
	this->correctAns = correctAns;
}


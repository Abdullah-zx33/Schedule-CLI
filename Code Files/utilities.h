
#pragma once

#include<iostream>
#include<cstring>
#include<windows.h>
using namespace std;

inline void animate(const char ch[]) {
	for (int i = 0; ch[i] != '\0'; i++) {
		cout << ch[i];
		cout.flush();
		Sleep(20);
	}
}

template<typename T>
inline void animate(const char ch[], T var) {
	for (int i = 0; ch[i] != '\0'; i++) {
		cout << ch[i];
		cout.flush();
		Sleep(20);
	}
	cout << var;
}
#include "stdafx.h"

MyTimer::MyTimer(){
	QueryPerformanceFrequency(&tf);
}

unsigned _int64 MyTimer::GetFrequency(){
	QueryPerformanceFrequency(&tf);
	return tf.QuadPart;
}

// µ•Œª ns - ƒ…√Î
unsigned _int64 MyTimer::GetTime(){
	return (LONGLONG)((double)(t2.QuadPart - t1.QuadPart) / tf.QuadPart * 1000000000);
}

void MyTimer::Start(){
	QueryPerformanceCounter(&t1);
	//return t1.QuadPart;
}

void MyTimer::Stop(){
	QueryPerformanceCounter(&t2);
	//return t2.QuadPart;
}

unsigned _int64 MyTimer::GetBegin(){
	return t1.QuadPart;
}

unsigned _int64 MyTimer::GetEnd(){
	return t2.QuadPart;
}
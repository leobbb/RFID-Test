#ifndef _MyTimer_h_
#define _MyTimer_h_

#include <Windows.h>

class MyTimer{
private:
	LARGE_INTEGER t1, t2, tf;
public:
	MyTimer();
	unsigned _int64 GetFrequency();
	unsigned _int64 Start();
	unsigned _int64 Stop();
	unsigned _int64 GetTime();
};

#endif
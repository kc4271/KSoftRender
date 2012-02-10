#pragma once

inline long long GetCnj(int n,int j)
{
	long long res = 1;
	for(int i = 0;i < n - j;i++)
		res = res * (j + i + 1) / (i + 1);
	return res;
}

inline int square(int t)
{
	return t*t;
}
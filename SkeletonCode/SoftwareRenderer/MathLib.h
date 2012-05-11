#pragma once

#define MY_PI	3.1415926535897932384626433832795
#define TWO_PI  (2.0f * MY_PI)

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

typedef struct _D3DMATRIX {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };
        float m[4][4];
    };
} D3DMATRIX;
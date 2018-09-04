#include "mathtools.h"

mathtools::mathtools()
{
}


mathtools::~mathtools()
{
}

int mathtools::binom(int n, int k)
{
	if (k > n || n < 0 || k < 0)
		return 0;
	else
	{
		if (k > n / 2)
			k = n - k;
		int i;
		float result = 1.0;
		for (i = 1; i < k + 1; i++)
			result *= ((float)(n - k + i) / (float)i);
		return (int)result;
	}
}
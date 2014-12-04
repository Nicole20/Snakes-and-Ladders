#include "stdafx.h"
#include "ladders.h"

ladders::ladders(void)
{
	srand(time(NULL));

	num = rand() % 4 + 4;

	for (int i = 0; i < num; i++)
	{
		temp1 = rand() % 99 + 1;
		temp2 = rand() % 99 + 1;

		if (abs(temp1 - temp2) > 62 || abs(temp1 - temp2) < 5)
		{
			i--;
		}
		else if (temp1 > temp2)
		{
			top.push_back(temp1);
			bottom.push_back(temp2);
		}
		else if (temp1 < temp2)
		{
			top.push_back(temp2);
			bottom.push_back(temp1);
		}
		else
		{
			i--;
		}
	}
	check();
	erase();
}

int ladders::getBottom(int spot)
{
	for (int i = 0; i < num; i++)
	{
		if (bottom[i] == spot)
		{
			return top[i];
		}
	}
	return -1;
}

void ladders::check()
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (top[i] == bottom[j])
			{
				top[i] = 0;
				bottom[i] = 0;
			}
		}

		for (int j = i + 1; j < num; j++)
		{
			if (top[i] == top[j])
			{
				top[i] = 0;
				bottom[i] = 0;
			}
			if (bottom[i] == bottom[j])
			{
				top[i] = 0;
				bottom[i] = 0;
			}
		}
	}
}

void ladders::erase()
{
	for (int i = num - 1; i != -1; i--)
	{
		if (top[i] == 0)
		{
			top.erase(top.begin() + i);
			bottom.erase(bottom.begin() + i);
		}
	}
	num = top.size();
}

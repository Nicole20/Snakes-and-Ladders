#include "stdafx.h"
#include "snakes.h"

snakes::snakes(void)
{
	srand(time(NULL));

	num = rand() % 4 + 4;

	for (int i = 0; i < num; i++)
	{
		temp1 = rand() % 97 + 2;
		temp2 = rand() % 97 + 2;

		if (abs(temp1 - temp2) > 62 || abs(temp1 - temp2) < 5)
		{
			i--;
		}
		else if (temp1 > temp2)
		{
			head.push_back(temp1);
			tail.push_back(temp2);
		}
		else if (temp1 < temp2)
		{
			head.push_back(temp2);
			tail.push_back(temp1);
		}
		else
		{
			i--;
		}
	}
	check();
	erase();
}

int snakes::getHead(int spot)
{
	for (int i = 0; i < num; i++)
	{
		if (head[i] == spot)
		{
			return tail[i];
		}
	}
	return -1;
}

void snakes::check()
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (head[i] == tail[j])
			{
				head[i] = 0;
				tail[i] = 0;
			}
		}

		for (int j = i + 1; j < num; j++)
		{
			if (head[i] == head[j])
			{
				head[i] = 0;
				tail[i] = 0;
			}
			if (tail[i] == tail[j])
			{
				head[i] = 0;
				tail[i] = 0;
			}
		}
	}
}

void snakes::erase()
{
	for (int i = num - 1; i != -1; i--)
	{
		if (head[i] == 0)
		{
			head.erase(head.begin() + i);
			tail.erase(tail.begin() + i);
		}
	}
	num = head.size();
}

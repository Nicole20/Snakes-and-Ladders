#include "stdafx.h"
#include "snakesladders.h"

snakesladders::snakesladders(void)
{
	check();
	snake.erase();
	ladder.erase();

	starter.action = false;
	starter.action_spot = 0;
	starter.previous = 0;
	starter.spot = 0;

	players.push_back(starter);
	players.push_back(starter);

	num = 1;
	win = false;

	//to keep track of the Snakes and Ladders
	cout << "Snakes:" << endl;

	for (int i = 0; i < snake.head.size(); i++)
	{
		cout << snake.head[i] << " " << snake.tail[i] << " ";
	}

	cout << "\nLadders:" << endl;

	for (int i = 0; i < ladder.bottom.size(); i++)
	{
		cout << ladder.bottom[i] << " " << ladder.top[i] << " ";
	}

	cout << endl;
}

void snakesladders::check()
{
	for (int i = 0; i < ladder.num; i++)
	{
		for (int j = 0; j < snake.num; j++)
		{
			if (ladder.bottom[i] == snake.head[j])
			{
				ladder.top[i] = 0;
				ladder.bottom[i] = 0;
			}
			if (ladder.top[i] == snake.head[j])
			{
				snake.head[j] = 0;
				snake.tail[j] = 0;
			}
			if (ladder.bottom[i] == snake.tail[j])
			{
				ladder.top[i] = 0;
				ladder.bottom[i] = 0;
			}
			if (ladder.top[i] == snake.tail[j])
			{
				snake.head[j] = 0;
				snake.tail[j] = 0;
			}
		}
	}
}

int snakesladders::dice()
{
	srand(time(NULL));

	roll = rand() % 6 + 1;

	return roll;
}

void snakesladders::game()
{
	bottom = ladder.getBottom(players[num].spot);
	head = snake.getHead(players[num].spot);

	if (bottom != -1)
	{
		players[num].action = true;
		players[num].action_spot = players[num].spot;
		players[num].spot = bottom;
	}
	else if (head != -1)
	{
		players[num].action = true;
		players[num].action_spot = players[num].spot;
		players[num].spot = head;
	}
	else
	{
		players[num].action = false;
		players[num].action_spot = 0;
	}
	
	if (players[num].spot >= 100)
	{
		players[num].spot = 100;
		win = true;
		return;
	}	
}

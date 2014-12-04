#pragma once

#include "stdafx.h"
#include "snakes.h"
#include "ladders.h"
#include<stdlib.h>
#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<math.h>
#include<ctime>
#include<glut.h>

using namespace std;

class snakesladders
{
public:
	snakes snake;
	ladders ladder;
	int num;
	int roll;
	bool win;
	struct player
	{
		int previous;
		int spot;
		bool action;
		int action_spot;
	} starter;

	vector <player> players;

	int bottom, head;

	snakesladders(void);

	void check();
	int dice();
	void game();
};

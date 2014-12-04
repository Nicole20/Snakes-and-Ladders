// SnakesAndLadders.cpp
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<glut.h>
#include<freeglut.h>
#include<math.h>
#include<ctime>
#include "ObjLoader.h"
#include "snakesladders.h"

using namespace std;

int snake, ladder, pawn;
int temp = 0, wait = 0;
int xx = 0, yy = 0, zz = 0, xxx, yyy, zzz, xprev, yprev, xspot, yspot;
float xmove1 = 0, ymove1 = 0, xmove2 = 0, ymove2 = 0, xxmove = 0, yymove = 0, xxxmove = 0, yyymove = 0, divide;
ObjLoader obj_snake, obj_ladder, obj_pawn;
snakesladders board;

char *numbers = { "1 2 3 4 5 6 7 8 9 10"
"20191817161514131211"
"21222324252627282930"
"40393837363534333231"
"41424344454647484950"
"60595857565554535251"
"61626364656667686970"
"80797877767574737271"
"81828384858687888990"
"100999897969594939291" };

void initialize();
void snakeandladder();  //display function

void drawSnake();
void drawLadder();
void drawPawn();
void drawBoard();
void drawTile(float x, float y);
void drawDice();

void calcDice();
void calcPlayer();

void placeSnakes();
void placeLadders();
void placePawn(int player);

void mouse(int button, int state, int x, int y);
void rotate(int key, int x, int y);

void TimerDice(int value);
void TimerPlayer(int value);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(550, 450);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Snakes and Ladders");

	initialize();

	glutDisplayFunc(snakeandladder);
	glutMouseFunc(mouse);
	glutSpecialFunc(rotate);

	glutMainLoop();

	return 0;
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (board.num == 0)
			{
				board.num++;
				xmove2 = 0;
				ymove2 = 0;
			}
			else
			{
				board.num = 0;
				xmove1 = 0;
				ymove1 = 0;
			}

			if (!board.win)
			{
				board.players[board.num].previous = board.players[board.num].spot;
				board.players[board.num].spot += board.dice();
			}

			board.game();
			calcDice();
			calcPlayer();
			temp = 0;
			xx = 0;
			yy = 0;
			zz = 0;

			glutTimerFunc(0, TimerDice, 0);
		}
	}
	glutPostRedisplay();
}

void rotate(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		glRotatef(5, 1, 0, 0);
	}
	else if (key == GLUT_KEY_DOWN)
	{
		glRotatef(-5, 1, 0, 0);
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		glRotatef(5, 0, 1, 0);
	}
	else if (key == GLUT_KEY_LEFT)
	{
		glRotatef(-5, 0, 1, 0);
	}

	glutPostRedisplay();
}

void initialize()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glOrtho(-8, 40, 0, 38, -40, 40);

	snake = obj_snake.load("snake.obj");
	ladder = obj_ladder.load("ladder.obj");
	pawn = obj_pawn.load("pawn.obj");
}

void snakeandladder()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	glTranslatef(7, 5, 0);
	drawBoard();

	placeSnakes();
	placeLadders();

	glPushMatrix();
	glColor3f(0.7, 0, 0);
	placePawn(0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0.7);
	placePawn(1);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 10, -2);
	glRotatef(xx, 1, 0, 0);
	glRotatef(yy, 0, 1, 0);
	glRotatef(zz, 0, 0, 1);
	drawDice();
	glPopMatrix();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void TimerDice(int value)
{
	xx += xxx;
	yy += yyy;
	zz += zzz;

	temp++;

	if (temp < wait)
	{
		glutPostRedisplay();
		glutTimerFunc(25, TimerDice, 0);
	}
	else
	{
		glutTimerFunc(100, TimerPlayer, 0);
	}
}

void TimerPlayer(int value)
{
	if (board.players[board.num].action == true)
	{
		if (board.players[board.num].action_spot == board.players[board.num].previous)
		{
			if (board.num == 0)
			{
				if (xxmove > 0)
				{
					if (yymove > 0)
					{
						if (xmove1 + xxxmove <= xxmove && ymove1 + yyymove <= yymove)
						{
							xmove1 += xxxmove;
							ymove1 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
					else
					{
						if (xmove1 + xxxmove <= xxmove && ymove1 + yyymove >= yymove)
						{
							xmove1 += xxxmove;
							ymove1 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
				}
				else
				{
					if (yymove > 0)
					{
						if (xmove1 + xxxmove >= xxmove && ymove1 + yyymove <= yymove)
						{
							xmove1 += xxxmove;
							ymove1 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
					else
					{
						if (xmove1 + xxxmove >= xxmove && ymove1 + yyymove >= yymove)
						{
							xmove1 += xxxmove;
							ymove1 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
				}
			}
			else
			{
				if (xxmove > 0)
				{
					if (yymove > 0)
					{
						if (xmove2 + xxxmove <= xxmove && ymove2 + yyymove <= yymove)
						{
							xmove2 += xxxmove;
							ymove2 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
					else
					{
						if (xmove2 + xxxmove <= xxmove && ymove2 + yyymove >= yymove)
						{
							xmove2 += xxxmove;
							ymove2 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
				}
				else
				{
					if (yymove > 0)
					{
						if (xmove2 + xxxmove >= xxmove && ymove2 + yyymove <= yymove)
						{
							xmove2 += xxxmove;
							ymove2 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
					else
					{
						if (xmove2 + xxxmove >= xxmove && ymove2 + yyymove >= yymove)
						{
							xmove2 += xxxmove;
							ymove2 += yyymove;
							glutPostRedisplay();
							glutTimerFunc(100, TimerPlayer, 0);
						}
					}
				}
			}
		}
		else
		{
			board.players[board.num].previous++;
			if (board.num == 0)
			{
				xmove1 = 0;
				ymove1 = 0;
			}
			else
			{
				xmove2 = 0;
				ymove2 = 0;
			}
			glutPostRedisplay();
			glutTimerFunc(500, TimerPlayer, 0);
		}
	}
	else
	{
		if (board.num == 0)
		{
			xmove1 = 0;
			ymove1 = 0;
		}
		else
		{
			xmove2 = 0;
			ymove2 = 0;
		}

		if (board.players[board.num].previous != board.players[board.num].spot)
		{
			board.players[board.num].previous++;
			glutPostRedisplay();
			glutTimerFunc(500, TimerPlayer, 0);
		}
	}
}

void drawSnake()
{
	for (unsigned int i = 0; i < obj_snake.faces.size(); i++)
	{
		if (obj_snake.faces[i]->four)
		{
			glBegin(GL_QUADS);
			for (int ii = 0; ii < 4; ii++)
			{
				glVertex3f(obj_snake.vertex[obj_snake.faces[i]->faces[ii] - 1]->xx,
					obj_snake.vertex[obj_snake.faces[i]->faces[ii] - 1]->yy,
					obj_snake.vertex[obj_snake.faces[i]->faces[ii] - 1]->zz);
			}
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			for (int ii = 0; ii < 3; ii++)
			{
				glVertex3f(obj_snake.vertex[obj_snake.faces[i]->faces[ii] - 1]->xx,
					obj_snake.vertex[obj_snake.faces[i]->faces[ii] - 1]->yy,
					obj_snake.vertex[obj_snake.faces[i]->faces[ii] - 1]->zz);
			}
			glEnd();
		}
	}
}

void drawLadder()
{
	for (unsigned int i = 0; i < obj_ladder.faces.size(); i++)
	{
		if (obj_ladder.faces[i]->four)
		{
			glBegin(GL_QUADS);
			for (int ii = 0; ii < 4; ii++)
			{
				glVertex3f(obj_ladder.vertex[obj_ladder.faces[i]->faces[ii] - 1]->xx,
					obj_ladder.vertex[obj_ladder.faces[i]->faces[ii] - 1]->yy,
					obj_ladder.vertex[obj_ladder.faces[i]->faces[ii] - 1]->zz);
			}
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			for (int ii = 0; ii < 3; ii++)
			{
				glVertex3f(obj_ladder.vertex[obj_ladder.faces[i]->faces[ii] - 1]->xx,
					obj_ladder.vertex[obj_ladder.faces[i]->faces[ii] - 1]->yy,
					obj_ladder.vertex[obj_ladder.faces[i]->faces[ii] - 1]->zz);
			}
			glEnd();
		}
	}
}

void drawPawn()
{
	for (unsigned int i = 0; i < obj_pawn.faces.size(); i++)
	{
		if (obj_pawn.faces[i]->four)
		{
			glBegin(GL_QUADS);
			for (int ii = 0; ii < 4; ii++)
			{
				glVertex3f(obj_pawn.vertex[obj_pawn.faces[i]->faces[ii] - 1]->xx,
					obj_pawn.vertex[obj_pawn.faces[i]->faces[ii] - 1]->yy,
					obj_pawn.vertex[obj_pawn.faces[i]->faces[ii] - 1]->zz);
			}
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
			for (int ii = 0; ii < 3; ii++)
			{
				glVertex3f(obj_pawn.vertex[obj_pawn.faces[i]->faces[ii] - 1]->xx,
					obj_pawn.vertex[obj_pawn.faces[i]->faces[ii] - 1]->yy,
					obj_pawn.vertex[obj_pawn.faces[i]->faces[ii] - 1]->zz);
			}
			glEnd();
		}
	}
}

void drawBoard()
{
	glPushMatrix();

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			drawTile(i, j);
			j++;
			j++;
		}
		i++;
		i++;
	}

	glColor3f(0, 0, 0);
	int k = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			glRasterPos2f(j * 3 + 0.5, i * 3 + 0.5);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, numbers[k]);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, numbers[k + 1]);
			k = k + 2;
			if (i == 9 && j == 0)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, numbers[k]);
				k++;
			}
		}
	}

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -1);
	glVertex3f(30, 0, -1);
	glVertex3f(30, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 30, -1);
	glVertex3f(0, 30, 0);

	glVertex3f(30, 0, 0);
	glVertex3f(30, 0, -1);
	glVertex3f(30, 30, -1);
	glVertex3f(30, 30, 0);

	glVertex3f(30, 30, 0);
	glVertex3f(30, 30, -1);
	glVertex3f(0, 30, -1);
	glVertex3f(0, 30, 0);

	glVertex3f(0, 0, -1);
	glVertex3f(30, 0, -1);
	glVertex3f(30, 30, -1);
	glVertex3f(0, 30, -1);
	glEnd();

	glPopMatrix();
}

void drawTile(float x, float y)
{
	glColor3f(1 - x / 30, 1 - y / 30, (x + y) / 60);
	glBegin(GL_QUADS);
	glVertex3f(x, y, -0.1);
	glVertex3f(x + 3, y, -0.1);
	glVertex3f(x + 3, y + 3, -0.1);
	glVertex3f(x, y + 3, -0.1);
	glEnd();
}

void drawDice()
{
	glColor3f(0, 0, 0);

	glBegin(GL_LINE_STRIP);
	glVertex3f(-1, -1, 1);
	glVertex3f(-4, -1, 1);
	glVertex3f(-4, -4, 1);
	glVertex3f(-1, -4, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, 4);
	glVertex3f(-4, -1, 4);
	glVertex3f(-4, -4, 4);
	glVertex3f(-1, -4, 4);
	glVertex3f(-1, -1, 4);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(-4, -1, 1);
	glVertex3f(-4, -1, 4);

	glVertex3f(-4, -4, 1);
	glVertex3f(-4, -4, 4);

	glVertex3f(-1, -4, 1);
	glVertex3f(-1, -4, 4);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 1);
	glVertex3f(-4, -1, 1);
	glVertex3f(-4, -4, 1);
	glVertex3f(-1, -4, 1);

	glVertex3f(-1, -1, 4);
	glVertex3f(-4, -1, 4);
	glVertex3f(-4, -4, 4);
	glVertex3f(-1, -4, 4);

	glVertex3f(-1, -1, 1);
	glVertex3f(-4, -1, 1);
	glVertex3f(-4, -1, 4);
	glVertex3f(-1, -1, 4);

	glVertex3f(-4, -4, 1);
	glVertex3f(-1, -4, 1);
	glVertex3f(-1, -4, 4);
	glVertex3f(-4, -4, 4);

	glVertex3f(-4, -1, 1);
	glVertex3f(-4, -1, 4);
	glVertex3f(-4, -4, 4);
	glVertex3f(-4, -4, 1);

	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, 4);
	glVertex3f(-1, -4, 4);
	glVertex3f(-1, -4, 1);

	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);

	//one
	glVertex3f(-2, -2, 0.9);
	glVertex3f(-3, -2, 0.9);
	glVertex3f(-3, -3, 0.9);
	glVertex3f(-2, -3, 0.9);

	//six
	glVertex3f(-1.3, -1.3, 4.1);
	glVertex3f(-1.7, -1.3, 4.1);
	glVertex3f(-1.7, -1.7, 4.1);
	glVertex3f(-1.3, -1.7, 4.1);

	glVertex3f(-1.3, -2.3, 4.1);
	glVertex3f(-1.7, -2.3, 4.1);
	glVertex3f(-1.7, -2.7, 4.1);
	glVertex3f(-1.3, -2.7, 4.1);

	glVertex3f(-1.3, -3.3, 4.1);
	glVertex3f(-1.7, -3.3, 4.1);
	glVertex3f(-1.7, -3.7, 4.1);
	glVertex3f(-1.3, -3.7, 4.1);

	glVertex3f(-3.3, -1.3, 4.1);
	glVertex3f(-3.7, -1.3, 4.1);
	glVertex3f(-3.7, -1.7, 4.1);
	glVertex3f(-3.3, -1.7, 4.1);

	glVertex3f(-3.3, -2.3, 4.1);
	glVertex3f(-3.7, -2.3, 4.1);
	glVertex3f(-3.7, -2.7, 4.1);
	glVertex3f(-3.3, -2.7, 4.1);

	glVertex3f(-3.3, -3.3, 4.1);
	glVertex3f(-3.7, -3.3, 4.1);
	glVertex3f(-3.7, -3.7, 4.1);
	glVertex3f(-3.3, -3.7, 4.1);

	//two
	glVertex3f(-1.3, -0.9, 1.3);
	glVertex3f(-2, -0.9, 1.3);
	glVertex3f(-2, -0.9, 2);
	glVertex3f(-1.3, -0.9, 2);

	glVertex3f(-3, -0.9, 3);
	glVertex3f(-3.7, -0.9, 3);
	glVertex3f(-3.7, -0.9, 3.7);
	glVertex3f(-3, -0.9, 3.7);

	//five
	glVertex3f(-1.7, -4.1, 1.3);
	glVertex3f(-1.3, -4.1, 1.3);
	glVertex3f(-1.3, -4.1, 1.7);
	glVertex3f(-1.7, -4.1, 1.7);

	glVertex3f(-1.7, -4.1, 3.3);
	glVertex3f(-1.3, -4.1, 3.3);
	glVertex3f(-1.3, -4.1, 3.7);
	glVertex3f(-1.7, -4.1, 3.7);

	glVertex3f(-3.7, -4.1, 1.3);
	glVertex3f(-3.3, -4.1, 1.3);
	glVertex3f(-3.3, -4.1, 1.7);
	glVertex3f(-3.7, -4.1, 1.7);

	glVertex3f(-3.7, -4.1, 3.3);
	glVertex3f(-3.3, -4.1, 3.3);
	glVertex3f(-3.3, -4.1, 3.7);
	glVertex3f(-3.7, -4.1, 3.7);

	glVertex3f(-2.3, -4.1, 2.3);
	glVertex3f(-2.7, -4.1, 2.3);
	glVertex3f(-2.7, -4.1, 2.7);
	glVertex3f(-2.3, -4.1, 2.7);

	//three
	glVertex3f(-4.1, -1.3, 1.3);
	glVertex3f(-4.1, -1.3, 1.7);
	glVertex3f(-4.1, -1.7, 1.7);
	glVertex3f(-4.1, -1.7, 1.3);

	glVertex3f(-4.1, -2.3, 2.3);
	glVertex3f(-4.1, -2.3, 2.7);
	glVertex3f(-4.1, -2.7, 2.7);
	glVertex3f(-4.1, -2.7, 2.3);

	glVertex3f(-4.1, -3.3, 3.3);
	glVertex3f(-4.1, -3.3, 3.7);
	glVertex3f(-4.1, -3.7, 3.7);
	glVertex3f(-4.1, -3.7, 3.3);

	//four
	glVertex3f(-0.9, -1.3, 1.3);
	glVertex3f(-0.9, -1.3, 1.7);
	glVertex3f(-0.9, -1.7, 1.7);
	glVertex3f(-0.9, -1.7, 1.3);

	glVertex3f(-0.9, -1.3, 3.3);
	glVertex3f(-0.9, -1.3, 3.7);
	glVertex3f(-0.9, -1.7, 3.7);
	glVertex3f(-0.9, -1.7, 3.3);

	glVertex3f(-0.9, -3.3, 1.3);
	glVertex3f(-0.9, -3.3, 1.7);
	glVertex3f(-0.9, -3.7, 1.7);
	glVertex3f(-0.9, -3.7, 1.3);

	glVertex3f(-0.9, -3.3, 3.3);
	glVertex3f(-0.9, -3.3, 3.7);
	glVertex3f(-0.9, -3.7, 3.7);
	glVertex3f(-0.9, -3.7, 3.3);
	glEnd();
}

void placeSnakes()
{
	int head_x, head_y, tail_x, tail_y;
	float x, y, hyp;
	GLfloat angle, red = 0, green = 0.5, blue = 0;

	for (int i = 0; i < board.snake.num; i++)
	{
		if (red + 0.1 < 0.5)
		{
			red = red + 0.1;
		}
		else
		{
			red = 0;
		}

		if (green + 0.1 < 0.8)
		{
			green = green + 0.1;
		}
		else
		{
			green = 0.5;
		}

		if (blue + 0.1 < 0.5)
		{
			blue = blue + 0.1;
		}
		else
		{
			blue = 0;
		}

		head_x = board.snake.head[i] % 10;
		head_y = board.snake.head[i] / 10;
		tail_x = board.snake.tail[i] % 10;
		tail_y = board.snake.tail[i] / 10;

		if (head_x == 0)
		{
			if (head_y % 2 != 0)
			{
				head_x = 10;
			}
			else
			{
				head_x = 1;
			}
			head_y--;
		}
		else
		{
			if (head_y % 2 != 0)
			{
				head_x = 11 - head_x;
			}
		}

		if (tail_x == 0)
		{
			if (tail_y % 2 != 0)
			{
				tail_x = 10;
			}
			else
			{
				tail_x = 1;
			}
			tail_y--;
		}
		else
		{
			if (tail_y % 2 != 0)
			{
				tail_x = 11 - tail_x;
			}
		}

		x = 3 * (head_x + tail_x) / 2;
		y = 3 * (head_y + tail_y) / 2;

		if (head_y != tail_y)
		{
			angle = atan(abs((float)head_x - (float)tail_x) / abs((float)head_y - (float)tail_y)) * 180 / 3.14159;
		}
		else
		{
			angle = 90;
		}

		if (head_x != tail_x && head_y != tail_y)
		{
			hyp = hypotf(abs(head_x - tail_x), abs(head_y - tail_y));
		}
		else if (head_x == tail_x)
		{
			hyp = abs(head_y - tail_y);
		}
		else if (head_y == tail_y)
		{
			hyp = abs(head_x - tail_x);
		}

		glPushMatrix();

		glTranslatef(x - 0.9, y + 0.9, 0.2);
		glRotatef(-90, 1, 0, 0);

		if (head_x > tail_x)
		{
			glRotatef(angle, 0, 1, 0);
		}
		else if (head_x < tail_x)
		{
			glRotatef(-angle, 0, 1, 0);
		}

		if (hyp > 9)
		{
			glScalef(1.1, 1.1, hyp / 10 + 2.6);
		}
		else if (hyp > 8)
		{
			glScalef(1.1, 1.1, hyp / 10 + 2.5);
		}
		else if (hyp > 7)
		{
			glScalef(1.1, 1.1, hyp / 10 + 2.35);
		}
		else if (hyp > 5.9)
		{
			glScalef(1.1, 1.1, hyp / 10 + 2);
		}
		else if (hyp > 5)
		{
			glScalef(1.1, 1.1, hyp / 10 + 1.7);
		}
		else if (hyp > 4)
		{
			glScalef(1.1, 1.1, hyp / 10 + 1.4);
		}
		else if (hyp > 3.5)
		{
			glScalef(1.1, 1.1, hyp / 10 + 1.3);
		}
		else if (hyp > 2.8)
		{
			glScalef(1.1, 1.1, hyp / 10 + 1);
		}
		else
		{
			glScalef(1.1, 1.1, hyp / 10 + 0.72);
		}

		glColor3f(red, green, blue);
		drawSnake();
		glPopMatrix();
	}
}

void placeLadders()
{
	int top_x, top_y, bottom_x, bottom_y;
	float x, y, hyp;
	GLfloat angle, red = 0.4, green = 0.3, blue = 0.2;

	for (int i = 0; i < board.ladder.num; i++)
	{
		if (red + 0.1 < 0.8)
		{
			red = red + 0.1;
		}
		else
		{
			red = 0.4;
		}

		if (green + 0.1 < 0.7)
		{
			green = green + 0.1;
		}
		else
		{
			green = 0.3;
		}

		if (blue + 0.1 < 0.6)
		{
			blue = blue + 0.1;
		}
		else
		{
			blue = 0.2;
		}

		top_x = board.ladder.top[i] % 10;
		top_y = board.ladder.top[i] / 10;
		bottom_x = board.ladder.bottom[i] % 10;
		bottom_y = board.ladder.bottom[i] / 10;

		if (top_x == 0)
		{
			if (top_y % 2 != 0)
			{
				top_x = 10;
			}
			else
			{
				top_x = 1;
			}
			top_y--;
		}
		else
		{
			if (top_y % 2 != 0)
			{
				top_x = 11 - top_x;
			}
		}

		if (bottom_x == 0)
		{
			if (bottom_y % 2 != 0)
			{
				bottom_x = 10;
			}
			else
			{
				bottom_x = 1;
			}
			bottom_y--;
		}
		else
		{
			if (bottom_y % 2 != 0)
			{
				bottom_x = 11 - bottom_x;
			}
		}

		x = 3 * (top_x + bottom_x) / 2;
		y = 3 * (top_y + bottom_y) / 2;

		if (top_y != bottom_y)
		{
			angle = atan(abs((float)top_x - (float)bottom_x) / abs((float)top_y - (float)bottom_y)) * 180 / 3.14159;
		}
		else
		{
			angle = 90;
		}

		if (top_x != bottom_x && top_y != bottom_y)
		{
			hyp = hypotf(abs(top_x - bottom_x), abs(top_y - bottom_y));
		}
		else if (top_x == bottom_x)
		{
			hyp = abs(top_y - bottom_y);
		}
		else if (top_y == bottom_y)
		{
			hyp = abs(top_x - bottom_x);
		}

		glPushMatrix();
		glTranslatef(x - 1.2, y + 2, 0.5);
		glRotatef(-90, 0, 1, 0);

		if (top_x > bottom_x)
		{
			glRotatef(-angle, 1, 0, 0);
		}
		else if (top_x < bottom_x)
		{
			glRotatef(angle, 1, 0, 0);
		}

		if (hyp > 8)
		{
			glScalef(1, hyp / 10 + 1.5, 0.4);
		}
		else if (hyp > 7.5)
		{
			glScalef(1, hyp / 10 + 1.4, 0.4);
		}
		else if (hyp > 6.9)
		{
			glScalef(1, hyp / 10 + 1.3, 0.4);
		}
		else if (hyp > 6.3)
		{
			glScalef(1, hyp / 10 + 1.1, 0.4);
		}
		else if (hyp > 4.4)
		{
			glScalef(1, hyp / 10 + 1, 0.4);
		}
		else if (hyp > 3)
		{
			glScalef(1, hyp / 10 + 0.7, 0.4);
		}
		else if (hyp > 2.6)
		{
			glScalef(1, hyp / 10 + 0.6, 0.4);
		}
		else
		{
			glScalef(1, hyp / 10 + 0.4, 0.4);
		}

		glColor3f(red, green, blue);
		drawLadder();
		glPopMatrix();
	}
}

void placePawn(int player)
{
	int x, y, x_prev, y_prev;

	if (board.players[player].action == true)
	{
		x = board.players[player].action_spot % 10;
		y = board.players[player].action_spot / 10;
	}
	else
	{
		x = board.players[player].spot % 10;
		y = board.players[player].spot / 10;
	}

	x_prev = board.players[player].previous % 10;
	y_prev = board.players[player].previous / 10;

	if (x_prev == 0)
	{
		if (y_prev % 2 != 0)
		{
			x_prev = 10;
		}
		else
		{
			x_prev = 1;
		}
		y_prev--;
	}
	else
	{
		if (y_prev % 2 != 0)
		{
			x_prev = 11 - x_prev;
		}
	}

	x_prev = 3 * x_prev;
	y_prev = 3 * y_prev;

	if (player == 0)
	{
		glTranslatef(x_prev + xmove1 - 1, y_prev + ymove1 + 0.8, 1.5);
	}
	else
	{
		glTranslatef(x_prev + xmove2 - 1, y_prev + ymove2 + 2.2, 1.5);
	}

	glRotatef(90, 1, 0, 0);
	glScalef(0.6, 0.6, 0.6);

	drawPawn();
}

void calcDice()
{
	switch (board.roll)
	{
	case 1:
		xxx = 8;
		yyy = 4;
		zzz = 4;
		wait = 45;
		break;
	case 2:
		xxx = 6;
		yyy = 6;
		zzz = 4;
		wait = 45;
		break;
	case 3:
		xxx = 4;
		yyy = 6;
		zzz = 8;
		wait = 45;
		break;
	case 4:
		xxx = 4;
		yyy = 6;
		zzz = 4;
		wait = 45;
		break;
	case 5:
		xxx = 4;
		yyy = 6;
		zzz = 6;
		wait = 45;
		break;
	case 6:
		xxx = 4;
		yyy = 4;
		zzz = 8;
		wait = 45;
		break;
	default:
		break;
	}
}

void calcPlayer()
{
	int x, y, xprev, yprev;

	xprev = board.players[board.num].action_spot % 10;
	yprev = board.players[board.num].action_spot / 10;
	x = board.players[board.num].spot % 10;
	y = board.players[board.num].spot / 10;

	if (xprev == 0)
	{
		if (yprev % 2 != 0)
		{
			xprev = 10;
		}
		else
		{
			xprev = 1;
		}
		yprev--;
	}
	else
	{
		if (yprev % 2 != 0)
		{
			xprev = 11 - xprev;
		}
	}

	if (x == 0)
	{
		if (y % 2 != 0)
		{
			x = 10;
		}
		else
		{
			x = 1;
		}
		y--;
	}
	else
	{
		if (y % 2 != 0)
		{
			x = 11 - x;
		}
	}

	xxmove = x - xprev;
	yymove = y - yprev;

	xxmove = xxmove * 3;
	yymove = yymove * 3;

	divide = sqrt(pow(xxmove, 2) + pow(yymove, 2));

	xxxmove = xxmove / divide;
	yyymove = yymove / divide;
}

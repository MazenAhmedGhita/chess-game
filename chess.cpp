#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>
#include <math.h>
#include<windows.h>
#include<conio.h>
#include "CC212SGL.h"
//Link to the Graphics .lib file
// a huge problem Solved by student Mahmoud Ayman
#pragma comment(lib, "CC212SGL.lib")
CC212SGL gr;
#define wpawn 2 
#define wking 5 
#define wqueen 4 
#define wbishop 3 
#define wknight 6 
#define wrook 7
#define bpawn 12 
#define bking 15 
#define bqueen 14 
#define bbishop 13 
#define bknight 16 
#define brook 17
#define wtabyeet 300
#define btabyeet 400
#define makshoosh 66
#define msh_makshoosh 77
#define elkash_makshoosh 100
int checkmove(int x, int y, int board[][8], int moves[][8], int dir, int dir1); // first move to see the green are to move to
int zero(int moves[8][8]);
int bishop(int x, int y, int selection, int board[8][8], int moves[][8]); //feel
int Rook(int x, int y, int selection, int board[8][8], int moves[][8]);//eltabya
int bishop(int x, int y, int selection, int board[][8], int moves[][8]);
int Rook(int x, int y, int selection, int board[][8], int moves[][8]);
int checksaftymove(int unknown, int unknown2, int selection, int white, int black);
int bordercheck(int x, int y, int board[][8], int selection);
int kingqueen(int x, int y, int selection, int board[][8], int moves[][8]);
int kingboarder(int x, int y, int board[][8], int selection);
int kingrook(int x, int y, int selection, int board[][8], int moves[][8]);
int kingbishop(int x, int y, int selection, int board[][8], int moves[][8]);
int cancelplaces(int x, int y, int board[][8], int moves[][8], int safty[][8]);
int checkmove(int x, int y, int board[][8], int moves[][8], int dir, int dir1);
int calcx(int x);
int calcy(int y);
//-----------------------------------------
int postorow(int x,int y)
{
	int squareHeight = gr.getWindowHeight() / 8; // The X-offset of the board
	int boardYOffset = -15;   // The Y-offset of the board
	return (y - boardYOffset) / squareHeight;
}
int postocolumn(int x, int y) {
	int squareWidth = (gr.getWindowWidth() - 700) / 8;
	int boardXOffset = 340; // The X-offset of the board 
	return (x - boardXOffset) / squareWidth;// The Y-offset of the board
}


int kingboarder(int x, int y, int board[][8], int selection)
{
	if (x >= 8 || x < 0 || y >= 8 || y < 0)//borders 8*8
	{
		return 0;
	}
	else
	{
		if (board[x][y] == 0)
			return 10;

		if (selection > 1 && selection < 8)//white
		{
			if (board[x][y] > 1 && board[x][y] < 8)
				return board[x][y];//frined
			else
				return board[x][y];//enemy
		}
		if (selection > 11 && selection < 18)//black
		{
			if (board[x][y] > 11 && board[x][y] < 18)
				return board[x][y];//frined
			else
				return board[x][y];//enemy
		}
	}
}
int checksaftymove(int unknown, int unknown2, int selection, int white, int black)//lw feh tahded hayrag3 ely bayhaded lw feh friend hayrga3 zero
{
	if (selection == wking && (unknown > 1 && unknown < 7) && unknown2 == black)//king white enemy black bishop
		return unknown2;
	else if (selection == bking && (unknown > 11 && unknown < 17) && unknown2 == white)//king black enwmy is white bishop
		return unknown2;
	else
		return 0;//mafe4 tahded
}
int kingrook(int x, int y, int selection, int board[][8], int moves[][8], int saftypicerook[][8])// el king moves like rook if he find sameone and then find someone hanetcheck lw kan el 2wal freind w eltany rook enemy
{
	saftypicerook[8][8] = { 0 };//ta7ded elements that save the king
	moves[x][y] = selection;
	int unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	for (int i = x + 1; i < 8; i++) {//btemshy l ta7t
		if (selection == wking || selection == bking)
		{
			moves[i][y] = kingboarder(i, y, board, selection);
			if (moves[i][y] != 10)//ay 7aga 
			{
				flag++;
				if (flag == 1 && moves[i][y] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
				{
					unknown = moves[i][y];
					xunknown = i;
					yunknown = y;
				}
				if (flag == 2)
				{
					unknown2 = moves[i][y];
					result = checksaftymove(unknown, unknown2, selection, wrook, brook);//ba5od ely ana msh 3arfhom a3rf homa men 
					moves[i][y] = result;
					if (result != 0)//feh tahded ya3ni feh enemy rook behaind the frind
					{
						saftypicerook[xunknown][yunknown] = unknown;
					}
					else if (result == 0)//mafe4 tahded ya3ni frined wara friend 
					{
						saftypicerook[xunknown][yunknown] = 0;
					}
					break;
				}
			}//end of sec if (!=10)
			else//(=10)
				saftypicerook[i][y] = 10;

		}
	}
	unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	for (int i = x - 1; i >= 0; i--) {//btemshy l foo2
		if (selection == wking || selection == bking)
		{
			moves[i][y] = kingboarder(i, y, board, selection);
			if (moves[i][y] != 10)
			{
				flag++;
				if (flag == 1 && moves[i][y] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
				{
					unknown = moves[i][y];
					xunknown = i;
					yunknown = y;
				}
				if (flag == 2)
				{
					unknown2 = moves[i][y];
					result = checksaftymove(unknown, unknown2, selection, wrook, brook);
					moves[i][y] = result;
					if (result != 0)
					{
						saftypicerook[xunknown][yunknown] = unknown;
					}
					else if (result == 0)
					{
						saftypicerook[xunknown][yunknown] = 0;
					}
					break;
				}
			}
			else//(=10)
				saftypicerook[i][y] = 10;
		}
	}
	unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	for (int j = y + 1; j < 8; j++) {//btemshy l ymeen
		if (selection == wking || selection == bking)
		{
			moves[x][j] = kingboarder(x, j, board, selection);
			if (moves[x][j] != 10)
			{
				flag++;
				if (flag == 1 && moves[x][j] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
				{
					unknown = moves[x][j];
					xunknown = x;
					yunknown = j;
				}
				if (flag == 2)
				{
					unknown2 = moves[x][j];
					result = checksaftymove(unknown, unknown2, selection, wrook, brook);
					moves[x][j] = result;
					if (result != 0)
					{
						saftypicerook[xunknown][yunknown] = unknown;
					}
					else if (result == 0)
					{
						saftypicerook[xunknown][yunknown] = 0;
					}
					break;
				}
			}
			else//(=10)
				saftypicerook[x][j] = 10;
		}
	}
	unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	for (int j = y - 1; j >= 0; j--) {         //btemshy l shemal
		if (selection == wking || selection == bking)
		{
			moves[x][j] = kingboarder(x, j, board, selection);
			if (moves[x][j] != 10)
			{
				flag++;
				if (flag == 1 && moves[x][j] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
				{
					unknown = moves[x][j];
					xunknown = x;
					yunknown = j;
				}
				if (flag == 2)
				{
					unknown2 = moves[x][j];
					result = checksaftymove(unknown, unknown2, selection, wrook, brook);
					moves[x][j] = result;
					if (result != 0)
					{
						saftypicerook[xunknown][yunknown] = unknown;
					}
					else if (result == 0)
					{
						saftypicerook[xunknown][yunknown] = 0;
					}
					break;
				}
			}
			else//(=10)
				saftypicerook[x][j] = 10;
		}
	}
	return 0;
}
int kingbishop(int x, int y, int selection, int board[][8], int moves[][8], int saftypicebishop[][8])
{
	int unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	moves[x][y] = selection;
	saftypicebishop[8][8] = { 0 };
	for (int i = 1; i < 8; i++)//4th Q
	{
		moves[x + i][y + i] = kingboarder(x + i, y + i, board, selection);
		if (moves[x + i][y + i] != 10)
		{
			flag++;
			if (flag == 1 && moves[x + i][y + i] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
			{
				unknown = moves[x + i][y + i];
				xunknown = x + i;
				yunknown = y + i;
			}
			if (flag == 2)
			{
				unknown2 = moves[x + i][y + i];
				result = checksaftymove(unknown, unknown2, selection, wbishop, bbishop);
				moves[x + i][y + i] = result;
				if (result != 0)
				{
					saftypicebishop[xunknown][yunknown] = unknown;
				}
				else if (result == 0)//mafe4 tahded 
				{
					saftypicebishop[xunknown][yunknown] = 0;
				}
				break;
			}
		}
		else//(=10)
			saftypicebishop[x + i][y + i] = 10;
	}
	unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	for (int i = -1; i < 8; i--)//2nd Q
	{
		moves[x + i][y + i] = kingboarder(x + i, y + i, board, selection);
		if (moves[x + i][y + i] != 10)
		{
			flag++;
			if (flag == 1 && moves[x + i][y + i] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
			{
				unknown = moves[x + i][y + i];
				xunknown = x + i;
				yunknown = y + i;
			}
			if (flag == 2)
			{
				unknown2 = moves[x + i][y + i];
				result = checksaftymove(unknown, unknown2, selection, wbishop, bbishop);
				moves[x + i][y + i] = result;
				if (result != 0)
				{
					saftypicebishop[xunknown][yunknown] = unknown;
				}
				else if (result == 0)
				{
					saftypicebishop[xunknown][yunknown] = 0;
				}
				break;
			}
		}
		else//(=10)
			saftypicebishop[x + i][y + i] = 10;
	}
	unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	for (int i = -1; i < 8; i--)//1st Q
	{
		moves[x + i][y - i] = kingboarder(x + i, y - i, board, selection);
		if (moves[x + i][y - i] != 10)
		{
			flag++;
			if (flag == 1 && moves[x + i][y - i] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
			{
				unknown = moves[x + i][y - i];
				xunknown = x + i;
				yunknown = y - i;
			}
			if (flag == 2)
			{
				unknown2 = moves[x + i][y - i];
				result = checksaftymove(unknown, unknown2, selection, wbishop, bbishop);
				moves[x + i][y - i] = result;
				if (result != 0)
				{
					saftypicebishop[xunknown][yunknown] = unknown;
				}
				else if (result == 0)
				{
					saftypicebishop[xunknown][yunknown] = 0;
				}
				break;
			}
		}
		else//(=10)
			saftypicebishop[x + i][y - i] = 10;
	}
	unknown = -1, unknown2 = -1, flag = 0, xunknown = -1, yunknown = -1, result = -1;
	for (int i = -1; i < 8; i--)//3rd Q
	{
		moves[x - i][y + i] = kingboarder(x - i, y + i, board, selection);
		if (moves[x - i][y + i] != 10)
		{
			flag++;
			if (flag == 1 && moves[x - i][y + i] != 10)//en feh 7ad feh el makan dah msh makan yanfa3 2t7ark feh
			{
				unknown = moves[x - i][y + i];
				xunknown = x - i;
				yunknown = y + i;
			}
			if (flag == 2)
			{
				unknown2 = moves[x - i][y + i];
				result = checksaftymove(unknown, unknown2, selection, wbishop, bbishop);
				moves[x - i][y + i] = result;
				if (result != 0)
				{
					saftypicebishop[xunknown][yunknown] = unknown;
				}
				else if (result == 0)
				{
					saftypicebishop[xunknown][yunknown] = 0;
				}
				break;
			}
		}
		else//(=10)
			saftypicebishop[x - i][y + i] = 10;
	}
	return 0;
}
/*
int kingqueen(int x, int y, int selection, int board[][8], int moves[][8])
{
	kingrook(x, y, selection, board, moves,saftypicerook);
	kingbishop(x, y, selection, board, moves,saftypicebishop);
	return 0;
}
*/
int bordercheck(int x, int y, int board[8][8], int selection)
{
	if (x >= 8 || x < 0 || y >= 8 || y < 0)//borders 8*8
	{
		return 0;
	}
	else
	{
		if (board[x][y] == 0)
			return 1;
		if (selection > 1 && selection < 8)//white
		{
			if (board[x][y] > 1 && board[x][y] < 8)
				return 9;//frined
			else if (board[x][y] == bking) {
				return 999;
			}
			else
				return 8;//enemy
		}
		if (selection > 11 && selection < 18)//black
		{
			if (board[x][y] > 11 && board[x][y] < 18)
				return 9;//frined
			else if (board[x][y] == wking) {
				return 999;
			}
			else
				return 8;//enemy
		}
	}
}
//------------------------- peice movement ---------------------------------
int King(int x, int y, int selection, int board[8][8], int moves[][8]) {
	zero(moves);
	moves[x][y] = selection;
	if (x + 1 < 8) {
		moves[x + 1][y] = bordercheck(x + 1, y, board, selection);//ymeen
	}
	if (x - 1 >= 0)
		moves[x - 1][y] = bordercheck(x - 1, y, board, selection);//shemal
	if (y + 1 < 8) {
		moves[x][y + 1] = bordercheck(x, y + 1, board, selection);//ta7t
	}
	if (y - 1 >= 0)
		moves[x][y - 1] = bordercheck(x, y - 1, board, selection);//fo2
	if (x + 1 < 8 && y + 1 < 8)
		moves[x + 1][y + 1] = bordercheck(x + 1, y + 1, board, selection);//diagonal ta7t ymeen
	if (x - 1 >= 0 && y - 1 >= 0) {
		moves[x - 1][y - 1] = bordercheck(x - 1, y - 1, board, selection);//diagonal fo2 shemal
	}
	if (x + 1 < 8 && y - 1 >= 0) {
		moves[x + 1][y - 1] = bordercheck(x + 1, y - 1, board, selection);//diagonal fo2 ymeen
	}
	if (x - 1 >= 0 && y + 1 < 8)
		moves[x - 1][y + 1] = bordercheck(x - 1, y + 1, board, selection);//diagonal ta7t shemal
	return 0;

}
int Queen(int x, int y, int selection, int board[8][8], int moves[][8]) {//wazeer
	moves[x][y] = board[x][y];
	bishop(x, y, selection, board, moves);
	Rook(x, y, selection, board, moves);
	return 0;
}
int bishop(int x, int y, int selection, int board[8][8], int moves[][8]) //feel
{
	zero(moves);
	moves[x][y] = selection;
	for (int i = 1; i < 8; i++)//4th Q
	{
		if (x + i < 8 && y + i < 8) {
			moves[x + i][y + i] = bordercheck(x + i, y + i, board, selection);
			if (moves[x + i][y + i] != 1)
				break;
		}
	}
	for (int i = 1; i < 8; i++)//2nd Q
	{
		if (x - i >= 0 && y - i >= 0) {
				moves[x - i][y - i] = bordercheck(x - i, y - i, board, selection);
					if (moves[x - i][y - i] != 1)
						break;
		}
	}
	for (int i = 1; i < 8; i++)//1st Q
	{
		if (x - i >= 0 && y + i < 8) {
				moves[x - i][y + i] = bordercheck(x - i, y + i, board, selection);
				if (moves[x - i][y + i] != 1)
					break;
		}
	}
	for (int i = 1; i < 8; i++)//3rd Q
	{
		if (x + i < 8 && y - i >= 0) {
				moves[x + i][y - i] = bordercheck(x + i, y - i, board, selection);
				if (moves[x + i][y - i] != 1)
					break;
		}
	}
	return 0;
}
int knight(int x, int y, int selection, int board[][8], int moves[][8]) //hosan
{	moves[x][y] = selection;
	if (x - 2 >= 0 && y + 1 <= 7)
		moves[x - 2][y + 1] = bordercheck(x - 2, y + 1, board, selection);//1
	if (x - 1 >= 0 && y + 2 <= 7)
		moves[x - 1][y + 2] = bordercheck(x - 1, y + 2, board, selection);//2
	if (x + 2 <= 7 && y + 1 <= 7)
		moves[x + 2][y + 1] = bordercheck(x + 2, y + 1, board, selection);//4
	if (x + 1 <= 7 && y + 2 <= 7)
		moves[x + 1][y + 2] = bordercheck(x + 1, y + 2, board, selection);//3
	if (x + 2 <= 7 && y - 1 >= 0)
		moves[x + 2][y - 1] = bordercheck(x + 2, y - 1, board, selection);//5
	if (x + 1 <= 7 && y - 2 >= 0)
		moves[x + 1][y - 2] = bordercheck(x + 1, y - 2, board, selection);//6
	if (x - 1 >= 0 && y - 2 >= 0)
		moves[x - 1][y - 2] = bordercheck(x - 1, y - 2, board, selection);//7
	if (x - 2 >= 0 && y - 1 >= 0)
		moves[x - 2][y - 1] = bordercheck(x - 2, y - 1, board, selection);//8
	return 0;
}
int Pawn(int x, int y, int selection, int board[][8], int moves[][8]) {
	moves[x][y] = board[x][y];
	if (board[x][y] == 2) { // white
		if (board[x - 1][y + 1] > 10) {
			moves[x - 1][y + 1] = 8;
		}
		if (board[x - 1][y - 1] > 10) {
			moves[x - 1][y - 1] = 8;
		}
		if (x == 6) { // first move
			moves[x - 1][y] = bordercheck(x - 1, y, board, board[x][y]);
			if (moves[x - 1][y] == 8 || moves[x - 1][y] == 9) {
				moves[x - 1][y] = 0;
			}
			if (moves[x - 1][y] == 1) {
				moves[x - 2][y] = bordercheck(x - 2, y, board, board[x][y]);
			}
			if (moves[x - 2][y] == 8 || moves[x - 2][y] == 9) {
				moves[x - 2][y] = 0;
			}
		}
		else { //normal
			moves[x - 1][y] = bordercheck(x - 1, y, board, board[x][y]);
			if (moves[x - 1][y] == 8 || moves[x - 1][y] == 9) {
				moves[x - 1][y] = 0;
			}
		}
	}

	if (board[x][y] == 12) { // black
		if (board[x + 1][y + 1] < 10 && board[x + 1][y + 1] != 0) {
			moves[x + 1][y + 1] = 8;
		}
		if (board[x + 1][y - 1] < 10 && board[x + 1][y - 1] != 0) {
			moves[x + 1][y - 1] = 8;
		}
		if (x == 1) { // first move
			moves[x + 1][y] = bordercheck(x + 1, y, board, board[x][y]);
			if (moves[x + 1][y] == 8 || moves[x + 1][y] == 9) {
				moves[x + 1][y] = 0;
			}
			if (moves[x + 1][y] == 1) {
				moves[x + 2][y] = bordercheck(x + 2, y, board, board[x][y]);
				if (moves[x + 2][y] == 8 || moves[x + 2][y] == 9) {
					moves[x + 2][y] = 0;
				}
			}
		}
		else {
			moves[x + 1][y] = bordercheck(x + 1, y, board, board[x][y]);
			if (moves[x + 1][y] == 8 || moves[x + 1][y] == 9) {
				moves[x + 1][y] = 0;
			}
		}
	}
	return 0;
}

int Rook(int x, int y, int selection, int board[8][8], int moves[][8]) {//eltabya
	moves[8][8] = { 0 };
	moves[x][y] = selection;
	for (int i = x + 1;i < 8;i++) {//btemshy l ta7t
		moves[i][y] = bordercheck(i, y, board, selection);
		if (moves[i][y] != 1)
			break;
	}
	for (int i = x - 1;i >= 0;i--) {//btemshy l foo2
		moves[i][y] = bordercheck(i, y, board, selection);
		if (moves[i][y] != 1)
			break;
	}
	for (int j = y + 1;j < 8;j++) {//btemshy l ymeen
		moves[x][j] = bordercheck(x, j, board, selection);
		if (moves[x][j] != 1)
			break;
	}
	for (int j = y - 1;j >= 0;j--) {//btemshy l shemal
		moves[x][j] = bordercheck(x, j, board, selection);
		if (moves[x][j] != 1)
			break;
	}
	return 0;
}
int checkmate(int x, int y, int selection, int board[8][8], int moves[][8], int elykasho[][8]) {
	elykasho[8][8] = { 0 };
	moves[x][y] = selection;
	int counter = 0;
	Rook(x, y, selection, board, moves);
	for (int i = 0; i < 8; i++) {//kesh malek mn eltabya w elwazeer
		for (int j = 0; j < 8; j++) {
			if (moves[i][j] == 8 && (board[i][j] == 17 || board[i][j] == 14 || board[i][j] == 7 || board[i][j] == 4))
			{
				elykasho[i][j] = board[i][j];//3ayzen negeeb maakan ely kasho 
				counter++;
			}
		}
	}

	bishop(x, y, selection, board, moves);
	for (int i = 0; i < 8; i++) {//keshmalek mn elfeel w elwazeer
		for (int j = 0; j < 8; j++) {
			if (moves[i][j] == 8 && (board[i][j] == 13 || board[i][j] == 14 || board[i][j] == 3 || board[i][j] == 4))
			{
				elykasho[i][j] = board[i][j];//3ayzen negeeb maakan ely kasho 
				counter++;
			}
		}
	}
	moves[8][8] = { 0 };
	if (selection < 10 && selection>0) {//kesh malek mn el3askary
		if (board[x - 1][y + 1] == 12) //diagonal fo2 ymeen
		{
			elykasho[x - 1][y + 1] = board[x - 1][y + 1];//3ayzen negeeb maakan ely kasho 
			counter++;
		}
		if (board[x - 1][y - 1] == 12) //diagonal ta7t shemal
		{
			elykasho[x - 1][y - 1] = board[x - 1][y - 1];//3ayzen negeeb maakan ely kasho 
			counter++;
		}
	}
	if (selection > 10) {
		if (board[x + 1][y - 1] == 2)//diagonal ta7t shemal
		{
			elykasho[x + 1][y - 1] = board[x + 1][y - 1];//3ayzen negeeb maakan ely kasho 
			counter++;
		}

		if (board[x + 1][y + 1] == 2) //diagonal ta7t yemeen	
		{
			elykasho[x + 1][y + 1] = board[x + 1][y + 1];//3ayzen negeeb maakan ely kasho 
			counter++;
		}

	}

	knight(x, y, selection, board, moves);
	for (int i = 0; i < 8; i++) {//kesh malek mn el7osan
		for (int j = 0; j < 8; j++) {
			if (moves[i][j] == 8 && (board[i][j] == 16 || board[i][j] == 6)) {
				counter++;
				elykasho[i][j] = board[i][j];//3ayzen negeeb maakan ely kasho 
			}
		}
	}
	King(x, y, selection, board, moves);
	for (int i = 0; i < 8; i++) {//kesh malek mn king
		for (int j = 0; j < 8; j++) {
			if (moves[i][j] == 8 && (board[i][j] == 15 || board[i][j] == 5)) {
				counter++;
				elykasho[i][j] = board[i][j];//3ayzen negeeb maakan ely kasho 
			}
		}
	}

	if (counter > 0)
		return makshoosh;
	else
		return msh_makshoosh;
}
int check(int x, int y, int selection, int board[8][8], int moves[][8], int enemy[][8])
{
	moves[x][y] = selection;
	int counter = 0;
	int counter1 = 0;
	Rook(x, y, selection, board, moves);

	printf("moves\n");
	for (int i = 0; i < 8; i++) {//kesh malek mn eltabya w elwazeer
		for (int j = 0; j < 8; j++) {

			if (moves[i][j] == 8 && (board[i][j] == wrook || board[i][j] == brook || board[i][j] == wqueen || board[i][j] == bqueen))
			{
				enemy[i][j] = 8;
				counter++;
			}


		}
	}

	bishop(x, y, selection, board, moves);
	for (int i = 0; i < 8; i++) {//keshmalek mn elfeel w elwazeer
		for (int j = 0; j < 8; j++) {

			if (moves[i][j] == 8 && (board[i][j] == wbishop || board[i][j] == bbishop || board[i][j] == wqueen || board[i][j] == bqueen))
			{
				enemy[i][j] = 8;
				counter++;
			}


		}
	}
	moves[8][8] = { 0 };
	if (selection < 10 && selection>0) {//kesh malek mn el3askary
		if (board[x - 1][y + 1] == 12) {//diagonal fo2 ymeen 			
			enemy[x - 1][y + 1] = 8;
			counter++;
		}
		if (board[x - 1][y - 1] == 12) {//diagonal ta7t shemal			
			enemy[x - 1][y - 1] = 8;
			counter++;
		}
	}
	if (selection > 10) {
		if (board[x + 1][y - 1] == 2) {//diagonal ta7t shemal			
			enemy[x + 1][y - 1] = 8;
			counter++;
		}

		if (board[x + 1][y + 1] == 2) {//diagonal ta7t yemeen			
			enemy[x + 1][y + 1] = 8;
			counter++;
		}
	}
	knight(x, y, selection, board, moves);
	for (int i = 0; i < 8; i++) {//kesh malek mn el7osan
		for (int j = 0; j < 8; j++) {
			if (moves[i][j] == 8 && (board[i][j] == wknight || board[i][j] == bknight))
			{
				enemy[i][j] = 8;
				counter++;
			}
		}
	}
	if (counter > 0)
		return makshoosh;
	else
		return msh_makshoosh;

}

int test(int x, int y, int king, int board[][8], int temp[][8], int moves[][8])
{
	if (king == wking)

	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == brook)
					Rook(i, j, brook, board, moves);
				if (moves[x][y] == temp[x][y])
					temp[x][y] = 0;

				if (board[i][j] == bqueen)
					Queen(i, j, bqueen, board, moves);
				if (moves[x][y] == temp[x][y])
					temp[x][y] = 0;

				if (board[i][j] == bpawn)
					Pawn(i, j, bpawn, board, moves);
				if (moves[x][y] == 1 && temp[x][y] == 1 || moves[x][y] == 8 && temp[x][y] == 8)
					temp[x][y] = 0;

				if (board[i][j] == bking)
					King(i, j, bking, board, moves);
				if (moves[x][y] == 1 && temp[x][y] == 1 || moves[x][y] == 8 && temp[x][y] == 8)
					temp[x][y] = 0;

				if (board[i][j] == bbishop)
					bishop(i, j, bbishop, board, moves);
				if (moves[x][y] == 1 && temp[x][y] == 1 || moves[x][y] == 8 && temp[x][y] == 8)
					temp[x][y] = 0;

			}
		}
	}
	if (king == bking)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == wrook)
					Rook(i, j, wrook, board, moves);
				if (moves[x][y] == temp[x][y])
					temp[x][y] = 0;

				if (board[i][j] == wqueen)
					Queen(i, j, wqueen, board, moves);
				if (moves[x][y] == temp[x][y])
					temp[x][y] = 0;

				if (board[i][j] == wpawn)
					Pawn(i, j, wpawn, board, moves);
				if (moves[x][y] == 1 && temp[x][y] == 1 || moves[x][y] == 8 && temp[x][y] == 8)
					temp[x][y] = 0;

				if (board[i][j] == wking)
					King(i, j, wking, board, moves);
				if (moves[x][y] == 1 && temp[x][y] == 1 || moves[x][y] == 8 && temp[x][y] == 8)
					temp[x][y] = 0;

				if (board[i][j] == wbishop)
					bishop(i, j, wbishop, board, moves);
				if (moves[x][y] == 1 && temp[x][y] == 1 || moves[x][y] == 8 && temp[x][y] == 8)
					temp[x][y] = 0;

			}
		}

	}
	printf("\n");
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d  ", moves[i][j]);
		}
		printf("\n");
	}
	*/

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%d  ", temp[i][j]);
		}
		printf("\n");
	}
	printf("\nmoves of test");
	return 0;
}

int kingmove(int x, int y, int king, int board[][8], int moves[][8]) {//btshoof law elmalek yenfa3 yet7arak	
	int counter1 = 0, counter = 0, flag = 1;
	int temp[8][8] = { 0 };
	King(x, y, king, board, moves);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			temp[i][j] = moves[i][j];
			moves[i][j] = 0;
		}
		printf("\n");
	}
	printf("\n");


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (temp[i][j] == 1 || temp[i][j] == 8)
			{
				counter++;
				test(i, j, king, board, temp, moves);
			}//end of if
		}//end of inner loop
	}//end of outer loop
	/*

	printf("temp");
	*/
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d", temp[i][j]);
		}
		printf("\n");
	}
	if (counter1 == counter)
		return makshoosh;//king cant move
	else
		return msh_makshoosh;//king can move
}
int piecekill(int x, int y, int selection, int board[][8], int moves[][8], int enemy[][8]) {
	//btshoof law elpiece momken tetakel mn ay 7ad 3shan ne7my elmalek
	int a;
	enemy[8][8] = { 0 };
	check(x, y, selection, board, moves, enemy);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (enemy[i][j] == 8) {
				//enemy[8][8] = { 0 };
				a = check(i, j, selection, board, moves, enemy);
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						printf("%d", enemy[i][j]);
					}
					printf("\n");
				}
				printf("enemy\n ");
				if (a == 66) {//elkash makshosh
					return makshoosh;
				}
				else
					return msh_makshoosh;
			}
		}
	}
	return 0;
}
int safty(int x, int y, int king, int board[][8], int moves[][8], int saftypicerook[][8], int saftypicebishop[][8])
{

	moves[8][8] = { 0 };
	kingrook(x, y, king, board, moves, saftypicerook);


	kingbishop(x, y, king, board, moves, saftypicebishop);

	moves[8][8] = { 0 };
	printf("\n=================\n");
	/*
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d  ", moves[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d  ", saftypicerook[i][j]);
			}
			printf("\n");
		}
		printf("\n=================\n");

		*/

		/*for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d  ", moves[i][j]);
			}
			printf("\n");
		}
		printf("safty moves\n");
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d  ", saftypicebishop[i][j]);
			}
			printf("\n");
		}
		printf("safty safty\n");
		kingqueen(x, y, king, board, moves);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d  ", moves[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				printf("%d  ", board[i][j]);
			}
			printf("\n");
		}
		*/




	return 0;
}
int cancelplaces(int x, int y, int board[][8], int moves[][8], int safty[][8])
{
	moves[8][8] = { 0 };
	if (board[x][y] == wpawn || board[x][y] == bpawn)
		Pawn(x, y, board[x][y], board, moves);

	if (board[x][y] == wknight || board[x][y] == bknight)
		knight(x, y, board[x][y], board, moves);

	if (board[x][y] == wqueen || board[x][y] == bqueen)
		Queen(x, y, board[x][y], board, moves);

	if (board[x][y] == wrook || board[x][y] == brook)
		Rook(x, y, board[x][y], board, moves);

	if (board[x][y] == wbishop || board[x][y] == bbishop)
		bishop(x, y, board[x][y], board, moves);
	/*
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d  ", moves[i][j]);
		}
		printf("\n");
	}
	printf("cancel moves\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d  ", safty[i][j]);
		}
		printf("\n");
	}
	printf("cancel saftyrook\n");
	printf("moves of cancel\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d  ", moves[i][j]);
		}
		printf("\n");
	}
	printf("cancel moves\n");
	*/

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (moves[i][j] == 1 && safty[i][j] == 10)
			{
				moves[i][j] = 1;
			}
			else if (safty[i][j] == 10 || moves[i][j] == 10 || moves[i][j] == 1)
			{
				moves[i][j] = 0;
			}
		}
	}

	return 0;
}
int squaremove(char c, int* x, int* y, int board[8][8], int moves[8][8], int dir, int dir1)
{
	int squareWidth = (gr.getWindowWidth() - 700) / 8;
	int squareHeight = gr.getWindowHeight() / 8;
	int boardXOffset = 340; // The X-offset of the board
	int boardYOffset = -15;   // The Y-offset of the board
	if (c == 'w') {
		*y = (*y) - (gr.getWindowHeight() / 8) + 3;
	}	
	else if (c == 's') {
		*y = *y + (gr.getWindowHeight() / 8	) - 3;
	}
	else if (c == 'a') {
		*x = *x - ((gr.getWindowWidth() - 700) / 8) + 3;
	}
	else if (c == 'd') {
		*x = *x + ((gr.getWindowWidth() - 700) / 8) - 3;
	}
	if (c == 'W') {
		*x = (*x) + ((gr.getWindowHeight() - 700) / 8)+3;
	}
	else if (c == 'S') {
		*x = *x - ((gr.getWindowHeight() - 700) / 8)-3;
	}
	else if (c == 'A') {
		*y = *y - ((gr.getWindowWidth() - 700) / 8)+3;
	}
	else if (c == 'D') {
		*y = *y + ((gr.getWindowWidth() - 700) / 8)-3;
	}
	else if (c == 32) {
		int col = (*x - boardXOffset) / squareWidth;
		int row = (*y-boardYOffset) / squareHeight;

		// Ensure the calculated indices are within bounds
		if (col >= 0 && col < 8 && row >= 0 && row < 8) {
			// Perform a move check
			checkmove(row, col, board, moves, dir, dir1);
		}
		else {
			return 0;
		}
	}
}
int canmove(int moves[][8], int x, int y, int dir, int dir1) {
	if (moves[x][y] == 1) {
		if (x == 8 && y == 8) {
			moves[8][8] = { 0 };
		}
		return dir;
	}
	else if (moves[x][y] == 8) {
		if (x == 8 && y == 8) {
			moves[8][8] = { 0 };
		}
		return dir1;
	}
	else if (moves[x][y] == 999) {
		return dir1;
	}

	//else
		//return NULL;
}
int checkmove(int x, int y, int board[][8], int moves[][8], int dir, int dir1) { // first move to see the green are to move to

	if (board[x][y] == wrook) {
		Rook(x, y, wrook, board, moves);
	}
	else if (board[x][y] == wknight) {
		knight(x, y, wknight, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == wbishop) {
		bishop(x, y, wbishop, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == wqueen) {
		Queen(x, y, wqueen, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == wking) {
		King(x, y, wking, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == wpawn) {
		Pawn(x, y, wpawn, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == brook) {
		Rook(x, y, brook, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == bknight) {
		knight(x, y, bknight, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == bbishop) {
		bishop(x, y, bbishop, board, moves);
		//	return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == bqueen) {
		Queen(x, y, bqueen, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == bking) {
		King(x, y, bking, board, moves);
		//return canmove(moves, x, y, dir, dir1);
	}
	else if (board[x][y] == bpawn) {
		Pawn(x, y, bpawn, board, moves);
		//	return canmove(moves, x, y, dir, dir1);
	}
	else
		return 0;
}
int calcx(int x)
{
	int square = (gr.getWindowWidth() - 700) / 8;
	return square / 3 + 350 + ((((gr.getWindowWidth() - 700) - 8) / 8) * x);
}
int calcy(int y)
{
	int square = 20;
	return square + ((((gr.getWindowHeight()) / 8) - 2) * y);
}
int drawp(int board[8][8], int warr[6], int barr[6], int x, int y) {
	if (board[x][y] == wrook)
		return warr[0];
	else if (board[x][y] == wbishop)
		return warr[1];
	else if (board[x][y] == wknight)
		return warr[2];
	else if (board[x][y] == wqueen)
		return warr[3];
	else if (board[x][y] == wking)
		return warr[4];
	else if (board[x][y] == wpawn)
		return warr[5];
	else if (board[x][y] == brook)
		return barr[0];
	else if (board[x][y] == bbishop)
		return barr[1];
	else if (board[x][y] == bknight)
		return barr[2];
	else if (board[x][y] == bqueen)
		return barr[3];
	else if (board[x][y] == bking)
		return barr[4];
	else if (board[x][y] == bpawn)
		return barr[5];
	else
		return NULL;
}
// testing
// this function is provided by alot of searcing and alittle bit of AI ( chat GPT) to endure that is satisfies with the library and baord
int zero(int moves[8][8]) {
	for (int i = 0;i < 8;i++)
		for (int j = 0; j < 8; j++) {
			moves[i][j] = 0;
		}
	return 0;
}
int replace(int x, int y,int xold,int yold , int selection, int board[8][8], int moves[][8],int wd[16], int bd[16],int *wi,int*bi) {
	selection = board[xold][yold];
	if (moves[x][y] == 1) {
		board[x][y] = selection;
		board[xold][yold] = 0;
		PlaySound(TEXT("move-self.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 1;
	}
	else if (moves[x][y] == 8) {
		if (board[x][y] > 10){
			wd[*wi] = board[x][y];
			(*wi)++;
			
		}
		else if (board[x][y] < 10) {
			bd[*bi] = board[x][y];
			(*bi)++;
			
		}
		board[x][y] = selection;
		board[xold][yold] = 0;
		PlaySound(TEXT("capture.wav"), NULL, SND_FILENAME | SND_ASYNC);
		return 2;
	}
	else
		return 0;
}
int checkpd( int warr[6], int barr[6],int x, int arr[12]) {
	if (arr[x] == wrook)
		return warr[0];
	else if (arr[x] == wbishop)
		return warr[1];
	else if (arr[x] == wknight)
		return warr[2];
	else if (arr[x] == wqueen)
		return warr[3];
	else if (arr[x] == wking)
		return warr[4];
	else if (arr[x] == wpawn)
		return warr[5];
	else if (arr[x] == brook)
		return barr[0];
	else if (arr[x] == bbishop)
		return barr[1];
	else if (arr[x] == bknight)
		return barr[2];
	else if (arr[x] == bqueen)
		return barr[3];
	else if (arr[x] == bking)
		return barr[4];
	else if (arr[x] == bpawn)
		return barr[5];
	else
		return NULL;
}
//Declare instance from the Graphics Library
int main()
{
	gr.setup();
	gr.setFullScreenMode();
	gr.showCursor();
	int background, warr[6], barr[6], moves[8][8] = { 0 }, dir, t, dir1, m, flag = 1, xm = 360 + (gr.getWindowWidth() - 700) / 8, ym = 10, x, y, xold, yold, flag2 = 1, turn = 0, wd[12] = { 0 }, bi = 0, wi = 0, bd[12] = { 0 }, tmp7 = 10, tmp8 = 10, enemy[8][8] = {0},tmpx=0,tmpy=0,tmp999=0;
	int board[8][8] =
	{ {17,16,13,14,15,13,16,17},
	 {12,12,12,12,12,12,12,12},
		{0,0,0,0,0,0,0,0} ,
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2},
		{7,6,3,4,5,3,6,7} };
	printf("loading....");
	background = gr.loadImage("board0.png");
	warr[0] = gr.loadImage("white0.png");
	warr[1] = gr.loadImage("white1.png");
	warr[2] = gr.loadImage("white2.png");
	warr[3] = gr.loadImage("white3.png");
	warr[4] = gr.loadImage("white4.png");
	warr[5] = gr.loadImage("white5.png");
	barr[0] = gr.loadImage("black0.png");
	barr[1] = gr.loadImage("black1.png");
	barr[2] = gr.loadImage("black2.png");
	barr[3] = gr.loadImage("black3.png");
	barr[4] = gr.loadImage("black4.png");
	barr[5] = gr.loadImage("black5.png");
	dir = gr.loadImage("direction.png");
	dir1 = gr.loadImage("direction 2.png");
	m = gr.loadImage("main.png");
	//PlaySound(TEXT("chess.wav"), NULL, SND_FILENAME | SND_ASYNC);
	printf("loaded");
	gr.resizeImage(background, gr.getWindowWidth() - 700, gr.getWindowHeight());
	gr.resizeImage(warr[0], 80, 110);
	gr.resizeImage(warr[1], 80, 110);
	gr.resizeImage(warr[2], 80, 110);
	gr.resizeImage(warr[3], 80, 110);
	gr.resizeImage(warr[4], 80, 110);
	gr.resizeImage(warr[5], 80, 110);
	gr.resizeImage(barr[0], 80, 110);
	gr.resizeImage(barr[1], 80, 110);
	gr.resizeImage(barr[2], 80, 110);
	gr.resizeImage(barr[3], 80, 110);
	gr.resizeImage(barr[4], 80, 110);
	gr.resizeImage(barr[5], 80, 110);
	gr.resizeImage(dir, (gr.getWindowWidth() - 700) / 8, gr.getWindowHeight() / 8);
	gr.resizeImage(dir1, (gr.getWindowWidth() - 700) / 8, gr.getWindowHeight() / 8);
	gr.resizeImage(m, (gr.getWindowWidth() - 700) / 8, gr.getWindowHeight() / 8);
	while (1) {
		gr.beginDraw();
		gr.setDrawingColor(gr.generateFromRGB(0, 0, 0));
		gr.drawSolidRectangle(0, 0, gr.getWindowWidth(), gr.getWindowHeight());
		gr.drawImage(background, 350, 0, NULL);
		if (flag == 1) {
			for (int i = 0;i < 8;i++) // Green squares
				for (int j = 0; j < 8; j++) {
					gr.drawImage(canmove(moves, i, j, dir, dir1), calcx(j) -39-1.5*j , calcy(i)-9-1*i, gr.generateFromRGB(255,255,255));
				}
		}
		for (int i = 0;i < 8;i++) // FOR PIECES
			for (int j = 0; j < 8; j++) {
				gr.drawImage(drawp(board, warr, barr, i, j), calcx(j), calcy(i), NULL);
			}
		gr.drawImage(m, xm, ym, NULL);
		for (int i = 0;i < 9;i++) {
			gr.drawImage(checkpd(warr,barr,i,wd), 10+30*i, 10, NULL);
			gr.drawImage(checkpd(warr, barr, i, bd), 350 + (gr.getWindowWidth() - 700) + 30 * i, 10, NULL);
		}
		for (int i = 9;i < 12;i++) {
			gr.drawImage(checkpd(warr, barr, i, wd), 10 + 30 * (i-9), 150, NULL);
			gr.drawImage(checkpd(warr, barr, i, bd), 350 + (gr.getWindowWidth() - 700) + 30 * (i-9), 150, NULL);
		}
		gr.endDraw();
		if (kbhit()) {
			char c = getch();
			if (c == 'w') {
				if (20 <= (ym)) {
					squaremove(c, &xm, &ym, board, moves, dir, dir1);
				}
			}
			else if (c == 's') {
				if (ym <= gr.getWindowHeight() - 150) {
					squaremove(c, &xm, &ym, board, moves, dir, dir1);
				}
			}
			else if (c == 'a') {
				if (xm > 400) {
					squaremove(c, &xm, &ym, board, moves, dir, dir1);
				}
			}
			else if (c == 'd') {
				if (xm < gr.getWindowWidth()-350-250) {
					squaremove(c, &xm, &ym, board, moves, dir, dir1);
				}
			}
			if (c == 'W') {
				if (20 <= (ym)) {
					squaremove(c, &xm, &ym, board, moves, dir, dir1);
				}
			}
			else if (c == 'S') {
				if (ym <= gr.getWindowHeight() - 150) {
					squaremove(c, &xm, &ym, board, moves, dir, dir1);
				}
			}
			else if (c == 'A') {
				squaremove(c, &xm, &ym, board, moves, dir, dir1);
			}
			else if (c == 'D') {
				squaremove(c, &xm, &ym, board, moves, dir, dir1);
			}
			else if (c == 32)
			{	
				if (turn==0){ // white
					if (flag2 == 1) { // to make firts moveent and second movement
						xold = postorow(xm, ym);
						yold = postocolumn(xm, ym);
						if (board[xold][yold] < 10 && board[xold][yold] > 0) { // to select to piece to move
							for (int i = 0;i < 8;i++)
								for (int j = 0; j < 8; j++)
									if (board[i][j] == wking) {
										tmpx = i;
										tmpy = j;
									}
							if (checkmate(tmpx, tmpy, board[tmpx][tmpy], board, moves, enemy) == makshoosh) {
								for (int i = 0;i < 8;i++)
									for (int j = 0; j < 8; j++)
										if (enemy[i][j] !=0) {
											tmp999=piecekill(i, j, board[i][j], board, moves, enemy);
										}
								if (tmp999 == makshoosh) {
									squaremove(c, &xm, &ym, board, moves, dir, dir1);
									flag2 = 0;
								}
								else if (tmp999 == msh_makshoosh) {
									exit(1);
								}
							}
							squaremove(c, &xm, &ym, board, moves, dir, dir1);
							flag2 = 0;
						}
					}
					else if (flag2 == 0) { // to make the piece move after it is selected
						x = postorow(xm, ym);
						y = postocolumn(xm, ym);

						t = replace(x, y, xold, yold, board[x][y], board, moves, wd, bd, &wi, &bi);
						// if replace ==1 then zero the moves
						flag2 = 1;
						zero(moves);
						if (t != 0)
							turn = 1;
					}
				}// white
				else if (turn == 1) {
					if (flag2 == 1) {
						xold = postorow(xm, ym);
						yold = postocolumn(xm, ym);
						if (board[xold][yold] > 10 ) { 
							for (int i = 0;i < 8;i++)
								for (int j = 0; j < 8; j++)
									if (board[i][j] == bking) {
										tmpx = i;
										tmpy = j;
									}
							if (checkmate(tmpx, tmpy, board[tmpx][tmpy], board, moves, enemy) == makshoosh) {
								for (int i = 0;i < 8;i++)
									for (int j = 0; j < 8; j++)
										if (enemy[i][j] != 0) {
											tmp999 = piecekill(i, j, board[i][j], board, moves, enemy);
										}
								if (tmp999 == makshoosh) {
									squaremove(c, &xm, &ym, board, moves, dir, dir1);
									flag2 = 0;
								}
								else if (tmp999 == msh_makshoosh) {
									exit(1);
								}
							}
							squaremove(c, &xm, &ym, board, moves, dir, dir1);
							flag2 = 0;
						}
					}
					else if (flag2 == 0) { // to make the piece move after it is selected
						x = postorow(xm, ym);
						y = postocolumn(xm, ym);
						t=replace(x, y, xold, yold, board[x][y], board, moves,wd,bd,&wi,&bi);
						// if replace ==1 then zero the moves
						flag2 = 1;
						zero(moves);
						if (t != 0)
							turn = 0;

					}
				}
	
				
			}
		}
	}
}
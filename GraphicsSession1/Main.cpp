#include <stdio.h>
#include "CC212SGL.h"

//Link to the Graphics .lib file
#pragma comment(lib, "CC212SGL.lib")

//Declare instance from the Graphics Library
CC212SGL gr;

float circle_x = 100, circle_y = 100;
float circle2_x = 100, circle2_y = 100;


int main()
{
	gr.setup();
	gr.setFullScreenMode();
	gr.hideCursor();

	while (true) //Endless loop to redner the graphics and perform the logic
	{
		//All renderings must be placed in-between the beginDraw and endDraw functions
		gr.beginDraw();

		gr.setDrawingColor(COLORS::LIME);
		gr.drawCircle(circle_x, circle_y, 200);

		gr.setDrawingColor(COLORS::RED);
		gr.drawCircle(circle2_x, circle2_y+=0.5, 200);

		gr.endDraw();
	
		if (kbhit()) //returns true only if the user presses on the keyboard
		{
			char c = getch(); //Blocking call. It needs kbhit()/
			if (c == 'A')
				circle_x--;
			else if (c == 'D')
				circle_x++;
		}
		//Some processing and calculations
		//circle_x += 1;

	}

	return 0;
}
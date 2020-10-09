//#include <stdbool.h>
//#include <stddef.h>
//#include <stdint.h>
#include <tice.h>
//#include <math.h>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
//#include <fileioc.h>
//#include <debug.h>
//#include <fontlibc.h>

// ++ GLOBAL VARIABLES ++
	int globalColorVariable; //used in setColorProper
// -- GLOBAL VARİABLES --

void setColorProper(int color) {
	globalColorVariable = color;
	gfx_SetColor(color);
}

int getColorProper() {
	return globalColorVariable;
}

void printCenter(const char *str) { //for debug purposes
	//clear the print area
	setColorProper(255);
	gfx_FillRectangle((LCD_WIDTH - gfx_GetStringWidth(str)) / 2,
	                  ((LCD_HEIGHT - 8) / 2),
	                  gfx_GetStringWidth(str),
	                  10);
	//actually print
	setColorProper(0);
	gfx_PrintStringXY(str,
	                  (LCD_WIDTH - gfx_GetStringWidth(str)) / 2,
	                  (LCD_HEIGHT - 8) / 2);
}

void clearBox(int boxNumber) {
	// clear the ui boxes by index
	boxNumber -= 1; //let numbering start from 1, may be a bad decision
	
	//store for later use
	int tempColorVar;
	tempColorVar = getColorProper();

	setColorProper(255);
	gfx_FillRectangle((boxNumber * (LCD_WIDTH / 5))+1,
	                  (LCD_HEIGHT - (LCD_HEIGHT / 10))+1,
	                  (LCD_WIDTH / 5)-2,
	                  (LCD_HEIGHT / 10)-2);
	
	//restore old value
	setColorProper(tempColorVar);
}

void drawUI() {
	//draw boxes in the bottom
	setColorProper(0);
	gfx_Rectangle((0),
	              (LCD_HEIGHT-(LCD_HEIGHT/10)),
	              (LCD_WIDTH/5),
	              (LCD_HEIGHT/10)); //will be buy

	gfx_Rectangle((LCD_WIDTH/5),
	              LCD_HEIGHT-(LCD_HEIGHT/10),
	              (LCD_WIDTH/5),
	              (LCD_HEIGHT/10)); //will be money

	gfx_Rectangle((LCD_WIDTH/5)*2,
	              LCD_HEIGHT-(LCD_HEIGHT/10),
	              ((LCD_WIDTH/5)),
	              (LCD_HEIGHT/10)); //will be price

	gfx_Rectangle((LCD_WIDTH/5)*3,
	              LCD_HEIGHT-(LCD_HEIGHT/10),
	              ((LCD_WIDTH/5)),
	              (LCD_HEIGHT/10)); //will be dollals

	gfx_Rectangle(LCD_WIDTH-(LCD_WIDTH/5),
	              LCD_HEIGHT-(LCD_HEIGHT/10),
	              (LCD_WIDTH/5),
	              (LCD_HEIGHT/10)); //will be sell
	
	//clear boxes from graph points; money, price, and dollals are not filled because they already get cleared when printing
	clearBox(1); //buy
	clearBox(5); //sell

	//draw text for the boxes
	gfx_PrintStringXY("buy",
	                  ((LCD_WIDTH/5)*0 + ((LCD_WIDTH/5) - gfx_GetStringWidth("buy"))/2),
	                  ((LCD_HEIGHT-4)-((LCD_HEIGHT/10)/2)));

	gfx_PrintStringXY("sell",
	                  (LCD_WIDTH-((LCD_WIDTH/5)/2)-(gfx_GetStringWidth("sell")/2)),
	                  ((LCD_HEIGHT-4)-((LCD_HEIGHT/10)/2)));
}

void printMoney(int money) { //money rectangle on the bottom
	char strMoney[9] = ""; //initialise char so you can sprintf to it
	sprintf(strMoney,"%8d",money); //sprintf int to str so you can print it
	setColorProper(255); //you appartently have to set color before FillRecrangle
	clearBox(2);

	gfx_PrintStringXY(strMoney,
	                  ((LCD_WIDTH/5)*1 + ((LCD_WIDTH/5) - gfx_GetStringWidth(strMoney))/2),
	                  ((LCD_HEIGHT-4)-((LCD_HEIGHT/10)/2))); //print to box with coords
} //same for the rest of the printThing functions

void printPrice(int price) { //price rectangle on the bottom
	char strPrice[9] = "";
	sprintf(strPrice,"%8d",price);
	clearBox(3);

	gfx_PrintStringXY(strPrice,
	                  ((LCD_WIDTH/5)*2 + ((LCD_WIDTH/5) - gfx_GetStringWidth(strPrice))/2),
	                  ((LCD_HEIGHT-4)-((LCD_HEIGHT/10)/2)));
}

void printDollals(int dollals) { //dollal rectangle on the bottom
	char strDollals[9] = "";
	sprintf(strDollals,"%8d",dollals);
	clearBox(4);

	gfx_PrintStringXY(strDollals,
	                  ((LCD_WIDTH/5)*3 + ((LCD_WIDTH/5) - gfx_GetStringWidth(strDollals))/2),
	                  ((LCD_HEIGHT-4)-((LCD_HEIGHT/10)/2)));
}

// ++ GLOBAL VARIABLES FOR graphPoint ++
	int previousPoint[2];
	char debug[10] = "";
	//int tempColorVar;
// -- GLOBAL VARIABLES FOR graphPoint --


void graphPoint(int value,int max,int index, int drawMode) {
	static int usableScreenHeight = 9*(LCD_HEIGHT/10);
	static int columns = 160;
	int columnSize = (LCD_WIDTH/columns);

	if (index%columns == 0) {
		previousPoint[0] = index;
		previousPoint[1] = value;
		gfx_SetColor(255);
		gfx_FillRectangle(0,0,LCD_WIDTH,usableScreenHeight);
	}

	gfx_SetColor(0);

	if (drawMode == 0) { //draw as line
		//draw the line
		gfx_Line((previousPoint[0]%columns)*columnSize,
				((max - previousPoint[1])*usableScreenHeight)/max,
				(index%columns)*columnSize,
				((((max - value)*usableScreenHeight))/max));
	} else { //draw as point
		gfx_FillRectangle((previousPoint[0]%columns)*columnSize,
		                  (((max - previousPoint[1])*usableScreenHeight))/max,
		                  5,
		                  5);
	}

	previousPoint[0] = index;
	previousPoint[1] = value;

	//graph the point right now
	//gfx_FillRectangle((index%columns)*columnSize,
	//                  ((((max - value)*usableScreenHeight))/max),
	//                  2,
	//                  2);

}
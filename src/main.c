#include <tice.h>
#include <stdio.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>

#include "functions.h"

void main() {
	gfx_Begin();
	setColorProper(0);

	drawUI(); //draw boxes in the bottom

	srand(rtc_Time()); //seed the pseudo random generator, for pricing

	//all of the following are used in the main loop
	int currentPrice;
	currentPrice = 500;

	int loopNumber;
	loopNumber = 0;

	int money;

	int dollals;
	dollals = 0;

	int exitVar;
	exitVar = 0;

	int priceLoop;
	priceLoop = 0;

	int btnPressed;
	btnPressed = 0;

	int drawMode;
	drawMode = 0;

	//used in r/w operations
	ti_var_t fileVar;
	char writeString[6] = "";
	char readString[6] = "";

	ti_CloseAll(); //close any files that may be open already

	//load money
	fileVar = ti_Open("moneyVar","r");
	ti_GetC(fileVar);
	ti_Read(readString,sizeof(readString),1,fileVar);
	if (atoi(readString) == 0) {
		money = 1000;
	} else {
		money = atoi(readString);
	}
	ti_CloseAll();

	//load dollals
	fileVar = ti_Open("dllalVar","r");
	ti_GetC(fileVar);
	ti_Read(readString,sizeof(readString),1,fileVar);
	dollals = atoi(readString);
	ti_CloseAll();

	while (true) { //main loop
		loopNumber += 1;
		kb_Scan();

		if (kb_Data[6] & kb_Clear) {
			//write money
			fileVar = ti_Open("moneyVar","w");
			ti_PutC("a",fileVar);
			sprintf(writeString,"%d",money);
			ti_Write(writeString,sizeof(writeString),1,fileVar);
			ti_CloseAll();

			//write dollals
			fileVar = ti_Open("dllalVar","w");
			ti_PutC("a",fileVar);
			sprintf(writeString,"%d",dollals);
			ti_Write(writeString,sizeof(writeString),1,fileVar);
			ti_CloseAll();
			break;
			}; //quit if clear is pressed, clear is at block 6

		if ((kb_Data[1] & kb_Yequ) && (btnPressed == 0)&& (currentPrice < money)) { //buy
			money -= currentPrice;
			dollals++;
			btnPressed = 1;
		};

		if ((kb_Data[1] & kb_Graph) && (btnPressed == 0) && (dollals > 0)) { //sell
			money += currentPrice;
			dollals--;
			btnPressed = 1;
		};

		if (kb_Data[1] & kb_Mode) { //change draw mode
			if (drawMode == 0) {drawMode = 1;} else
			if (drawMode == 1) {drawMode = 0;}
		}

		if ((loopNumber % 100) == 0) {
			priceLoop += 1;
			//price set
			if (currentPrice < 0)   {currentPrice = 50;} else 
			if (currentPrice < 200) {currentPrice += (random()%50)-20;} else
			if (currentPrice > 900) {currentPrice += (random()%50)-30;} else
			{currentPrice += ((random()%50)-25);}
			printMoney(money);
			printPrice(currentPrice);
			printDollals(dollals);
			graphPoint(currentPrice,1000,priceLoop,drawMode);
			drawUI(); //redraw because blob gets onto buy and sell, annoying; can safely be removed after line graphing is implemented.
			btnPressed = 0; //reset button presses, allow buy and sell at the start of next loop
		};
	};
	gfx_End();
}
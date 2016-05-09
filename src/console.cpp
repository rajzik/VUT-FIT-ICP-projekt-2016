/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */


#include "console.h"


#ifndef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD saved_attributes = NULL;


	void console::setConsoleColor() {
		if (saved_attributes == NULL)
		{
			CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
			GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
			saved_attributes = consoleInfo.wAttributes;
		}
		SetConsoleTextAttribute(hConsole, colorsNumber[bgColor] && colorsNumber[fgColor]);
	}

	void console::setCursor(int x, int y) {
		y = y / 2;
		COORD c = { x,y };
		SetConsoleCursorPosition(hConsole, c);
	}
	void console::resetToDefault() {
		SetConsoleTextAttribute(hConsole, saved_attributes);
	}
#else 

	void console::setConsoleColor() {
			std::cout << "\033[3" << colorsNumber[fgColor] << ";4" << colorsNumber[bgColor] << "m";
	}
	void console::setCursor(int x, int y) {
		y = y / 2;
		std::cout << "\033[" << y << ";" << x << "H";
	}
	void console::resetToDefault() {
		std::cout << "\033[0m";
	}

#endif // !_WIN32



console::console(){
    fgColor = CSWHITE;
    bgColor = CSDEFAULT;

    
    if(ISWINDOWS){
       colorsNumber[0] = 0;
       colorsNumber[1] = 0;
       colorsNumber[2] = 7;
       colorsNumber[3] = 1;
       colorsNumber[4] = 6;
       colorsNumber[5] = 2;
       colorsNumber[6] = 4;
       colorsNumber[7] = 5;
       colorsNumber[8] = 6;
    }
    else{
       colorsNumber[0] = 0;
       colorsNumber[1] = 0;
       colorsNumber[2] = 7;
       colorsNumber[3] = 1;
       colorsNumber[4] = 3;
       colorsNumber[5] = 2;
       colorsNumber[6] = 4;
       colorsNumber[7] = 5;
       colorsNumber[8] = 6;
    }
}

console::~console(){
    if (ISWINDOWS)
    {
		resetToDefault();
    }
    else
    {
        std::cout<< "\033c";
    }
}

void console::setBgColor(int color){
    bgColor = color;
    setConsoleColor();
}

void console::setFgColor(int color){
    fgColor = color;
    setConsoleColor();
}



void console::clear(){
	if (ISWINDOWS)
	{
		system("cls");
	}
    else
    {
        std::cout << "\033[2J\033c";
    }
}



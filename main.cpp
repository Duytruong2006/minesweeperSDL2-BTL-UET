#include "Texture.h"
#include "Buttons.h"
#include "Variables.h"
#include "constant.h"
#include "function.h"
using namespace std;


int WinMain(int argc, char* argv[])
{
	if (!init())
	{
		cout << "fail to initialize.\n" << endl;
	}
	else
	{
		if (loadmedia())
		{
			if (loadMenuMedia())
			{
				showMenu();
				while (mainLoop)
				{
					if (isChoosing)
					{
						showModeChoice();
					}
					if(customMode) CustomMode();
					while (isRunning)
					{
						handleEvent();
						setButtonPosition();
						renderGame();
					}
				}
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}




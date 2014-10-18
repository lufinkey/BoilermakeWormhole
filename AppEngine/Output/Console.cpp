
#include "Console.h"
#include <iostream>
#include "SDL_rwops.h"
#include "../ObjCBridge/ObjCBridge.h"

namespace AppEngine
{
	String Console::outputFile = "";
	bool Console::tofile = false;
	
	void Console::Write(const String&text)
	{
		//std::cout << text;
		AppEngine_Log(text);
		if(tofile)
		{
			SDL_RWops*file = SDL_RWFromFile(outputFile, "a+");
			SDL_RWseek(file,0,RW_SEEK_END);
			SDL_RWwrite(file,(char*)text,1,text.length());
			SDL_RWclose(file);
		}
	}
	
	void Console::WriteLine(const String&text)
	{
		//std::cout << text << std::endl;
		AppEngine_Log(text + '\n');
		if(tofile)
		{
			SDL_RWops*file = SDL_RWFromFile(outputFile, "a+");
			SDL_RWseek(file,0,RW_SEEK_END);
			SDL_RWwrite(file,(char*)(text + '\n'),1,text.length()+1);
			SDL_RWclose(file);
		}
	}
	
	void Console::OutputToFile(bool toggle, const String&filePath)
	{
		tofile = toggle;
		outputFile = (String)getenv("HOME") + "/Documents/" + filePath;
	}
}
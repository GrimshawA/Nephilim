// Engine interfaces
#include <Nephilim/Music.h>
using namespace nx;

#include <stdio.h>

extern "C"
{
	

void __declspec(dllexport) playSound(const char* filename)
{
	printf("OpenAL init\n");	

	Music* m = new Music();
	m->openFromFile(filename);
	m->play();
	m->setLoop(true);
}

}

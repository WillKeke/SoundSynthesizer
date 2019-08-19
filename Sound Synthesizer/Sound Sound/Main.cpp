#include <iostream>
using namespace std;
#include "olcNoiseMaker.h"


atomic<double> dFrequencyOutput = 0.0;  // Global variable

double MakeNoise(double dTime)
{
	double dOutput = 0.3*sin(dFrequencyOutput * 2 * 3.1415*dTime);

	if (dOutput > 0.0)
		return 0.2;
	else
		return -0.2;

	//return 0.3*sin(220.0 * 2 * 3.1415*dTime); (use for other wave)
}

int main()
{
	wcout << "onelonecoder.com - Synthesizer Part 1" << endl;

	//this gets all of the sound hardware
	vector<wstring>devices = olcNoiseMaker<short>::Enumerate();

	//Display findings
	for (auto d : devices) wcout << "Found Output Device:" << d << endl;

	// Create sound maching!!
	olcNoiseMaker<short> sound(devices[0],44100,1,8,512);

	// Link noise function with sound maching (function pointer)
	sound.SetUserFunction(MakeNoise);

	double dOctaveBaseFrequency = 110.0; //A2
	double d12thRootOf2 = pow(2.0, 1.0 / 12.0);

	while (1){

		// Adds a keyboard
		//using GetAsyncKeyState() allows us to see any key state on the keyboard
		// 0x8000 shows if it is the higest bit then it is press and if it is not it is realeased
		bool bKeyPressed = false;
		for (int k = 0; k<15; k++)
		{
			if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000)
			{
				dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootOf2, k);
				bKeyPressed = true;
			}
		}
		if (!bKeyPressed)
		{
			dFrequencyOutput = 0.0;
	}


	}

	return 0;
}
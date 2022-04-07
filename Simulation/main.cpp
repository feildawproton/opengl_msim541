#include "TransportSimulation.h"

using namespace std;

int main(int argc, char** argv)
{
	transportSimulation transSim; //instance of transportation simulation

	//there are defualt values for window size and title
	//you can set them here but it is not neccessary
	transSim.InitializeSimulation(argc, argv);//need to initialize it
	transSim.Run(); //run the sim

	return 0;
}
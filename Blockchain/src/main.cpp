#include <iostream>
#include "miner.h"

int main()
{
	Blockchain bc;

	Miner miner(bc);

	miner.input();

	return 0;
}
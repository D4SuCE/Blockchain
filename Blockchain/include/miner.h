#pragma once

#include "ledger.h"

class Miner
{
private:
	Blockchain blockchain;

public:
	Miner(const Blockchain& blockchain);
	~Miner();

	void input();

private:
	void start();
};
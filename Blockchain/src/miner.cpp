#include <iostream>
#include <spdlog/spdlog.h>

#include "miner.h"
#include "utils.h"

Miner::Miner(const Blockchain& blockchain)
	: blockchain(blockchain)
{
	start();
}

Miner::~Miner()
{}

void Miner::input()
{
	while (true)
	{
		std::cout << "/print - printing all blocks\n"
			<< "/add - add new block\n";
		
		std::string input;
		std::cin >> input;

		if (input == "/print")
		{
			blockchain.printBlocks();
		}
		else if (input == "/add")
		{
			std::string miner;
			std::string inTX;
			std::string outTX;
			float amount;
			size_t difficulty;

			spdlog::info("Miner's name: ");
			std::cin >> miner;
			spdlog::info("inTX: ");
			std::cin >> inTX;
			spdlog::info("outTX: ");
			std::cin >> outTX;
			spdlog::info("Amount: ");
			std::cin >> amount;
			spdlog::info("Difficulty: ");
			std::cin >> difficulty;

			std::string tx = "Miner: " + miner + " inTX: " + inTX + " outTX: " + outTX + " Amount: " + std::to_string(amount) + "RFRT";

			std::vector<std::string> data;
			data.push_back(tx);

			std::pair<std::string, size_t> nonce = Utils::findHash(difficulty, blockchain.getNumOfBlocks(), blockchain.getLatestBlockHash(), data);

			blockchain.addBlock(nonce.second, nonce.first, blockchain.getLatestBlockHash(), Block::getTime(), data, blockchain.getNumOfBlocks(), difficulty);
		}
	}
}

void Miner::start()
{
	spdlog::info("Creating a new blockchain...");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	blockchain.start(Blockchain::Stage::GENESIS);
}

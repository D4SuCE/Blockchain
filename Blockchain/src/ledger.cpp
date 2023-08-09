#include <spdlog/spdlog.h>

#include "utils.h"
#include "ledger.h"

Blockchain::Blockchain()
	: stage(Stage::UNDEFINED), version(0.1), blockchain()
{}

Blockchain::~Blockchain()
{}

void Blockchain::printBlocks() const
{
	for (const auto& block : blockchain)
	{
		block.print();
	}
}

inline Blockchain::Stage Blockchain::getStage() const
{
	return stage;
}

inline float Blockchain::getVersion() const
{
	return version;
}

size_t Blockchain::getNumOfBlocks() const
{
	return blockchain.size();
}

std::string Blockchain::getLatestBlockHash() const
{
	return blockchain.back().getHash();
}

void Blockchain::addBlock(size_t nonce, 
				const std::string& hash, 
				const std::string& prevHash, 
				const std::string& timestamp, 
				const std::vector<std::string>& data, 
				size_t counter, size_t difficulty)
{
	std::string target("0", difficulty);
	std::string header = std::to_string(counter) + prevHash + Utils::getMerkleRoot(data).to_string() + std::to_string(nonce);

	if (!Utils::sha256(header).compare(hash) && hash.substr(0, difficulty) == target && counter == blockchain.size())
	{
		spdlog::info("Difficulty: {0:d}", difficulty);
		spdlog::info("Hash: {0}", hash);
		blockchain.push_back(Block(nonce, hash, prevHash, timestamp, data, counter, difficulty));
		return;
	}

	spdlog::error("Hash not validate");
}

void Blockchain::start(Stage stage)
{
	switch (stage)
	{
		case Stage::GENESIS:
		{
			std::vector<std::string> data;
			data.push_back("Genesis");

			std::pair<std::string, size_t> nonce = Utils::findHash(1, 0, std::string("000000000000000000000000000000000000000001"), data);

			blockchain.push_back(Block(nonce.second, nonce.first, std::string("000000000000000000000000000000000000000001"), Block::getTime(), data, 0, 1));

			spdlog::info("Blockchain has been created");

			printBlocks();

			break;
		}

		case Stage::JOIN:
		{
			spdlog::info("Joined blockchain");
			break;
		}

		default:
		{
			spdlog::error("Something went wrong");
			break;
		}
	}
}


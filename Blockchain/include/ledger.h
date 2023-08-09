#pragma once

#include "block.h"

class Blockchain
{
public:
	enum class Stage
	{
		UNDEFINED = 0,
		GENESIS,
		JOIN
	};

private:
	Stage stage;
	float version;
	std::vector<Block> blockchain;

public:
	Blockchain();
	~Blockchain();

	void start(Stage stage);
	void printBlocks() const;

	inline Stage getStage() const;
	inline float getVersion() const;
	size_t getNumOfBlocks() const;
	std::string getLatestBlockHash() const;

	void addBlock(size_t nonce,
		const std::string& hash,
		const std::string& prevHash,
		const std::string& timestamp,
		const std::vector<std::string>& data,
		size_t counter, size_t difficulty);
};
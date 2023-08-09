#pragma once

#include <vector>
#include <string>

class Block
{
private:
	size_t nonce;
	size_t counter;
	size_t difficulty;
	std::string hash;
	std::string prevHash;
	std::string timestamp;
	std::vector<std::string> data;

public:
	Block() = default;

	Block(size_t nonce,
		  const std::string& hash,
		  const std::string& prevHash,
		  const std::string& timestamp,
		  const std::vector<std::string>& data,
		  size_t counter = 0, size_t difficulty = 0);

	~Block();


	
	static std::string getTime();

	void print() const;
	std::string getHash() const;
	inline size_t getNonce() const;
	inline size_t getCounter() const;
	inline std::string getTransactions() const;
	inline std::string getPreviousHash() const;
	inline std::vector<std::string> getData() const;
};


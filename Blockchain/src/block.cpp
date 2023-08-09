#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fort.hpp>

#include "block.h"

Block::Block(size_t nonce,
			 const std::string& hash,
			 const std::string& prevHash,
			 const std::string& timestamp,
			 const std::vector<std::string>& data,
			 size_t counter, size_t difficulty)
	: nonce(nonce), counter(counter), difficulty(difficulty),
	 hash(hash), prevHash(prevHash), timestamp(timestamp), data(data)
{}

Block::~Block()
{}

inline size_t Block::getNonce() const
{
	return nonce;
}

inline size_t Block::getCounter() const
{
	return counter;
}

inline std::string Block::getTransactions() const
{
	std::string str;

	for (int i = 0; i < data.size(); ++i)
	{
		str += data[i];
	}

	return str;
}

std::string Block::getHash() const
{
	return hash;
}

inline std::string Block::getPreviousHash() const
{
	return prevHash;
}

inline std::vector<std::string> Block::getData() const
{
	return data;
}

std::string Block::getTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::stringstream ss;
	std::tm timeinfo;

	localtime_s(&timeinfo, &in_time_t);

	ss << std::put_time(&timeinfo, "%Y-%m-%d | %X");
	
	return ss.str();
}

void Block::print() const
{
	fort::char_table table;

	table << fort::header
		<< "Block: " << counter << fort::endr
		<< "Time: " << timestamp << fort::endr
		<< "Hash: " << hash << fort::endr
		<< "Prev: " << prevHash << fort::endr
		<< "Nonce: " << nonce << fort::endr
		<< "Transaction: " << getTransactions() << fort::endr;

	std::cout << table.to_string() << std::endl;
}
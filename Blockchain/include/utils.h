#pragma once

#include <string>
#include <vector>
#include <merklecpp.h>

namespace Utils
{
	std::string sha256(const std::string& str);
	merkle::Hash getMerkleRoot(const std::vector<std::string>& data);
	std::pair<std::string, size_t> findHash(size_t difficulty, size_t index, const std::string& prevHash, const std::vector<std::string>& data);
}
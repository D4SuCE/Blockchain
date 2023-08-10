#define _CRT_SECURE_NO_WARNINGS

#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <spdlog/spdlog.h>

#include "utils.h"

namespace Utils
{
	std::string sha256(const std::string& str)
	{
		EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
		const EVP_MD* md = EVP_sha256();
		unsigned char hash[EVP_MAX_MD_SIZE];
		unsigned int len;

		EVP_DigestInit_ex(mdctx, md, nullptr);
		EVP_DigestUpdate(mdctx, str.c_str(), str.length());
		EVP_DigestFinal_ex(mdctx, hash, &len);
		EVP_MD_CTX_free(mdctx);

		std::stringstream ss;

		for (size_t i = 0; i < len; i++)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
		}

		return ss.str();
	}

	merkle::Hash getMerkleRoot(const std::vector<std::string>& data)
	{
		merkle::Tree mt;

		for (size_t i = 0; i < data.size(); i++)
		{
			mt.insert(sha256(data[i]));
		}

		return mt.root();
	}

	std::pair<std::string, size_t> findHash(size_t difficulty, size_t index, const std::string& prevHash, const std::vector<std::string>& data)
	{
		std::string target(difficulty, '0');
		std::string header =  std::to_string(index) + prevHash + getMerkleRoot(data).to_string();

		auto start = std::chrono::high_resolution_clock::now();
		for (size_t i = 384993400; i > 0; --i)
		{
			std::string hash = sha256(header + std::to_string(i));

			std::cout << "Mining: " << hash << "\r";
			
			if (hash.substr(0, difficulty) == target)
			{
				std::cout << std::endl;
				auto finish = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> elapsed = finish - start;
				spdlog::info("Success!");
				std::this_thread::sleep_for(std::chrono::seconds(1));
				std::cout << "Elapsed Time: ~" << (elapsed.count() / 1000) << " seconds" << std::endl;
				std::cout << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return std::make_pair(hash, i);
			}
		}

		spdlog::error("Mining failed");
		return std::make_pair("", 0);
	}
}
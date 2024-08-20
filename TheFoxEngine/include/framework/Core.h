#pragma once

#include<stdio.h>
#include<memory>
#include<vector>
#include<map>
#include<unordered_map>
#include<unordered_set>

namespace tf
{
template<typename T>
using unique = std::unique_ptr<T>;

template<typename T>
using shared = std::shared_ptr<T>;

template<typename T>
using weak = std::weak_ptr<T>;

template<typename T>
using list = std::vector<T>;

template<typename KeyType, typename valType, typename pr = std::less<KeyType>>
using map = std::map<KeyType, valType, pr>;

template<typename KeyType, typename valType, typename hasher = std::hash<KeyType>>
using dictionary = std::unordered_map<KeyType, valType, hasher>;

template<typename T>
using set = std::unordered_set<T>;

using uint8 = unsigned char;

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}
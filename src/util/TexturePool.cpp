#include <unordered_map>
#include <cassert>
#include "TexturePool.h"
#include "util.h"


static std::unordered_map<std::size_t, Texture2D> pool{};


Texture2D pk::texture_pool_get(const char* filepath) {
	const std::size_t h = pk::hash_str(filepath);
	if (pool.find(h) == pool.end()) {
		const auto& p = pool.emplace(h, LoadTexture(filepath));
		assert(p.first->second.id > 0);
	}
	return pool[h];
}


void pk::texture_pool_clear() {
	for (auto& pair : pool) {
		UnloadTexture(pair.second);
	}
	pool.clear();
}
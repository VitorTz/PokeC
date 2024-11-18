#pragma once
#include <queue>
#include "../util/types.h"


namespace pk {

	class EntityManager {

	private:
		std::queue<pk::entity_t> q{};
		std::size_t m_size{};

	public:
		EntityManager();
		pk::entity_t entity_create();
		void entity_destroy(pk::entity_t e);
		void clear();
		std::size_t size() const;

	};

}
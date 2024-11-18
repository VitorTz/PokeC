#include <cassert>
#include "Entity.h"
#include "../constants.h"


pk::EntityManager::EntityManager() {
	for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
		this->q.push(e);
	}
}


pk::entity_t pk::EntityManager::entity_create() {
	assert(this->q.empty() == false);
	const pk::entity_t e = this->q.front();
	this->q.pop();
	this->m_size++;
	return e;
}


void pk::EntityManager::entity_destroy(const pk::entity_t e) {
	this->q.push(e);
	this->m_size--;
}


void pk::EntityManager::clear() {
	this->q = std::queue<pk::entity_t>();
	for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
		this->q.push(e);
	}
	this->m_size = 0;
}


std::size_t pk::EntityManager::size() const {
	return this->m_size;
}
#pragma once

#include <basyx/reference.h>

#include <basyx/util/optional/optional.hpp>

namespace basyx
{

class HasSemantics
{
private:
	util::optional<Reference> semanticId;
	std::vector<Reference> supplementalSemanticIdList;
public:
	HasSemantics() = default;

	HasSemantics(const HasSemantics&) = default;
	HasSemantics(HasSemantics&&) = default;

	HasSemantics & operator=(const HasSemantics&) noexcept = default;
	HasSemantics & operator=(HasSemantics&&) noexcept = default;

	~HasSemantics() = default;
public:
	const util::optional<Reference> & getSemanticId() const { return this->semanticId; };
	void setSemanticId(Reference semanticId) { this->semanticId = std::move(semanticId); };

	std::vector<Reference> & getSupplementalSemanticIds() { return this->supplementalSemanticIdList; };
	const std::vector<Reference> & getSupplementalSemanticIds() const { return this->supplementalSemanticIdList; };
};

};

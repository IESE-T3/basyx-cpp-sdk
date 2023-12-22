#pragma once

#include <basyx/submodelelement/dataelement.h>

#include <basyx/modeltype.h>

#include <basyx/submodelelement/property.h>

#include <basyx/util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class AnnotatedRelationshipElement : public SubmodelElement,
	private ModelType<ModelTypes::AnnotatedRelationshipElement>,
	private serialization::Serializable<AnnotatedRelationshipElement>
{
public:
	using annotation_t = std::unique_ptr<DataElement>;
	using annotation_list_t = std::vector<annotation_t>;
public:
	Reference first;
	Reference second;
	annotation_list_t annotations;
public:
	AnnotatedRelationshipElement(util::string_view idShort, Reference first, Reference second);

	AnnotatedRelationshipElement(const AnnotatedRelationshipElement&) = default;
	AnnotatedRelationshipElement& operator=(const AnnotatedRelationshipElement&) = default;

	AnnotatedRelationshipElement(AnnotatedRelationshipElement&&) noexcept = default;
	AnnotatedRelationshipElement& operator=(AnnotatedRelationshipElement&&) noexcept = default;

	~AnnotatedRelationshipElement() = default;
};

}

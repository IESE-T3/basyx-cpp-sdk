#include <basyx/serialization/json/serializer_fwd.h>

#include <basyx/key.h>
#include <basyx/reference.h>
#include <basyx/submodel.h>
#include <basyx/assetadministrationshell.h>

#include <basyx/submodelelement/blob.h>
#include <basyx/submodelelement/file.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/capability.h>
#include <basyx/submodelelement/referenceelement.h>
#include <basyx/submodelelement/relationshipelement.h>
#include <basyx/submodelelement/entity.h>
#include <basyx/submodelelement/basicevent.h>
#include <basyx/submodelelement/annotatedrelationshipelement.h>
#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/property.h>

namespace basyx::serialization::json
{

template<typename Container>
void serialize_list(json_t& json, const std::string& key, const Container& cont) {
	auto json_array = json_t::array();
	for (const auto& entry : cont)
		json_array.emplace_back(serialize(entry));

	if (!json_array.empty())
		json[key] = std::move(json_array);
};

template<typename Opt>
void serialize_opt(json_t& json, const std::string& key, const Opt& opt) {
	if (opt)
		json[key] = serialize(*opt);
};


void serialize_helper(json_t& json, const MultiLanguageProperty& multiLangProperty)
{
	serialize_submodelelement_helper(json, multiLangProperty);

	if (!multiLangProperty.get_value().empty())
		json["value"] = serialize(multiLangProperty.get_value());

	if (multiLangProperty.get_value_id())
		json["valueId"] = serialize(*multiLangProperty.get_value_id());
};

void serialize_helper(json_t& json, const Property& prop)
{
	serialize_submodelelement_helper(json, prop);

	if (prop.has_value())
		json["value"] = prop.get_value_string();

	if (prop.valueId)
		json["valueId"] = serialize(*prop.valueId);

	json["valueType"] = DataTypeDefinition_::to_string(prop.get_value_type());
};

template<typename T>
inline void serialize_submodelelement(json_t& json, const SubmodelElement& submodelElement)
{
	serialize_helper(json, static_cast<const T&>(submodelElement));
};

void serialize_helper(json_t& json, const HasSemantics& hasSemantics)
{
	serialize_opt(json, "semanticId", hasSemantics.getSemanticId());
	serialize_list(json, "supplementalSemanticIds", hasSemantics.getSupplementalSemanticIds());
};

void serialize_helper(json_t& json, const HasKind& hasKind)
{
	if (hasKind.getKind() != ModelingKind::None)
		json["kind"] = ModelingKind_::to_string(hasKind.getKind());
};

void serialize_helper(json_t& json, const modeltype_base& modelType)
{
	json["modelType"] = ModelTypes_::to_string(modelType.get_model_type());
};

void serialize_helper(json_t& json, const Key& key)
{
	json["type"] = KeyElements_::to_string(key.type);
	json["value"] = key.value;
};

void serialize_helper(json_t& json, const Reference& ref)
{
	auto keyList = json_t::array();

	json["type"] = ReferenceTypes_::to_string(ref.type);

	for (std::size_t i = 0; i < ref.size(); ++i) {
		keyList.emplace_back(serialize(ref.get_key(i)));
	};
	json["keys"] = std::move(keyList);

	auto referred_semantic_id = ref.get_referred_semantic_id();
	if (referred_semantic_id) {
		serialize_helper(json["referredSemanticId"], *referred_semantic_id);
	};
};

void serialize_helper(json_t& json, const Entity& entity)
{
	serialize_submodelelement_helper(json, entity);

	json["statements"] = json_t::array();

	if (entity.getGlobalAssetId())
		json["globalAssetId"] = serialize(*entity.getGlobalAssetId());

	if (entity.getSpecificAssetId())
		json["specificAssetIds"] = serialize(*entity.getSpecificAssetId());

};

void serialize_helper(json_t& json, const Referable& referable)
{
	serialize_helper_h<modeltype_base>(json, referable);

	if (referable.getIdShort() && !referable.getIdShort()->empty())
		json["idShort"] = *referable.getIdShort();

	if (referable.getCategory())
		json["category"] = *referable.getCategory();

	if (referable.getDescription())
		json["description"] = serialize(*referable.getDescription());

	if (referable.getDisplayname())
		json["displayName"] = serialize(*referable.getDisplayname());
};

void serialize_helper(json_t& json, const langstringset_t& langstrings)
{
	json = json_t::array();

	for (const auto& langstring : langstrings) {
		json.emplace_back(json_t{
			{"language", langstring.get_code().to_string() },
			{"text", langstring.get_value().to_string() }
			});
	}
};

void serialize_helper(json_t& json, const SpecificAssetId& kvPair)
{
	serialize_helper_h<HasSemantics>(json, kvPair);

	json["key"] = kvPair.name;
	json["value"] = kvPair.value;

	serialize_opt(json, "subjectId", kvPair.externalSubjectId);

	//json["subjectId"] = json_t();
	//if(kvPair.getExternalSubjectId())
	//	json["subjectId"] = serialize(*kvPair.getExternalSubjectId());
}

void serialize_helper(json_t& json, const AssetAdministrationShell& aas)
{
	serialize_helper_h<Identifiable>(json, aas);
	//serialize_helper_h<HasDataSpecification>(json, aas);
	//serialize_helper_h<modeltype_base>(json, aas);

	if (aas.derivedFrom)
		json["derivedFrom"] = serialize(*aas.derivedFrom);

	auto submodels = json_t::array();
	for (const auto& submodel : aas.getSubmodels()) {
		submodels.emplace_back(serialize(*submodel));
	};

	if (!submodels.empty())
		json["submodels"] = std::move(submodels);

	json["assetInformation"] = serialize(aas.assetInformation);

	if (aas.getSecurity())
		// actually, ToDo: 
		// json["security"] = serialize(*aas.getSecurity());
		json["security"] = *aas.getSecurity();
};

void serialize_helper(json_t& json, const Capability& capability)
{
	serialize_submodelelement_helper(json, capability);
}

void serialize_helper(json_t& json, const AdministrativeInformation& administrativeInformation)
{
	serialize_opt(json, "version", administrativeInformation.version);
	serialize_opt(json, "revision", administrativeInformation.revision);
	serialize_opt(json, "creator", administrativeInformation.creator);
	serialize_opt(json, "templateId", administrativeInformation.templateId);
};

void serialize_helper(json_t& json, const ReferenceElement& ref_element)
{
	serialize_submodelelement_helper(json, ref_element);

	if (ref_element.getValue())
		json["value"] = serialize(*ref_element.getValue());
}

void serialize_helper(json_t& json, const RelationshipElement& rel_element)
{
	serialize_submodelelement_helper(json, rel_element);

	json["first"] = serialize(rel_element.getFirst());
	json["second"] = serialize(rel_element.getSecond());
}

void serialize_helper(json_t& json, const AnnotatedRelationshipElement& rel_element)
{
	serialize_submodelelement_helper(json, rel_element);

	json["first"] = serialize(rel_element.first);
	json["second"] = serialize(rel_element.second);

	if (!rel_element.annotations.empty()) {
		auto annotations = json_t::array();
		for (const auto& annotation : rel_element.annotations) {
			annotations.emplace_back( serialize(*annotation) );
		};
		json["annotation"] = std::move(annotations);
	}
}

void serialize_helper(json_t& json, const BasicEvent& basicEvent)
{
	serialize_submodelelement_helper(json, basicEvent);

	json["observed"] = serialize(basicEvent.getObserved());
}

void serialize_helper(json_t& json, const Blob& blob)
{
	serialize_submodelelement_helper(json, blob);

	// Todo: encode blob.getBlob() in base64
	json["value"] = "";

	json["mimeType"] = blob.getMimeType();
};

void serialize_helper(json_t& json, const File& file)
{
	serialize_submodelelement_helper(json, file);

	if (file.value)
		json["value"] = *file.value;
	else
		json["value"] = "";

	json["mimeType"] = file.mimeType;
};

void serialize_helper(json_t& json, const Identifier& identifier)
{
	json = identifier;
};

void serialize_helper(json_t& json, const Identifiable& identifiable)
{
	serialize_helper_h<Referable>(json, identifiable);

	json["id"] = serialize(identifiable.getId());

	if (identifiable.getAdministration())
		json["administration"] = serialize(*identifiable.getAdministration());
	//else
	//	json["administration"] = json_t::object();
};

void serialize_helper(json_t& json, const Resource& resource)
{
	json["path"] = resource.path;
	serialize_opt(json, "contentType", resource.contentType);
};

void serialize_helper(json_t& json, const SubmodelElementCollection& collection)
{
	serialize_submodelelement_helper(json, collection);

	json_t value = json_t::array();

	for (const auto& element : collection.getSubmodelElements()) {
		value.emplace_back(serialize(*element));
	};

	if (value.size() > 0)
		json["value"] = std::move(value);
};

template<typename ContainerT>
void serialize_element_container(json_t& json, const std::string& key, const ContainerT& container)
{
	if (container.size() > 0) {
		json_t elements = json_t::array();
		for (const auto& element : container) {
			elements.emplace_back(serialize(*element));
		};
		json[key] = std::move(elements);
	};

};

void serialize_helper(json_t& json, const Submodel& submodel)
{
	serialize_helper_h<Identifiable>(json, submodel);
	serialize_helper_h<HasSemantics>(json, submodel);
	serialize_helper_h<HasKind>(json, submodel);
	serialize_element_container(json, "submodelElements", submodel.getSubmodelElements());
};


void serialize_helper(json_t& json, const AssetInformation& assetInf)
{
	json["assetKind"] = AssetKind_::to_string(assetInf.assetKind);

	serialize_opt(json, "globalAssetId", assetInf.globalAssetId);
	serialize_list(json, "specificAssetIds", assetInf.specificAssetIds);
	serialize_opt(json, "defaultThumbnail", assetInf.defaultThumbnail);
	serialize_opt(json, "assetType", assetInf.assetType);
}

};

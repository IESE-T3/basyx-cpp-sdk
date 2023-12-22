#include "deserializer.h"

namespace basyx::serialization::json
{
	template<typename EnumT>
	auto deserialize_enum(const json_t& json) -> typename EnumT::type_t {
		return EnumT::from_string((std::string)json); 
	};

	template<typename T>
	util::optional<T> deserialize_helper(const json_t& json)
	{
		return {};
	};

	template<typename T>
	util::optional<T> deserialize_opt(const json_t& json, const std::string& key)
	{
		if (json.contains(key))
		{
			return deserialize_helper<T>(json[key]);
		};

		return {};
	};

	template<>
	util::optional<Resource> deserialize_helper<Resource>(const json_t& json)
	{
		util::optional<Resource> resource;

		if (!json.contains("path"))
			return resource;

		PathType path = json["path"];
		resource.emplace(path);

		if (json.contains("contentType"))
			resource->contentType = json["contentType"];

		return resource;
	};

	template<>
	util::optional<AssetInformation> deserialize_helper<AssetInformation>(const json_t& json)
	{
		util::optional<AssetInformation> asset_inf;

		if (!json.contains("assetKind"))
			return asset_inf;

		auto assetKind = deserialize_enum<AssetKind_>(json["assetKind"]);
		asset_inf.emplace(assetKind);

		if (json.contains("globalAssetId")) {
			asset_inf->globalAssetId = json["globalAssetId"];
		};

		if (json.contains("assetType")) {
			asset_inf->assetType = json["assetType"];
		};

		if (json.contains("defaultThumbnail")) {
			asset_inf->defaultThumbnail = deserialize_helper<Resource>(json["defaultThumbnail"]);
		}

		std::vector<SpecificAssetId> specificAssetIds;

		return asset_inf;
	};

	AdministrativeInformation deserialize_administrative_information(const json_t& json)
	{
		AdministrativeInformation info;
		info.creator = deserialize_opt<Reference>(json, "creator");
		info.version = deserialize_opt<std::string>(json, "version");
		info.revision = deserialize_opt<std::string>(json, "revision");
		info.templateId = deserialize_opt<Identifier>(json, "templateId");
		return info;
	};

	ModelTypes extract_modeltype(const json_t & json)
	{
		return ModelTypes_::from_string(json["modelType"]);
	};


	Key deserialize_key(const json_t & json)
	{
		auto key_element = deserialize_enum<KeyElements_>(json["type"]);
		std::string value = json["value"];

		return Key{ key_element, value };
	};

	util::optional<Reference> deserialize_reference(const json_t & json)
	{
		util::optional<Reference> ref;
		auto type = deserialize_enum<ReferenceTypes_>(json["type"]);

		for (const auto & key : json["keys"]) {
			// emplace first key
			if (!ref) {
				ref.emplace(type, deserialize_key(key));
			}
			else {// add rest of key list
				ref->add(deserialize_key(key));
			};
		}

		if (json.contains("referredSemanticId")) {
			auto semantic_id = deserialize_reference(json["referredSemanticId"]);
			if (semantic_id)
				ref->set_referred_semantic_id(std::move(*semantic_id));
		};

		return ref;
	};

	langstringset_t deserialize_langstrings(const json_t & json)
	{
		langstringset_t langstrings;

		for (const auto & entry : json) {
			std::string lang = entry["language"];
			std::string value = entry["text"];
			langstrings.add(lang, value);
		};

		return langstrings;
	};

	//Identifier deserialize_identifier(const json_t & json)
	//{
	//	std::string identifier = json["id"];
	//	std::string idType = json["idType"];

	//	return Identifier{KeyType_::from_string(idType), identifier};
	//};

	template<typename Obj>
	void deserialize_has_semantics(const json_t& json, Obj& obj)
	{
		if (json.contains("semanticId")) {
			auto semantic_id = deserialize_reference(json["semanticId"]);
			if(semantic_id)
				obj.setSemanticId(std::move(*semantic_id));
		};

		if (json.contains("supplementalSemanticIds")) {
			for (const auto& entry : json["supplementalSemanticIds"]) {
				auto semantic_id = deserialize_reference(entry);
				if (semantic_id)
					obj.getSupplementalSemanticIds().emplace_back(std::move(*semantic_id));
			};
		};
	};

	template<typename Obj>
	void deserialize_referable(const json_t & json, Obj & obj)
	{
		if (json.contains("displayName"))
			obj.setDisplayname(deserialize_langstrings(json["displayName"]));

		if(json.contains("category"))
			obj.setCategory((std::string)json["category"]);
	
		if(json.contains("description"))
			obj.setDescription(deserialize_langstrings(json["description"]));
	};

	template<typename Obj>
	void deserialize_identifiable(const json_t& json, Obj& obj)
	{
		deserialize_referable(json, obj);

		if (json.contains("administration") && !json["administration"].empty())
		{
			auto admin_info = deserialize_administrative_information(json["administration"]);
			obj.setAdministration(std::move(admin_info));
		};
	};

	MultiLanguageProperty deserialize_multilang_prop(const json_t & json)
	{
		std::string idShort = json["idShort"];
		auto mlp = MultiLanguageProperty{ std::move(idShort) };

		if (json.contains("value")) {
			mlp.set_value(deserialize_langstrings(json["value"]));
		}

		deserialize_referable(json, mlp);

		return mlp;
	};

	std::unique_ptr<SubmodelElement> deserialize_submodelelement(const json_t & json)
	{
		auto modelType = extract_modeltype(json);

		std::unique_ptr<SubmodelElement> element;

		switch (modelType)
		{
		case ModelTypes::Property:
			break;
		case ModelTypes::MultiLanguageProperty:
			element = std::make_unique<MultiLanguageProperty>(deserialize_multilang_prop(json));
			break;
		case ModelTypes::SubmodelElementCollection:
			element = std::make_unique<SubmodelElementCollection>(deserialize_submodelelement_collection(json));
			break;
		case ModelTypes::AnnotatedRelationshipElement:
			element = std::make_unique<AnnotatedRelationshipElement>(deserialize_annotated_relationship(json));
			break;
		};
		
		return element;
	};

	AnnotatedRelationshipElement deserialize_annotated_relationship(const json_t& json)
	{
		std::string idShort = json["idShort"];

		auto first = deserialize_reference(json["first"]);
		auto second = deserialize_reference(json["second"]);


		auto rel = AnnotatedRelationshipElement{ idShort, std::move(*first), std::move(*second) };
		
		deserialize_referable(json, rel);

		return rel;
	};

	SubmodelElementCollection deserialize_submodelelement_collection(const json_t & json)
	{
		std::string idShort = json["idShort"];

		SubmodelElementCollection col(idShort);
		
		for (const auto & value : json["value"]) {
			auto element = deserialize_submodelelement(value);
			col.getSubmodelElements().add(std::move(element));
		};

		return col;
	};

	ModelingKind deserialize_has_kind(const json_t& json)
	{
		if (json.contains("kind")) {
			return deserialize_enum<ModelingKind_>(json["kind"]);
		};

		return ModelingKind::None;
	};

	Submodel deserialize_submodel(const json_t& json)
	{
		// Extract mandatory identifier
		Identifier identifier = json["id"];	

		// Check for optional idShort
		std::string idShort = "";
		if (json.contains("idShort"))
			idShort = json["idShort"];

		// Create submodel object
		Submodel submodel(std::move(idShort), std::move(identifier));

		// Extract Identifiable info
		deserialize_identifiable(json, submodel);

		// Extract HasSemantics info
		deserialize_has_semantics(json, submodel);

		// Check for modeling kind
		auto modeling_kind = deserialize_has_kind(json);
		if (modeling_kind != ModelingKind::None)
			submodel.setKind(modeling_kind);

		// Parse submodel elements
		auto submodel_elements = json.find("submodelElements");
		if (submodel_elements != json.end()) {
			for (const auto& element : submodel_elements.value()) {
				submodel.getSubmodelElements().add(deserialize_submodelelement(element));
			};
		};

		return submodel;
	};

	AssetAdministrationShell deserialize_aas(const json_t & json)
	{
		std::string id = json["id"];

		std::string idShort = "";
		if(json.contains("idShort"))
			idShort = json["idShort"];

		AssetAdministrationShell aas(idShort, id, basyx::AssetInformation(AssetKind::Instance));

		deserialize_referable(json, aas);
		
		if (json.contains("assetInformation")) {
			auto asset_information = deserialize_helper<AssetInformation>(json["assetInformation"]);
			if (asset_information) {
				aas.assetInformation = std::move(*asset_information);
			};
		};

		if(json.contains("submodels"))
		for (const auto & submodel : json["submodels"]) {
			aas.getSubmodels().add(deserialize_submodel(submodel));
		};


		if (json.contains("derivedFrom")) {
			aas.derivedFrom = deserialize_reference(json["derivedFrom"]);
		};

		return aas;
	};
};

SET(SOURCE_FILES_BASYX
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/administrativeinformation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/asset/assetinformation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/assetadministrationshell.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/basyx_enums.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/token.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/valuetypedefs.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecification.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecificationContent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecificationIEC61360.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecificationPhysicalUnit.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/ValueList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/AssetKind.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/DataTypeDefinition.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/DataTypeIEC61360.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/IdentifiableElements.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/KeyElements.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/KeyType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/LevelType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ModelingKind.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ModelTypes.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ModelingKind.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/QualifierKind.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ReferenceTypes.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ReferableElements.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/SubmodelElements.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/environment.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/haskind.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/hassemantics.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/identifiable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/identifier.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/key.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/labelType.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/langstringset.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/modeltype.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/qualifiable/qualifiable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/qualifiable/qualifier.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/referable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/reference.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/semantics/conceptdescription.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/semantics/hasDataSpecification.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/json/deserializer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/json/serializer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/private/deserializer_priv.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/xml/deserializer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/xml/xmldeserializer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/specificAssetId.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/annotatedrelationshipelement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/basicevent.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/blob.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/dataelement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/entity.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/event.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/file.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/multilanguageproperty.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/operation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/operationvariable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/property.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/range.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/referenceelement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/relationshipelement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/submodelelement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/submodelelementcollection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/versionRevisionType.cpp
)

SET(HEADER_FILES_BASYX
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/administrativeinformation.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/asset/assetinformation.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/assetadministrationshell.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/basyx_enum_base.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/copyable.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/copyable_base.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/elementcontainer.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/elementvector.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/token.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/base/valuetypedefs.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecification.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecificationContent.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecificationIEC61360.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/DataSpecificationPhysicalUnit.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/ValueList.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/dataspecification/ValueReferencePair.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/AssetKind.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/Conversions.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/DataTypeDefinition.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/DataTypeIEC61360.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/EntityType.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/IdentifiableElements.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/IdentifierType.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/KeyElements.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/KeyType.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/LevelType.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/LocalKeyType.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ModelTypes.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ModelingKind.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ModelTypes.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/QualifierKind.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ReferableElements.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/ReferenceTypes.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/SubmodelElements.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/enums/XsdTypes.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/environment.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/haskind.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/hassemantics.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/identifiable.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/identifier.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/key.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/labelType.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/langstringset.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/modeltype.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/qualifiable/qualifiable.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/qualifiable/qualifiable_fwd.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/qualifiable/qualifierbase.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/qualifiable/qualifier.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/referable.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/reference.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/semantics/conceptdescription.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/semantics/hasDataSpecification.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/base/serialization.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/json/deserializer.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/json/serializer.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/json/serializer_fwd.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/json/types.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/private/deserializer_priv.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/serializable.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/serializable_base.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/deserializer.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/serializer.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/xml/deserializer.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/serialization/xml/xmldeserializer.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/specificAssetId.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodel.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/annotatedrelationshipelement.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/basicevent.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/blob.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/capability.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/dataelement.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/entity.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/event.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/file.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/multilanguageproperty.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/operation.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/operationvariable.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/property.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/range.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/referenceelement.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/relationshipelement.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/submodelelement.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/submodelelement/submodelelementcollection.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/versionRevisionType.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/common_types.h
	${CMAKE_CURRENT_SOURCE_DIR}/basyx/resource.h
)
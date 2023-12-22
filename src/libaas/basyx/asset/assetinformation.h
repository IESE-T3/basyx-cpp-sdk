#pragma once

#include <basyx/resource.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/specificAssetId.h>

#include <basyx/enums/AssetKind.h>

#include <basyx/util/optional/optional.hpp>

namespace basyx
{

	class AssetInformation
	{
	public:
		AssetKind assetKind = AssetKind::NotApplicable;
		util::optional<Identifier> globalAssetId;
		std::vector<SpecificAssetId> specificAssetIds;
		util::optional<Identifier> assetType;
		util::optional<Resource> defaultThumbnail;
	public:
		AssetInformation(AssetKind assetkind) : assetKind(assetkind) {};

		AssetInformation(const AssetInformation& other) = default;
		AssetInformation& operator=(const AssetInformation& other) = default;

		AssetInformation(AssetInformation&&) noexcept = default;
		AssetInformation& operator=(AssetInformation&&) noexcept = default;
	};
}

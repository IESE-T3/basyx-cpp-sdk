#pragma once

#include <string>

#include <basyx/util/optional/optional.hpp>
#include <basyx/common_types.h>

namespace basyx
{

class Resource
{
public:
	util::optional<ContentType> contentType;
	PathType path;
public:
	Resource(PathType path) : path(std::move(path)) {};
	Resource(PathType path, ContentType contentType) : path(std::move(path)) , contentType(std::move(contentType)) {};

	Resource(const Resource&) = default;
	Resource& operator=(const Resource&) = default;

	Resource(Resource&&) noexcept = default;
	Resource& operator=(Resource&&) noexcept = default;

	~Resource() = default;
public:
};

};

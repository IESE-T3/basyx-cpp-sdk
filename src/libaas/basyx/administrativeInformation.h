#ifndef ADMINISTRATIVEINFORMATION_H
#define ADMINISTRATIVEINFORMATION_H

#include <string>

#include <basyx/util/optional/optional.hpp>
#include <basyx/langstringset.h>
#include <basyx/key.h>
#include <basyx/reference.h>
#include <basyx/common_types.h>
#include <basyx/semantics/hasDataSpecification.h>

namespace basyx
{

class AdministrativeInformation: public HasDataSpecification
{
public:
   util::optional<std::string> version;
   util::optional<std::string> revision;
   util::optional<Reference> creator;
   util::optional<Identifier> templateId;
public:
	AdministrativeInformation() = default;
	AdministrativeInformation(util::string_view version);
	AdministrativeInformation(util::string_view version, util::string_view revision);

	AdministrativeInformation(const AdministrativeInformation&) = default;
	AdministrativeInformation& operator=(const AdministrativeInformation&) = default;

	AdministrativeInformation(AdministrativeInformation&&) noexcept = default;
	AdministrativeInformation& operator=(AdministrativeInformation&&) noexcept = default;

	~AdministrativeInformation() = default;
};

};

#endif /* ADMINISTRATIVEINFORMATION_H */

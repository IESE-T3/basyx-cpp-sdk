<h1 align="center"><a href="https://eclipse.dev/basyx/">Eclipse BaSyx</a> C++ SDK</h1><br>

<p align="center">
  <a href="https://eclipse.dev/basyx/">
    <img src="https://www.eclipse.org/basyx/img/basyxlogo.png" alt="BaSyx logo">
  </a>
</p>

<p align="center">
  Eclipse BaSyx is the world's most versatile, extensible, and feature-packed open-source software <br> for working with Asset Administration Shells
</p>

# Repository Overview

This is the C++ SDK of the <a href="https://eclipse.dev/basyx/">Eclipse BaSyx</a> project and implements the Asset Administration Shell Metamodel according to the Specification of the Asset Administration Shell Version 3. It comes with its own API according and an exemplary REST Server, as defined in Part 2 of the official specification.
The repository currently contains a release candidate of v3.0 and is thus still heavily in development, so bugs and other issues may still be present.

# Pre-requisites

The BaSyx C++ SDK requires a C++14 compliant compiler. Older versions of the C++ Standard might currently not be supported.
Additionally the SDK uses CMake as its build system, so CMake v3.14 (or newer) is required to build it.

The SDK has a few dependencies to external libraries, which will be pulled in and built automatically through the CMake's FetchContent module.

# Build instructions

Upon cloning of the repository, a build with CMake can be started by creating a directory for the build process and invoking the CMake client, e.g.:

```
git clone "https://github.com/IESE-T3/basyx-cpp-sdk.git"
mkdir build && cd build
cmake ..
```

Tests can be enabled by specifying the variable BASYX_BUILD_TESTS=ON during the CMake configuration, e.g. by supplying it on the command line:
```
cmake -DBASYX_BUILD_TESTS=ON ..
```

Upon creation of the build files, a typical build can be started by using e.g. make:
```
make -j4 
```
This should build the whole contents of the SDK

# Usage

The classes of the metamodel can either be used stand alone or the exemplary REST server can be used to host your own AAS locally.
An example of how to use the SDK to create an AAS and to have it hosted at a REST interface can be seen in [src/http/main.cpp](src/http/basyxpp-http/main.cpp)

```cpp
#include <basyxpp-http/SubmodelRepositoryHttpHandler.h>

#include <basyx/submodel.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/property.h>

#include <basyx/api/impl/aas_env_api.h>

#include <basyxpp-http/HttpHandler.h>

using namespace basyx;
using namespace basyx::http;

int main()
{
	std::cout << "BaSyx C++ AAS REST server" << std::endl;

	AssetInformation asset_inf_1{ AssetKind::Instance };
	AssetAdministrationShell aas_1{ "aas_1", "https://admin-shell.io/cpp#aas_1", asset_inf_1 };

	// Create submodels
	auto sm = aas_1.getSubmodels().create<Submodel>("sm1", "https://admin-shell.io/cpp#sm1");
	sm->setCategory("test");
	sm->setSemanticId({ ReferenceTypes::ExternalReference, {KeyElements::GlobalReference, "0173-1#02-AAR972#002" } });
	sm->setAdministration({ "1.0", "v2" });

	Submodel sm2("sm2", "https://admin-shell.io/cpp#sm2");

	// Add submodel elements to submodel
	sm->getSubmodelElements().add(Property("testProperty1", "This is a string value!"));
	sm->getSubmodelElements().add(Property("testProperty2", "This is another string value!"));
	sm->getSubmodelElements().add(Property("intProp", 32));
	sm->getSubmodelElements().add(Property("floatProp", 44.4f));

	sm->getSubmodelElements().add(SubmodelElementCollection("collection",
		MultiLanguageProperty("multiLang", { { "de", "beispiel" }, { "en", "example" } }),
		Property("floatProp", 5.0f),
		SubmodelElementCollection("collection2",
			Property("floatProp", 5.0f),
			Property("floatProp2", 5.0f))));

	AssetInformation asset_inf_2{ AssetKind::Instance };
	AssetAdministrationShell aas_2{ "aas_2", "https://admin-shell.io/cpp#aas_2", asset_inf_2 };

	Environment env;
	env.getAssetAdministrationShells().add(std::move(aas_1));
	env.getAssetAdministrationShells().add(std::move(aas_2));

	// Add to handler and start server
	auto handler = basyx::http::HttpHandler::make_http_handler<api::AasEnvApi>("127.0.0.1", 8080, env);
	handler->run();

	return 0;
}
```
The exemplary REST server will be build through the basyspp-http-exe target in CMake and will then be put in the bin/ directory of the build's output files.
Upon starting of the server binary, the AAS Server will listen on port 8080, and its content can be received through a REST call, e.g.
```wget -qO- "http://127.0.0.1:8080/shells```
will retrieve all currently hosted AAS on the server.



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


# Inspired by https://github.com/devcontainers/images/tree/main/src/cpp
ARG VARIANT=debian-11
FROM mcr.microsoft.com/devcontainers/base:0-${VARIANT}
USER root

# Install needed packages. Use a separate RUN statement to add your own dependencies.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install build-essential cmake cppcheck valgrind clang lldb llvm gdb \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Uncomment this section to install additional OS packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends git clang-format doxygen graphviz lcov

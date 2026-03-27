# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/igor/calculator/build/_deps/libmath-src"
  "/home/igor/calculator/build/_deps/libmath-build"
  "/home/igor/calculator/build/_deps/libmath-subbuild/libmath-populate-prefix"
  "/home/igor/calculator/build/_deps/libmath-subbuild/libmath-populate-prefix/tmp"
  "/home/igor/calculator/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp"
  "/home/igor/calculator/build/_deps/libmath-subbuild/libmath-populate-prefix/src"
  "/home/igor/calculator/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/igor/calculator/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/igor/calculator/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

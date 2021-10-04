CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include(RezBuild)
include(ExternalProject)


set(make_args -j$ENV{REZ_BUILD_THREAD_COUNT})

if(${REZ_BUILD_INSTALL})
    set(install_cmd make install ${make_args})
else()
    set(install_cmd "")
endif()

ExternalProject_add(
    lcms
    SOURCE_DIR ${CMAKE_SOURCE_DIR}
    PREFIX lcms
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-jpeg=$ENV{REZ_LIBJPEG_ROOT} --with-tiff=$ENV{REZ_LIBTIFF_ROOT}
    INSTALL_COMMAND "${install_cmd}"
    BUILD_IN_SOURCE 0
    BUILD_COMMAND make ${make_args}
)

# Necessary so REZ can create a `make install` target
rez_install_files(
    empty.txt
    DESTINATION .
)

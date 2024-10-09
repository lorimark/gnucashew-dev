# CMakeLists.txt for GnuCashew

cmake_minimum_required (VERSION 3.10)
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.14.0)
  cmake_policy(SET CMP0082 NEW)
endif()

project (gnucashew-bin
    VERSION 1.0
)

#
# this library is used in the file guid.cpp for generating
#  UUID values for the back-end database.
#
add_compile_definitions( GUID_LIBUUID )

set ( CMAKE_CXX_FLAGS "-std=c++17 -Wfatal-errors -Wbuiltin-macro-redefined -g" )

set (PACKAGE_NAME GnuCashew)
#set (PACKAGE_BUGREPORT "https://bugs.gnucash.org")
set (PACKAGE_STRING "${PACKAGE_NAME} ${PROJECT_VERSION}")
set (PACKAGE_URL "https://github.com/lorimark/gnucashew-dev")

# Change this in development versions when changing anything that
# affects stored data structures. Reset to zero when bumping version.

set (GNUCASHEW_RESAVE_VERSION "19920")

# Clear cache variables that will be filled later during the cmake run
unset(dist_generated CACHE)
unset(dist_generated_depends CACHE)

add_subdirectory( 3rd )
add_subdirectory( Dbo )
add_subdirectory( Eng )
add_subdirectory( Gui )
add_subdirectory( Glb )

include_directories(
  /opt/Wt4/include
  /usr/include/glib-2.0
  /usr/lib/x86_64-linux-gnu/glib-2.0/include
  Glb
)

link_directories(
  /opt/Wt4/lib
  /usr/local/lib
  /usr/local/lib/gnucash
  /usr/lib/x86_64-linux-gnu
)

add_executable (
  gnucashew-bin
  main.cpp
  App.cpp
  Config.cpp
  GnuCashew.cpp
  ${GCW_FILES}
  )

target_link_libraries(
  gnucashew-bin
  wt
  wthttp
  wtdbo
  wtdbosqlite3
  boost_system
  hpdf
  pthread
  xml2
  gnc-app-utils
  gnc-backend-sql
  gnc-backend-xml-utils
  gnc-core-utils
  gnc-engine
  gnc-gnome
  gnc-html
  gnc-locale-tax
  gnc-module
  gnucash-guile
  glib-2.0
  gobject-2.0
  uuid
)


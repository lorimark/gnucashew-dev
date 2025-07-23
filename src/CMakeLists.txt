cmake_minimum_required (VERSION 3.10)
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.14.0)
  cmake_policy(SET CMP0082 NEW)
endif()

project (gnucashew-bin
    VERSION 1.0
)

option(ENABLE_BILLPAY "Enable BillPay modules" OFF)
option(ENABLE_ASAN "Enable AddressSanitizer for memory debugging" OFF)

#
# this library is used in the file guid.cpp for generating
#  UUID values for the back-end database.
#
add_compile_definitions(GUID_LIBUUID)

if(ENABLE_BILLPAY)
  add_compile_definitions(ENABLE_BILLPAY)
endif()

# Set base compile flags
#
# DEC_NAMESPACE is for the decimal.h library.  It needs a namespace
#  directive, and the best place to do it is in the compiler flags
#  rather than somewhere in the source code
#
set(CMAKE_CXX_FLAGS "-DDEC_NAMESPACE=DECIMAL -std=c++17 -Wfatal-errors -Wbuiltin-macro-redefined -g")

# Append AddressSanitizer flags if requested
if(ENABLE_ASAN)
  message(STATUS "AddressSanitizer ENABLED")
  set(ASAN_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ASAN_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ASAN_FLAGS}")
else()
  message(STATUS "AddressSanitizer DISABLED")
endif()

set(PACKAGE_NAME GnuCashew)
#set(PACKAGE_BUGREPORT "https://bugs.gnucash.org")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PROJECT_VERSION}")
set(PACKAGE_URL "https://github.com/lorimark/gnucashew-dev")

set(GNUCASHEW_RESAVE_VERSION "19920")

unset(dist_generated CACHE)
unset(dist_generated_depends CACHE)

add_subdirectory(3rd)
add_subdirectory(Dbo)
add_subdirectory(Eng)
add_subdirectory(Gui)
add_subdirectory(Glb)

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

add_executable(
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
  uuid
)



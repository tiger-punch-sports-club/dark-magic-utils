cmake_minimum_required(VERSION 3.16)
project(dark-magic)
set(CMAKE_CXX_STANDARD 17)


# ---------------------------------------
# core
# ---------------------------------------
set(DARK_MAGIC_DIR "${PROJECT_SOURCE_DIR}/source")

add_library(  
  dark-magic-lib STATIC
  ${DARK_MAGIC_DIR}/KeyValue.h
  ${DARK_MAGIC_DIR}/LinearAllocator.h
  ${DARK_MAGIC_DIR}/TypeName.h
  ${DARK_MAGIC_DIR}/ServiceLocator.h
  ${DARK_MAGIC_DIR}/CompileTimeHash.h
  ${DARK_MAGIC_DIR}/EventBus.h
  ${DARK_MAGIC_DIR}/EventSocket.h
  ${DARK_MAGIC_DIR}/Utils.h
  ${DARK_MAGIC_DIR}/Singleton.h
  ${DARK_MAGIC_DIR}/ScopedPointer.h
  ${DARK_MAGIC_DIR}/TypeId.h
  
  ${DARK_MAGIC_DIR}/Library.cpp
)

# ---------------------------------------
# sandbox
# ---------------------------------------
set(SANDBOX_DIR "${PROJECT_SOURCE_DIR}/sandbox")

add_executable(
  dark-magic-sandbox
  ${SANDBOX_DIR}/main.cpp
)

target_include_directories(
  dark-magic-sandbox
  PRIVATE ${DARK_MAGIC_DIR}
)

target_link_libraries(
    dark-magic-sandbox
    PUBLIC dark-magic-lib
)


# ---------------------------------------
# preprocessor definitions
# ---------------------------------------
if (WIN32)
  string(REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable RTTI
  string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable exceptions
  
  target_compile_definitions(dark-magic-sandbox PRIVATE PLATFORM_WINDOWS PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_definitions(dark-magic-lib PRIVATE PLATFORM_WINDOWS PRIVATE _CRT_SECURE_NO_WARNINGS)

else()
  # set stuff for other systems
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")
endif()
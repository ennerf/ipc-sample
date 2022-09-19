cmake_minimum_required(VERSION 3.13  FATAL_ERROR)

project(ipc_sample)

set(THIRD_PARTY_ROOT ${PROJECT_SOURCE_DIR}/third_party)

# Aeron IPC framework
set(AERON_DIR ${THIRD_PARTY_ROOT}/aeron)
set(aeron_build_dir aeron-${CMAKE_BUILD_TYPE})
add_subdirectory(${AERON_DIR} ${aeron_build_dir})

# Aeron Flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /Od /Zi /MP /wd4251")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /MP /wd4251")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")

# Protobuf messages and runtime
set(PROTOBUF_SOURCES ${THIRD_PARTY_ROOT}/google/protobuf/src) # Protobuf sources directory
set(PROTOCOL_DIR ${PROJECT_SOURCE_DIR}/protocol/) # Root directory of generated protocol (protobuf)
set(PROTOBUF_SOURCE_FILES
		${PROTOBUF_SOURCES}/google/protobuf/arena.cc
		${PROTOBUF_SOURCES}/google/protobuf/arenastring.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/status.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/stringprintf.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/int128.cc
		${PROTOBUF_SOURCES}/google/protobuf/message_lite.cc
		${PROTOBUF_SOURCES}/google/protobuf/generated_message_util.cc
		${PROTOBUF_SOURCES}/google/protobuf/wire_format_lite.cc
		${PROTOBUF_SOURCES}/google/protobuf/io/coded_stream.cc
		${PROTOBUF_SOURCES}/google/protobuf/io/zero_copy_stream.cc
		${PROTOBUF_SOURCES}/google/protobuf/io/zero_copy_stream_impl_lite.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/common.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/once.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/atomicops_internals_x86_msvc.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/stringpiece.cc
		${PROTOBUF_SOURCES}/google/protobuf/stubs/structurally_valid.cc
		${PROTOBUF_SOURCES}/google/protobuf/repeated_field.cc)

set(PROTOBUF_GENERATED_SOURCE_FILES
		${PROTOCOL_DIR}/rima.pb.cc)

set(SRC "src/main.cpp")
add_executable(${PROJECT_NAME}
		${SRC}
		${PROTOBUF_SOURCE_FILES}
		${PROTOBUF_GENERATED_SOURCE_FILES})

# include directories specified here
target_include_directories(${PROJECT_NAME} PUBLIC
		include
		${PROTOBUF_SOURCES}
		${PROTOCOL_DIR})

# specific libraries linked to here
target_link_libraries(${PROJECT_NAME} PUBLIC aeron_client)

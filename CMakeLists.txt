cmake_minimum_required(VERSION 3.25...3.30)
project(CsponServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 根据构建配置（Debug 或 Release）设置运行时库
set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:>")

find_package(GDAL REQUIRED)
find_package(GEOS REQUIRED)
find_package(rapidjson CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_path(BSHOSHANY_THREAD_POOL_INCLUDE_DIRS "BS_thread_pool.hpp")
find_package(Taskflow CONFIG REQUIRED)

add_definitions(-D_UNICODE -DUNICODE)
add_definitions(-DNOMINMAX)

if (MSVC)
    add_compile_options(/utf-8)
    add_compile_options(/permissive- /Zc:__cplusplus)
    add_compile_options(/EHsc)
    add_compile_options(/std:c++20)
endif ()

if (NOT MSVC)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif ()

add_executable(${PROJECT_NAME} src/main.cpp)

aux_source_directory(src/controllers CTL_SRC)
aux_source_directory(src/filters FILTER_SRC)
aux_source_directory(src/plugins PLUGIN_SRC)
aux_source_directory(src/models MODEL_SRC)


target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRC_DIR}
        ${CTL_SRC}
        ${FILTER_SRC}
        ${PLUGIN_SRC}
        ${MODEL_SRC})


target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS})

message(STATUS "BSHOSHANY_THREAD_POOL_INCLUDE_DIRS directory: ${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS}")

target_link_libraries(${PROJECT_NAME} PRIVATE GDAL::GDAL)
target_link_libraries(${PROJECT_NAME} PRIVATE GEOS::geos GEOS::geos_c)
target_link_libraries(${PROJECT_NAME} PRIVATE rapidjson)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE Taskflow::Taskflow)
# 定义目标目录变量
set(CONFIGS_DIR ${CMAKE_SOURCE_DIR}/configs)
set(OUTPUT_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# 配置构建时复制 configs 目录到二进制目录
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CONFIGS_DIR}
        ${OUTPUT_DIR}/configs
        COMMENT "Copying configs directory to binary directory"
)


# 获取 GDAL 和 PROJ 数据目录
if (TARGET GDAL::GDAL)
    get_target_property(GDAL_DATA_DIR GDAL::GDAL GDAL_DATA)
    if (NOT GDAL_DATA_DIR)
        # 默认路径（如果未定义）
        set(GDAL_DATA_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/gdal")
    endif ()
endif ()

if (TARGET PROJ::proj)
    get_target_property(PROJ_LIB_DIR PROJ::proj PROJ_LIB)
    if (NOT PROJ_LIB_DIR)
        # 默认路径（如果未定义）
        set(PROJ_LIB_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/proj")
    endif ()
endif ()

# 复制 GDAL_DATA
if (GDAL_DATA_DIR)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${GDAL_DATA_DIR}" "${OUTPUT_DIR}/gdal_data"
    )
    message(STATUS "GDAL data directory: ${GDAL_DATA_DIR}")
endif ()

# 复制 PROJ_LIB
if (PROJ_LIB_DIR)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJ_LIB_DIR}" "${OUTPUT_DIR}/proj_lib"
    )
    message(STATUS "PROJ lib directory: ${PROJ_LIB_DIR}")
endif ()

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${OUTPUT_DIR}/logs
        COMMENT "Creating logs directory in binary directory if it does not exist"
)

message(STATUS "Configs directory: ${CONFIGS_DIR}")
cmake_minimum_required(VERSION 3.25...3.30)
project(CsponServer)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 根据构建配置（Debug 或 Release）设置运行时库
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:>")

# 查找依赖项
find_package(GDAL REQUIRED)
find_package(GEOS REQUIRED)
find_package(rapidjson CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_path(BSHOSHANY_THREAD_POOL_INCLUDE_DIRS "BS_thread_pool.hpp")
find_package(Taskflow CONFIG REQUIRED)

# 定义宏
add_definitions(-D_UNICODE -DUNICODE -DNOMINMAX)

# 编译器特定的选项
if (MSVC)
    add_compile_options(
            /utf-8                # UTF-8 编码支持
            /permissive-          # 标准兼容模式
            /Zc:__cplusplus       # 启用 __cplusplus 的正确值
            /EHsc                 # 启用 C++ 异常处理
            /std:c++20            # 使用 C++20 标准
    )
else ()
    add_compile_options(
            -finput-charset=UTF-8 # 输入文件字符集
            -fexec-charset=UTF-8  # 执行时字符集
    )
endif ()

# 添加源文件
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
aux_source_directory(${SRC_DIR}/controllers CTL_SRC)
aux_source_directory(${SRC_DIR}/filters FILTER_SRC)
aux_source_directory(${SRC_DIR}/plugins PLUGIN_SRC)
aux_source_directory(${SRC_DIR}/models MODEL_SRC)

# 定义可执行文件
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp ${CTL_SRC} ${FILTER_SRC} ${PLUGIN_SRC} ${MODEL_SRC})

# 包含目录
target_include_directories(${PROJECT_NAME}
        PRIVATE ${SRC_DIR}
        ${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS}
)

# 链接库
target_link_libraries(${PROJECT_NAME}
        PRIVATE GDAL::GDAL
        PRIVATE GEOS::geos GEOS::geos_c
        PRIVATE rapidjson
        PRIVATE Drogon::Drogon
        PRIVATE Taskflow::Taskflow
)

# 定义配置目录变量
set(CONFIGS_DIR ${CMAKE_SOURCE_DIR}/configs)
set(OUTPUT_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# 构建后操作：复制配置文件并创建必要的目录
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONFIGS_DIR} ${OUTPUT_DIR}/configs
        COMMENT "正在复制配置目录到二进制目录"
)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}/logs
        COMMENT "正在创建日志目录（如果不存在）"
)

# 获取 GDAL 和 PROJ 的数据目录
if (TARGET GDAL::GDAL)
    get_target_property(GDAL_DATA_DIR GDAL::GDAL GDAL_DATA)
    if (NOT GDAL_DATA_DIR)
        set(GDAL_DATA_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/gdal")
    endif ()
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${GDAL_DATA_DIR}" "${OUTPUT_DIR}/gdal_data"
            COMMENT "正在复制 GDAL 数据目录到二进制目录"
    )
    message(STATUS "GDAL 数据目录: ${GDAL_DATA_DIR}")
endif ()

if (TARGET PROJ::proj)
    get_target_property(PROJ_LIB_DIR PROJ::proj PROJ_LIB)
    if (NOT PROJ_LIB_DIR)
        set(PROJ_LIB_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/proj")
    endif ()
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJ_LIB_DIR}" "${OUTPUT_DIR}/proj_lib"
            COMMENT "正在复制 PROJ 库目录到二进制目录"
    )
    message(STATUS "PROJ 库目录: ${PROJ_LIB_DIR}")
endif ()

# 输出重要路径信息
message(STATUS "配置文件目录: ${CONFIGS_DIR}")
message(STATUS "BSHOSHANY_THREAD_POOL_INCLUDE_DIRS 目录: ${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS}")

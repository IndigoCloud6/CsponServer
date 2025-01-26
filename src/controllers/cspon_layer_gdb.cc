﻿#include "cspon_layer_gdb.h"
#include <string>
#include <gdal_priv.h>
#include "cpl_port.h"
#include <gdal.h>
#include <ogrsf_frmts.h>
#include <drogon/HttpAppFramework.h>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h> // 用于 Windows 的 _getcwd
#else
#include <unistd.h> // 用于 Linux/Unix 的 getcwd
#endif

using namespace cspon::layer;

namespace fs = std::filesystem;

// 获取当前工作目录的函数
std::string GetCurrentDirectory() {
    char pathBuffer[1024];

#if defined(_WIN32) || defined(_WIN64)
    if (!_getcwd(pathBuffer, sizeof(pathBuffer))) {
        LOG_INFO << "无法获取 Windows 平台的当前工作目录。\n";
        return "";
    }
#else
    if (!getcwd(pathBuffer, sizeof(pathBuffer))) {
        LOG_INFO << "无法获取 Linux/Unix 平台的当前工作目录。\n";
        return "";
    }
#endif

    return std::string(pathBuffer);
}

// 获取环境变量的函数
std::string GetEnvironmentVariable(const char *varName) {
#if defined(_WIN32) || defined(_WIN64)
    char *buffer = nullptr;
    size_t bufferSize = 0;
    if (_dupenv_s(&buffer, &bufferSize, varName) == 0 && buffer != nullptr) {
        std::string value(buffer);
        free(buffer);
        return value;
    }
    return "";
#else
    const char *value = std::getenv(varName);
    return value ? std::string(value) : "";
#endif
}

// 初始化 GDAL 的环境变量
void InitializeGDALDataAndProjLib() {
    std::string currentDir = GetCurrentDirectory();
    if (currentDir.empty()) {
        std::cerr << "无法确定当前目录。初始化中止。\n";
        return;
    }

    std::string defaultGDALData = currentDir + "/gdal_data";
    std::string defaultProjLib = currentDir + "/proj_lib";

    auto setEnvVar = [](const std::string &varName, const std::string &defaultPath) {
        std::string envValue = GetEnvironmentVariable(varName.c_str());
        if (!envValue.empty() && fs::exists(envValue)) {
            LOG_INFO << varName << " 已设置为有效路径：" << envValue << "\n";
        } else {
            LOG_INFO << varName << " 未设置或无效。设置为：" << defaultPath << "\n";
            CPLSetConfigOption(varName.c_str(), defaultPath.c_str());
        }
    };

    setEnvVar("GDAL_DATA", defaultGDALData);
    setEnvVar("PROJ_LIB", defaultProjLib);
}

// 递归报告矢量图层和子组
static void ReportHierarchicalLayers(CPLJSONObject &oRoot, const GDALGroup *group) {
    const auto &vectorLayerNames = group->GetVectorLayerNames();
    CPLJSONArray layerArray;
    oRoot.Add("layerNames", layerArray);

    for (const auto &layerName: vectorLayerNames) {
        OGRLayer *poLayer = group->OpenVectorLayer(layerName);
        if (poLayer) {
            CPLJSONObject layerObject;
            layerObject.Add("name", poLayer->GetName());
            layerObject.Add("type", OGRToOGCGeomType(poLayer->GetGeomType()));

            const char *alias = poLayer->GetMetadataItem("ALIAS_NAME");
            alias ? layerObject.Add("alias", alias) : layerObject.AddNull("alias");

            layerObject.Add("count", poLayer->GetFeatureCount());

            if (auto *spatialRef = poLayer->GetSpatialRef()) {
                const char *authorityCode = spatialRef->GetAuthorityCode(nullptr);
                authorityCode ? layerObject.Add("authoritycode", authorityCode) : layerObject.AddNull("authoritycode");
            }

            layerArray.Add(layerObject);
        }
    }

    const auto &subGroupNames = group->GetGroupNames();
    CPLJSONArray groupArray;
    oRoot.Add("groups", groupArray);

    for (const auto &subGroupName: subGroupNames) {
        if (auto subGroup = group->OpenGroup(subGroupName)) {
            CPLJSONObject groupObject;
            groupArray.Add(groupObject);
            groupObject.Set("name", subGroupName);
            ReportHierarchicalLayers(groupObject, subGroup.get());
        }
    }
}

// 获取 GDAL GDB 信息的处理函数
void gdb::getGdbInfo(const HttpRequestPtr &pReq, std::function<void(const HttpResponsePtr &)> &&fCallback) {
    InitializeGDALDataAndProjLib();
    GDALAllRegister();

    Json::Value responseJson;
    auto pReqJson = pReq->getJsonObject();
    // 优化 GDAL 性能
    CPLSetConfigOption("GDAL_CACHEMAX", "512");
    CPLSetConfigOption("GDAL_NUM_THREADS", "ALL_CPUS");

    if (!pReqJson) {
        responseJson["code"] = 400;
        responseJson["message"] = "无效或缺失的 JSON 请求体";
    } else if (pReqJson->isMember("file_path") && (*pReqJson)["file_path"].isString()) {
        std::string filePath = (*pReqJson)["file_path"].asString();
        LOG_INFO << "file_path: " << filePath;

        char **allowedDrivers = CSLAddString(nullptr, "OpenFileGDB");
        std::unique_ptr<GDALDataset> dataset(GDALDataset::Open(filePath.c_str(), GDAL_OF_VECTOR, allowedDrivers));
        CSLDestroy(allowedDrivers);

        if (!dataset) {
            LOG_INFO << "无法打开：" << filePath;
            responseJson["code"] = 400;
            responseJson["message"] = "无法打开文件";
        } else {
            LOG_INFO << "驱动名称：" << dataset->GetDriverName();

            CPLJSONObject rootObject;
            if (auto rootGroup = dataset->GetRootGroup();
                rootGroup && (!rootGroup->GetGroupNames().empty() || !rootGroup->GetVectorLayerNames().empty())) {
                CPLJSONObject groupObject;
                rootObject.Add("rootGroup", groupObject);
                ReportHierarchicalLayers(groupObject, rootGroup.get());
            }

            LOG_INFO << "图层信息：" << rootObject.ToString();

            Json::Value resultData;
            Json::CharReaderBuilder builder;
            JSONCPP_STRING errors;
            std::istringstream inputStream(rootObject.ToString());

            if (Json::parseFromStream(builder, inputStream, &resultData, &errors)) {
                responseJson["code"] = 200;
                responseJson["data"] = resultData;
            } else {
                responseJson["code"] = 400;
                responseJson["message"] = "JSON 格式无效";
            }
        }
    } else {
        responseJson["code"] = 400;
        responseJson["message"] = "缺少或无效的参数：file_path";
    }

    auto response = HttpResponse::newHttpJsonResponse(responseJson);
    response->setStatusCode(responseJson["code"].asInt() == 200 ? drogon::k200OK : drogon::k400BadRequest);
    fCallback(response);
}

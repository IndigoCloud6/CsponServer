#include "cspon_layer_gdb.h"
#include <string>
#include <gdal_priv.h>
#include "cpl_port.h"
#include <gdal.h>
#include <ogrsf_frmts.h>
#include <drogon/HttpAppFramework.h>
#include "BS_thread_pool.hpp" // BS::thread_pool
using namespace cspon::layer;


static void ReportHierarchicalLayers(CPLJSONObject &oRoot, const GDALGroup *group, bool bGeomType) {
    const auto aosVectorLayerNames = group->GetVectorLayerNames();
    CPLJSONArray oLayerNames;
    oRoot.Add("layerNames", oLayerNames);
    for (const auto &osVectorLayerName: aosVectorLayerNames) {
        OGRLayer *poLayer = group->OpenVectorLayer(osVectorLayerName);
        if (poLayer) {
            CPLJSONObject oLayer;
            oLayer.Add("name", poLayer->GetName());
            oLayer.Add("type", OGRToOGCGeomType(poLayer->GetGeomType()));
            const char *alias = poLayer->GetMetadataItem("ALIAS_NAME");
            alias ? oLayer.Add("alias", alias) : oLayer.AddNull("alias");
            oLayer.Add("count", poLayer->GetFeatureCount());
            OGRSpatialReference *oSpatialRef = poLayer->GetSpatialRef();
            const char *authoritycode = oSpatialRef->GetAuthorityCode(nullptr);
            authoritycode ? oLayer.Add("authoritycode", authoritycode) : oLayer.AddNull("authoritycode");
            oLayerNames.Add(oLayer);
        }
    }

    auto aosSubGroupNames = group->GetGroupNames();
    CPLJSONArray oGroupArray;
    oRoot.Add("groups", oGroupArray);
    for (const auto &osSubGroupName: aosSubGroupNames) {
        auto poSubGroup = group->OpenGroup(osSubGroupName);
        if (poSubGroup) {
            CPLJSONObject oGroup;
            oGroupArray.Add(oGroup);
            oGroup.Set("name", osSubGroupName);
            ReportHierarchicalLayers(oGroup, poSubGroup.get(), bGeomType);
        }
    }
}


void periodic_task_async_a(int interval_ms, int repeat_count) {
    for (int i = 0; i < repeat_count; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        std::cout << "AAAA  Task executed at: "
                << std::chrono::steady_clock::now().time_since_epoch().count()
                << "\n";
    }
}

void periodic_task_async_b(int interval_ms, int repeat_count) {
    for (int i = 0; i < repeat_count; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        std::cout << "BBBB   Task executed at: "
                << std::chrono::steady_clock::now().time_since_epoch().count()
                << "\n";
    }
}


drogon::AsyncTask gdb::synctest(
    const HttpRequestPtr req,
    std::function<void(const HttpResponsePtr &)> callback) {
    // 异步任务

    int interval_ms = 500; // 间隔500ms
    int repeat_count = 10; // 执行10次
    app().getLoop()->queueInLoop(async_func([interval_ms,repeat_count]() -> Task<> {
        periodic_task_async_a(interval_ms, repeat_count);
        co_return;
    }));
    // 创建响应
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("Hello, world!");
    callback(resp);
    co_return;
}

void gdb::getinfo(const HttpRequestPtr &pReq, std::function<void(const HttpResponsePtr &)> &&fCallback) {
    int interval_ms = 500; // 间隔500ms
    int repeat_count = 10; // 执行10次
    /*
    std::thread([] {
        // 模拟耗时任务
        std::this_thread::sleep_for(std::chrono::seconds(5));
        auto clientPtr = drogon::app().getDbClient("local");
        std::string xzqmc = "草堂镇"; // 确保字符串是 UTF-8 编码
        std::string connectionInfo = clientPtr->connectionInfo();
        std::cout << connectionInfo << "connectionInfo" << std::endl;
        clientPtr->execSqlAsync("select * from jbcy_2569520 where xzqmc=$1",
                                [](const drogon::orm::Result &result) {
                                    LOG_INFO << result.size();
                                    std::cout << result.size() << " rows selected!" << std::endl;
                                    int i = 0;
                                    for (auto row: result) {
                                        std::cout << i++ << ": user name is " << row["xzqmc"].as<std::string>() <<
                                                std::endl;
                                    }
                                },
                                [](const drogon::orm::DrogonDbException &e) {
                                    std::cerr << "error:" << e.base().what() << std::endl;
                                },
                                xzqmc);
        LOG_INFO << "Async task completed!";
        // 在此处处理任务的逻辑
    }).detach();
    */

    auto param = pReq->getParameter("param");

    /*
    BS::thread_pool pool(50);
    std::vector<std::future<int> > results;
    for (int i = 0; i < 10; ++i) {
        results.push_back(pool.submit_task([i]() {
            // 模拟一些计算
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "BBBB   Task executed at: "
                << std::chrono::steady_clock::now().time_since_epoch().count()
                << "\n";
            return i * i;
        }));
    }
    // 获取任务结果
    for (auto &result: results) {
        std::cout << "Result: " << result.get() << '\n';
    }
    */

    GDALAllRegister();

    //auto clientPtr = drogon::app().getDbClient("local");

    Json::Value responseJson;
    auto pRespJson = pReq->getJsonObject();
    const char *projLibPath = nullptr;
    const char *gdalData = nullptr;

#ifdef _WIN32
    // Windows 系统路径
    projLibPath = "gdal_data";
    gdalData = "proj_lib";
#elif __linux__
    // Linux 系统路径
    projLibPath = "./gdal_data";
    gdalData = "./proj_lib";
#endif
    CPLSetConfigOption("PROJ_LIB", projLibPath);
    CPLSetConfigOption("GDAL_DATA", gdalData);
    CPLSetConfigOption("GDAL_CACHEMAX", "512"); // 设置为 512MB
    CPLSetConfigOption("GDAL_NUM_THREADS", "ALL_CPUS");

    if (!pRespJson) {
        responseJson["code"] = 400;
        responseJson["message"] = "Invalid or missing JSON body";
    } else if (pRespJson->isMember("file_path") && (*pRespJson)["file_path"].isString()) {
        std::string file_path = (*pRespJson)["file_path"].asString();
        LOG_INFO << "file_path: " << file_path;

        char **papszAllowedDrivers = nullptr;
        papszAllowedDrivers = CSLAddString(papszAllowedDrivers, "OpenFileGDB");

        GDALDataset *poDS = GDALDataset::Open(file_path.c_str(), GDAL_OF_VECTOR, papszAllowedDrivers, nullptr,
                                              nullptr);
        if (poDS == nullptr) {
            LOG_INFO << "Failed to open: " << file_path;
            responseJson["code"] = 400;
            responseJson["message"] = "Failed to open";
        } else {
            const char *DriverName = poDS->GetDriverName();
            LOG_INFO << "DriverName: " << DriverName;
            CPLJSONObject oRoot;
            auto poRootGroup = poDS->GetRootGroup();
            if (poRootGroup && (!poRootGroup->GetGroupNames().empty() || !poRootGroup->GetVectorLayerNames().empty())) {
                CPLJSONObject oGroup;
                oRoot.Add("rootGroup", oGroup);
                ReportHierarchicalLayers(oGroup, poRootGroup.get(), true);
            }
            LOG_INFO << "Layer Information:." << oRoot.ToString();
            GDALClose(poDS);
            LOG_INFO << "Dataset closed successfully.";
            Json::Value resultData;
            Json::CharReaderBuilder builder;
            JSONCPP_STRING errs;

            std::istringstream iss(oRoot.ToString());
            if (Json::parseFromStream(builder, iss, &resultData, &errs)) {
                responseJson["code"] = 200;
                responseJson["data"] = resultData;
            } else {
                responseJson["code"] = 400;
                responseJson["message"] = "Invalid JSON format";
            }
        }
    } else {
        responseJson["code"] = 400;
        responseJson["message"] = "Missing or invalid parameter: file_path";
    }

    auto resp = HttpResponse::newHttpJsonResponse(responseJson);
    resp->setStatusCode(responseJson["code"].asInt() == 200 ? drogon::k200OK : drogon::k400BadRequest);
    fCallback(resp);
}

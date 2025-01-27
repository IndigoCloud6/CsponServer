#pragma once

#include <drogon/drogon.h>
#include <drogon/HttpController.h>
using namespace drogon;

namespace cspon {
    namespace layer {
        class gdb : public drogon::HttpController<gdb> {
        public:
            METHOD_LIST_BEGIN
                ADD_METHOD_TO(gdb::getGdbInfo, "/GetGdbLayerInfo", drogon::Post);
                ADD_METHOD_TO(gdb::GetLayerFeatures, "/GetLayerFeatures", drogon::Post);
            METHOD_LIST_END

            static void getGdbInfo(const drogon::HttpRequestPtr &pReq,
                         std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);

            static void GetLayerFeatures(const drogon::HttpRequestPtr &pReq,
                         std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);
        };
    }
}

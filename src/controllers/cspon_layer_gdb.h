#pragma once

#include <drogon/drogon.h>
#include <drogon/HttpController.h>
#include <taskflow/taskflow.hpp>  // Taskflow is header-only
using namespace drogon;

namespace cspon {
    namespace layer {
        class gdb : public drogon::HttpController<gdb> {
        public:
            METHOD_LIST_BEGIN
                ADD_METHOD_TO(gdb::getinfo, "/getinfo", drogon::Post);
                ADD_METHOD_TO(gdb::synctest, "/synctest", drogon::Get);
            METHOD_LIST_END

            void getinfo(const drogon::HttpRequestPtr &pReq,
                         std::function<void(const drogon::HttpResponsePtr &)> &&fCallback);

            drogon::AsyncTask synctest(
                HttpRequestPtr req,
                std::function<void(const HttpResponsePtr &)> callback);
        };
    }
}

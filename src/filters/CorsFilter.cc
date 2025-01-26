/**
 *
 *  CorsFilter.cc
 *
 */

#include "CorsFilter.h"

using namespace drogon;

void CorsFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    //Edit your logic here
    if (1)
    {

        LOG_INFO << "进入过滤器: CorsFilter";
        //Passed
        fccb();
        return;
    }
    //Check failed
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k500InternalServerError);
    fcb(res);
}

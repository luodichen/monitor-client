#include "LActiveRequest.h"
#include "errcode.h"

const char *szAPI = "/api/active/";

LActiveRequest::LActiveRequest(const char *szServer)
    : LRequester((std::string(szServer) + szAPI).c_str())
    , m_sIPAddress("")
    , m_sErrorInfo("")
    , m_bIsUpdated(false)
{

}

LActiveRequest::~LActiveRequest()
{

}

int LActiveRequest::Request()
{
    int nRet = LRequester::Request();
    if (0 != nRet)
        return nRet;

    Json::Value response;
    if (!GetResponse(response))
        return ERR::BAD_RESPONSE;

    m_sIPAddress = response["ip_address"].asString();
    m_sErrorInfo = response["text"].asString();
    m_bIsUpdated = response["ddns_update"].asBool();

    return response["code"].asInt();
}

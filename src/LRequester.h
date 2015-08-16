#pragma once

#include "curl.h"
#include <string>
#include <map>
#include <set>
#include <json/json.h>

class LRequester
{
public:
    LRequester(const char *szURL);
    virtual ~LRequester();

public:
    void SetPostData(std::map<std::string, std::string> &mData);
    virtual int Request();

protected:
    bool GetResponse(Json::Value &response);

private:
    static size_t CURLWriteCallback(char *ptr, size_t size, size_t nmemb, 
                                    void *userdata);

private:
    std::string m_sPostFields;
    std::string m_sResponse;
    std::string m_sURL;
    CURL *m_pCURL;
};

#pragma once

#include "curl.h"
#include <string>
#include <map>

class LRequester
{
public:
    LRequester(const char *szURL);
    virtual ~LRequester();

public:
    void SetPostData(std::map<std::string, std::string> &mData);
    int Request();

private:
    std::string m_sURL;
    CURL *m_pCURL;
};


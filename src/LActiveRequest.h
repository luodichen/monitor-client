#pragma once
#include "LRequester.h"
class LActiveRequest : public LRequester
{
public:
    LActiveRequest(const char *szServer);
    virtual ~LActiveRequest();

public:
    std::string m_sIPAddress;
    std::string m_sErrorInfo;
    bool m_bIsUpdated;

public:
    virtual int Request();
};


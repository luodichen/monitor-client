#include "LRequester.h"
#include <assert.h>
#include "errcode.h"

#pragma comment(lib, "libcurl.lib")

LRequester::LRequester(const char *szURL)
    : m_sPostFields("")
    , m_sResponse("")
    , m_sURL(szURL)
    , m_pCURL(curl_easy_init())
{
    assert(NULL != m_pCURL);
    curl_easy_setopt(m_pCURL, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(m_pCURL, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(m_pCURL, CURLOPT_ACCEPTTIMEOUT_MS, 10000L);
    curl_easy_setopt(m_pCURL, CURLOPT_LOW_SPEED_TIME, 15L);
    curl_easy_setopt(m_pCURL, CURLOPT_URL, szURL);
    curl_easy_setopt(m_pCURL, CURLOPT_WRITEFUNCTION, CURLWriteCallback);
    curl_easy_setopt(m_pCURL, CURLOPT_WRITEDATA, (void *)this);
}

LRequester::~LRequester()
{
    curl_easy_cleanup(m_pCURL);
}

void LRequester::SetPostData(std::map<std::string, std::string>& mData)
{
    m_sPostFields = "";
    std::map<std::string, std::string>::const_iterator iter = mData.begin();
    int i = 0;
    for (; iter != mData.end(); iter++)
    {
        if (i++ > 0)
            m_sPostFields += "&";
        char *szUrlencode = curl_easy_escape(m_pCURL, iter->second.c_str(), 0);
        m_sPostFields += (iter->first + "=" + szUrlencode);
        curl_free(szUrlencode);
    }
}

int LRequester::Request()
{
    m_sResponse = "";
    curl_easy_setopt(m_pCURL, CURLOPT_POSTFIELDSIZE, m_sPostFields.size());
    curl_easy_setopt(m_pCURL, CURLOPT_POSTFIELDS, m_sPostFields.c_str());

    CURLcode code = curl_easy_perform(m_pCURL);
    if (CURLE_OK != code)
        return ERR::CURL_BASE + code;

    return 0;
}

bool LRequester::GetResponse(Json::Value &response)
{
    Json::Reader render;
    return render.parse(m_sResponse, response, false);
}

size_t LRequester::CURLWriteCallback(char * ptr, size_t size, 
                                    size_t nmemb, void * userdata)
{
    LRequester *pThis = (LRequester *)userdata;
    pThis->m_sResponse.append(ptr, size * nmemb);

    return size * nmemb;
}

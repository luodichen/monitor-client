#include "LRequester.h"
#include <assert.h>

#pragma comment(lib, "libcurl.lib")

LRequester::LRequester(const char *szURL)
    : m_sURL(szURL)
    , m_pCURL(NULL)
{
    assert(NULL != (m_pCURL = curl_easy_init()));
    curl_easy_setopt(m_pCURL, CURLOPT_URL, szURL);
}

LRequester::~LRequester()
{
    curl_easy_cleanup(m_pCURL);
}

void LRequester::SetPostData(std::map<std::string, std::string>& mData)
{

}

int LRequester::Request()
{
    return 0;
}

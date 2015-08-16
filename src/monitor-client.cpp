#include "monitor-client.h"
#include "LActiveRequest.h"
#include "errcode.h"
#include <json/json.h>

void ClientEntry(void *pParams)
{
    LActiveRequest requester("http://monitor.luodc.cn");
    std::map<std::string, std::string> form;
    form["token"] = "c2huIHdxaSBrdHIgZmt1ZQ";
    requester.SetPostData(form);

    while (true)
    {
        int nRetCode = requester.Request();

        time_t t = time(NULL);
        struct tm *pLocalTime = localtime(&t);
        char szTime[128];
        strftime(szTime, sizeof(szTime), "%F %H:%M:%S", pLocalTime);
        printf("[%s] ", szTime);

        if (ERR::OK == nRetCode)
        {
            printf("status=%s, client-ip=%s, update-ddns=%s\n",
                requester.m_sErrorInfo.c_str(),
                requester.m_sIPAddress.c_str(),
                requester.m_bIsUpdated ? "yes" : "no");
        }
        else
        {
            printf("failed:%d - %s\n", nRetCode, requester.m_sErrorInfo.c_str());
        }

        Sleep(60000);
    }
}

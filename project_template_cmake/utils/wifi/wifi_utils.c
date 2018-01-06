#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "u_ipcd.h"
#include "u_dbg.h"
#include "u_wifi_utils.h"

/*-----------------------------------------------------------------------------
 * macro  declarations
 *---------------------------------------------------------------------------*/
#define WIFI_MAX_STRING 100

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static UCHAR wifi_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


BOOL u_wifi_get_connect_status(VOID)
{
    INT32 i4_ret;
	UCHAR tar[WIFI_MAX_STRING+1] = {0};
	UCHAR *ch = NULL;

    i4_ret = system("wpa_cli -iwlan0 -p/data/wifi/sockets status > tmp/wifi_status");
    if (0 != i4_ret)
    {
        printf("<wifi>[%s:%d]wpa_cli current not start, wait!\n", __FUNCTION__, __LINE__);
        return FALSE;
    }

	FILE * fp = fopen("tmp/wifi_status", "r");
    if (NULL != fp)
    {
		//wifi status parser
		while(fgets(tar,WIFI_MAX_STRING,fp)!=NULL)
		{
			ch = strtok(tar,"=");
			if(0 != strcmp("wpa_state",ch))
			{
				continue;
			}
			//printf("<wifi> string :%s\n",ch);
			ch = strtok(NULL,"\n");
			//printf("<wifi> start to parser string :%s\n",ch);
			break;
		}
    }
    else
    {
        return FALSE;
    }

	fclose(fp);

	if(0 == strcmp("CONNECTED",ch))
	{
		//printf("<wifi>current status is : CONNECTED\n");
		return TRUE;
	}
	else if(0 == strcmp("DISCONNECTED",ch))
	{
		//printf("<wifi>current status is : DISCONNECTED\n");
		return FALSE;
	}
	else
	{
		//printf("<wifi>current status is : %s\n",ch);
		return FALSE;
	}

    return FALSE;
}


INT32 u_wifi_get_mac_address(UCHAR *mac)
{
    INT32 i4_ret;
	UCHAR tar[WIFI_MAX_STRING+1] = {0};
	UCHAR *ch = NULL;
	int index=0;

	assert(NULL != mac);

	i4_ret = system("wpa_cli -iwlan0 -p/data/wifi/sockets status > tmp/wifi_status");
    if (0 != i4_ret)
    {
        printf("<wifi>[%s:%d]wpa_cli current not start, wait!\n", __FUNCTION__, __LINE__);
        return -1;
    }

	FILE * fp = fopen("tmp/wifi_status", "r");
    if (NULL != fp)
    {
		//wireless mac address
	    while(fgets(tar,WIFI_MAX_STRING,fp)!=NULL)
		{
	        ch = strtok(tar,"=");
			if(0 != strcmp("address",ch))
			{
				continue;
			}

			for(index=0;index<6;index++)
			{
				ch = strtok(NULL,":");
				wifi_mac[index] = strtol(ch,NULL,16);
			}

			printf("<wifi>parser wifi_mac is ");

			for(index=0;index<6;index++)
			{
	        	printf("0x%02x ",wifi_mac[index]);
				mac[index] = wifi_mac[index];
			}
			printf("\n");
			break;
	    }
	}
    else
    {
        return -1;
    }

    fclose(fp);

    return 0;
}

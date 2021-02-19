#include "Pushover.h"
const char *PUSHOVER_ROOT_CA = "-----BEGIN CERTIFICATE-----\n"
							   "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
							   "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
							   "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
							   "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
							   "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
							   "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
							   "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
							   "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
							   "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
							   "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
							   "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
							   "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
							   "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
							   "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
							   "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
							   "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
							   "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
							   "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
							   "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
							   "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
							   "-----END CERTIFICATE-----\n";

Pushover::Pushover(String token, String user)
{
	_token = token;
	_user = user;
}
void Pushover::setMessage(String message)
{
	_message = message;
}
void Pushover::setToken(String token)
{
	_token = token;
}
void Pushover::setUser(String user)
{
	_user = user;
}
void Pushover::setDevice(String device)
{
	_device = device;
}
void Pushover::setTitle(String title)
{
	_title = title;
}
void Pushover::setUrl(String url)
{
	_url = url;
}
void Pushover::setUrlTitle(String url_title)
{
	_url_title = url_title;
}
void Pushover::setPriority(int8_t priority)
{
	_priority = priority;
}
void Pushover::setTimestamp(uint32_t timestamp)
{
	_timestamp = timestamp;
}
void Pushover::setSound(String sound)
{
	_sound = sound;
}
void Pushover::setTimeout(uint16_t timeout)
{
	_timeout = timeout;
}
void Pushover::setHTML(boolean html)
{
	_html = html;
}
int Pushover::send(void)
{
	
	HTTPClient myClient;
	
	myClient.begin("https://api.pushover.net/1/messages.json", PUSHOVER_ROOT_CA);
	myClient.addHeader("Content-Type", "application/json"); 
	DynamicJsonDocument doc(2048);
	doc["token"]=_token;
	doc["user"]=_user;
	doc["message"]=_message;
	doc["title"]=_title;
	doc["url"]=_url;
	doc["url_title"]=_url_title;
	doc["html"]=_html;
	doc["priority"]=_priority;
	doc["sound"]=_sound;

	doc["timestamp"]=_timestamp;
	char output[256];
	serializeJson(doc, output);
	int code=myClient.POST(output);

	myClient.end();
	return code;

}

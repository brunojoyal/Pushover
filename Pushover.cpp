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

Pushover::Pushover(String token, String user, bool unsafe = false)
{
	_token = token;
	_user = user;
	_unsafe = unsafe;
}
void Pushover::setMessage(String message)
{
	_message = message;
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
void Pushover::setRetry(uint16_t retry)
{
	_retry = retry;
}
void Pushover::setExpire(uint16_t expire)
{
	_expire = expire;
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
bool Pushover::send(void)
{
	bool success=false;
	WiFiClientSecure *client = new WiFiClientSecure;

	if (client)
	{

		client->setCACert(PUSHOVER_ROOT_CA);
		{
			if (client->connect("api.pushover.net", 443))
			{
				Serial.println("https connection established.");
				String post = String("token=") + _token + "&user=" + _user + "&title=" + _title + "&message=" + _message + "&device=" + _device + "&url=" + _url + "&url_title=" + _url_title + "&priority=" + _priority + "&retry=" + _retry + "&expire=" + _expire + "&sound=" + _sound;
				if (_timestamp != 0)
					post += String("&timestamp=") + _timestamp;
				if (_html == true)
					post += String("&html=1");
				String http = String("POST /1/messages.json HTTP/1.1\r\nHost: api.pushover.net\r\nConnection: close\r\nContent-Length: ") + post.length() + "\r\n\r\n" + post;
				client->print(http);
				int timeout_at = millis() + _timeout;
				while (!client->available() && timeout_at - millis() < 0)
				{
					client->stop();
					return false;
				}
				String line;
				while (client->available() != 0)
				{
					if (client->read() == '{')
						break;
				}
				line = client->readStringUntil('\n');
				client->stop();
				success=line.indexOf("\"status\":1") != -1 || line.indexOf("200 OK") != -1;
			}
			else
			{
				success=false;
				client->stop();
			}
		}
		delete client;
	}
	return success;
}

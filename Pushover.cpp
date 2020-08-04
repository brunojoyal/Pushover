#include "Pushover.h"

Pushover::Pushover(String token, String user, bool unsafe = false) {
	_token = token;
	_user = user;
	_unsafe = unsafe;
}
void Pushover::setMessage(String message) {
	_message = message;
}
void Pushover::setDevice(String device) {
	_device = device;
}
void Pushover::setTitle(String title) {
	_title = title;
}
void Pushover::setUrl(String url) {
	_url = url;
}
void Pushover::setUrlTitle(String url_title) {
	_url_title = url_title;
}
void Pushover::setPriority(int8_t priority) {
	_priority = priority;
}
void Pushover::setRetry(uint16_t retry) {
	_retry = retry;
}
void Pushover::setExpire(uint16_t expire) {
	_expire = expire;
}
void Pushover::setTimestamp(uint32_t timestamp) {
	_timestamp = timestamp;
}
void Pushover::setSound(String sound) {
	_sound = sound;
}
void Pushover::setTimeout(uint16_t timeout) {
	_timeout = timeout;
}
void Pushover::setHTML(boolean html) {
	_html = html;
}
boolean Pushover::send(void) {
	WiFiClientSecure client = new WifiClientSecure;
	int responseCode=-1;
	if(client){
		client.setCACert(root_ca);
		{
			HTTPClient https;
			https.begin(client, "api.pushover.net");
			if (!client.connect("api.pushover.net", 80, root_ca)) {
				return false;
			}
			String post = String("token=")+_token+"&user="+_user+"&title="+_title+"&message="+_message+"&device="+_device+"&url="+_url+"&url_title="+_url_title+"&priority="+_priority+"&retry="+_retry+"&expire="+_expire+"&sound="+_sound;
			if (_timestamp != 0) post += String("&timestamp=")+_timestamp;
			if (_html == true) post += String("&html=1");
			//String http = String("POST /1/messages.json HTTP/1.1\r\nHost: api.pushover.net\r\nConnection: close\r\nContent-Length: ")+post.length()+"\r\n\r\n"+post;
			responseCode = https.POST(post);
			https.end();
		}
		delete client;
	}
	else{
		Serial.println("Pushover: Unable to create client.");
	}
	return responseCode==200;
}


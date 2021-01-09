#include "../titans.h"

int getBalance(char *publicAddress)
{
	char				int_getBalance[200];
	char				*result;
	start_len			data = {.start = 0, .len = 0};
	get_request			req = {.buffer = NULL, .len = 0, .buflen = 0};
	CURLcode			ret;
	CURL				*hnd;
	struct curl_slist	*slist1;

	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "content-type: application/json;");
	hnd = curl_easy_init();

	snprintf(int_getBalance, sizeof(int_getBalance), "{\"jsonrpc\":\"2.0\",\"method\":\"int_getBalance\",\"params\":[\"%s\", \"latest\"],\"id\":1}", publicAddress);

	curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
	curl_easy_setopt(hnd, CURLOPT_URL, "http://localhost:8555/testnet");
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, int_getBalance);
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	req.buffer = malloc(CHUNK_SIZE);
	req.buflen = CHUNK_SIZE;
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&req);

	ret = curl_easy_perform(hnd);
	if (strstr((const char*)req.buffer, "result"))
	{
		result = value_of_json(req.buffer);
		printf("Balance: %f INT\n", hexToDec(result));
	}
	else
		print_error(req.buffer);
	free(req.buffer);
	curl_easy_cleanup(hnd);
	hnd = NULL;
	curl_slist_free_all(slist1);
	slist1 = NULL;
	return (0);
}

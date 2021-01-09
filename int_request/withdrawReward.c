#include "../titans.h"

int withdrawReward(char *fromAddress, char *delegateAddress)
{
	char				int_withdrawReward[300];
	char				*result;
	start_len			data = {.start = 0, .len = 0};
	get_request			req = {.buffer = NULL, .len = 0, .buflen = 0};
	CURLcode			ret;
	CURL				*hnd;
	struct curl_slist	*slist1;

	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "content-type: application/json;");
	hnd = curl_easy_init();

	snprintf(int_withdrawReward, sizeof(int_withdrawReward), "{\"jsonrpc\":\"2.0\",\"method\":\"int_withdrawReward\",\"params\":[\"%s\", \"%s\"],\"id\":1}", fromAddress, delegateAddress);

	curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
	curl_easy_setopt(hnd, CURLOPT_URL, "http://localhost:8555/testnet");
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, int_withdrawReward);
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	req.buffer = malloc(CHUNK_SIZE);
	req.buflen = CHUNK_SIZE;
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&req);

	ret = curl_easy_perform(hnd);
	// printf("Result = %u\n",ret);
	// printf("Total received bytes: %zu\n", req.len);
	data = ft_truncate(req.buffer, '"', 5); // tell where to start and where to end.
	if (!(result = ft_strsub((char const*)req.buffer, data.start, data.len))) // crop string
		return (-1);
	// printf("Received data: %s\n", result);
	printf("TX: %s\n", result);

	free(req.buffer);

	curl_easy_cleanup(hnd);
	hnd = NULL;
	curl_slist_free_all(slist1);
	slist1 = NULL;
	return (0);
}

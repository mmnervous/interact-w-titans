#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	unsigned char *buffer;
	size_t len;
	size_t buflen;
} get_request;

typedef struct {
	size_t start;
	size_t len;
} start_len;

#define CHUNK_SIZE 2048

size_t	write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize = size * nmemb;
	get_request *req = (get_request *) userdata;

	// printf("receive chunk of %zu bytes\n", realsize);
	while (req->buflen < req->len + realsize + 1)
	{
		req->buffer = realloc(req->buffer, req->buflen + CHUNK_SIZE);
		req->buflen += CHUNK_SIZE;
	}
	memcpy(&req->buffer[req->len], ptr, realsize);
	req->len += realsize;
	req->buffer[req->len] = 0;

	return realsize;
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s)
	{
		i = 0;
		str = (char*)malloc(len + 1);
		if (!str)
			return (NULL);
		while (s[start] && i < len)
		{
			str[i] = s[start];
			++i;
			++start;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

start_len ft_truncate(char *buffer, int delimiter, int x) // this function calculate where to start and where to end
{
	int		j;
	int		k;
	start_len data = {.start = 0, .len = 0};

	j = 0;
	k = 0;
	while (buffer[data.start] && x != j)
	{
		if (buffer[data.start] == delimiter)
			++j;
		++data.start;
	}
	k = data.start;
	while (buffer[k] && buffer[k] != delimiter)
		++k;
	data.len = k - data.start;
	// printf("truncate : data.start = %d, j = %d, k = %d, data.len = %d\n", data.start, j, k, data.len); // debug
	return (data);
}

void getBalance(char *argv)
{
	char		int_getBalance[500];
	char		*result;
	start_len	data = {.start = 0, .len = 0};
	get_request req = {.buffer = NULL, .len = 0, .buflen = 0};
	CURLcode ret;
	CURL *hnd;
	struct curl_slist *slist1;
	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "content-type: application/json;");
	hnd = curl_easy_init();

	sprintf(int_getBalance, "{\"jsonrpc\":\"2.0\",\"method\":\"int_getBalance\",\"params\":[\"%s\", \"latest\"],\"id\":1}", argv);

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
	// printf("Result = %u\n",ret);
	// printf("Total received bytes: %zu\n", req.len);
	data = ft_truncate(req.buffer, '"', 9);
	result = ft_strsub(req.buffer, data.start, data.len);
	printf("Received data: %s\n", result);
	free(req.buffer);

	curl_easy_cleanup(hnd);
	hnd = NULL;
	curl_slist_free_all(slist1);
	slist1 = NULL;
}

int	main(int argc, char *argv[])
{
	getBalance(argv[1]);
	return (0);
}

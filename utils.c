#include "titans.h"

// char	*value_of_json(unsigned char *buffer, char *valueOf)
// {
// 	char	*buffer2;
// 	char	*result;
// 	int		i = 0;
// 	int		j;

// 	buffer2 = strstr((const char*)buffer, valueOf);
// 	if (buffer2)
// 	{
// 		result = (char*)malloc(strlen(buffer2));
// 		result = strcpy(result, buffer2);
// 		result = result+(strlen(valueOf));
// 		while (result[i] == '"' || result[i] == ':')
// 			++i;
// 		j = strlen(result);
// 		printf("j = %d\n", j);
// 		while (result[j] != '"')
// 		{
// 			printf("j = %d\n", j);
// 			--j;
// 		}
// 		printf("j = %d\n", j);
// 		result = ft_strsub(result, i, j);

// 	}
// 	return (result);
// }

void	print_error(unsigned char *buffer)
{
	/* unlock account */
	if (strstr((const char*)buffer, "could not decrypt key with given passphrase"))
		printf("Error: could not decrypt key with given passphrase\n");
	else if (strstr((const char*)buffer, "no key for given address or file"))
		printf("Error: no key for given address or file\n");

	/* withdraw reward */
	else if (strstr((const char*)buffer, "unknown account"))
		printf("Error: unknown account\n");
	else if (strstr((const char*)buffer, "have no reward to withdraw"))
		printf("Error: have no reward to withdraw\n");

	/* unForbidden */
	else if (strstr((const char*)buffer, "password or unlock"))
		printf("Error: authentication needed: password or unlock\n");
	else if (strstr((const char*)buffer, "should not unforbidden"))
		printf("Error: should not unforbidden\n");

	/* global error*/
	else if (strstr((const char*)buffer, "error"))
		printf("req.buffer: %s\n", buffer);
	else
		printf("unknown error\n");
}

char	*value_of_json(unsigned char *buffer)
{
	char	*result;
	int		j;

	result = strrchr((const char*)buffer, ':');
	// printf("%p, %p\n", result, buffer+32);
	j = strlen(result);
	while (result[--j] != '"');
	result = ft_strsub(result, 2, j-2);
	return (result);
}

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

start_len ft_truncate(unsigned char *buffer, int delimiter, int x) // this function calculate where to start and where to end
{
	int		j;
	int		k;

	x = x * 2 - 1;
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

double hexToDec(char *hex)
{
	if (!hex)
		return (-1);
	else
	{
		mpz_t	nr;
		mpf_t	f;
		char	*base10;
		double	decimal;

		mpz_init(nr);
		mpf_init(f);
		mpz_set_str(nr, hex+2, 16);
		base10 = mpz_get_str(NULL, 10, nr);
		mpf_set_str(f, base10, 10);
		mpf_div_ui (f, f, 1e+18);
		decimal = mpf_get_d(f);
		mpz_clear(nr);
		return (decimal);
	}
}

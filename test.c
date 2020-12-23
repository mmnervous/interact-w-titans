#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t start;
    size_t len;
} start_len;

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

start_len truncate(char *buffer, int delimiter, int x) // this function calculate where to start and the len of the return
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

int main(void)
{
	char *result;
	char *buffer = "{\"jsonrpc\":\"2.0\",\"id\":1,\"result\":\"0x7b86def20e8bf6b6d5\"}";
	start_len data = {.start = 0, .len = 0};

	printf("buffer = %s\n", buffer);
	data = truncate(buffer, '"', 9);
	result = ft_strsub(buffer, data.start, data.len);
	printf("data.start = %d, data.len = %d\n", data.start, data.len); // debug
	printf("result = %s\n", result);

	return (0);
}

#include "cub3D.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		str_len;
	char		*ptr;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	**memerror(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static size_t	get_word_len(char const *s, char c, size_t *start)
{
	size_t	word_len;

	word_len = 0;
	while (s[*start] == c)
		(*start)++;
	while (s[*start + word_len] && s[*start + word_len] != c)
		word_len++;
	return (word_len);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	size_t	start;
	size_t	num_words;
	size_t	word_len;
	char	**result;

	if (!s)
		return (NULL);
	start = 0;
	j = 0;
	num_words = count_words(s, c);
	result = malloc(sizeof(char *) * (num_words + 1));
	if (!result)
		return (NULL);
	while (j < num_words)
	{
		word_len = get_word_len(s, c, &start);
		result[j] = ft_substr(s, start, word_len);
		if (!result[j])
			return (memerror(result));
		j++;
		start += word_len;
	}
	result[j] = NULL;
	return (result);
}
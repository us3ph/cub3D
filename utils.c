#include "cub3D.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char *ft_strncpy(char *dest, const char *src, int n)
{
	int i;

	i = 0;

	while(i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n) 
    {
        dest[i] = '\0';
        i++;
    }
	return(dest);
}
#include "get_next_line.h"

size_t ft_strlen(const char *str){
    int i = 0;
    while (str && str[i])
        i++;
    return (i);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    void *rec;
    void *rec1;

    if (!dest && !src)
        return (0);
    rec = (char *)dest;
    rec1 = (char *)src;
    while (n--)
        *(char *)rec++ = *(char *)rec1++;
    return (dest);
}

size_t ft_strlcpy(char *dst, char const *src, size_t size) 
{
    size_t len = ft_strlen((char *)src);
    if (size == 0) 
        return len;

    if (len >= size) 
    {
        ft_memcpy(dst, src, size - 1);
        dst[size - 1] = '\0';
    } else {
        ft_memcpy(dst, src, len + 1);
    }

    return (len);
}

char *ft_strdup(const char *s) {
    size_t len = ft_strlen(s) + 1;
    char *dup = malloc(len);

    if (dup != NULL) {
        ft_memcpy(dup, s, len);
    }
	free((char*)s);
	s = NULL;
    return dup;
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*res;

	res = malloc(elementSize * elementCount);
	if (!res)
		return (NULL);
	ft_bzero(res, elementSize * elementCount);
	return (res);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	free((char *)s);
	s = NULL;
	return (str);
}

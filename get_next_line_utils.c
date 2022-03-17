
#include <stddef.h>
#include <stdlib.h>

char	*my_strcat(char *str, char *s1, char *s2)
{
	int		i;

	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*my_substr(char *dest, char *str, int start, int end)
{
	int		i;

	i = 0;
	while (start < end)
		dest[i++] = str[start++];
	dest[i] = '\0';
	return (dest);
}

int	my_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str++)
		i++;
	return (i);
}

char	*my_realloc(char *str, int size)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = malloc(sizeof(char) * size + 1);
	ptr[0] = 0;
	ptr = my_strcat(ptr, ptr, str);
	if (str)
		free(str);
	return (ptr);
}
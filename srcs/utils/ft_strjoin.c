#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	free(s1);
	str[s1_len + s2_len] = '\0';
	return (str);
}
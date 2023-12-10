#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (0);
	while (str1[count] == str2[count] && str1[count] != '\0' && count < (n - 1))
		count++;
	return ((unsigned char)str1[count] - (unsigned char)str2[count]);
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*c_s;
	size_t	count1;
	size_t	count2;

	count1 = 0;
	count2 = 0;
	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	c_s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!c_s)
		return (NULL);
	while (s[count1] && count2 < len)
	{
		if (count1 >= start)
		{
			c_s[count2] = s[count1];
			count2++;
		}
		count1++;
	}
	c_s[count2] = 0;
	return (c_s);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		count;
	char		*dst_dst;
	const char	*src_src;

	count = 0;
	dst_dst = (char *)dst;
	src_src = (const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (count < n)
	{
		dst_dst[count] = src_src[count];
		count++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	char	*s2;

	s_len = ft_strlen(s1) + 1;
	s2 = malloc(s_len);
	if (s2 == NULL)
		return (NULL);
	return ((char *)ft_memcpy(s2, s1, s_len));
}

static int	ft_number_of_words(char const *str, char c)
{
	int	iter;
	int	count;

	iter = 0;
	count = 0;
	while (str[iter] != '\0')
	{
		if (str[iter] != c)
		{
			count++;
			while (str[iter] && str[iter] != c)
				iter++;
			if (str[iter] == '\0')
				return (count);
		}
		iter++;
	}
	return (count);
}

static void	free_all(char **word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		free(word[i]);
		i++;
	}
	free(word);
}

static int	ft_split_loop(char const *str, char c, char **word)
{
	int	iter;
	int	len;

	iter = 0;
	while (*str)
	{
		if (*str != c)
		{
			len = 0;
			while (*str && *str != c && ++len)
				++str;
			word[iter] = ft_substr(str - len, 0, len);
			if (!word[iter])
			{
				free_all(word);
				return (0);
			}
			++iter;
			if (*str == '\0')
				break ;
		}
		++str;
	}
	word[iter] = 0;
	return (1);
}

char	**ft_split(char const *str, char c)
{
	char	**word;
	int		res;

	word = (char **) malloc(sizeof(char *) * (ft_number_of_words(str, c) + 1));
	if (word == NULL)
		return (0);
	res = ft_split_loop(str, c, word);
	if (res == 0)
		return (NULL);
	return (word);
}


// char	*heredoc(char *str)
// {
// 	int i, j;
// 	char *doc, *curr;
// 	int doc_size, curr_size;
// 	if (ft_strlen(str) >= 2)
// 	{
// 		i = 0;
// 		if (str[i] == '<' && str[i + 1] == '<')
// 		{
// 			i = 2;
// 			if (str[i] == ' ')
// 				i++;
// 			if (str[i] == '\n')
// 				error_exit("syntax error near unexpected token `newline'");
// 			else
// 				i++;
// 			j = 0;
// 			if (str[i])
// 			{
// 				doc_size = 1024;
// 				doc = (char *)malloc(doc_size);
// 				if (!doc)
// 					error_exit("Memory allocation error");
// 				while (str[i] && str[i] != '\n')
// 				{
// 					if (j >= doc_size - 1)
// 					{
// 						doc_size *= 2;
// 						doc = (char *)realloc(doc, doc_size);
// 						if (!doc)
// 							error_exit("Memory reallocation error");
// 					}
// 					doc[j++] = str[i++];
// 				}
// 				doc[j] = '\0';
// 				printf(">\n");
// 				i++;
// 				curr_size = 1024;
// 				curr = (char *)malloc(curr_size);
// 				if (!curr)
// 				{
// 					free(doc);
// 					error_exit("Memory allocation error");
// 				}
// 				while (ft_strncmp(doc, curr, ft_strlen(curr)) != 0)
// 				{
// 					j = 0;
// 					while (str[i] && str[i] != '\n')
// 					{
// 						if (j >= curr_size - 1)
// 						{
// 							curr_size *= 2;
// 							curr = (char *)realloc(curr, curr_size);
// 							if (!curr)
// 								error_exit("Memory reallocation error");
// 						}
// 						curr[j++] = str[i++];
// 					}
// 					curr[j] = '\0';
// 				}
// 				free(doc);
// 				free(curr);
// 			}
// 		}
// 	}
// 	return (NULL);
// }

// int	main(void)
// {
// 	char	*result;

// 	char input[] = "<< EOF\nline 1\nline 2\nline 3\nEOF";
// 	result = heredoc(input);
// 	if (result != NULL)
// 	{
// 		printf("Heredoc content:\n%s\n", result);
// 	}
// 	else
// 	{
// 		printf("Heredoc parsing failed.\n");
// 	}
// 	return (0);
// }


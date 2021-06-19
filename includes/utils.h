/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunlee <hyunlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:03:21 by hyunlee           #+#    #+#             */
/*   Updated: 2021/05/16 18:03:22 by hyunlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

int		ft_atoi(const char *nptr);
int		ft_strlen(const char *s);
char	*ft_str_char_del(char *before, int index);
char	*ft_str_char_embed(char *before, char c, int index);
char	*ft_str_char_join(char *before, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
int		ft_print_err(char *s1, char *s2, char *s3, int code);
int		ft_print_synerr(char c, int rd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2, int to_free);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy_i_to_j(char *line, int i, int j);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);

#endif

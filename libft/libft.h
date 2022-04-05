#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

size_t	ft_strlen(const char *s);
size_t	ft_strslen(char **strs);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strtrimchr(const char *str, char c);
char	*ft_strupdate(char *s1, const char *s2);
int		ft_atoi(const char *str);
int		ft_htoi(char *str);
void	ft_freeints(int **ints, int length);
void	ft_freestrs(char **strs);
char	*ft_itoa(int n);

#endif

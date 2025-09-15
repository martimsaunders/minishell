#include "execution.h"

int	hd_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (s1[i] == '\n' && i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void create_here_doc(char *delimiter) //adicionar expancao e sinal ctrl
{
	size_t limit;
	char *line;
	
	if (pipe(pc()->fd.previous) < 0)
		total_exit("pipe() error!");
	limit = ft_strlen(delimiter);
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		total_exit("mallo() error!");
	while (hd_strncmp(line, delimiter, limit))
	{
		ft_putstr_fd(line, pc()->fd.previous[1]);
		free(line);
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			total_exit("mallo() error!");
	}
	free(line);
	ft_close(&pc()->fd.previous[1]);
}
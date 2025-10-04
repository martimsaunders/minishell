#include "../../minishell.h"

char *find_expansion(char *str, int size)
{
	t_env *node;

	node = pc()->ms_env;
	while (node)
	{
		if (!ft_strncmp(node->name, str, size) && node->name[size] == '\0')
			break ;
		node = node->next;
	}
	if (!node)
		return (NULL);
	return (node->value);
}

int digits_manage(char *str, int n)
{
	int i;
    int num;

    num = n;
	i = 1;
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	if (str)
    {
        str += (i - 1);
        while (num > 9)
        {
            *str-- = (num % 10) + 48;
            num = num / 10;
        }
		*str = (num % 10) + 48;
    }
	return (i);
}

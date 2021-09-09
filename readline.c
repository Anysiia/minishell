#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

# define NRM	"\x1B[0m"
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define BLD	"\x1B[1m"
# define SHELL_NAME "[minishell] "

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_freestr(char **string)
{
	if (string && *string)
	{
		free(*string);
		*string = NULL;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (dstsize == 0)
		return (len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = 0;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[i] && i < dstsize)
		i++;
	j = i;
	while (src[i - j] && i < dstsize - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	if (j < dstsize)
		dst[i] = '\0';
	return (j + ft_strlen(src));
}

char	*readline_prompt(char *prompt, char *path)
{
	ft_strlcpy(prompt, MAG, 1024);
	ft_strlcat(prompt, BLD, 1024);
	ft_strlcat(prompt, SHELL_NAME, 1024);
	if (path)
	{
		ft_strlcat(prompt, CYN, 1024);
		ft_strlcat(prompt, path, 1024);
		ft_strlcat(prompt, NRM, 1024);
		ft_strlcat(prompt, " > ", 1024);
	}
	else
	{
		ft_strlcat(prompt, NRM, 1024);
		ft_strlcat(prompt, "> ", 1024);
	}
	return (prompt);
}

int main(int ac, char **av)
{
    // Configure readline to auto-complete paths when the tab key is hit.
	char	prompt[1024];

    while (1) {
        // Display prompt and read input
        char* input = readline(readline_prompt(prompt, av[1]));

        // Check for EOF.
        if (!input)
            break;

        // Add input to readline history.
        add_history(input);

        // Do stuff...

        // Free buffer that was allocated by readline
        free(input);
    }
    return 0;
}

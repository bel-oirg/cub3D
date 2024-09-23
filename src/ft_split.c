#include "../inc/cub.h"

int word_count(char *line)
{
	int count;
	int i;
	int is_space;

	i = 0;
	count = 0;
	is_space = 1;
	while(line && line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '\t' || line[i] == ' ')
			is_space = 1;
		else if (is_space == 1 && (line[i] != '\n' || line[i] != '\0'))
		{
			count++;
			is_space = 0;
		}
		i++;
	}
	return (count);	
}

void alloc_cpy(char **res,char *line,int words,int idx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(line[i] != '\0' && line[i] != '\n' && idx < words)
	{
		while(line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		j = i;
		while(line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			i++;
		if (i > j)
		{
			res[idx] = malloc(sizeof(char) * (i - j) + 1);
			if (!res[idx])
				return;
			ft_strlcpy(res[idx],line + j,i - j);
			idx++;
		}
	}
}

char **ft_split(char *line)
{
	char **res;
	int words;
	
	if (!line)
		return (NULL);
	words = word_count(line);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	if (res > 0)
		alloc_cpy(res,line,words,0);
	res[words] = NULL;
	return (res); 
}
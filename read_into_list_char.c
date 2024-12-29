//HEADER

#include "push_swap.h"

char    **check_whitespace(char *str)//go through arg and search for space to indicate multiple nrs
{
    char    **ptr;

    ptr = NULL;
    if (ft_strchr(str, ' ') != NULL) //=whitespace within str
    {
        ptr = ft_split(str, ' '); //MALLOC
        return (ptr);
    }
    return NULL;
}


void	add_to_list(t_list **list, char *ptr)
{
	t_list	*node;

	//ceate new node
	node = ft_lstnew(ptr); //MALLOC
	//append to list
	ft_lstadd_back(list, node);

	//return (list);
}

void	create_str_to_list(t_list **list, char *argv)
{
	int	len;
	char *str;

	//ft_printf("arg: %s\n",argv[i]);
	len = 0;
	while (argv[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	//if (!str)
		//free all ; //TO DO 
	
	ft_memcpy(str, argv, (sizeof(char) * (len + 1)));
	str[len + 1] = '\0';
	//ft_printf("str: %s\n", str);

	add_to_list(list, str);

}


t_list	*read_into_list(int argc, char *argv[])
{
	ft_printf("in read list\n");
	t_list	*list;
	char	**ptr;
	int		i;

	ptr = NULL;
	list = NULL;
	//go thru args and create list of chars
		//for each:
			//check if whitespace: if yes split and append whole thing to list , if no just append to list
	i = 1;
	while (i < argc)
	{
		ptr = check_whitespace(argv[i]); //returns split array if space is found
		if (ptr)
		{
			ft_printf("single str\n");
			while (*ptr)
			{
				//ft_printf("in loop\n");

				add_to_list(&list, *ptr); //MALLOC
				ptr++;
			}
		}
		else
		{
			ft_printf("normal arg\n");
			create_str_to_list(&list, argv[i]); //MALLOC
		}
		i++;
	}
	return (list);
}

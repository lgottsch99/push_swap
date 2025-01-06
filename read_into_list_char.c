/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_into_list_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:22:27 by lgottsch          #+#    #+#             */
/*   Updated: 2025/01/06 17:27:42 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char    **check_whitespace(char *str, t_list *lst)//go through arg and search for space to indicate multiple nrs
{
    char    **ptr;

    ptr = NULL;
    if (ft_strchr(str, ' ') != NULL) //=whitespace within str
    {
        ptr = ft_split(str, ' '); //MALLOC OK
		if (!ptr)
		{
			free_list(lst);
			exit(1);
		}
        return (ptr);
    }
    return NULL;
}


void	add_to_list(t_list **list, char *ptr)
{
	t_list	*node;

	node = NULL;
	//ceate new node
	node = ft_lstnew(ptr); //MALLOC OK
	if (!node)
	{
		free_list(*list);
		exit (1);
	}
	//append to list
	ft_lstadd_back(list, node);
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
	if (!str)
	{
		free_list(*list);
		exit (1);
	}
	
	ft_memcpy(str, argv, (sizeof(char) * (len + 1)));
	str[len + 1] = '\0';
	//ft_printf("str: %s\n", str);

	add_to_list(list, str);

}


t_list	*read_into_list(int argc, char *argv[])
{
	//ft_printf("in read list\n");
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
		ptr = check_whitespace(argv[i], list); //returns split array if space is found
		if (ptr)
		{
			//ft_printf("single str\n");
			while (*ptr)
			{
				//ft_printf("in loop\n");
				add_to_list(&list, *ptr); //MALLOC
				ptr++;
			}
		}
		else
		{
			//ft_printf("normal arg\n");
			create_str_to_list(&list, argv[i]); //MALLOC
		}
		i++;
	}
	return (list);
}

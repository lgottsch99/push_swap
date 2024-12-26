#include "push_swap.h"


void print_list(t_list *list)
{
	while(list)
	{
		ft_printf("char list content: %s\n", (char*)list->content);
		list = list->next;
	}
}

void print_int_list(t_list *list)
{
	while(list)
	{
		ft_printf("int list content: %i\n", *(int*)list->content);
		list = list->next;
	}
}

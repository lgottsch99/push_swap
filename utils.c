#include "push_swap.h"


void print_list(t_list *list)
{
	while(list)
	{
		ft_printf("char list content: %s\n", (char*)list->content);
		list = list->next;
	}
}

void print_int_list(t_list *list, char s)
{
	int i;

	while(list)
	{
		i = *(int*)list->content;
		ft_printf("int list %c", s);
		ft_printf(": %i\n", i);

		list = list->next;
	}
}

void	print_both(t_stack *stacks)
{
	t_list	*a;
	t_list	*b;
	int		i;
	int		y;

	a = stacks->a;
	b = stacks->b;
	while (a || b)
	{
		i = 0;
		y = 0;
		if (a)
		{
			i = *(int*)a->content;
			ft_printf("stack a: %i", i);
			a = a->next;
		}
		else
			ft_printf("          ", i);
		ft_printf("|	");
		if (b)
		{
			y = *(int*)b->content;
			ft_printf("stack b: %i\n", y);
			b = b->next;
		}
		else
			ft_printf("\n");
	}
	ft_printf("\n");
}
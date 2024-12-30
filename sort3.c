//HEADER

#include "push_swap.h"

int	get_position(t_list *list, t_list *node)
{
	int	i;

	i = 1;
	while (list && *(int *)list->content != *(int *)node->content)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_stack	*sort_3(t_stack *stacks) //list is def 3 in size, atm only stack a 
{
	ft_printf("in sort 3\n");
	//get min + max value and position
	//decide how to swap (max 2 op. in only two cases)

	t_list	*min;
	t_list	*max;
	t_list	*list;
	int		minpos;
	int		maxpos;

	list = stacks->a;
	min = get_min(list);
		// ft_printf("min is: %i\n", *(int *)min->content);
	minpos = get_position(list, min);
		// ft_printf("pos min is: %i\n",minpos);

	max = get_max(list);
	maxpos = get_position(list, max);
		// ft_printf("max is: %i\n", *(int *)max->content);
		// ft_printf("pos max is: %i\n",maxpos);

	if (minpos == 1) //no need to check max, bc if max = 3 dann already sorted
	{
			stacks = rra(stacks);
			stacks = sa(stacks);
	}
	if (minpos == 2)
	{
		if (maxpos == 1)
			stacks = ra(stacks);
		if (maxpos == 3)
			stacks = sa(stacks);
	}
	if (minpos == 3)
	{
		if (maxpos == 1)
		{
			stacks = ra(stacks);
			stacks = ra(stacks);
		}
		if (maxpos == 2)
			stacks = rra(stacks);
	}
	return (stacks);
}



//HEADER

#include "push_swap.h"

/*
rra (reverse rotate a): Shift down all elements of stack a by 1.
The last element becomes the first one.
rrb (reverse rotate b): Shift down all elements of stack b by 1. The last element becomes the first one.
rrr : rra and rrb at the same time.
*/



t_stack	*real_rra(t_stack *stacks) //Shift down all elements of stack a by 1.
{
	t_list	*last;
	int		lstsize;
	int		i;
	t_list	*newlast;
	//get size, if 0 or 1 do nothing
	lstsize = ft_lstsize(stacks->a);
	if (lstsize <= 1)
		return (stacks);
	//get last elem and save, make it first in list
	last = ft_lstlast(stacks->a);
	last->next = stacks->a;
	stacks->a = last;//set a to new first elem in list
	//go to one before last elem and set next to NULL
	i = 0;
	newlast = stacks->a;
	while (i < lstsize - 1)
	{
		newlast = newlast->next;
		i++;
	}
	//ft_printf("new last: %i\n", *(int*)newlast->content);
	newlast->next = NULL;
	return (stacks);
}

t_stack	*rra(t_stack *stacks) //Shift down all elements of stack a by 1.
{
	ft_printf("rra\n");
	stacks = real_rra(stacks);
	return (stacks);
}

t_stack	*real_rrb(t_stack *stacks)
{
	t_list	*last;
	int		lstsize;
	int		i;
	t_list	*newlast;
	//get size, if 0 or 1 do nothing
	lstsize = ft_lstsize(stacks->b);
	if (lstsize <= 1)
		return (stacks);
	//get last elem and save, make it first in list
	last = ft_lstlast(stacks->b);
	last->next = stacks->b;
	stacks->b = last;//set a to new first elem in list
	//go to one before last elem and set next to NULL
	i = 0;
	newlast = stacks->b;
	while (i < lstsize - 1)
	{
		newlast = newlast->next;
		i++;
	}
	//ft_printf("new last: %i\n", *(int*)newlast->content);
	newlast->next = NULL;
	return (stacks);

}

t_stack	*rrb(t_stack *stacks) //Shift down all elements of stack b by 1.
{
	ft_printf("rrb\n");
	stacks = real_rrb(stacks);
	return (stacks);
}

t_stack	*rrr(t_stack *stacks)
{
	ft_printf("rrr\n");
    stacks = real_rra(stacks);
    stacks = real_rrb(stacks);
	return (stacks);
}
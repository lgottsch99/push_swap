//HEADER

#include "push_swap.h"

/*
ra (rotate a): Shift up all elements of stack a by 1.
The first element becomes the last one.
rb (rotate b): Shift up all elements of stack b by 1. The first element becomes the last one.
rr : ra and rb at the same time.


*/

t_stack *ra(t_stack *stacks)//Shift up all elements of stack a by 1. The first element becomes the last one.
{
	int	size;
	t_list	*first;
	//get size if 0 or 1 do nothing
	size = ft_lstsize(stacks->a);
	if (size <= 1)
		return (stacks);

	//save first and diconnect from rest
	first = stacks->a;
	stacks->a = first->next; //2nd becomes new first
	first->next = NULL;

	//go to last and append first
	ft_lstadd_back(&stacks->a, first);
	
	ft_printf("ra\n");
	return (stacks);
}

t_stack *rb(t_stack *stacks)//Shift up all elements of stack a by 1. The first element becomes the last one.
{
	int	size;
	t_list	*first;
	//get size if 0 or 1 do nothing
	size = ft_lstsize(stacks->b);
	if (size <= 1)
		return (stacks);

	//save first and diconnect from rest
	first = stacks->b;
	stacks->b = first->next; //2nd becomes new first
	first->next = NULL;

	//go to last and append first
	ft_lstadd_back(&stacks->b, first);
	ft_printf("rb\n");
	return (stacks);
}

t_stack	*rr(t_stack *stacks)
{
    stacks = ra(stacks);
    stacks = rb(stacks);
	ft_printf("rr\n");
	return (stacks);
}
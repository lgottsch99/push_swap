//HEADER

#include "push_swap.h"

/*
pa (push a): Take the first element at the top of b and put it at the top of a.
Do nothing if b is empty.
pb (push b): Take the first element at the top of a and put it at the top of b.
Do nothing if a is empty.


typedef struct s_stack {
    t_list  *a;
    t_list  *b;
} t_stack;
*/

t_stack	*pa(t_stack *stacks)//Take the first element at the top of b and put it at the top of a.
{
	t_list	*tmp;
	int		len;

	len = ft_lstsize(stacks->b);
	if (len == 0)
		return(stacks);
	//go to 1st elem
	tmp = stacks->b;
	stacks->b = stacks->b->next;

	//disconnect from rest of list
	tmp->next = NULL;
	//add to a
	ft_lstadd_front(&stacks->a, tmp);
	ft_printf("pa\n");
	return(stacks);
}


t_stack	*pb(t_stack *stacks)
{
    //fisrt elem in a , put it to top of b
	t_list	*tmp;
	int		len;

	len = ft_lstsize(stacks->a);
	if (len == 0)
		return (stacks);

	tmp = stacks->a;
	stacks->a = stacks->a->next;

	//disconnect from rest of list
	tmp->next = NULL;
	//add to a
	ft_lstadd_front(&stacks->b, tmp);
	ft_printf("pb\n");
	return (stacks);
}
//HEADER

#include "push_swap.h"


int	get_pos_in_a(int nr_b, t_list *a) //TO DO : check if working
{
	//get pos first and decide which way to rot eff. next
	t_list *current;
	t_list *one_before;
	int		pos;

	pos = 1;
	current = a; // start at first
	one_before = ft_lstlast(a); //start at last
	while (!(*(int *)current->content > nr_b && *(int *)one_before->content < nr_b) && pos <= ft_lstsize(a))
	{
		pos++;
		if (!one_before->next)
			one_before = a;
		else	
			one_before = current;
		if (current->next)
			current = current->next;
		else
			break;
	}
	ft_printf("pos for stack b %i in a ", nr_b);
	return (pos);
}

t_stack	*push_back(t_stack *stacks)//push back to a (!a ASCENDING ORDER smallest 1st)
{
			//TO DO

		//for 1st in b:
			//find correct pos in a to push 
			//rotate a so that one bigger is at 1
			//pa
	int	pos_a;

	// while(ft_lstsize(stacks->b) > 0)
	// {
	pos_a = get_pos_in_a(*(int*)stacks->b->content, stacks->a);
	ft_printf("is: %i\n", pos_a);

	// }


	return (stacks);
}
//HEADER

#include "push_swap.h"

/*
1. check if input already sorted

2. sort accoring to size??

typedef struct s_stack {
    t_list  *a;
    t_list  *b;
} t_stack;
*/

int	is_input_sorted(t_stack *stacks) //returns 1 if sorted, 0 if not
{
	int	size;
	int	i;
	t_list	*tmp;
	int	y;

	i = 0;
	y = 0;
	size = ft_lstsize(stacks->a);
	tmp = stacks->a;
	//go thru list
	while (tmp && size > 1 && i < size) //if size 1 or kleiner no need to sort
	{
		//ft_printf("in loop \n");
		i++;
		//check if current position smaller than next
		if (tmp->next)
		{
			if (*(int *)tmp->content < *(int *)tmp->next->content)
			{
						//ft_printf("in if \n");
				y++;
				//if yes go further
				if (tmp->next)
					tmp = tmp->next;
				else
					break;
			}
		}
		else
			break;
	}
	//ft_printf("y is: %i\n", y);
	if (y == size - 1)
		return (1);
	return (0);
}

t_stack	*sort_3(t_stack *stacks)//list is def 3 in size, only a atm
{
	ft_printf("in sort 3\n");

	t_list	*tmp;
	t_list	*last;

	last = ft_lstlast(stacks->a);
	while (is_input_sorted(stacks) == 0)
	{
	tmp = stacks->a;
	if (*(int *)tmp->content > *(int *)tmp->next->content)
	{
		ft_printf("1st > 2nd\n");
		stacks = sa(stacks);
		print_both(stacks);
	}
	if (is_input_sorted(stacks))
		return (stacks);
	tmp = stacks->a;
	if (*(int *)tmp->content > *(int *)last->content)
	{
		ft_printf("1st > 3rd\n");
		stacks = rra(stacks);
		print_both(stacks);
	}
	if (is_input_sorted(stacks))
		return (stacks);
	tmp = stacks->a;
	if (*(int *)tmp->next->content > *(int *)last->content)
	{
		ft_printf("2nd > 3rd\n");
		stacks = rra(stacks);
		print_both(stacks);
	}
	}
	return (stacks);
}

t_stack	*sort_2(t_stack *stacks)//list is def 2 in size
{
	ft_printf("in sort 2\n");
	t_list	*tmp;

	tmp = stacks->a;
	if (*(int *)tmp->content > *(int *)tmp->next->content)
	{
		ft_printf("1st > 2nd\n");
		stacks = sa(stacks);
		print_both(stacks);
	}
	return (stacks);
}

// t_stack *sort_4_for_5(t_stack *stacks) //only in a 
// {
// 	t_list	*tmp;
// 	t_list	*last;

// 	last = ft_lstlast(stacks->a);
// 	tmp = stacks->a;
// 	if (*(int *)tmp->content < *(int *)tmp->next->content)
// 		return (stacks);
// 	if (*(int *)tmp > *(int *)last->content) // easy case
// 		stacks = ra(stacks);
		
// }

t_stack	*sort_5(t_stack *stacks) //in max 12 operations!
{
	ft_printf("in sort 5\n");
	t_list	*tmp;
	t_list	*last;

	//divide into 2 in b and 3 in a
	stacks = pb(stacks);
	stacks = pb(stacks);
	print_both(stacks);
	
	stacks = sort_3(stacks); // sort stack a 
	ft_printf("after sorting a\n");
	print_both(stacks);

	//push back one by one and sort in a (a is def sorted by now!)
	stacks = pa(stacks);
		print_both(stacks);

	//stacks = sort_4_for_5(stacks);

	stacks = sort_one_back(stacks); //TO DO
	//if first < 2nd do nothing
	//if first > last ra /put last
	//else if (first > 2nd) && (first < last) //falls dazwischen
		// sa (swap 1st u 2nd)
		// ra (first becomes last) -> check if new one smaller than next and bigger than one before, if not do again
		// 
		//sort to get smallest up


	
	return (stacks);
}


t_stack	*sort(t_stack *stacks)//TO DO: logik/approach entscheiden
{
	int	size;

	size = ft_lstsize(stacks->a);

	if (is_input_sorted(stacks) == 1)//check if list already sorted
	{
		ft_printf("input is sorted\n");
		return (NULL);
	}
	if (size == 2) // change later
		stacks = sort_2(stacks);
	if (size == 3)
		stacks = sort_3(stacks);
	if (size == 5)
		stacks = sort_5(stacks);

	return (stacks);
}
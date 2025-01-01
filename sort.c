//HEADER

#include "push_swap.h"

/*
1. check if input already sorted

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

t_stack *sort_one_back(t_stack *stacks) //only in a 
{
		ft_printf("in sort one back\n");

	t_list	*tmp;
	t_list	*last;
	int		check;

	last = ft_lstlast(stacks->a);
	ft_printf("last is: %i\n", *(int *)last->content);
	tmp = stacks->a;
	if (*(int *)tmp->content < *(int *)tmp->next->content)
		return (stacks);
	if (*(int *)tmp->content > *(int *)last->content) // easy case
		return (ra(stacks));
		
	check = 1;
	while (is_input_sorted(stacks) == 0 && check == 1) //find right pos.
	{
		check = 0;
		tmp = stacks->a;
		if (*(int *)tmp->content > *(int *)tmp->next->content)
		{
			stacks = sa(stacks);
			check = 1;
		}
		if (is_input_sorted(stacks) == 1)
			return (stacks);
		tmp = stacks->a;
		if ( *(int *)tmp->next->content > *(int *)tmp->next->next->content)
		{
			stacks = ra(stacks);
			check = 1;
		}
		if (is_input_sorted(stacks) == 1)
			return (stacks);
	}
	//rotate back to smallest = first
	while (is_input_sorted(stacks) == 0)
		stacks = rra(stacks);
	return (stacks);
}

t_stack	*sort_5(t_stack *stacks) //in max 12 operations!
{
	ft_printf("in sort 5\n");
	// t_list	*tmp;
	// t_list	*last;

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
	stacks = pa(stacks);
		print_both(stacks);
	stacks = sort_one_back(stacks); //TO DO


	
	return (stacks);
}


t_stack	*sort(t_stack *stacks)//TO DO: logik/approach entscheiden
{
	int	size;

	size = ft_lstsize(stacks->a);

	if (is_input_sorted(stacks) == 1)//check if list already sorted
	{
		ft_printf("input is sorted\n");
		return (stacks);
	}



	if (size == 2) // change later
		stacks = sort_2(stacks);
	else if (size == 3)
		stacks = sort_3(stacks);
	// if (size == 5)
	// 	stacks = sort_5(stacks);
	else
	{
		//push 2 to b
		stacks = pb(stacks);
		stacks = pb(stacks);
		print_both(stacks);
		while (ft_lstsize(stacks->a) > 3)
		{
			stacks = do_bigger_sort(stacks);
			print_both(stacks);
		}
	}

	return (stacks);
}
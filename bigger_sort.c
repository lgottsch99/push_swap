//HEADER

#include "push_swap.h"

t_list	*get_node_at_pos(t_list *list, int pos)
{
	t_list	*node;
	int 	i;

	node = list;
	i = 1;
	while (i != pos)
		node = node->next;
	
	return (node);
}

int	get_pos_in_b(t_list	*node_a, t_list	*b, int max_b)
{
	//b is sorted descending
	//traverse list b and find correct pos for node_a (not min or max)
	int	pos;

	pos = 1;
	//start at max and then go down until *(int *)node_a ???is what
	//TO DO ;
	//how to find correct pos in b for random node


}

int	rotation_b(t_list *node_a, t_list *b)
{
	//check conditions in b: (und size b? bei 2 eig egal)
		//node in a > maxb oder < minb
		//if dazwischen: get position of closest 
	t_list	*min;
	t_list	*max;
	int		maxpos;
	int		pos_in_b;
	int		size_b;
	int		mid;
	int		steps;
	
	//get size of list b, max pos and minpos
	size_b = ft_lstsize(b);
	min = get_min(b);
	max = get_max(b);
	maxpos = get_position(b, max);
	//compare value from a against min max in b
	if (*(int *)node_a->content > *(int *)max->content || *(int *)node_a->content < *(int *)min->content)//new is new max or min
	{		//max in b needs to become pos 1 in b (new needs to be above it after pb)
		//calc steps how to get there

		//LATER: source this into own ft -----
		steps = 0;
		mid = size_b / 2;

		if (maxpos <= mid)//in erster hälfte
		{
			while (maxpos != 1)
			{
				maxpos--;
				steps++;
			}
		}
		else if (maxpos > mid)//zweite hälfte
		{
			while (maxpos <= (size_b + 1))
			{
				maxpos++;
				steps++;
			}
		}
		//-----------
	}
	else//new is inbetween
	{
		//traverse list b and find correct pos for node_a
		pos_in_b = get_pos_in_b(node_a, b, maxpos);
		//calc steps how to get there (rotation only)
	}
		ft_printf("rotation steps b: %i\n", steps);
	return (steps);

}

int	rotation_a(int pos_a, int size_a)//pos_a = node für die calculated 
{	//1. pb nur möglich wenn node pos 1 in a
		//get position in a, decide which way to rotate: ra oder rra
	int	mid;
	int	steps;

	steps = 0;
	mid = size_a / 2;
	ft_printf("mid pos is: %i\n", mid);

	if (pos_a <= mid)//in erster hälfte
	{
		while (pos_a != 1)//until we reached pos
		{
			pos_a--;
			steps++;
		}
	}
	if (pos_a > mid)//2. hälfte
	{
		while (pos_a != (size_a + 1))//rotate up to 1. pos
		{
			pos_a++;
			steps++;
		}
	}
	ft_printf("rotation steps a: %i\n", steps);

	return (steps);

}

t_stack	*do_bigger_sort(t_stack	*stacks)
{
	ft_printf("in bigger sort\n");
	int		pos_a;
	int		steps_needed;
	int		size_a;
	int		cheapest_pos;//keep position of cheapest
	int		cheapest_steps;
	t_list	*node;

	//push 2 to b
	stacks = pb(stacks);
	stacks = pb(stacks);
	print_both(stacks);

	size_a = ft_lstsize(stacks->a);
	
	pos_a = 1;
	//cheapest = pos_a;

	while (pos_a <= size_a)
	{
		steps_needed = 0;
	//go thru whole stack a (until only 3 left) and calc for each number how many steps (in a and b) would be needed to put in right position
		//always: get min and max in b, compare each new number to this
			//if > max oder <min dann pos eindeutig (rotate until true und pb)
			//if dazwischen: get position of closest 
		node = get_node_at_pos(stacks->a, pos_a);
	//1. pb nur möglich wenn node pos 1 in a
		//get position in a, decide which way to rotate: ra oder rra
		steps_needed += rotation_a(pos_a, size_a);
	//2. check conditions in b: (und size b? bei 2 eig egal)
		//node in a > maxb oder < minb
		//if dazwischen: get position of closest 
		steps_needed += rotation_b(node, stacks->b);

	ft_printf("pos: %i\n",pos_a);
	ft_printf("total steps_needed: %i\n", steps_needed);
	if (pos_a == 1)//1st
	{
		cheapest_pos = pos_a;
		cheapest_steps = steps_needed;
	}
	else if (steps_needed < cheapest_steps)
	{
		cheapest_steps = steps_needed;
		cheapest_pos = pos_a;
	}
	pos_a++;
	}
	ft_printf("cheapest pos a: %i\n", cheapest_pos);


	return (stacks);
}
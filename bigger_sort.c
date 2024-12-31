//HEADER

#include "push_swap.h"

t_list	*get_node_at_pos(t_list *list, int pos)
{
	t_list	*node;
	int 	i;

	node = list;
	i = 1;
	while (i != pos && pos <= ft_lstsize(list))
	{
		if (node->next)
			node = node->next;
		else
			break ;
	}
	return (node);
}

int	get_pos_in_b(t_list	*node_a, t_list	*b, t_list	*min)//we know safe dass new < max!
{
	//einfach von anfang bis ende durchgehen!
	int	pos;
	t_list	*tmp;
	t_list	*next;

	pos = 0;
	tmp = min; //start at min
	if (tmp->next)
		next = tmp->next;
	else
		next = b; //falls am ende start am anfang

	//go to minpos, then go further until next is > than new
	while (pos == 0)//only change pos if found
	{
		//compare tmp + next to new
		if ((*(int *)tmp->content < *(int *)node_a->content) && (*(int *)next->content > *(int *)node_a->content))
			pos = get_position(b, tmp);
		else
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				tmp = b;
			if (next->next)
				next = next->next;
			else
				next = b;
		}
	}
	ft_printf("pos für new in b: %i\n", pos);
	return (pos);
}

int calc_steps(t_list *lst, int pos) //pos needs to be 1 to push correctly
{
	int	steps;
	int	mid;
	int size;

	size = ft_lstsize(lst) / 2;
	mid = size / 2;
	steps = 0;

	if (pos <= mid)//in erster hälfte
	{
		while (pos != 1)
		{
			pos--;
			steps++;
		}
	}
	else if (pos > mid)//zweite hälfte
	{
		while (pos <= (size + 1))
		{
			pos++;
			steps++;
		}
	}
	return (steps);
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
	steps = 0;

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
		pos_in_b = get_pos_in_b(node_a, b, min);
		//calc steps how to get there (rotation only)
		steps += calc_steps(b, pos_in_b);
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

	//TO DO: some structure to keep track of results??
	while (pos_a <= size_a)
	{
		ft_printf("\nchecking stack a pos: %i\n", pos_a);

		steps_needed = 0;
	//go thru whole stack a (until only 3 left) and calc for each number how many steps (in a and b) would be needed to put in right position
		//always: get min and max in b, compare each new number to this
			//if > max oder <min dann pos eindeutig (rotate until true und pb)
			//if dazwischen: get position of closest 
		node = get_node_at_pos(stacks->a, pos_a);
		ft_printf("got node at pos\n");

	//1. pb nur möglich wenn node pos 1 in a
		//get position in a, decide which way to rotate: ra oder rra
		steps_needed += rotation_a(pos_a, size_a);
				ft_printf("got rot a\n");

	//2. check conditions in b: (und size b? bei 2 eig egal)
		//node in a > maxb oder < minb
		//if dazwischen: get position of closest 
		steps_needed += rotation_b(node, stacks->b);
						ft_printf("got rot b\n");

	//TO DO: rotation check: if same direction check if ss rrr etc possible!

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
	ft_printf("\ncheapest pos in a: %i\n", cheapest_pos);


	return (stacks);
}
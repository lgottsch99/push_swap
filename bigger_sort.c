//HEADER

#include "push_swap.h"

typedef struct s_info { //splitten in eins für info und eins für cheapest!
	int	size_a;
	int size_b;
	int rot_a; //indicating rotation direction: 1 is up ra, 0 is down rra
	int rot_b; //indicating rotation direction: 1 is up ra, 0 is down rra 
	int steps_a; //keeping amount of steps for each pos
	int steps_b;
	int rr; //amount steps for rr
	int rrr;
	int total_steps;
	int pos_a;
	// int cheapest_pos_a;
	// int cheapest_steps_a;
	// int cheapest_rot_a; //to safe direction for execution
	// int cheapest_rot_b;


} t_info;


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
	//if pos is letzte in list, steps = o weil einfach pb nach oben ok
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

int calc_steps(t_list *lst, int pos, int *rot) //pos needs to be 1 to push correctly
{
	ft_printf("in normal calc steps\n");
	int	steps;
	int	mid;
	int size;

	size = ft_lstsize(lst);
	if (size <= 3)
		mid = 1;
	else
		mid = size / 2;

	steps = 0;

	if (pos <= mid)//in erster hälfte
	{
		*rot = 1; //ra
		while (pos != 1)
		{
			pos--;
			steps++;
		}
	}
	else if (pos > mid)//zweite hälfte
	{
		*rot = 0; //rra
		while (pos <= (size + 1))
		{
			pos++;
			steps++;
		}
	}
	return (steps);
}

//try without first
int calc_steps_last(t_list *lst, int pos, int *rot) //pos needs to be LAST, whichever rot closer
{
	ft_printf("in calc steps to last\n");

	int	steps;
	int	mid;
	int size;

	size = ft_lstsize(lst);
	if (size <= 3)
		mid = 1;
	else
		mid = size / 2;
	steps = 0;
	ft_printf("mid b in calc steps to last: %i\n", mid);

	if (pos <= mid)//in erster hälfte
	{
		*rot = 1; //ra
		while (pos != 0)
		{
			pos--;
			steps++;
		}
	}
	else if (pos > mid)//zweite hälfte
	{
		*rot = 0; //rra
		while (pos < size)
		{
			pos++;
			steps++;
		}
	}
		ft_printf("steps b to last: %i\n", steps);

	return (steps);
}


int	rotation_b(t_list *node_a, t_list *b, t_info *info)
{
	//check conditions in b: (und size b? bei 2 eig egal)
		//node in a > maxb oder < minb
		//if dazwischen: get position of closest 
	t_list	*min;
	t_list	*max;
	int		maxpos;
	int		pos_in_b;
	//int		size_b;
	//int		mid;
	//int		steps;
	
	//get size of list b, max pos and minpos
	info->steps_b = 0;

	info->size_b = ft_lstsize(b);
	min = get_min(b);
	max = get_max(b);
	maxpos = get_position(b, max);
	//compare value from a against min max in b
	if (*(int *)node_a->content > *(int *)max->content || *(int *)node_a->content < *(int *)min->content)//new is new max or min
	{		//max in b needs to become pos LAST in b ^
		ft_printf("nr would be new min /Max\n");
		//calc steps how to get there
				ft_printf("max pos b is: %i\n", maxpos);

		info->steps_b = calc_steps_last(b, maxpos, &info->rot_b);
	}
	else//new is inbetween
	{
				ft_printf("nr would be in between\n");

		//traverse list b and find correct pos for node_a
		pos_in_b = get_pos_in_b(node_a, b, min); //node at posinb is smaller than new
		//calc steps how to get there (rotation only)s
		info->steps_b = calc_steps(b, pos_in_b, &info->rot_b);
		
	}
	ft_printf("rotation steps b: %i\n", info->steps_b);
	ft_printf("direction rot_b: %i\n", info->rot_b);

	return (info->steps_b);

}

int	rotation_a(int pos_a, int size_a, t_info *info)//pos_a = node für die calculated 
{	//1. pb nur möglich wenn node pos 1 in a
		//get position in a, decide which way to rotate: ra oder rra
	int	mid;
	int	steps;
		
		//--------zsmfassen mit calc steps
	steps = 0;
	mid = size_a / 2;
	ft_printf("mid pos is: %i\n", mid);


	if (pos_a <= mid)//in erster hälfte
	{
		info->rot_a = 1; //ra
		while (pos_a != 1)//until we reached pos
		{
			pos_a--;
			steps++;
		}
	}
	if (pos_a > mid)//2. hälfte
	{
		info->rot_a = 0; //rra

		while (pos_a != (size_a + 1))//rotate up to 1. pos
		{
			pos_a++;
			steps++;
		}
	}
	//---------------
	info->steps_a = steps;
	ft_printf("rotation steps a: %i\n", steps);
	ft_printf("direction rot_a: %i\n", info->rot_a);

	return (steps);
}

void init_info(t_info *info)
{
	info->size_a = 0;
	info->size_b = 0;
	info->rot_a = -1;
	info->rot_b = -1;
	info->steps_a = 0;
	info->steps_b = 0;
	info->rr = 0;
	info->rrr = 0;
	info->total_steps = 0;
	info->pos_a = 0;
	// info->cheapest_pos_a = 0;
	// info->cheapest_steps_a = 0;
	// info->cheapest_rot_a = -1;
	// info->cheapest_rot_b = -1;

}

void	do_push(t_stack *stacks, t_info *cheapest)
{
	ft_printf("in do push\n");
	//read info from cheapest and exec
	//rr or rrr first
	if (cheapest->rr > 0 || cheapest->rrr > 0)
	{
		while (cheapest->rr != 0)
		{
			stacks = rr(stacks);
			cheapest->rr--;
		}
		while (cheapest->rrr != 0)
		{
			stacks = rrr(stacks);
			cheapest->rrr--;
		}
	}
	//dann leftover steps a/b
	while (cheapest->steps_a > 0)
	{
		if (cheapest->rot_a == 1)
			stacks = ra(stacks);
		else if (cheapest->rot_a == 0)
			stacks = rra(stacks);
		cheapest->steps_a--;
	}
	while (cheapest->steps_b > 0)
	{
		if (cheapest->rot_b == 1)
			stacks = rb(stacks);
		else if (cheapest->rot_b == 0)
			stacks = rrb(stacks);
		cheapest->steps_b--;
	}
	//dann pb
	stacks = pb(stacks);

}

t_stack	*do_bigger_sort(t_stack	*stacks)
{
	ft_printf("in bigger sort\n");
	int		pos_a;
	int		steps_needed;
	//int		size_a;
	//int		cheapest_pos;//keep position of cheapest
	//int		cheapest_steps;
	t_list	*node;
	t_info	info;
	t_info	cheapest;

	init_info(&info);
	init_info (&cheapest);


	info.size_a = ft_lstsize(stacks->a);
	pos_a = 1;
	//cheapest = pos_a;

	//TO DO: some structure to keep track of results?? = 2 structs
	while (pos_a <= info.size_a) //calculating cheapest to push
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
		steps_needed += rotation_a(pos_a, info.size_a, &info);
				ft_printf("got rot a\n");

		steps_needed++; // pb
	//2. check conditions in b: (und size b? bei 2 eig egal)
		//node in a > maxb oder < minb
		//if dazwischen: get position of closest 
		steps_needed += rotation_b(node, stacks->b, &info);
						ft_printf("got rot b\n");

	// rotation check: if same direction check if ss rrr etc possible!
		//rr both up
		///rrr both down
		if((info.rot_a == info.rot_b) && ((info.steps_a > 0) && (info.steps_b > 0)))//rot direction is the same and we have rot steps in both
		{
			//decrease overall steps
			if (info.rot_a == 1) //ra
			{
				while (info.steps_a > 0 && info.steps_b > 0)
				{
					info.rr++;
					info.steps_a--;
					info.steps_b--;
				}
			}
			if (info.rot_a == 0) //rra
			{
				while (info.steps_a > 0 && info.steps_b > 0)
				{
					info.rrr++;
					info.steps_a--;
					info.steps_b--;
				}
			}
		}
		info.total_steps = 1 + info.steps_a + info.steps_b + info.rr + info.rrr; //1 für pb

		ft_printf("pos: %i\n",pos_a);
		ft_printf("steps needed before rot check: %i\n", steps_needed);
		ft_printf("total steps_needed after rot check: %i\n", info.total_steps );
		if (pos_a == 1 || info.total_steps < cheapest.total_steps)//1st
		{
			cheapest.pos_a = pos_a;
			cheapest.rot_a = info.rot_a;
			cheapest.rot_b = info.rot_b;
			cheapest.steps_a = info.steps_a;
			cheapest.steps_b = info.steps_b;
			cheapest.rr = info.rr;
			cheapest.rrr = info.rrr;
			cheapest.total_steps = info.total_steps;
		}
		// else if (info.total_steps < cheapest.total_steps)
		// {
		// 	info.cheapest_steps_a = steps_needed;
		// 	info.cheapest_pos_a = pos_a;
		// }
		pos_a++;

	}
	ft_printf("\ncheapest pos in a: %i\n", cheapest.pos_a);
print_both(stacks);
	//TO DO: execution of push, recursion to do until size_a == 3??
	do_push(stacks, &cheapest);
	
	return (stacks);
}
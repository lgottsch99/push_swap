/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigger_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:26:11 by lgottsch          #+#    #+#             */
/*   Updated: 2025/01/06 15:28:30 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// typedef struct s_info { //splitten in eins für info und eins für cheapest!
// 	int	size_a;
// 	int size_b;
// 	int rot_a; //indicating rotation direction: 1 is up ra, 0 is down rra
// 	int rot_b; //indicating rotation direction: 1 is up ra, 0 is down rra 
// 	int steps_a; //keeping amount of steps for each pos
// 	int steps_b;
// 	int rr; //amount steps for rr
// 	int rrr;
// 	int total_steps;
// 	int pos_a;
// 	// int cheapest_pos_a;
// 	// int cheapest_steps_a;
// 	// int cheapest_rot_a; //to safe direction for execution
// 	// int cheapest_rot_b;

// } t_info;

t_list	*get_node_at_pos(t_list *list, int pos)
{
	t_list	*node;
	int 	i;

	node = list;
	i = 1;
	while (i != pos)// && pos <= ft_lstsize(list))
	{
		//if (node->next)
			node = node->next;
		//else
			//break ;
		i++;
	}
	return (node);
}

int	get_pos_in_b(t_list	*node_a, t_list	*b, t_list	*max)//we know safe dass new < max!
{
	// LOGIK = DESCENDING ORDER!!!

	//einfach von anfang bis ende durchgehen!
	int	pos;
	t_list	*tmp;
	t_list	*next;

	pos = 0;
	tmp = max; //start at max
	if (tmp->next)
		next = tmp->next;
	else
		next = b; //falls am ende start am anfang

	//go to maxpos, then go further until next is < than new
	while (pos == 0)//only change pos if found
	{
		//compare tmp + next to new
		if ((*(int *)tmp->content > *(int *)node_a->content) && (*(int *)next->content < *(int *)node_a->content))
			pos = get_position(b, next);
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
//ft_printf("pos smaller für new in b: %i\n", pos);
	return (pos);
}

int calc_steps(t_list *lst, int pos, int *rot) //pos needs to be 1 to push correctly
{
	//ft_printf("in normal calc steps\n");
	int	steps;
	int	mid;
	int size;

	size = ft_lstsize(lst);
	if (size <= 3)
		mid = 1;
	else
		mid = get_mid_pos(lst);

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
		while (pos != (size + 1))
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
	//ft_printf("in calc steps to last\n");

	int	steps;
	int	mid;
	int size;

	size = ft_lstsize(lst);
	if (size <= 3)
		mid = 1;
	else
		mid = get_mid_pos(lst);
	steps = 0;
	//ft_printf("mid b in calc steps to last: %i\n", mid);

	if (pos < mid)//in erster hälfte
	{
		*rot = 1; //ra
		while (pos > 0) //0 bc we wantto get last pos
		{
			pos--;
			steps++;
		}
	}
	else if (pos >= mid)//zweite hälfte
	{
		*rot = 0; //rra
		while (pos < size)
		{
			pos++;
			steps++;
		}
	}
	//ft_printf("steps b to last: %i\n", steps);

	return (steps);
}


int	rotation_b(t_list *node_a, t_list *b, t_info *info)
{
	//node in a > maxb oder < minb ? oder dazwischen
	t_list	*min;
	t_list	*max;
	int		maxpos;
	int		pos_in_b;
	
	//get size of list b, max pos and minpos
	info->steps_b = 0;
	info->size_b = ft_lstsize(b);
	min = get_min(b);
	max = get_max(b);
			//  ft_printf("max b is: %i\n", *(int *)max->content);
			//  ft_printf("min b is: %i\n", *(int *)min->content);

	maxpos = get_position(b, max);
		//	 ft_printf("max pos b is: %i\n", maxpos);

	//minpos = get_position(b, min);
	//compare value from a against min max in b
	if (*(int *)node_a->content > *(int *)max->content || *(int *)node_a->content < *(int *)min->content)//new is new max or min
	{		//max in b needs to become pos 1 in b 
		// ft_printf("nr would be new min /Max\n");
		//do nothing if mamakx is pos 1st already 
		if (maxpos > 1)
			info->steps_b = calc_steps(b, maxpos, &info->rot_b);
		else 
			info->steps_b = 0;
	}
	else//new is inbetween
	{
		//ft_printf("node_a: %i would be in between\n", *(int*)node_a->content);

		//traverse list b and find correct pos for node_a
		pos_in_b = get_pos_in_b(node_a, b, max); //node at posinb is smaller than new // TO DO : update ft
		//ft_printf("pos for a in b would be: %i\n", pos_in_b);
		//calc steps how to get there (rotation only)s
		if (pos_in_b > 1)
			info->steps_b = calc_steps(b, pos_in_b, &info->rot_b); //smaller should  be 1st!!
		else 
			info->steps_b = 0;
	}
	// ft_printf("rotation steps b: %i\n", info->steps_b);
	// ft_printf("direction rot_b: %i\n", info->rot_b);

	return (info->steps_b);

}

int	get_mid_pos(t_list *lst)//get middle node of list effectively using %
{
	int mid;
	int size;

	size = ft_lstsize(lst);
	if (size % 2 == 1)//ungerade 
		mid = size / 2 + 1;
	else //gerade anzahl
		mid = size / 2;
	return (mid);
}

void	rotation_a(int pos_a, int size_a, t_info *info, t_list *a)//pos_a = node für die calculated 
{	//1. pb nur möglich wenn node pos 1 in a
		//get position in a, decide which way to rotate: ra oder rra

	int	mid;
	int	steps;
	
		//--------zsmfassen mit calc steps
	steps = 0;
	mid = get_mid_pos(a);
	//ft_printf("mid pos is: %i\n", mid);

	if (pos_a <= mid)//in erster hälfte
	{
		info->rot_a = 1; //ra
		while (pos_a > 1)//until we reached pos
		{
			pos_a--;
			steps++;
		}
	}
	if (pos_a > mid)//2. hälfte
	{
		info->rot_a = 0; //rra

		while (pos_a < (size_a + 1))//rotate up to 1. pos
		{
			pos_a++;
			steps++;
		}
	}
	//---------------
	//ft_printf("steps a: %i\n", steps);
	info->steps_a = steps;

}

void init_info(t_info *info, int pos, t_list *a)
{
	info->size_a = ft_lstsize(a);
	info->size_b = 0;
	info->rot_a = -1;
	info->rot_b = -1;
	info->steps_a = 0;
	info->steps_b = 0;
	info->rr = 0;
	info->rrr = 0;
	info->total_steps = 0;
	info->pos_a = pos;

}

void	do_push(t_stack *stacks, t_info *cheapest)
{
	//ft_printf("in do push\n");
	//read info from cheapest and exec
	//rr or rrr first
	if (cheapest->rr > 0 || cheapest->rrr > 0)
	{
		while (cheapest->rr > 0)
		{
			stacks = rr(stacks);
			cheapest->rr--;
		}
		while (cheapest->rrr > 0)
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

// t_stack *final_rot_b(t_stack *stacks)//want max to be at 1 in b
// {
// 	t_list	*max;
// 	int		maxpos;
// 	int 	rot;
// 	int		steps;
// 	//get pos max
// 	rot = -1;
// 	steps = 0;
// 	max = get_max(stacks->b);
// 	maxpos = get_position(stacks->b, max);
// 	if (maxpos != 1)
// 		steps = calc_steps(stacks->b, maxpos, &rot);
// 	//rotate b
// 	while (steps > 0)//1 is up ra, 0 is down rra 
// 	{
// 		if (rot == 1)//
// 			stacks = rb(stacks);
// 		else if (rot == 0)
// 			stacks = rrb(stacks);
// 		steps--;
// 	}
// 	return (stacks);
// }

t_info	*rot_check(t_info *info)
{
	//check if some ra/rra can be optimized w rr/rrr
	//1 is up ra, 0 is down rra
	if (info->rot_a == info->rot_b)//rot same direction
	{
		if(info->steps_a > 0 && info->steps_b > 0)
		{
			while (info->steps_a > 0 && info->steps_b > 0)
			{
				if (info->rot_a == 1)//1 is up ra, 0 is down rra
					info->rr += 1;
				else if (info->rot_a == 0)
					info->rrr += 1;

				info->steps_a--;
				info->steps_b--;
			}
		}
	}
	info->total_steps = 1 + info->steps_a + info->steps_b + info->rr + info->rrr; //1 für pb
	return(info);
}

t_stack	*do_bigger_sort(t_stack	*stacks)
{
	//ft_printf("in bigger sort\n");
	int		pos_a;
	t_list	*node;
	t_info	info;
	t_info	cheapest;

	pos_a = 1;
	init_info(&info, pos_a, stacks->a);
	init_info (&cheapest, 0, stacks->a);

	info.size_a = ft_lstsize(stacks->a);
	//ft_printf("size a: %i\n", info.size_a);
	while (pos_a <= info.size_a) //calculating cheapest to push
	{
		init_info(&info, pos_a, stacks->a);
		//ft_printf("\nchecking stack a pos: %i\n", pos_a);

	//go thru whole stack a (until only 3 left) and calc for each number how many steps (in a and b) would be needed to put in right position
		//always: get min and max in b, compare each new number to this
			//if > max oder <min dann pos eindeutig (rotate until true und pb)
			//if dazwischen: get position of closest 
		node = get_node_at_pos(stacks->a, pos_a);
		//ft_printf("got node at pos\n");

	//1. pb nur möglich wenn node pos 1 in a
		//get position in a, decide which way to rotate: ra oder rra
		//info.steps_a = rotation_a(pos_a, info.size_a, &info, stacks->a);
		rotation_a(pos_a, info.size_a, &info, stacks->a);
			// ft_printf("rotation steps a: %i\n", info.steps_a);
			// ft_printf("direction rot_a: %i\n", info.rot_a);

	//2. check conditions in b: (und size b? bei 2 eig egal)
		info.steps_b = rotation_b(node, stacks->b, &info);
		// 	ft_printf("rotation steps b: %i\n", info.steps_b);
		// 	ft_printf("direction rot_b: %i\n", info.rot_b);
		// ft_printf("total steps_needed before rot check: %i\n", info.steps_a + info. steps_b + 1);

	// rotation check: if same direction check if rrr etc possible!
		//print_info(&cheapest);
		//print_info(&info);
		info = *rot_check(&info);
		//print_info(&info);


		// ft_printf("a pos: %i\n",pos_a);
		// ft_printf("total steps_needed after rot check: %i\n", info.total_steps);
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

		pos_a++;

	}
	// ft_printf("cheapest info:\n");
	// print_info(&cheapest);
	do_push(stacks, &cheapest);

	return (stacks);
}

void	print_info(t_info *info)
{
		//ft_printf("\ninfo cheapest:\n");

	ft_printf("size_a; %i\n", info->size_a);
	ft_printf("size_b; %i\n", info->size_b);
	ft_printf("rot_a; %i\n", info->rot_a);
	ft_printf("rot_b; %i\n", info->rot_b);
	ft_printf("steps_a; %i\n", info->steps_a);
	ft_printf("steps_b; %i\n", info->steps_b);
	ft_printf("rr; %i\n", info->rr);
	ft_printf("rrr; %i\n", info->rrr);
	ft_printf("total steps; %i\n", info->total_steps);
	ft_printf(" pos in a; %i\n\n", info->pos_a);

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:21:04 by lgottsch          #+#    #+#             */
/*   Updated: 2025/01/06 15:28:06 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	//ft_printf("in sort 2\n");
	t_list	*tmp;

	tmp = stacks->a;
	if (*(int *)tmp->content > *(int *)tmp->next->content)
	{
		//ft_printf("1st > 2nd\n");
		stacks = sa(stacks);
		//print_both(stacks);
	}
	return (stacks);
}

t_stack *final_rot_b(t_stack *stacks)//want max to be at 1 in b
{
	t_list	*max;
	int		maxpos;
	int 	rot;
	int		steps;
	//get pos max
	rot = -1;
	steps = 0;
	max = get_max(stacks->b);
	maxpos = get_position(stacks->b, max);
	if (maxpos != 1)
		steps = calc_steps(stacks->b, maxpos, &rot);
	//rotate b
	while (steps > 0)//1 is up ra, 0 is down rra 
	{
		if (rot == 1)//
			stacks = rb(stacks);
		else if (rot == 0)
			stacks = rrb(stacks);
		steps--;
	}
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
	else //bigger than 3
	{
		//PHASE 1: push 2 to b
		stacks = pb(stacks);
		stacks = pb(stacks);
		//print_both(stacks);
		while (ft_lstsize(stacks->a) > 3)
		{
			stacks = do_bigger_sort(stacks);
			//print_both(stacks);
		}
		//rotate b so that max on top //TO DO
		// 		ft_printf("before final rot b\n");
		// print_both(stacks);

		stacks = final_rot_b(stacks);
			//			ft_printf("\nafter final rot b\n");

		//print_both(stacks);
		stacks = sort_3(stacks);
		//print_both(stacks);

		//push back to a (!a ASCENDING ORDER smallest 1st)
		stacks = push_back(stacks);
			//TO DO
		//for 1st in b: 
			//find correct pos in a to push 
			//rotate a so that one bigger is at 1
			//pa
	}
	return (stacks);
}

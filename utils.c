/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:25:08 by lgottsch          #+#    #+#             */
/*   Updated: 2025/01/06 13:08:46 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_list(t_list *list)
{
	while(list)
	{
		ft_printf("char list content: %s\n", (char*)list->content);
		list = list->next;
	}
}

void print_int_list(t_list *list, char s)
{
	int i;

	while(list)
	{
		i = *(int*)list->content;
		ft_printf("int list %c", s);
		ft_printf(": %i\n", i);

		list = list->next;
	}
}

void	print_both(t_stack *stacks)
{
	t_list	*a;
	t_list	*b;
	int		i;
	int		y;

	a = stacks->a;
	b = stacks->b;
	while (a || b)
	{
		i = 0;
		y = 0;
		if (a)
		{
			i = *(int*)a->content;
			ft_printf("stack a: %i", i);
			a = a->next;
		}
		else
			ft_printf("          ", i);
		ft_printf("|	");
		if (b)
		{
			y = *(int*)b->content;
			ft_printf("stack b: %i\n", y);
			b = b->next;
		}
		else
			ft_printf("\n");
	}
	ft_printf("\n");
}

t_list	*get_min(t_list	*list)
{
	//traverse int list and keep track of node w smallest value
	t_list	*min;

	min = list; //set to 1st node
	while (list)
	{
		if (*(int *)min->content > *(int *)list->content)//change if current is bigger than new 
			min = list;
		
		list = list->next; //go to next
	}
	return (min);
}

t_list	*get_max(t_list	*list)
{
	//traverse int list and keep track of node w smallest value
	t_list	*max;

	max = list; //set to 1st node
	while (list)
	{
		if (list)
		{
			if (*(int *)max->content < *(int *)list->content)//change if current is smaller than new 
				max = list;
		}
		list = list->next; //go to next

	}
	return (max);
}

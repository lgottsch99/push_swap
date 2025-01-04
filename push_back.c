//HEADER

#include "push_swap.h"

int calc_steps_a(t_list *lst, int pos, int *rot) //pos needs to be 1 to push correctly, own ft for a bc ascending order
{
	ft_printf("in normal calc steps\n");
	int	steps;
	int	mid;
	int size;

	size = ft_lstsize(lst);
	if (size <= 3)
		mid = 2;
	else
		mid = size / 2;

	steps = 0;
	if (pos <= mid)//in erster hälfte
	{
		*rot = 1; //ra
		while (pos > 1)
		{
			pos--;
			steps++;
		}
	}
	else if (pos > mid)//zweite hälfte
	{
		*rot = 0; //rra
		while (pos < (size + 1))
		{
			pos++;
			steps++;
		}
	}
	return (steps);
}

int	inbetween(int nr_b, t_list *a)
{
	t_list *current;
	t_list *one_before;
	int		pos;

	//inbetween:
	pos = 1;
	current = a; // start at first
	one_before = ft_lstlast(a); //start at last
	while (!(*(int *)current->content > nr_b && *(int *)one_before->content < nr_b) && pos <= ft_lstsize(a))
	{
		if (!one_before->next)
			one_before = a;
		else	
			one_before = current;
		if (current->next)
			current = current->next;
		else
			break;
		pos++;
	}
	return (pos);

}

int	get_pos_in_a(int nr_b, t_list *a) //TO DO : check if working
{
	//3 scenarios!: min, max or inbetween
		//if min or max i need current min at 1
	int		pos;
	//get pos first and decide which way to rot a eff. next
	//if min /max
	t_list	*min;
	t_list	*max;

	min = get_min(a);
	max = get_max(a);
	pos = 0;
	if (nr_b < *(int *)min->content || nr_b > *(int *)max->content)//nr is new min or max
	{
		pos = get_position(a, min);
	}
	else
	{
		pos = inbetween(nr_b, a);
	}
	ft_printf("pos for stack b %i in a ", nr_b); //at pos is the one bigger
		return (pos);
}

t_stack	*final_rot_a(t_stack *stacks)
{
	t_list	*min;
	int		minpos;
	int 	steps;
	int		rot;

	rot = -1;
	//get minpos
	min = get_min(stacks->a);
	minpos = get_position(stacks->a, min);
	//get steps + rotation
	steps = calc_steps_a(stacks->a, minpos, &rot);
			ft_printf("final a rot: %i\n", rot);
		ft_printf("final steps: %i\n", steps);

	//rotate --possible new ft
	while (steps > 0)
	{
		if (rot == 1)//1 is up ra, 0 is down rra
			stacks = ra(stacks);
		else if (rot == 0)
			stacks = rra(stacks);
		steps--;
	}//---------
	return (stacks);
}

t_stack	*push_back(t_stack *stacks)//push back to a (!a ASCENDING ORDER smallest 1st)
{
			//TO DO

		//for 1st in b:
			//find correct pos in a to push 
			//rotate a so that one bigger is at 1
			//pa
	int	pos_a;
	int	rot; //direction rotation a, 1 is up ra, 0 is down rra
	int	steps;//amount of steps needed to rotate a;
	
	rot = -1;
	steps = 0;
	while(ft_lstsize(stacks->b) > 0)
	{
		//TODO check if new max min or inbetween!
		pos_a = get_pos_in_a(*(int*)stacks->b->content, stacks->a);
		ft_printf("is: %i\n", pos_a); //pos_a is the one bigger ->needs to become first, then pa
		
		steps = calc_steps_a(stacks->a, pos_a, &rot);
		ft_printf("a rot: %i\n", rot);
		ft_printf("steps: %i\n", steps);
		//rotate a -----possible outsource
		while (steps > 0)
		{
			if (rot == 1)//1 is up ra, 0 is down rra
				stacks = ra(stacks);
			else if (rot == 0)
				stacks = rra(stacks);
			steps--;
		}//---------
		stacks = pa(stacks);
	}
	//rotate a to have min at first
	stacks = final_rot_a(stacks);

	return (stacks);
}


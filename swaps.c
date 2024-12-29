//HEADER

#include "push_swap.h"
//operate on pointers to stack to actually change lists

/*
sa (swap a): Swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
sb (swap b): Swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements.
ss : sa and sb at the same time.


typedef struct s_stack {
    t_list  *a;
    t_list  *b;
} t_stack;
*/

t_stack  *sa(t_stack *stack) //insert first elem. after 2nd, 
{
	ft_printf("sa\n");
	stack = real_sa(stack);
	return (stack);
}

//sa (swap a): Swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
t_stack  *real_sa(t_stack *stack) //insert first elem. after 2nd, 
{
    int     lstlen;
    t_list  *tmp;
    t_list  *third;
    //check len of list a
    lstlen = ft_lstsize(stack->a);
    if (lstlen <= 1)
        return (stack);
    
    tmp = stack->a; //tmp pointing to 1st elem
    stack->a = stack->a->next; //a pointing to 2nd element, which now 1st
    third = stack->a->next;
        // ft_printf("tmp val: %i\n", *(int*)tmp->content);
        // ft_printf("a val: %i\n", *(int*)stack->a->content);
        // ft_printf("third val: %i\n", *(int*)third->content);

    //insert tmp btw a and third
    stack->a->next = tmp;
    tmp->next = third;

   // ft_printf("sa\n");
    return (stack);
   // print_list(*a); //if print here ok, in main nr 2 is gone :(
}

t_stack  *sb(t_stack *stack) //insert first elem. after 2nd, 
{
	ft_printf("sa\n");
	stack = real_sb(stack);
	return (stack);
}


t_stack  *real_sb(t_stack *stack)
{
	int     lstlen;
	t_list  *tmp;
	t_list  *third;
    //check len of list a
	lstlen = ft_lstsize(stack->b);
	if (lstlen <= 1)
		return (stack);
    
	tmp = stack->b; //tmp pointing to 1st elem
	stack->b = stack->b->next; //a pointing to 2nd element, which now 1st
	third = stack->b->next;
        // ft_printf("tmp val: %i\n", *(int*)tmp->content);
        // ft_printf("b val: %i\n", *(int*)stack->b->content);
        // ft_printf("third val: %i\n", *(int*)third->content);

    //insert tmp btw a and third
	stack->b->next = tmp;
	tmp->next = third;

	//ft_printf("sb\n");
	return (stack);

   // print_list(b); //if print here ok, in main nr 2 is gone :(
}

t_stack	*ss(t_stack *stacks)
{
	stacks = real_sa(stacks);
	stacks = real_sb(stacks);
	ft_printf("ss\n");
	return (stacks);
}
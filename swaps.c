//HEADER

#include "push_swap.h"
//operate on pointers to stack to actually change lists

/*
sa (swap a): Swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
sb (swap b): Swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements.
ss : sa and sb at the same time.
*/

//sa (swap a): Swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements.
t_list  *sa(t_list *a) //insert first elem. after 2nd, 
{
    int     lstlen;
    t_list  *tmp;
    t_list  *third;
    //check len of list a
    lstlen = ft_lstsize(a);
    if (lstlen <= 1)
        return (a);
    
    tmp = a; //tmp pointing to 1st elem
    a = a->next; //a pointing to 2nd element, which now 1st
    third = a->next;
        ft_printf("tmp val: %i\n", *(int*)tmp->content);
        ft_printf("a val: %i\n", *(int*)a->content);
        ft_printf("third val: %i\n", *(int*)third->content);

    //insert tmp btw a and third
    a->next = tmp;
    tmp->next = third;

    ft_printf("sa\n");
    return (a);
   // print_list(*a); //if print here ok, in main nr 2 is gone :(
}

t_list  *sb(t_list *b)
{
    int     lstlen;
    t_list  *tmp;
    t_list  *third;
    //check len of list a
    lstlen = ft_lstsize(b);
    if (lstlen <= 1)
        return (b);
    
    tmp = b; //tmp pointing to 1st elem
    b = b->next; //a pointing to 2nd element, which now 1st
    third = b->next;
        ft_printf("tmp val: %i\n", *(int*)tmp->content);
        ft_printf("b val: %i\n", *(int*)b->content);
        ft_printf("third val: %i\n", *(int*)third->content);

    //insert tmp btw a and third
    b->next = tmp;
    tmp->next = third;

    ft_printf("sb\n");
    return (b);

   // print_list(b); //if print here ok, in main nr 2 is gone :(
}

void    ss(t_list *a, t_list *b)
{
    sa(a);
    sb(b);
}
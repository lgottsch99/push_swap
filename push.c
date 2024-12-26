//HEADER

#include "push_swap.h"

/*
pa (push a): Take the first element at the top of b and put it at the top of a.
Do nothing if b is empty.
pb (push b): Take the first element at the top of a and put it at the top of b.
Do nothing if a is empty.
*/

void    pa(t_list *a, t_list *b)
{
    //fisrt elem in b , put it to top of a
    t_list  *tmp;
    int     len;

    len = ft_lstsize(b);
    if (len == 0)
        return;

    tmp = b;
    b = b->next;
    ft_lstadd_front(&a, tmp);
}

void    pb(t_list *a, t_list *b)
{
    //fisrt elem in a , put it to top of b
    t_list  *tmp;
    int     len;

    len = ft_lstsize(a);
    if (len == 0)
        return;

    tmp = a;
    a = a->next;
    ft_lstadd_front(&b, tmp);

}
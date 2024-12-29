//HEADER

#include "push_swap.h"

void	free_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
}

void	free_everything(t_stack *stacks)
{
	free_list(stacks->a);
	free_list(stacks->b);
}
//HEADER

#include "push_swap.h"

/*
TO DO 
what if arg/input is empty? " " "" 
what if - or + only? OK
single input string "2 6  8  9 0" should work too! OK
memleaks check
norm
ERROR:
check pushing to b with big input has problems, not sorted
check push back, seems to be too many of ra rra

STRATEGY NEW
1. read input into char list : The first argument should be at the top of the stack (be careful about the order).
	go thru input, for every arg:
		chcek if empty " " ""
		check for whitespace, if yes split
		append to list of input

2.check for valid input:
	go trhu whole list:
		check only digits, int range, dups

3.sort and print operations
	check if input already sorted, if yes do nothing
	if no: 
		push everything to b but in descending-sorted order, then push back
		before doing anything, always scan and calc for cheapest number
	???

4. free list and all memory

*/


void	replace_int(t_list **list)
{
	//ft_printf("in replace int\n");

	int	*integer;
	int	nr;
	char *str;
	int	i;
	int	lstsize;
	t_list *tmp;

		//go trhu whole list and for each elem: 
		//malloc space for int 
		//atoi str and copy into int space
		//free node content and connect int
	tmp = *list;
	lstsize = ft_lstsize(*list);
	i = 0;
	while (i < lstsize)
	{
		str = (char *)tmp->content;
		//malloc space for int
		integer = (int *)malloc(sizeof(int));
		// if(!integer)
		// 	free_all(); //TO DOO
		//ft_printf("malloced\n");

		//atoi str and copy into int space
		nr = ft_atoi(str);
		ft_memcpy(integer, &nr, sizeof(int));

		//free node content and connect int
		free(tmp->content);
		tmp->content = integer;

		tmp = tmp->next;
		i++;
	}
}


int	main(int argc, char *argv[])
{
	t_stack	stacks;

	stacks.a = NULL; //stack a: The stack a contains a random amount of negative and/or positive numbers which cannot be duplicated.
	stacks.b = NULL; //stack b: empty
	if (argc <= 1 || argv[1][0] == '\0') //ggf check for "" 2 3 
		return (0);

	//1. read into char list 
	stacks.a = read_into_list(argc, argv); //maybe add sth about empty "  " later
	//print_list(stacks.a);

	//2. check each list elem for validity,
	if (check_valid(&stacks.a) == 1)
	{
	 	ft_printf("Error\n");
	 	return (1);
	}
	//ft_printf("input ok\n");

	//3. if all valid change to int
	replace_int(&stacks.a);
	//print_both(&stacks);

	//3.sort
	stacks = *sort(&stacks);

//print_both(&stacks);

	//free_everything(stacks);
	return (0);
}
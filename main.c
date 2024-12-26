//HEADER

#include "push_swap.h"

/*
TO DO 
write all operation fts
what if arg/input is empty? " " "" what if - or + only?
single input string "2 6  8  9 0" should work too! 

STRATEGY NEW
1. read input into char list : The first argument should be at the top of the stack (be careful about the order).
	go thru input, for every arg:
		chcek if empty " " ""
		check for whitespace, if yes split
		append to list of input

2.check for valid input:
	go trhu whole list:
		check only digits, int range, dups

3.sort

*/


void	replace_int(t_list **list)
{
	ft_printf("in replace int\n");

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
		ft_printf("malloced\n");

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
	t_list	*a; //stack a: The stack a contains a random amount of negative and/or positive numbers which cannot be duplicated.
	//t_list	*b; //stack b: empty

	if (argc <= 1 || argv[1][0] == '\0')
		return (0);

	a = NULL;
	//b = NULL;

	//1. read into char list 
	a = read_into_list(argc, argv); //maybe add sth about empty "  " later
	print_list(a);

	//2. check each list elem for validity,
	if (check_valid(&a) == 1)
	{
	 	ft_printf("Error\n");
	 	return (1);
	}
	ft_printf("input ok\n");

	//3. if all valid change to int
	replace_int(&a);
	print_int_list(a);


	//a = sa(a);

}
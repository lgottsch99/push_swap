//HEADER

#include "push_swap.h"

int check_range(char *str)
{
	long	input;
	int		sign;
	long	min; //int min
	long	max; //int max
	int		i;

	min = -2147483648;
	max = 2147483647;
	sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	if (str[0] == '+')
		i++;
	input = str[i] - '0';
	i++;
	while(str[i])
	{
		input = input * 10; //eins verschieben
		input = input + (str[i] - '0');
		i++;
	}
	input = input * sign;
	//printf("input as nbr: %ld\n", input);
	if (input < min || input > max)
		return (1);
	return (0);
}

int	check_int_range(char *str)
{
	int	strlen;	
	//ft_printf("str: %s\n", str);
	//check if str, that is made up of only digits, is within int range // ret 1 if not within range
	strlen = ft_strlen(str); //check length 
	if (strlen < 10)//sicher in range
		return (0);
	if (strlen == 10)
	{
		if (str[0] == '-' || str[0] == '+') //safe in range 
			return (0);
	}
	if (strlen > 11) //safe too big
		return (1);
	if (strlen == 11)
	{
		if (str[0] != '-' && str[0] != '+') //safe too big
			return (1);
	}
	if (check_range(str) == 1)
		return (1);	
	return (0);
}

int	check_dups(t_list **list, int i) //only digits within int range
{
	ft_printf("in check dups\n");

	t_list	*tmp;
	int		og;
	int		cmp;
	int		y;

	tmp = *list;
	//go to current node at position i, save value somewhere
	y = 0;
	while (y < i)
	{
		tmp = tmp->next;
		y++;
	}
	//ft_printf("tmp at: %s\n", (char*)tmp->content);

	og = ft_atoi((char*)tmp->content); //save current str
	//ft_printf("og atoied: %i\n", og);
	
	//go thru whole array vorwärts und compare
	tmp = *list;
	y = 0;
	while (y < i)
	{	//compare each og with cmp
		cmp = ft_atoi((char*)tmp->content);
		//ft_printf("cmp atoied: %i\n", cmp);

		if (og == cmp)//dup found
			return (1);
		tmp = tmp->next;
		y++;
	}
	return (0);
}

int	check_digits(char *str) 
{
	int	y;
	int	check;

	y = 0;
	check = 0;
	while (str[y])
	{			
		if (y == 0)
		{
			//ft_printf("char is: %c\n", str[y]);
			if (!ft_isdigit(str[y]))
			{
				if (str[y] != '-' && str[y] != '+')
					check += 1;
			}
		}
		else if (y > 0 && !ft_isdigit(str[y]))
			check += 1;
		y++;
	}
	if (check > 0)
		return (1);
	return (0);
}

int	check_valid(t_list **list)
{
	ft_printf("in check valid\n");

	t_list	*ptr;
	int 	size;
	int		i;
	//go thru whole char list and check for each elem:
		//check only digits, int range, dups
	size = ft_lstsize(*list);
	ft_printf("lst size: %i\n", size);

	ptr = *list;
	i = 0;
	while (i < size)
	{
		ft_printf("checking elem: %s\n", (char*)ptr->content);

		if(check_digits(ptr->content) == 1) //sth not digit
			return (1);
		ft_printf("digits ok\n");

		//ft_printf("check is: %i\n", check);
		if(check_int_range(ptr->content) == 1)
			return (1);
		ft_printf("int range ok\n");

		if(check_dups(list, i) == 1)
			return (1);
		ft_printf("dup ok\n");

		ptr = ptr->next;
		i++;
	}
	return (0);
}

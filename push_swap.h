//HEADER

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "./full_libft/full_libft.h"

typedef struct s_stack {
    t_list  *a;
    t_list  *b;
} t_stack;

typedef struct s_info { //splitten in eins für info und eins für cheapest!
	int	size_a;
	int size_b;
	int rot_a; //indicating rotation direction: 1 is up ra, 0 is down rra
	int rot_b; //indicating rotation direction: 1 is up ra, 0 is down rra 
	int steps_a; //keeping amount of steps for each pos
	int steps_b;
	int rr; //amount steps for rr
	int rrr;
	int total_steps;
	int pos_a;
	// int cheapest_pos_a;
	// int cheapest_steps_a;
	// int cheapest_rot_a; //to safe direction for execution
	// int cheapest_rot_b;

} t_info;

//check_input.c
int	check_digits(char *str);
int	check_dups(t_list **argv, int i);
int	check_int_range(char *str);
int check_range(char *str);
int	check_valid(t_list **list);


//swaps.c
t_stack  *sa(t_stack *stack);
t_stack  *real_sa(t_stack *stack);
t_stack  *sb(t_stack *stack);
t_stack  *real_sb(t_stack *stack);
t_stack	*ss(t_stack *stacks);

//push.c
t_stack	*pa(t_stack *stacks);
t_stack	*pb(t_stack *stacks);

//reverse
t_stack	*rra(t_stack *stacks); //Shift down all elements of stack a by 1.
t_stack	*rrb(t_stack *stacks); //Shift down all elements of stack b by 1.
t_stack	*rrr(t_stack *stacks);

//rotate
t_stack *ra(t_stack *stacks);//Shift up all elements of stack a by 1. The first element becomes the last one.
t_stack *rb(t_stack *stacks);//Shift up all elements of stack a by 1. The first element becomes the last one.
t_stack	*rr(t_stack *stacks);

//sort
t_stack	*sort(t_stack *stacks);
t_stack	*sort_5(t_stack *stacks); //in max 12 operations!

//sort3
int		get_position(t_list *list, t_list *node);
t_stack	*sort_3(t_stack *stacks);//list is def 3 in size


//read into list char
t_list	*read_into_list(int argc, char *argv[]);
void	create_str_to_list(t_list **list, char *argv);
void    add_to_list(t_list **list, char *ptr);
char    **check_whitespace(char *str);

//bigger sort
t_stack	*do_bigger_sort(t_stack	*stacks);

//push back
t_stack	*push_back(t_stack *stacks);


//main
void    print_list(t_list *list);

//free
void	free_everything(t_stack *stacks);
void	free_list(t_list *lst);



//utils
void    print_int_list(t_list *list, char s);
void    print_list(t_list *list);
void	print_both(t_stack *stacks);
t_list	*get_max(t_list	*list);
t_list	*get_min(t_list	*list);
void	print_info(t_info *info);



# endif
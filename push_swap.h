//HEADER

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "./full_libft/full_libft.h"

//check_input.c
int	check_digits(char *str);
int	check_dups(t_list **argv, int i);
int	check_int_range(char *str);
int check_range(char *str);
int	check_valid(t_list **list);


//swaps.c
t_list  *sa(t_list *a);
t_list  *sb(t_list *b);
void    ss(t_list *a, t_list *b);

//push.c
void    pa(t_list *a, t_list *b);

//read into list char
t_list	*read_into_list(int argc, char *argv[]);
void	create_str_to_list(t_list **list, char *argv);
void    add_to_list(t_list **list, char *ptr);
char    **check_whitespace(char *str);



//main
void    print_list(t_list *list);

//utils
void    print_int_list(t_list *list);
void    print_list(t_list *list);



# endif
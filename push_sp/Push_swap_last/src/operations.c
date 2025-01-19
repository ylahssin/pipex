#include "push_swap.h"

void    push_to_a(t_list **stack_a, t_list *top)
{
    if (!top)
        return ;
    ft_lstadd_front(stack_a, top);
    write(1, "pa\n", 3);
}

void    push_to_b(t_list **stack_b, t_list *top)
{
    if (!top)
        return ;
    ft_lstadd_front(stack_b, top);
    write(1, "pb\n", 3);
}

/* Rotate operations */
void    ra(t_list **stack_a)
{
    t_list  *first;
    t_list  *last;

    if (!stack_a || !*stack_a || !(*stack_a)->next)
        return ;
    first = *stack_a;
    last = *stack_a;
    while (last->next)
        last = last->next;
    *stack_a = first->next;
    first->next = NULL;
    last->next = first;
    write(1, "ra\n", 3);
}

void    rb(t_list **stack_b)
{
    t_list  *first;
    t_list  *last;

    if (!stack_b || !*stack_b || !(*stack_b)->next)
        return ;
    first = *stack_b;
    last = *stack_b;
    while (last->next)
        last = last->next;
    *stack_b = first->next;
    first->next = NULL;
    last->next = first;
    write(1, "rb\n", 3);
}

void    rr(t_list **stack_a, t_list **stack_b)
{
    if (!stack_a || !stack_b || !*stack_a || !*stack_b)
        return ;
    ra(stack_a);
    rb(stack_b);
    write(1, "rr\n", 3);
}


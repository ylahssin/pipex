#include "push_swap.h"

void    rra(t_list **stack_a)
{
    t_list  *last;

    if (!stack_a || !*stack_a || !(*stack_a)->next)
        return ;
    last = *stack_a;
    while (last->next)
        last = last->next;
    last->next = *stack_a;
    *stack_a = last;
    write(1, "rra\n", 4);
}

void    rrb(t_list **stack_b)
{
    t_list  *last;

    if (!stack_b || !*stack_b || !(*stack_b)->next)
        return ;
    last = *stack_b;
    while (last->next)
        last = last->next;
    last->next = *stack_b;
    *stack_b = last;
    write(1, "rrb\n", 4);
}

void    rrr(t_list **stack_a, t_list **stack_b)
{
    if (!stack_a || !stack_b || !*stack_a || !*stack_b)
        return ;
    rra(stack_a);
    rrb(stack_b);
    write(1, "rrr\n", 4);
}

t_list *pop_from_a(t_list **stack_a)
{
    t_list *top;

    top = *stack_a;
    if (!top)
        return (NULL);
    *stack_a = (*stack_a)->next;
    top->next = NULL;
    return (top);
}

t_list *pop_from_b(t_list **stack_b)
{
    t_list *top;

    top = *stack_b;
    if (!top)
        return (NULL);
    *stack_b = (*stack_b)->next;
    top->next = NULL;
    return (top);
}


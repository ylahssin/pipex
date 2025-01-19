#include "push_swap.h"

int main(int ac, char **av)
{
    t_list  *stack_a;
    t_list  *stack_b;
(void)stack_b;
    if (ac < 2)
        error(NULL);
    stack_a = first_stack(&av[1], ac - 1);
    stack_b = NULL;
    
    while (stack_a)
    {
        printf("%d->", stack_a->content);
        stack_a = stack_a->next;
    }
    printf("NULL\n");
    ft_lstclear(&stack_a);
    return (0);
}

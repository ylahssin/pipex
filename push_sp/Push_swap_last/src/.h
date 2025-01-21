#include "push_swap.h"

// Function to calculate cost for stack B
int calculate_cost(t_list *stack, int position, int direction)
{
    int size = ft_lstsize(stack);
    if (direction == 1) // Rotate
        return position;
    else // Reverse rotate
        return size - position;
}

// Function to calculate cost for stack A
int calculate_cost_for_a(t_list *stack_a, int value, int cost_b)
{
    t_list *tmp = stack_a;
    int position = 0;

    while (tmp)
    {
        if (tmp->content > value)
            break;
        position++;
        tmp = tmp->next;
    }

    if (position > ft_lstsize(stack_a) / 2)
        return (ft_lstsize(stack_a) - position) + cost_b;
    else
        return position + cost_b;
}

// Function to calculate the true combined cost
int calculate_true_cost(t_cost cost)
{
    return (cost.cost_a > cost.cost_b ? cost.cost_a : cost.cost_b);
}


#include "push_swap.h"

int cmp_1(int a, int b)
{
	return (a <= b);
}
void ft_swap(int *a, int *b)
{
    int swap = *a;
    *a = *b;
    *b = swap;
    write(1, "sa\n", 2);
}
t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int	swap;
	t_list	*tmp;

	tmp = lst;
	while(lst->next != NULL)
	{
		if (((*cmp)(lst->data, lst->next->data)) == 0)
		{
			ft_swap(&lst->data, &lst->next->data);
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

t_list *change_stack_a(t_list **stack_a, int *arr, int size)
{
    t_list *tmp = *stack_a;
    int i;

    while (tmp)
    {
        i = 0;
        while (i < size)
        {
            if (tmp->content == arr[i])
            {
                tmp->content = i;
                break;
            }
            i++;
        }
        tmp = tmp->next;
    }
    return (*stack_a);
}

void sort_int_tab(int *tab, unsigned int size)
{
    unsigned int i;
    unsigned int j;
    int temp;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size - 1)
        {
            if (tab[j] > tab[j + 1])
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

t_list *ft_get_runk(t_list *stack_a, int size)
{
    int *array = malloc(sizeof(int) * size);
    int i = 0;
    t_list *tmp = stack_a;

    if (!array)
        return (NULL);
    while (tmp)
    {
        array[i++] = tmp->content;
        tmp = tmp->next;
    }
    sort_int_tab(array, (unsigned int)size);
    stack_a = change_stack_a(&stack_a, array, size);
    free(array);
    return (stack_a);
}

int calculate_cost(t_list **stack, int current_position, int target_number)
{
    int midd = ft_lstsize(*stack) / 2;

    if(current_position >= ft_lstsize(*stack_b)) 
        return(ft_lstsize(*stack));
    else if(target_number && current_position >= midd)
        return(ft_lstsize(*stack) - current_position);
    else if(target_number && current_cost < midd) 
        return(-(current_position + 1));
    else if(!target_number && current_position >= midd)
        return(ft_lstsize(*stack) - current_position + 1);
    else if(target_number && current_cost < midd) 
        return(-(current_position));
}
int get_value(t_list **stack_a, int value, great_move)
{
    int best_m_position = -1;
    int val;
    char *tmp = *stack_a;
    int position = 0;
    int best_match;

    if(great_move == -1) best_match =  INT_MIN;
    else best_match  = INT_MAX;
    while(tmp)
    {
        val = tmp->content;
        if((great_move == -1 && val < value && best_match < val) || (great_move == 1 && val > value && best_match > val)
         {
            best_m_position  = position;
            best_match = val;
         }
        position++;
        tmp = tmp->next;
    }
    return(best_m_position);
}
int max(int a, int b)
{
    if(a >= b)
        return(a);
    return(b);
}
int min(int a, int b)
{
    if(a < b)
        return(a);
    else return(b);
}
int calculate_cost_for_a(t_list **stack_a, int value_fs_b, int cost_b)
{
    t_number best_num;
    best_num.less_number_position = get_value(*stack_a, value_fs_b, NEGATIVE);
    best_num.big_number_position = get_value(*stack_a, value_fs_b, POSIIVE);
    best_num.big_num_cost = calcule_cost(*stack_a, best_num.big_number_position, POSITIVE);
    best_num.less_num_cost = calcule_cost(*stack_a, best_num.less_number_position, ZERO);
    if(best_num.less_number_position == -1)
            return(best_num.big_number_cost);
    else if(best_num.big_num_cost == -1)
            return(best_num.less_number_cost);
    if(best_num.big_num_cost * best_num.less_num_cost >= 0)
    {
            if(best_num.big_num_cost < 0)
                return(max(best_num.big_num_cost, best_num.less_num_cost));
            else
                return(min(best_num.big_num_cost, best_num.less_num_cost));
    }
    //stop here
    return(next_move(best_num.big_num_cost, best_num.less_num_cost));
}
int ft_Abs(int number)
{
    if(number < 0)
        return(-number);
    else 
        return(number);
}
int caluclate_true_cost(t_cost check_cost)
{
    int abs_a = ft_abs(check_cost.cost_a);
    int abs_b = ft_abs(check_cost.cost_b);

    if(chech_cost.cost_a * check_cost.cost_b >= 0)
        return(max(abs_a, abs_b));
    else
        return(abs_a + abs_b);
}
void run_tow_cost(t_list **stack_a, t_list **stack_b, t_cost cheapest_cost)
{
    while(cheapest_cost.cost_a > 0 && cheapeset_cost.cost_b > 0)
    {
        rr(stack_a, stack_b);
        cheapeset_cost.cost_a--;
        cheapeset_cost.cost_b--;
    }
    while(cheapeset_cost.cost_a < 0 && cheapeset_cost.cost_b < 0)
    {
        rrr(stack_a, stack_b);
        cheapest_cost.cost_a++;
        cheapest_cost.cost_a--;
    }
    while(cheapeset_cost.cost_a > 0)
    {
        ra(stack_a);
        cheapest_cost.cost_a--;
    }
    while(cheapeset_cost.cost_a < 0)
    {
        rra(stack_a);
        cheapeset_cost.cost_a--;
    }
    while(cheapest_cost.cost_b > 0)
    {
        rb(stack_b);
        cheapeset_cost.cost_b--;
    }
    
    while(cheapest_cost.cost_b > 0)
    {
        rbb(stack_b);
        cheapeset_cost.cost_b--;
    }
}
void make_cheapest_push(t_list **stack_a, t_list **stack_b)
{
    t_cost cheapeset_cost;
    t_cost current_cost;
    int position;
    t_list *tmp;

    cheapest_cost.cost_a = ft_lstsize(*stack_a);
    cheapest_cost.cost_b = ft_lstsize(*stack_b);

    position = 0;
    tmp = *stack_b;
    while (tmp)
    {
        current_cost.cost_b = calculate_cost(*stack_b, position, POSITIVE);
        current_cost.cost_a = calculate_cost_for_a(*stack_a, tmp->content, current_cost.cost_b);

        if (calculate_true_cost(current_cost) < calculate_true_cost(cheapest_cost))
        {
            cheapest_cost.cost_a = current_cost.cost_a;
            cheapest_cost.cost_b = current_cost.cost_b;
        }
        tmp = tmp->next;
        position++;
    }

    run_two_costs(stack_a, stack_b, cheapest_cost);
    pa(stack_a, stack_b);
}
void cost_check(t_list **stack_a, t_list **stack_b, int size)
{
    while (*stack_b)
        make_cheapest_push(stack_a, stack_b);
}
void ft_pre_sort(t_list **stack_a, t_list **stack_b, int med)
{
    int i = 0;
    while(*stack_a)
    {
        if(i <= size - 3) break;
        if((*stack_a->content) >= med)
            push_to_b(*stack_b, pop_from_a(*stack_a));
        else 
        {
            push_to_b(*stack_b, pop_from_a(*stack_a));
            rb(*stack_b, pop_from_a(*stack_a));
        }
        stack_a = stack_a->next;
    }
    sort_list(stack_a, &cmp_1);
    cost_check(stack_a, stack_b, ft_lstsize(b));
}
int main(int ac, char **av)
{
    t_list *stack_a;
    t_list *stack_b = NULL;
    t_list *tmp;
    (void) stack_b;
    if (ac < 2)
        error(NULL);
    stack_a = first_stack(&av[1], ac - 1);
    stack_a = ft_get_runk(stack_a, ft_lstsize(stack_a));
    ft_pre_sort(&stack_a, &stack_b, ft_lstsize(stack_a) \ 2);
    tmp = stack_a;
    while (tmp)
    {
        printf("%d->", tmp->content);
        tmp = tmp->next;
    }
    printf("NULL\n");
    ft_lstclear(&stack_a);
    return (0);
}

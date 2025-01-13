#include "push_swap.h"
void ft_free_array(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int is_check(char *arr)
{
    while (*arr)
    {
        if (!(*arr >= '0' && *arr <= '9'))
            return (0);
        arr++;
    }
    return (1);
}

int is_duplicate(t_list *list, int number)
{
    while (list)
    {
        if (list->content == number)
            return (0);
        list = list->next;
    }
    return (1);
}

void error(void)
{
    write(2, "error\n", 6);
    exit(EXIT_FAILURE);
}

static t_list *first_stack(char **arr, int len_size)
{
    int i = -1, num;
    t_list *list = NULL;
    t_list *tmp;

    while (++i < len_size)
    {
        if (ft_strchr(arr[i], ' '))
        {
            char **args = ft_split(arr[i], ' ');
            int j = 0;
            while (args[j])
            {
                num = ft_atoi(args[j]);
                if (!is_check(args[j]) || !is_duplicate(list, num))
                {
                    ft_free_array(args);
                    ft_lstclear(&list);
                    error();
                }
                tmp = ft_lstnew(num);
                ft_lstadd_back(&list, tmp);
                j++;
            }
            ft_free_array(args);
            continue;
        }
        num = ft_atoi(arr[i]);
        if (!is_check(arr[i]) || !is_duplicate(list, num))
        {
            ft_lstclear(&list);
            error();
        }
        tmp = ft_lstnew(num);
        ft_lstadd_back(&list, tmp);
    }
    return list;
}

int get_prev(t_list *stack_a, int position)
{
    int currentIndex = 1;
    while (stack_a != NULL)
    {
        if (currentIndex == position)
            return stack_a->content;
        stack_a = stack_a->next;
        currentIndex++;
    }
    return -1;
}

void check_position_prev(t_prev *prev, int len, t_list *stack_a)
{
    prev->position_major = (3 * len) / 4;
    prev->position_minor = len / 4;
    prev->major = get_prev(stack_a, prev->position_major);
    prev->minor = get_prev(stack_a, prev->position_minor);
}

t_list *pop_from_a(t_list **stack_a)
{
    t_list *top = *stack_a;
    if (!top)
        return NULL;
    *stack_a = (*stack_a)->next;
    top->next = NULL;
    return top;
}

void push_to_b(t_list **stack_b, t_list *top)
{
    if (top)
    {
        ft_lstadd_front(stack_b, top);
        ft_printf("pb\n");
    }
}

void rotate_a(t_list **stack_a)
{
    if (!stack_a || !*stack_a || !(*stack_a)->next)
        return;
    t_list *first = *stack_a;
    t_list *last = *stack_a;
    while (last->next)
        last = last->next;
    *stack_a = first->next;
    first->next = NULL;
    last->next = first;
    ft_printf("ra\n");
}

void change_partition(t_list **stack_a, t_list **stack_b, t_prev *prev)
{
    t_list *node = *stack_a;

    while (node)
    {
        if (node->content < prev->minor || node->content > prev->major)
            push_to_b(stack_b, pop_from_a(stack_a));
        else
            rotate_a(stack_a);
        node = *stack_a;
    }
}

void recursive_sort(t_list **stack_a, t_list **stack_b, int len)
{
    if (len <= 1)
        return;

    t_prev *prev = malloc(sizeof(t_prev));
    if (!prev)
        return;
    check_position_prev(prev, len, *stack_a);
    change_partition(stack_a, stack_b, prev);

    int len_low = prev->position_minor;
    int len_mid = prev->position_major - prev->position_minor;
    int len_high = len - prev->position_major;

    recursive_sort(stack_a, stack_b, len_low);
    recursive_sort(stack_a, stack_b, len_mid);
    recursive_sort(stack_a, stack_b, len_high);

    free(prev);
}

void three_way_quick_sort(t_list *stack_a, t_list *stack_b, int len)
{
    recursive_sort(&stack_a, &stack_b, len);
}

int main(int ac, char **av)
{
    t_list *first_stack_a;
    t_list *second_stack_b = NULL;

    if (ac < 2)
        error();
    first_stack_a = first_stack(&av[1], ac - 1);
    three_way_quick_sort(first_stack_a, second_stack_b, ft_lstsize(first_stack_a));
    return 0;
}

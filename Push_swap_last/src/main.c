#include "push_swap.h"

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
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
    write(2, "error\n", ft_strlen("error\n"));
    exit(EXIT_FAILURE);
}

static t_list *first_stack(char **arr, int len_size)
{
    int i, num;
    t_list *list = NULL;
    t_list *tmp;

    for (i = 0; i < len_size; i++)
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
#include <stdio.h>
int main(int ac, char **av)
{
    t_list *first_stack_a;
    t_list *second_stack = NULL;
    (void)second_stack;
    if (ac < 2)
        error();

    first_stack_a = first_stack(&av[1], ac - 1);
    t_list *tmp = first_stack_a;
    while(first_stack_a)
  {
    printf("%d", first_stack_a->content);
    first_stack_a = first_stack_a->next;
  }
    ft_lstclear(&tmp);

    return 0;
}


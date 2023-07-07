/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:14:59 by ikayacio          #+#    #+#             */
/*   Updated: 2023/06/23 11:15:12 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//int philo_num, int die_time, int eat_time, int sleep_time, int must_eat_num

void	exit_program(t_list **a, t_list **b)
{
	if (a != NULL)
		ft_lstclear(a);
	if (b != NULL)
		ft_lstclear(b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int ft_atoi(const char *str)
{
    long long result;

    result = 0;
    while (*str == 32 || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '+')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + *str - 48;
        str++;
        if (result > 2147483647)
            result = -1;
    }
    return (result);
}

int arg_check(char **argv, int argc)
{
    int i;
    int j;

    if (argc < 5 || argc > 6)
        return (0);
    i = 0;
    while (argv[++i] != NULL)
    {
        j = -1;
        while (argv[i][++j] != '\0')
        {
            if (argv[i][j] == '+' && !(argv[i][j + 1] <= '9' && argv[i][j + 1] >= '0'))
                return (0);
            else if (argv[i][j] == '+' && (j != 0 && argv[i][j - 1] != ' '))
                return (0);
            else if (argv[i][j] != ' ' && argv[i][j] != '+' && (argv[i][j] < '0' || argv[i][j] > '9'))
                return (0);
        }
    }
    return (1);
}

void	get_args(char **argv)
{
	int		philo_num;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		must_eat_num;
	t_list	args;
	
	args = NULL;
	while (++argv)
		ft_atio(*argv, args);
	if (ft_lstsize(args) < 4 || ft_lstsize(args) > 5)
		exit_program(args);
	
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		must_eat_num;

	must_eat_num = -1;
	if (!arg_check(argv, argc) || ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1 || ft_atoi(argv[3]) == -1
		|| ft_atoi(argv[4]) || (argc == 6 && ft_atoi(argv[5]) == -1)) 
	{
        write(2, "Enter valid arguments!\n", 23);
        return (1);
    }
	if (argc == 6)
		must_eat_num = ft_atoi(argv[5]);

	get_args(argv);
}

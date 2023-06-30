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

void	ft_atoi(char *str, t_list **a) // need max min check also negative values arent acceptable
{
	long long		result;

	while (*str != '\0')
	{
		result = 0;
		while (*str == 32 || (*str >= 9 && *str <= 13))
			str++;
		if (*str != '\0')
		{
			if (*str == '-' || *str == '+')
				str++;
			while (*str >= '0' && *str <= '9')
			{
				result = result * 10 + *str - 48;
				str++;
			}
			while (*str == 32 || (*str >= 9 && *str <= 12))
				str++;
				if (result > MAX_INT)
					exit_program(a, NULL);
			ft_lstadd_back(a, ft_lstnew(result));
		}
	}
}

int	arg_check(char **argv) // arg count and non numeric/negative parameters check
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i] != NULL)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] == '+')
				&& !(argv[i][j + 1] <= '9' && argv[i][j + 1] >= '0'))
				return (0);
			else if (argv[i][j] == '+' && (j != 0 && argv[i][j - 1] != ' '))
				return (0);
			else if (argv[i][j] != ' ' && argv[i][j] != '+'
					&& (argv[i][j] < '0' || argv[i][j] > '9'))
				return (0);
		}
	}
	if (i < 6 || i > 7)
		return (0);
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
	if (!arg_check(argv))
			return (1);
	get_args(argv);
}

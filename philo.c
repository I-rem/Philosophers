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

void	ft_atoi(char *str, t_list **a)
{
	long		result;
	long		sign;

	while (*str != '\0')
	{
		result = 0;
		sign = 1;
		while (*str == 32 || (*str >= 9 && *str <= 13))
			str++;
		if (*str != '\0')
		{
			if (*str == '-')
				sign *= -1;
			if (*str == '-' || *str == '+')
				str++;
			while (*str >= '0' && *str <= '9')
			{
				result = result * 10 + *str - 48;
				str++;
			}
			while (*str == 32 || (*str >= 9 && *str <= 12))
				str++;
			ft_lstadd_back(a, ft_lstnew(result * sign));
		}
	}
}

int	arg_check(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i] != NULL)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if ((argv[i][j] == '-' || argv[i][j] == '+')
				&& !(argv[i][j + 1] <= '9' && argv[i][j + 1] >= '0'))
				return (0);
			else if ((argv[i][j] == '-' || argv[i][j] == '+') &&
					(j != 0 && argv[i][j - 1] != ' '))
				return (0);
			else if (argv[i][j] != ' ' && argv[i][j] != '-' && argv[i][j] != '+'
					&& (argv[i][j] < '0' || argv[i][j] > '9'))
				return (0);
		}
	}
	return (1);
}

void	get_args(int argc, char **argv)
{
	int	philo_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	must_eat_num;
	
}

int	main(int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (1);
}

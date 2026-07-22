/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:14:07 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:14:08 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	checkduplicates(t_env *env, int num)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (env->arr_a[i] == num)
			return (0);
		i++;
	}
	return (1);
}

static int	append_number(t_env *env, int num)
{
	int	*new_a;
	int	*new_idx;
	int	i;

	if (checkduplicates(env, num) == 0)
		return (0);
	new_a = malloc(sizeof(int) * (env->size + 1));
	new_idx = malloc(sizeof(int) * (env->size + 1));
	if (!new_a || !new_idx)
		return (0);
	i = -1;
	while (++i < env->size)
	{
		new_a[i] = env->arr_a[i];
		new_idx[i] = env->idx_a[i];
	}
	new_a[env->size] = num;
	free(env->arr_a);
	free(env->idx_a);
	env->arr_a = new_a;
	env->idx_a = new_idx;
	env->size++;
	return (1);
}

static int	extract_numbers(char *str, t_env *env)
{
	int		i;
	int		error;
	long	num;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			break ;
		error = 0;
		num = ft_atol(&str[i], &error);
		if (error || num < -2147483648 || num > 2147483647)
			return (0);
		if (!append_number(env, (int)num))
			return (0);
		if ((str[i] == '-' || str[i] == '+') && !(ft_isdigit(str[i - 1])))
			i++;
		while (ft_isdigit(str[i]))
			i++;
	}
	return (1);
}

static int	check_and_set_flag(char *arg, t_env *env)
{
	if (ft_strcmp(arg, "--bench") == 0)
		return (env->bench_mode = 1);
	if (ft_strcmp(arg, "--adaptive") == 0)
		return (env->strat = STRAT_ADAPTIVE, 1);
	if (ft_strcmp(arg, "--simple") == 0)
		return (env->strat = STRAT_SIMPLE, 1);
	if (ft_strcmp(arg, "--complex") == 0)
		return (env->strat = STRAT_COMPLEX, 1);
	if (ft_strcmp(arg, "--medium") == 0)
		return (env->strat = STRAT_MEDIUM, 1);
	return (0);
}

int	parse_arguments(int argc, char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_and_set_flag(argv[i], env) && !extract_numbers(argv[i], env))
			return (0);
		i++;
	}
	if (env->size > 0)
	{
		env->arr_b = malloc(sizeof(int) * env->size);
		env->idx_b = malloc(sizeof(int) * env->size);
		if (!env->arr_b || !env->idx_b)
			return (0);
	}
	env->top_a = 0;
	env->top_b = env->size;
	return (1);
}

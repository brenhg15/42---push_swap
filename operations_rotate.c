/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:18:46 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:18:50 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	ra(t_env *env)
{
	int	tmp;
	int	tmp_idx;
	int	i;

	if (env->size - env->top_a < 2)
		return ;
	tmp = env->arr_a[env->top_a];
	tmp_idx = env->idx_a[env->top_a];
	i = env->top_a;
	while (i < env->size - 1)
	{
		env->arr_a[i] = env->arr_a[i + 1];
		env->idx_a[i] = env->idx_a[i + 1];
		i++;
	}
	env->arr_a[env->size - 1] = tmp;
	env->idx_a[env->size - 1] = tmp_idx;
	write(1, "ra\n", 3);
	env->bench.ra++;
	env->bench.total_ops++;
}

void	rb(t_env *env)
{
	int	tmp;
	int	tmp_idx;
	int	i;

	if (env->size - env->top_b < 2)
		return ;
	tmp = env->arr_b[env->top_b];
	tmp_idx = env->idx_b[env->top_b];
	i = env->top_b;
	while (i < env->size - 1)
	{
		env->arr_b[i] = env->arr_b[i + 1];
		env->idx_b[i] = env->idx_b[i + 1];
		i++;
	}
	env->arr_b[env->size - 1] = tmp;
	env->idx_b[env->size - 1] = tmp_idx;
	write(1, "rb\n", 3);
	env->bench.rb++;
	env->bench.total_ops++;
}

void	rr(t_env *env)
{
	int	tmp;
	int	i;

	if (env->size - env->top_a >= 2 && env->size - env->top_b >= 2)
	{
		tmp = env->arr_a[env->top_a];
		i = env->top_a;
		while (i++ < env->size - 1)
			env->arr_a[i - 1] = env->arr_a[i];
		env->arr_a[env->size - 1] = tmp;
		tmp = env->arr_b[env->top_b];
		i = env->top_b;
		while (i++ < env->size - 1)
			env->arr_b[i - 1] = env->arr_b[i];
		env->arr_b[env->size - 1] = tmp;
	}
	write(1, "rr\n", 3);
	env->bench.rr++;
	env->bench.total_ops++;
}

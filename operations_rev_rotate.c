/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rev_rotate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:13:45 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:13:46 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	rra(t_env *env)
{
	int	tmp;
	int	tmp_idx;
	int	i;

	if (env->size - env->top_a < 2)
		return ;
	tmp = env->arr_a[env->size - 1];
	tmp_idx = env->idx_a[env->size - 1];
	i = env->size - 1;
	while (i > env->top_a)
	{
		env->arr_a[i] = env->arr_a[i - 1];
		env->idx_a[i] = env->idx_a[i - 1];
		i--;
	}
	env->arr_a[env->top_a] = tmp;
	env->idx_a[env->top_a] = tmp_idx;
	write(1, "rra\n", 4);
	env->bench.rra++;
	env->bench.total_ops++;
}

void	rrb(t_env *env)
{
	int	tmp;
	int	tmp_idx;
	int	i;

	if (env->size - env->top_b < 2)
		return ;
	tmp = env->arr_b[env->size - 1];
	tmp_idx = env->idx_b[env->size - 1];
	i = env->size - 1;
	while (i > env->top_b)
	{
		env->arr_b[i] = env->arr_b[i - 1];
		env->idx_b[i] = env->idx_b[i - 1];
		i--;
	}
	env->arr_b[env->top_b] = tmp;
	env->idx_b[env->top_b] = tmp_idx;
	write(1, "rrb\n", 4);
	env->bench.rrb++;
	env->bench.total_ops++;
}

void	rrr(t_env *env)
{
	int	tmp;
	int	i;

	if (env->size - env->top_a >= 2 && env->size - env->top_b >= 2)
	{
		tmp = env->arr_a[env->size - 1];
		i = env->size - 1;
		while (i > env->top_a)
		{
			env->arr_a[i] = env->arr_a[i - 1];
			i--;
		}
		env->arr_a[env->top_a] = tmp;
		tmp = env->arr_b[env->size - 1];
		i = env->size - 1;
		while (i > env->top_b)
		{
			env->arr_b[i] = env->arr_b[i - 1];
			i--;
		}
		env->arr_b[env->top_b] = tmp;
	}
	write(1, "rrr\n", 4);
	env->bench.rrr++;
	env->bench.total_ops++;
}

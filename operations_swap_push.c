/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap_push.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:13:57 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:13:58 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	sa(t_env *env)
{
	int	tmp;

	if (env->size - env->top_a < 2)
		return ;
	tmp = env->arr_a[env->top_a];
	env->arr_a[env->top_a] = env->arr_a[env->top_a + 1];
	env->arr_a[env->top_a + 1] = tmp;
	tmp = env->idx_a[env->top_a];
	env->idx_a[env->top_a] = env->idx_a[env->top_a + 1];
	env->idx_a[env->top_a + 1] = tmp;
	write(1, "sa\n", 3);
	env->bench.sa++;
	env->bench.total_ops++;
}

void	sb(t_env *env)
{
	int	tmp;

	if (env->size - env->top_b < 2)
		return ;
	tmp = env->arr_b[env->top_b];
	env->arr_b[env->top_b] = env->arr_b[env->top_b + 1];
	env->arr_b[env->top_b + 1] = tmp;
	tmp = env->idx_b[env->top_b];
	env->idx_b[env->top_b] = env->idx_b[env->top_b + 1];
	env->idx_b[env->top_b + 1] = tmp;
	write(1, "sb\n", 3);
	env->bench.sb++;
	env->bench.total_ops++;
}

void	ss(t_env *env)
{
	int	tmp;

	if (env->size - env->top_a >= 2 && env->size - env->top_b >= 2)
	{
		tmp = env->arr_a[env->top_a];
		env->arr_a[env->top_a] = env->arr_a[env->top_a + 1];
		env->arr_a[env->top_a + 1] = tmp;
		tmp = env->idx_a[env->top_a];
		env->idx_a[env->top_a] = env->idx_a[env->top_a + 1];
		env->idx_a[env->top_a + 1] = tmp;
		tmp = env->arr_b[env->top_b];
		env->arr_b[env->top_b] = env->arr_b[env->top_b + 1];
		env->arr_b[env->top_b + 1] = tmp;
		tmp = env->idx_b[env->top_b];
		env->idx_b[env->top_b] = env->idx_b[env->top_b + 1];
		env->idx_b[env->top_b + 1] = tmp;
	}
	write(1, "ss\n", 3);
	env->bench.ss++;
	env->bench.total_ops++;
}

void	pa(t_env *env)
{
	if (env->top_b >= env->size)
		return ;
	env->top_a--;
	env->arr_a[env->top_a] = env->arr_b[env->top_b];
	env->idx_a[env->top_a] = env->idx_b[env->top_b];
	env->top_b++;
	write(1, "pa\n", 3);
	env->bench.pa++;
	env->bench.total_ops++;
}

void	pb(t_env *env)
{
	if (env->top_a >= env->size)
		return ;
	env->top_b--;
	env->arr_b[env->top_b] = env->arr_a[env->top_a];
	env->idx_b[env->top_b] = env->idx_a[env->top_a];
	env->top_a++;
	write(1, "pb\n", 3);
	env->bench.pb++;
	env->bench.total_ops++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:14:31 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:14:32 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	get_max_bits(int size)
{
	int	max_num;
	int	max_bits;

	max_num = size - 1;
	max_bits = 0;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

void	sort_complex(t_env *env)
{
	int	max_bits;
	int	bit;
	int	i;
	int	size_a;

	max_bits = get_max_bits(env->size);
	bit = 0;
	while (bit < max_bits)
	{
		size_a = env->size - env->top_a;
		i = 0;
		while (i < size_a)
		{
			if (((env->idx_a[env->top_a] >> bit) & 1) == 1)
				ra(env);
			else
				pb(env);
			i++;
		}
		while (env->top_b < env->size)
			pa(env);
		bit++;
	}
}

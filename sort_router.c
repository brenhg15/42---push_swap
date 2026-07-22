/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_router.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:14:57 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:14:58 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	execute_sorting_strategy(t_env *env)
{
	if (env->size - env->top_a <= 1 || env->bench.disorder_score == 0.0)
		return ;
	if (env->size >= 3 && env->size <= 5)
		env->strat = STRAT_SIMPLE;
	else if (env->strat == STRAT_ADAPTIVE)
	{
		if (env->bench.disorder_score < 0.20)
			env->strat = STRAT_SIMPLE;
		else if (env->bench.disorder_score <= 0.50)
			env->strat = STRAT_MEDIUM;
		else
			env->strat = STRAT_COMPLEX;
	}
	if (env->strat == STRAT_SIMPLE)
		sort_simple(env);
	else if (env->strat == STRAT_MEDIUM)
		sort_medium(env);
	else if (env->strat == STRAT_COMPLEX)
		sort_complex(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:13:14 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:13:16 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void	init_environment(t_env *env)
{
	env->arr_a = NULL;
	env->idx_a = NULL;
	env->arr_b = NULL;
	env->idx_b = NULL;
	env->size = 0;
	env->top_a = 0;
	env->top_b = 0;
	env->bench_mode = 0;
	env->strat = STRAT_ADAPTIVE;
	env->bench.total_ops = 0;
	env->bench.sa = 0;
	env->bench.sb = 0;
	env->bench.ss = 0;
	env->bench.pa = 0;
	env->bench.pb = 0;
	env->bench.ra = 0;
	env->bench.rb = 0;
	env->bench.rr = 0;
	env->bench.rra = 0;
	env->bench.rrb = 0;
	env->bench.rrr = 0;
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
		return (0);
	init_environment(&env);
	if (!parse_arguments(argc, argv, &env))
		exit_error(&env);
	calculate_disorder_score(&env);
	execute_sorting_strategy(&env);
	display_benchmarks1(&env);
	display_benchmarks2(&env);
	free_environment(&env);
	return (0);
}

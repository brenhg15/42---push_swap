#include "push_swap.h"

static int	find_min_pos(t_env *env)
{
	int	i;
	int	min_idx;

	i = env->top_a;
	min_idx = i;
	while (i < env->size)
	{
		if (env->arr_a[i] < env->arr_a[min_idx])
			min_idx = i;
		i++;
	}
	return (min_idx);
}

static void	sort_three(t_env *env)
{
	int	a;
	int	b;
	int	c;

	a = env->arr_a[env->top_a];
	b = env->arr_a[env->top_a + 1];
	c = env->arr_a[env->top_a + 2];
	if (a > b && b < c && a < c)
		sa(env);
	else if (a > b && b > c)
	{
		sa(env);
		rra(env);
	}
	else if (a > b && b < c && a > c)
		ra(env);
	else if (a < b && b > c && a < c)
	{
		sa(env);
		ra(env);
	}
	else if (a < b && b > c && a > c)
		rra(env);
}

static void	push_min_to_b(t_env *env)
{
	int	min_pos;

	while (env->size - env->top_a > 3)
	{
		min_pos = find_min_pos(env);
		while (env->top_a != min_pos)
		{
			if (min_pos <= env->top_a + (env->size - env->top_a) / 2)
				ra(env);
			else
				rra(env);
			min_pos = find_min_pos(env);
		}
		pb(env);
	}
}

static void	sort_large_selection(t_env *env)
{
	int	min_pos;

	while (env->top_a < env->size)
	{
		min_pos = find_min_pos(env);
		while (env->top_a != min_pos)
		{
			if (min_pos <= env->top_a + (env->size - env->top_a) / 2)
				ra(env);
			else
				rra(env);
			min_pos = find_min_pos(env);
		}
		pb(env);
	}
	while (env->top_b < env->size)
		pa(env);
}

void	sort_simple(t_env *env)
{
	int	count;

	count = env->size - env->top_a;
	if (count <= 5)
	{
		if (count == 2 && env->arr_a[env->top_a] > env->arr_a[env->top_a + 1])
			sa(env);
		push_min_to_b(env);
		sort_three(env);
		while (env->top_b < env->size)
			pa(env);
	}
	else
		sort_large_selection(env);
}

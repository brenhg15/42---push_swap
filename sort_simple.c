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

static void	merge_back_to_a(t_env *env)
{
	while (env->top_b < env->size)
	{
		while (env->idx_a[env->top_a] < env->idx_b[env->top_b] 
			&& env->idx_a[env->size - 1] > env->idx_a[env->top_a])
			ra(env);
		pa(env);
		if (env->idx_a[env->top_a] > env->idx_a[env->top_a + 1])
			sa(env);
	}
	while (env->idx_a[env->top_a] > env->idx_a[env->size - 1])
		rra(env);
}

static void	sort_nearly_sorted(t_env *env)
{
	int	i;
	int	initial_count;

	initial_count = env->size - env->top_a;
	i = 0;
	while (i < initial_count - 1)
	{
		if (env->idx_a[env->top_a] > env->idx_a[env->top_a + 1])
			pb(env);
		else
			ra(env);
		i++;
	}
	merge_back_to_a(env);
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
		sort_nearly_sorted(env);
}

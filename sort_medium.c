#include "push_swap.h"

static int	find_max_pos_b(t_env *env)
{
	int	i;
	int	max_idx;

	i = env->top_b;
	max_idx = i;
	while (i < env->size)
	{
		if (env->idx_b[i] > env->idx_b[max_idx])
			max_idx = i;
		i++;
	}
	return (max_idx);
}

static void	push_back_to_a(t_env *env)
{
	int	max_pos;
	int	mid;

	while (env->top_b < env->size)
	{
		max_pos = find_max_pos_b(env);
		mid = env->top_b + (env->size - env->top_b) / 2;
		while (env->top_b != max_pos)
		{
			if (max_pos <= mid)
				rb(env);
			else
				rrb(env);
			max_pos = find_max_pos_b(env);
		}
		pa(env);
	}
}

void	sort_medium(t_env *env)
{
	int	i;
	int	chunk;

	i = 0;
	if (env->size <= 100)
		chunk = 15;
	else
		chunk = 30;
	while (env->top_a < env->size)
	{
		if (env->idx_a[env->top_a] <= i)
		{
			pb(env);
			rb(env);
			i++;
		}
		else if (env->idx_a[env->top_a] <= i + chunk)
		{
			pb(env);
			i++;
		}
		else
			ra(env);
	}
	push_back_to_a(env);
}

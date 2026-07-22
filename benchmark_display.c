/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhernand <bhernand@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 17:12:38 by bhernand          #+#    #+#             */
/*   Updated: 2026/07/02 17:12:41 by bhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

static void	ft_putdouble_percent_fd(double score, int fd)
{
	int	pct_whole;
	int	pct_frac;

	pct_whole = (int)(score * 100);
	pct_frac = (int)((score * 100 - pct_whole) * 100);
	if (pct_frac < 0)
		pct_frac = -pct_frac;
	ft_putnbr_fd(pct_whole, fd);
	ft_putstr_fd(".", fd);
	if (pct_frac < 10)
		ft_putstr_fd("0", fd);
	ft_putnbr_fd(pct_frac, fd);
	ft_putstr_fd("%\n", fd);
}

void	display_benchmarks1(t_env *env)
{
	if (!env->bench_mode)
		return ;
	ft_putstr_fd("[bench] disorder  : ", 2);
	ft_putdouble_percent_fd(env->bench.disorder_score, 2);
	ft_putstr_fd("[bench] strategy  : ", 2);
	if (env->strat == STRAT_SIMPLE)
		ft_putstr_fd("Simple — O(n²)\n", 2);
	else if (env->strat == STRAT_MEDIUM)
		ft_putstr_fd("Medium — O(n·√n)\n", 2);
	else if (env->strat == STRAT_COMPLEX)
		ft_putstr_fd("Complex — O(n·log n)\n", 2);
	ft_putstr_fd("[bench] total ops : ", 2);
	ft_putnbr_fd(env->bench.total_ops, 2);
	ft_putstr_fd("\n", 2);
}

void	display_benchmarks2(t_env *env)
{
	if (!env->bench_mode)
		return ;
	put_field("[bench] sa:", env->bench.sa, 2);
	put_field("  sb:", env->bench.sb, 2);
	put_field("  ss:", env->bench.ss, 2);
	put_field("  pa:", env->bench.pa, 2);
	put_field("  pb:", env->bench.pb, 2);
	put_field("\n[bench] ra:", env->bench.ra, 2);
	put_field("  rb:", env->bench.rb, 2);
	put_field("  rr:", env->bench.rr, 2);
	put_field("  rra:", env->bench.rra, 2);
	put_field("  rrb:", env->bench.rrb, 2);
	put_field("  rrr:", env->bench.rrr, 2);
	ft_putstr_fd("\n", 2);
}

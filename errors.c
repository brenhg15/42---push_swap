/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiakono <mdiakono@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:46:16 by mdiakono          #+#    #+#             */
/*   Updated: 2026/07/06 00:00:00 by mdiakono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	put_field(char *label, int value, int fd)
{
	ft_putstr_fd(label, fd);
	ft_putnbr_fd(value, fd);
}

void	free_environment(t_env *env)
{
	if (env->arr_a)
		free(env->arr_a);
	if (env->idx_a)
		free(env->idx_a);
	if (env->arr_b)
		free(env->arr_b);
	if (env->idx_b)
		free(env->idx_b);
}

void	exit_error(t_env *env)
{
	if (env)
		free_environment(env);
	write(STDERR_FILENO, ERROR_MSG, ft_strlen(ERROR_MSG));
	exit(EXIT_FAILURE);
}

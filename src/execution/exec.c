/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:15:52 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/23 17:55:46 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// check input
void	ft_check_exec_input(t_cmd_node *cmd)
{
	t_cmd_node	*temp;
	
	temp = cmd;
	
	while(temp)
	{
		

		temp = temp->next;
	}

}


void	ft_redir_init(char *infile, char *out_file)
{
	opene



int	ft_lstsize(t_cmd_node *lst)
{
	int			size;
	t_cmd_node	*ptr;

	if (lst == NULL)
		return (0);
	ptr = lst;
	size = 0;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

int	ft_files_check(t_cmd_node *cmd)
{
	if ()

	return (0);
}


// "input == to read from it" mode, we send to function 0
//  "out == write to it" mode , we send to funciton 1
int	ft_open_file(char *file, int mode)
{
	int	res;

	if (mode == 0)
		res = open(file, O_RDONLY, 0777);
	if (mode == 1)
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (res);
}

// initialisation of pipes


// initialisation of forks
int	fork_init(t_cmd_node cmd1);



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.x.free_free_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:02:19 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 18:41:40 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* to be freed at end of program runtime */

// 0.2.
// HISTORY		void rl_clear_history(void)
// PROMPT		free(prompt)



/* to be freed at end of pipeline execution */

// 2.1.
// CMD-STR-ARR		free(arr) - from ft_split
// LINKED LIST		free_stack

// 2.2.
// ARGS-ARRAY		free_stack

// 3.1. && 3.2.
// STRINGS (for args array)	freed with 2.2. free stack



// -----------------------------------------------------
// adjust to cmd_list
// void	free_stack(t_stack **stack)
// {
// 	t_node	*tmp;

// 	if (!stack || !*stack)
// 		return ;
// 	while (*stack)
// 	{
// 		tmp = (*stack)->next;
// 		free(*stack);
// 		*stack = tmp;
// 	}
// 	*stack = NULL;
// }

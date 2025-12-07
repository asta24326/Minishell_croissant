/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 17:26:58 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/07 18:25:47 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int main(void)
{
    t_shell shell;
    
    // 1. Заполняем shell
    shell.env = (char *[]){
        "USER=aidarsharafeev",
        "PATH=/usr/bin:/bin",
        NULL
    };
    shell.exit_status = 42;
    shell.shell_pid = 12345;
    shell.cmd = NULL;
    
    // 2. Создаем команду echo
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->args = malloc(sizeof(char *) * 6);
    cmd->args[0] = ft_strdup("echo");
    cmd->args[1] = ft_strdup("$USER");
    cmd->args[2] = ft_strdup("'$USER'");
	cmd->args[3] = ft_strdup("$$");
	cmd->args[4] = ft_strdup("$?");
    cmd->args[5] = NULL;
    cmd->builtin = true;
    cmd->redirs = NULL;
    cmd->next = NULL;
    
    shell.cmd = cmd;
    
    // 3. Печатаем до расширения
    printf("BEFORE expansion:\n");
    for (int i = 0; cmd->args[i]; i++)
        printf("  args[%d] = '%s'\n", i, cmd->args[i]);
    
    // 4. Выполняем расширение
    printf("\nCalling ft_expand_all_args()...\n");
    ft_expand_all_args(&shell);
    
    // 5. Печатаем после расширения
    printf("\nAFTER expansion:\n");
    for (int i = 0; cmd->args[i]; i++)
        printf("  args[%d] = '%s'\n", i, cmd->args[i]);
    
    // 6. Очистка
    for (int i = 0; cmd->args[i]; i++)
        free(cmd->args[i]);
    free(cmd->args);
    free(cmd);
    
    return 0;
}
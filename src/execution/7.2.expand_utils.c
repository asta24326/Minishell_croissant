/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.2.expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:31:01 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/01/08 00:02:11 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_get_var_name_len(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

bool	ft_is_valid_var_char(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*ft_expand_env_var(t_shell *shell, char *str, int len)
{
	char	*var_name;
	char	*var_value;

	printf("passed= [%s]\n", str);
	var_name = ft_substr(str, 1, len);
	if (!var_name)
		return (NULL);
	printf("result var_name: [%s]\n", var_name);
	var_value = ft_getenv(shell->env, var_name);
	printf("========var_after expansion: [%s]\n", var_value);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

static int	get_var_len_expanded(char *str)
{
	int		len;

	len = 1;
	printf("str passed: %s\n", str);
	if (str[len] == '$')
		return (1);
	else 
		while (str[len] && !is_whitespace(str[len]) && (str[len] != '$') && !is_quote(str[len]))
			len++;
	printf("var_len: %i\n", len - 1);
	return (len - 1);
}

char	*get_expand_str(t_shell *shell, char *str, char *unexp_str, int flag)
{
	char	*result;
	char	*expanded_var;
	int		index;

	index = 0;
	if (str[index + 1] && (str[index + 1] == ' ' || str[index + 1] == '"'))
		expanded_var = ft_strdup("$");
	else if (str[index + 1] && str[index + 1] == '?')
		expanded_var = ft_itoa(shell->exit_status);
	else if (str[index + 1] && str[index + 1] == '$')
		expanded_var = ft_itoa(shell->shell_pid);
	else if (str[index + 1] && ft_is_valid_var_char(str[index + 1]))
	{
		index = get_var_len_expanded(&str[index]);
		expanded_var = ft_expand_env_var(shell, str, index);
	}
	if (unexp_str != NULL)
	{
		result = ft_strjoin(unexp_str, expanded_var);
		if (flag == 1)
			free (unexp_str);
		if (!result)
			return (ft_putstr_fd("strjoin failed", 2), NULL);
	}
	else
		result = ft_strdup(expanded_var);
	return (free(expanded_var), result);
}

char	*get_unexpand_str(char *str, char *exp_str)
{
	char	*result;
	char	*temp;
	int		index;

	index = 0;
	while (str[index] != '"' && str[index] != '$')
		index++;
	temp = ft_substr(str, 0, index);
	if (exp_str && *exp_str)
	{
		result = ft_strjoin(exp_str, temp);
		if (!result)
			return (ft_putstr_fd("strjoin failed", 2), NULL);
	}
	else
		result = ft_strdup(temp);
	return (free(temp), result);
}

char	*ft_expand_dquotes_str(t_shell *shell, char *str)
{
	char	*temp;
	char	*temp2;
	int		i;
	int		len;
	int		last_opt;

	i = 1;
	len = 0;
	last_opt = 0;
	temp = NULL;
	temp2 = NULL;
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			len = get_var_len_expanded(&str[i]);
			if (last_opt == 1)
				temp = get_expand_str(shell, &str[i], temp, 1);
			else
				temp = get_expand_str(shell, &str[i], temp2, 2);
			i += len + 1;
			free(temp2);
			last_opt = 1;
		}
		else
		{
			temp2 = get_unexpand_str(&str[i], temp);
			free(temp);
			last_opt = 2;
			while (str[i] != '"' && str[i] != '$')
				i++;
		}
	}
	if (last_opt == 1)
		return (temp);
	return (temp2);
}

char	*ft_patch_with_dquotes(char *str)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin("\"", str);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, "\"");
	if (!result)
		return (free(temp), NULL);
	free(temp);
	return (result);
}

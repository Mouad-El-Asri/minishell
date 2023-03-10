#include "../include/minishell.h"

extern t_global	*g_global_vars;

void check_access(t_parser **parser, data **data)
{
	if ((*parser)->command[0] && ((*parser)->command[0][0] == '.' || \
			(*parser)->command[0][0] == '/'))
		{
			if (access((*parser)->command[0], F_OK) != 0)
				print_error((*parser)->command[0][0], 1);
			else if (access((*parser)->command[0], X_OK) != 0)
				print_error((*parser)->command[0][0], 2);
		}
		else
		{
			if ((*parser)->command[0])
			{
				(*parser)->command[0] = rap((*parser)->command[0], \
				(*data)->env_arr);
				check_and_adjust(parser);
				if (access((*parser)->command[0], F_OK) != 0)
					print_error((*parser)->command[0][0], 1);
				else if (access((*parser)->command[0], X_OK) != 0)
					print_error((*parser)->command[0][0], 2);
			}
		}
}

void expand_add_sign_check(t_parser **parser, int *flag, int *ret, int *i)
{
	int j;
	int temp;

	j = 0;
	temp = *i;
	while ((*parser)->command[temp])
	{
		while ((*parser)->command[temp][j] && (*parser)->command[temp][j + 1])
		{
			if ((*parser)->command[temp][j] == '+' &&
				(*parser)->command[temp][j + 1] == '=')
			{
				*flag = 1;
				*ret = 1;
				break ;
			}
			j++;
		}
		if (*flag == 1)
			break ;
		(temp)++;
		j = 0;
	}
}

int do_exec_assign_to_multiple(t_vars *vars, t_parser **parser, int *i, int *c, int *temp)
{
			char	*test;

			test = check_if_builtin(parser);
			if (test)
			{
				if (vars->pids[*i + 1] == 0)
				{
					fprintf(stderr, "%d---%d\n", *i, *c);
					dup2(vars->fds_all[*i][0], 0);
					if ((*parser)->next && (*parser)->out == 1)
					{
						dup2(vars->fds_all[*i + 1][1], 1);
						close(vars->fds_all[*i][1]);
						close(vars->fds_all[*i][0]);
						close(vars->fds_all[*i + 1][0]);
					}
					else if ((*parser)->out != 1)
					{
						dup2((*parser)->out, 1);
						close(vars->fds_all[*i][1]);
						close(vars->fds_all[*i][0]);
					}
					else
					{
						close(vars->fds_all[*i][1]);
						close(vars->fds_all[*i][0]);
					}
					while (*temp)
					{
						close(vars->fds_all[*i - *temp][1]);
						close(vars->fds_all[*i - *temp][0]);
						(*temp)--;
					}
					*temp = *c;
					handle_builtins(parser, test, &vars->env, &vars->export);
				}
				return 1;
			}
			return 0;
}

void expand_connect_and_handle(t_parser **parser, t_node **env, t_node **export, data **data)
{
	char *ret;

	if (ft_lstsize(*parser) == 1)
	{
		ret = check_if_builtin(parser);
		if (ret)
		{
			handle_builtins(parser, ret, env, export);
			(*parser) = (*parser)->next;
		}
		else
		{
			handle_single_command(parser, data);
			(*parser) = (*parser)->next;
		}
	}
}
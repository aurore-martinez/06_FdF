/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:40:07 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 15:40:34 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	error_message(char *msg, int mode)
{
	if (mode == 0)
		perror(msg);
	else
		write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int	word_count(char *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

/* i = 2 pour skip "0x" */
int	ft_atoi_base(char *str, int base)
{
	int	result;
	int	value;
	int	i;

	result = 0;
	i = 0;
	if (!str)
		return (0);
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = str[i] - 'A' + 10;
		else
			break ;
		if (value >= base)
			break ;
		result = result * base + value;
		i++;
	}
	return (result);
}

void	show_help(void)
{
	ft_putstr_fd("\nUtilisation : ./fdf [fichier.fdf]\n\n", 1);
	ft_putstr_fd("Contrôles :\n", 1);
	ft_putstr_fd("  Flèches   Déplacer la vue\n", 1);
	ft_putstr_fd("  +/-       Zoom avant/arrière\n", 1);
	ft_putstr_fd("  1/2       Augmenter/Réduire z_scale / la hauteur\n", 1);
	ft_putstr_fd("  9/0       Augmenter/Réduire tile_size\n", 1);
	ft_putstr_fd("  QWERTY    Changer les couleurs (Rouge, Vert, Bleu...)\n", 1);
	ft_putstr_fd("  ASDFGH    Changer les couleurs (Blanc, Orange...)\n", 1);
	ft_putstr_fd("  ESC       Quitter le programme\n", 1);
	ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 10:24:20 by arapaill          #+#    #+#             */
/*   Updated: 2020/10/06 10:43:44 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void    error_manager(int error)
{
    if (error == 1)
        ft_putstr_fd("MAP ERROR \n", 1);
    else if (error == 2)
        ft_putstr_fd("TEXTURES ERROR \n", 1);
    else if  (error == 3)
        ft_putstr_fd("MALLOC ERROR\n", 1);
    exit (-1);
}
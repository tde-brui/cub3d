/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: stijn <stijn@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 14:12:41 by stijn         #+#    #+#                 */
/*   Updated: 2024/02/19 00:20:42 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define CUB3D_ERRMAX 10

//MLX error codes go from 0 to 16, thus Cub3d error codes start at 17
typedef enum cub3d_errno
{
    MALLOC_FAIL = 17,
    PNG_FAIL,
    INCORRECT_NUM_ARG,
	INVALID_CHAR_MAP,
	FILE_ERROR,
    MULTIPLE_START_POS,
	MAP_NOT_CLOSED,
    NO_START_DIR,
    MAP_NOT_LAST,
    NOT_CUB_FILE,
} cub3d_errno_t;

void	exit_error(int error_code);

#endif
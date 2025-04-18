/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_points_v1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:19:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/03/06 10:22:00 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// display_points.c

#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../mlx_macos/mlx.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define ISO_ANGLE 0.523599 // 30 degrés en radians
#define WHITE 0xFFFFFF

typedef struct
{
	double	x;
	double	y;
	double	z;
} Point3D;

typedef struct
{
	int	x;
	int	y;
} Point2D;

typedef struct
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
} MLX;

// Fonction de projection isométrique
Point2D	iso_projection(Point3D p)
{
	Point2D	result;

	result.x = (p.x - p.y) * cos(ISO_ANGLE) * 100 + WIN_WIDTH / 2;
	result.y = (p.x + p.y) * sin(ISO_ANGLE) * 100 - p.z * 10 + WIN_HEIGHT / 2;
	return (result);
}

// Fonction pour afficher un pixel sur l'image
void put_pixel(MLX *mlx, int x, int y, int color) {
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT) {
        char *dst = mlx->data + (y * mlx->size_line + x * (mlx->bpp / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_points(MLX *mlx) {
    Point3D points[4] = {
        {0.0, 0.0, 0.0},
        {1.0, 0.0, 1.0},
        {1.0, 1.0, 2.0},
        {0.0, 1.0, 3.0}
    };

    int i = 0;
    while (i < 4) {
        Point2D projected = iso_projection(points[i]);
        printf("Projection Isométrique :\n3D (%.1f, %.1f, %.1f) -> 2D (%d, %d)\n",
               points[i].x, points[i].y, points[i].z, projected.x, projected.y);

        put_pixel(mlx, projected.x, projected.y, WHITE);
        i++;
    }
}

// Fonction de boucle
int loop_hook(void *param) {
    MLX *mlx = (MLX *)param;

    // On efface l'image précédente
    mlx_clear_window(mlx->mlx, mlx->win);

    // On affiche l'image mise à jour
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

    return (0);
}

int main() {
    MLX mlx;

    // Initialisation MinilibX
    mlx.mlx = mlx_init();
    if (!mlx.mlx) {
        printf("Erreur d'initialisation de MinilibX\n");
        return (1);
    }

    mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Isometric Projection");
    if (!mlx.win) {
        printf("Erreur de création de la fenêtre\n");
        return (1);
    }

    mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!mlx.img) {
        printf("Erreur de création de l'image\n");
        return (1);
    }

    mlx.data = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line, &mlx.endian);

    // Dessin des points
    draw_points(&mlx);

    // Boucle MinilibX
    mlx_loop_hook(mlx.mlx, loop_hook, &mlx);
    mlx_loop(mlx.mlx);

    return (0);
}

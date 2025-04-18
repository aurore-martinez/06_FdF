#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    if (!mlx)
    {
        printf("Erreur d'initialisation de MinilibX\n");
        return (1);
    }
    win = mlx_new_window(mlx, 800, 600, "Test Window");
    if (!win)
    {
        printf("Erreur de création de la fenêtre\n");
        return (1);
    }

    mlx_pixel_put(mlx, win, 400, 300, 0xFFFFFF);
    mlx_loop(mlx);
    return (0);
}

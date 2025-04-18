#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    // Initialisation de Minilibx
    void *mlx = mlx_init();
    if (!mlx) {
        printf("Erreur : Initialisation de mlx échouée\n");
        return (1);
    }

    // Création de la fenêtre
    void *win = mlx_new_window(mlx, 800, 600, "Isometric Projection");
    if (!win) {
        printf("Erreur : Création de la fenêtre échouée\n");
        return (1);
    }

    // Boucle d'événements pour garder la fenêtre ouverte
    mlx_loop(mlx);

    return (0);
}

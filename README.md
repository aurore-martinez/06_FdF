# FdF – Wireframe Viewer 🌄

Projet réalisé dans le cadre de l'école 42. L’objectif est de représenter en projection isométrique un terrain en 3D à partir d’un fichier `.fdf` contenant des altitudes.

## 🛠️ Fonctionnalités principales

- Lecture et parsing de fichiers `.fdf`
- Projection isométrique
- Affichage avec MiniLibX
- Navigation dans la map :
  - Déplacement (flèches directionnelles)
  - Zoom / Dézoom (`+` / `-`)
  - Changement d'échelle Z (`1` / `2`)
  - Ajustement taille des tuiles (`9` / `0`)
- Changement de couleur en temps réel (`Q` à `H`)
- Calcul dynamique de l’échelle Z et des tuiles selon la taille de la map

## 🎨 Bonus

- **Choix de couleurs dynamiques** via le clavier
- **Réactivité améliorée** sur les petites et grandes maps (échelle Z et tuiles ajustées automatiquement)
- **Touches de navigation et interaction claviers personnalisées**

## 📁 Utilisation

```bash
make
./fdf <map.fdf>

make
./test_fdf.sh

## 🎮 Contrôles
Touche	Action
Flèches	Déplacer la vue
+ / -	Zoom / Dézoom
1 / 2	Échelle de hauteur Z +/-
9 / 0	Taille des tuiles +/-
Q à H	Changer de couleurs

🤖 Auteur
Aurore Mignot

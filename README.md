*Ce projet a été réalisé dans le cadre du cursus de 42 par isoulima.*

# so_long

![Language](https://img.shields.io/badge/Language-C-blue)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen)

## Description

so_long est un petit jeu 2D top-down écrit en C, utilisant la bibliothèque
graphique MiniLibX de l'école 42. Le joueur doit collecter tous les objets
présents sur la carte avant de pouvoir atteindre la sortie. Le projet permet
de travailler la gestion d'une fenêtre X11, le chargement de textures, la
boucle d'événements clavier, le parsing et la validation d'un fichier de map,
et la libération propre des ressources allouées.

---

## Instructions

### Compilation

```bash
make
```

Compile la libft, MiniLibX, puis le binaire `so_long`.

```bash
make clean    # supprime les .o
make fclean   # supprime les .o, libft.a et le binaire
make re       # fclean + all
```

### Utilisation

```bash
./so_long maps/showcase.ber
```

Le programme attend un et un seul argument : un fichier `.ber` valide.
Une fois la fenêtre ouverte, le joueur se déplace au clavier.

| Touche | Action |
|---|---|
| `W` / flèche haut | Haut |
| `S` / flèche bas | Bas |
| `A` / flèche gauche | Gauche |
| `D` / flèche droite | Droite |
| `Échap` | Quitter |
| Croix de la fenêtre | Quitter |

À chaque déplacement valide, le compteur de mouvements est affiché dans le shell.

---

## Fonctionnalités

| Élément | Description |
|---------|-------------|
| Lecture de map | `read_map` lit le fichier `.ber` ligne par ligne via `get_next_line` |
| Validation | rectangulaire, entourée de murs, exactement 1 `P` et 1 `E`, au moins 1 `C`, caractères dans `01CEP` |
| Chemin valide | flood fill depuis `P` pour vérifier l'accessibilité de tous les `C` et de `E` |
| Affichage | autotile 16-variants pour le sol selon les voisins orthogonaux (N/E/S/W) |
| Mouvement | WASD et flèches ; le mur (`1`) bloque le déplacement |
| Compteur | nombre de mouvements affiché dans le shell à chaque déplacement |
| Verrouillage de sortie | `E` ne quitte que si tous les `C` ont été collectés |
| Fermeture propre | `Échap` et croix appellent `close_hook` qui libère toute la mémoire |

Format des cartes `.ber` :

| Char | Signification |
|---|---|
| `0` | Espace vide |
| `1` | Mur (rendu en eau) |
| `C` | Collectible (≥ 1) |
| `E` | Sortie (= 1) |
| `P` | Position de départ du joueur (= 1) |

En cas d'erreur, le programme affiche `Error\n` suivi d'un message explicite,
libère toute la mémoire allouée et quitte avec le code 1.

---

## Choix techniques

- **Structure unique `t_game`** contenant la map, le pointeur MLX, les
  pointeurs de fenêtre, les tableaux de textures et les compteurs. Passée par
  pointeur à toutes les fonctions de gameplay.
- **Pointeur file-scope `static t_game *g_game`** dans `main.c` permettant à
  `error_exit` de libérer la mémoire avant `exit(1)` même quand l'erreur
  remonte depuis `parse_map` ou `check_map`. Norm-compliant (`static`).
- **Bitmask 4-neighbor (`floor_mask`)** dans `utils.c` qui retourne un entier
  0–15 selon les murs présents au nord, est, sud, ouest. Sert à indexer les
  16 variants de tile chargés au boot pour faire les transitions herbe/eau
  proprement.
- **Validation en 3 passes** dans `check_map` : `check_walls` (bordures),
  `check_chars` (caractères + comptage P/E/C), `check_path_valid` (flood
  fill récursif sur une copie de la grid).
- **Chargement des textures via `mlx_xpm_file_to_image`** : 1 mur + 16 sols +
  16 variants de joueur + 16 collectibles + 16 sorties = 65 images chargées
  une seule fois au démarrage.
- **Aucune fuite mémoire** vérifiée avec `valgrind --leak-check=full
  --show-leak-kinds=all` sur les arguments invalides, tous les cas de map
  invalide, et la fermeture par `Échap`. Les warnings `libxcb` internes à
  MLX/X11 ne sont pas du user-code.
- **Norme 42** respectée : pas de fonction > 25 lignes, pas de globale
  non-`static`, pas de `printf`/`memcpy`/`strcpy` interdits, headers 42 sur
  tous les fichiers.

---

## Ressources

- Sujet officiel 42 (`en.subject.pdf`)
- Documentation MiniLibX par Harm Smits (harm-smits.github.io/42docs/libs/minilibx)
- Manuel Xlib pour comprendre les events `KeyPress` et `DestroyNotify`
- `man malloc`, `man open`, `man read`
- Tileset Tiny Swords par Pixel Frog (pixelfrog-assets.itch.io/tiny-swords)
  pour les textures (autotile 16-variants extrait de `Tilemap_color1.png`)

---

## AI usage

L'IA a été utilisée pour :

- identifier la structure du tileset Tiny Swords (mapping des 16 variants
  d'autotile dans la grille 9×6 du `Tilemap_color1.png`)
- générer les scripts de conversion PNG → XPM avec aplatissement alpha sur
  fond eau (XPM ne supporte que la transparence 1-bit, donc les bords
  anti-aliasés des PNG deviennent noirs sans pré-traitement)
- structurer ce README

L'implémentation, la logique de validation, le rendu et la compréhension du
code ont été réalisés manuellement.

---

## Auteur

42 Lausanne
Login : isoulima

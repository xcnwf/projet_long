# FUSE filesystem

> **ATTENTION :** CE CODE N'EST PAS UTILISE !

Une idée d'implémentation était d'utiliser FUSE pour créer un système de fichier basique, avec lequel il serait facile d'intéragir.

Malheureusement, le gadget USB `g_mass_storage.ko` sous la distribution standard de linux ne prend que des *block devices*, c'est à dire des blocks continus de mémoire, sur lesquels existent des systèmes de fichier (et c'est l'hote qui traite ces fichiers).

Or, pour réaliser l'attaque, il est nécessaire que l'hote ne présente que très peu (voire aucune si possible) de caractéristiques spéciales (telles un driver pour un système de fichier custom).

Cette idée a donc été abandonnée, le code reste disponible si jamais quelqu'un est intéressé.
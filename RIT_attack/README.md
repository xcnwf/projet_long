# Attaque RIT

The dossier contient (presque) tout ce que nous vaont utilisé pour réaliser l'attaque RIT (ou du moins un preuve de concept semi-pratique*)

**Note** : \**Les apects pratiques seront évoqués lors de la présentation.*

## Structure:

- Le dossier `fuse_filesystem` contient les sources d'un système de fichier modifié pour les besoins de l'attaque. Pour plus d'informations, se référer au README de ce dossier.
- Le fichier `startup.sh` contient les commandes qui doivent être exécutées par la Pi4 lors de son démarrage pour initialiser le comportement USB gagdet (qui est supprimé à chaque démarrage).
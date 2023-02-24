# Attaques par périphériques (projet long)

Ceci est le dépôt des sources ayant été utilisées pour réaliser les démonstrations lors de la présentation du rapport de fin de projet pour le projet long de TLS-SEC du groupe G12.

## Arborescence

### LED Exfiltration

le dossier `LED_exfiltration` contient les sources pour rélaiser l'exfiltration de données via les leds d'un clavier connecté.

C'est une toute petite PoC pour le principe d'utiliser un périphérique comme une partie intégrante d'une attaque (ici, pour récupérer les informations que l'on extrait de la victime.)

### RIT Attack

L'attaque RIT (de l'anglais *Read It Twice*) consiste à tromper l'assomption que font la plupart des systèmes et des développeurs, qui consiste à croire qu'ils ont le controle total sur un périphérique de stockage.
Dès lors, ils estiment que les informations contenues sur celui-ci sont sous le controle **exclusif** du système et qu'il n'y a pas de sources extérieures qui pourraient en changer le contenu.

Il est alors possible de réaliser une attaque TOCTTOU (de l'anglais *Time of Check to Time of Use*) sur un programme présentant une faille de logique.

Pour plus de détails, se référer au [readme de cette partie](./RIT_attack)


####### Réalisé dans le cadre du projet long par le Groupe G12

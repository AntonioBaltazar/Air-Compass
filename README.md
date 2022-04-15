# Air-Compass
Vous découvrirez dans ce projet un système de contrôle du trafic aérien international, une version graphique et console vous est sera proposé. 
L'application se veut intuitive et simple d'utilisation, lancez donc le fichier "Air-compass.exe" et laissez vous guider !

Ce projet à été développé sous __Linux__ et a l'aide de différents langages de programmation :
  - C et C++
  - SQL ( à l'aide de la bibliothèque SQLITE3)
  - Fonctions graphiques de la bibliothèque SDL

## Aperçu 
<img src="Markdown rsc/Terminal_menu.png"/>
### <center> <b> Menu console </b> </center>
<br> </br>   
<img src="Markdown rsc/Graphic_menu.png"/>
<div align="center"><b>Menu Graphique</b></div>
<img src="Markdown rsc/Simulation.png"/>
<div align="center"><b>Simulation</b></div>

## Installation de Ubuntu (Linux)
Ubuntu est une distribution de Linux parfaite pour s'initier à ce nouvel environnement, je vous mets à disposition un super lien du site LeCrabInfo ainsi que le lien de téléchargement de l'image iso et du logiciel Rufus que j'ai utilisé :
> - [Lecrabinfo](https://lecrabeinfo.net/installer-ubuntu-20-04-lts-le-guide-complet.html) 
> - [Image Ubuntu 20.04](https://releases.ubuntu.com/20.04/)
> - [Rufus](https://lecrabeinfo.net/telecharger/rufus)


## Installation de SDL2

La SDL2 est une librairie graphique très simple d'utilisation avec de nombreuses ressources disponibles sur internet.
Pour l'installer, rien de plus simple, suivez le tutoriel de la [documentation officiel Ubuntu](https://doc.ubuntu-fr.org/sdl) 

> - [La doc officielle](https://wiki.libsdl.org/)  
> - [Un petit tuto pour aller plus loin](https://devopssec.fr/category/apprendre-la-sdl-2).

## Installation de SQLite3

SQLite est une librairie C/C++ permettant d'executer des requêtes SQL à une base de données, pour l'installer veuiller suivre le rapide tuto de la [documentation officiel Ubuntu](https://doc.ubuntu-fr.org/sqlite)
> - [La doc officielle](https://www.sqlite.org/docs.html)  
> - [Un tuto pour aller plus loin](https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm).

## Création d'un fichier makefile 

Le fichier Makefile permettra de relier les bibliothèques précédemment installé à notre compliateur, pour l'installer suivez les 4 courtes étapes suivantes :

1. Installer l'extension suivante :
<img src="Markdown rsc/makefile.png"/>

2. Executer le raccourci `ctrl shift p` et selectionner ceci :
 <img src="Markdown rsc/makefile2.png"/>

3. Ensuite taper sur la touche `entrer` et faire le choix suivant :
<img src="Markdown rsc/makefile3.png"/>

4. Le fichier Makefile est crée, il ne reste plus qu'à préciser dans la partie `LDFLAGS` les bibliothèques que vous souhaitez utiliser à l'aide de la commande suivante :
  `-lsqlite3 -lSDL2main -lSDL2_image -lSDL2 -lGL -lGLEW -lSDL2_ttf -lSDL`
  <img src="Markdown rsc/makefile4.png"/>

# INF1070 Été 2020 - Travail pratique 2

**Ce travail est individuel (à faire seul).**

Ce travail porte principalement sur la découverte, l'installation, l'administration et l'utilisation sommaire de [SuiteCRM](https://suitecrm.com/). SuiteCRM est un 
logiciel de [gestion des relations avec la clientèle](https://fr.wikipedia.org/wiki/Gestion_de_la_relation_client)  (*Customer Relationship Management* -- CRM) open source. Il comporte plusieurs modules pour ajouter 
des fonctionnalités à celle déjà disponible dans l'installation de base (core). 
 La procédure d'[installation de suiteCRM](https://docs.suitecrm.com/admin/installation-guide/downloading-installing/) est disponible 
 dans la documentation ([https://docs.suitecrm.com/admin/installation-guide/downloading-installing/](https://docs.suitecrm.com/admin/installation-guide/downloading-installing/)). 
 Cet énoncé explique la procédure à suivre pour installer SuiteCRM à partir du code source. Le 
 but est de s'initier et d'expérimenter certaines tâches d'un administrateur système.
  **Dans le cadre de ce TP, il est strictement interdit d'installer suiteCRM avec un docker 
    ou un  gestionnaire de paquets effectuant toutes manipulations**. 
 
## Instructions générales

- Ce travail permet d'expérimenter quelques tâches effectuées  habituellement par un administrateur système. L'exercice consiste à installer et configurer une application Web avec les prérequis nécessaires. 
  Pour cela, on demande de procéder selon les instructions données dans le présent 
  document.

- Pour faciliter la reproduction des étapes importantes, on vous demande de créer un fichier ­`rapport-tp2.md` 
  selon le modèle fourni avec cet énoncé et d'y mettre les différentes commandes, 
   avec les résultats obtenus ainsi que les réponses à chaque question posée.

- Il faudra également mettre les extraits des fichiers de configuration modifiés dans le rapport `rapport-tp2.md`.


- Le fichier `solution-tp2.sh` devra contenir  les commandes 
  exécutées dans le cadre de ce TP. Dans une certaine mesure, ce fichier fait office 
  d'un programme Shell qu'on pourrait exécuter pour faire automatiquement toutes les activités d'installation. 

- Pour les captures d'écran, privilégiez le format PNG (.png) pour éviter des problèmes d'affichage 
  dans le rapport au format Markdown.

- Certaines commandes données dans l'énoncé peuvent nécessiter l'utilisation de `sudo` pour les exécuter. Notez que si l'on se connecte en tant que root (ex: sur un `container` docker, il n'est pas nécessaire d'utiliser `sudo`).

- Cet énoncé n'a pas vocation à donner toutes les commandes nécessaire à l'installation 
  et/ou la configuration. Il donne 
  plutôt les principales étapes pour guider dans le travail à faire.
  
## Environnement de travail - Configuration initiale

Toutes les applications devront être installés et configurés dans un container docker 
créé selon les spécifications suivantes. La matrice de compatibilité est disponible 
sur le lien [https://docs.suitecrm.com/admin/compatibility-matrix/](https://docs.suitecrm.com/admin/compatibility-matrix/). 
Pour cette session, nous installerons SuiteCRM 7.11.15.

###  Container docker - Ubuntu 20.04

**L'utilisation de cet environnement est obligatoire.**

- Un [`container`](https://www.docker.com/resources/what-container) est une unité standard contenant l'installation minimale (librairies, paquets, configuration, etc.) nécessaire pour faire fonctionner une application. Dans ce TP, un `container` docker pourra être utilisé comme une machine Linux (terminal seulement - pas d'environnement graphique).
- Pour travailler avec cet environnement, il faut avoir [installé Docker](https://docs.docker.com/install/). (Pour les 
  anciennes versions de Windows ou Mac (https://docs.docker.com/toolbox/overview/](https://docs.docker.com/toolbox/overview/).)
  - **Windows** [https://docs.docker.com/docker-for-windows/install/](https://docs.docker.com/docker-for-windows/install/) (Si vieille version Windows 
    [https://docs.docker.com/toolbox/overview/](https://docs.docker.com/toolbox/overview/))
  - **Mac OS** [https://docs.docker.com/docker-for-mac/install/](https://docs.docker.com/docker-for-mac/install/)
  - **Linux Ubuntu** [https://docs.docker.com/install/linux/docker-ce/ubuntu/](https://docs.docker.com/install/linux/docker-ce/ubuntu/)
  - **Linux Fedora** [https://docs.docker.com/install/linux/docker-ce/fedora/](https://docs.docker.com/install/linux/docker-ce/fedora/) 

*Notez que si vous ne voulez/pouvez pas installer Docker sur votre système d'exploitation Mac OS ou Windows, vous pouvez aussi installer Docker sur votre machine virtuelle Linux pour profiter des avantages expliqués ci-dessous.*

- Dans ce dossier, on vous donne un [Dockerfile](Dockerfile) (pour info: [https://docs.docker.com/engine/reference/builder/](https://docs.docker.com/engine/reference/builder/)) contenant la configuration initiale (Ubuntu 20.04). L'idée n'est pas d'écrire un 
  fichier Dockerfile mais de manipuler l'environnement docker en créant un `container` 
  pour travailler dans ce dernier comme si l'on était connecté sur un terminal Linux.

- L'avantage de travailler avec des `containers` est qu'on peut rapidement recommencer l'exercice autant de fois qu'on le veut en partant exactement de la même configuration. On peut aussi changer facilement de système d'exploitation pour son application (ex.: tester une autre distribution Linux).

- Dans le cadre de ce TP, on vous donne un fichier `Dockerfile` avec la configuration 
  initiale. Vous devez créer une image nommée `inf1070:suitecrm`. De cette image, vous 
  devriez créer un container nommé `suitecrm` dont le site web (crm) sera accessible 
  sur le port **4280**. Pour cela, il faut créer le container au moyen de la commande 
  suivante.

> ~~~csh
> $ sudo docker create -it --name suitecrm  -p 4280:4280 \
>      --mount src=`pwd`/,target=/inf1070,type=bind \
>       inf1070:suitecrm  /bin/bash
> ~~~ 
>
> - La première fois, il faut avoir une connexion Internet  parce que le système va procéder au téléchargement des paquets, et à la création de l'image, et du `container` docker.
> - Les autres fois (pour vous connecter à votre docker Linux), la connexion Internet n'est plus requise (sauf si vous voulez installer quelque chose avec le gestionnaire de paquets 
ou télécharger quelque chose, évidemment).
> - Démarrer le container suitecrm
> - Si tout se passe bien, le dossier courant sera monté dans le `container` sous `/inf1070`. 
Ce dossier peut-être utilisé pour l'échange des fichiers entre le `container` et la 
machine locale.
> - Taper la commande suivante pour se connecter sur le `container`
> ~~~csh
> docker exec -it -u admincrm suitecrm /bin/bash
> ~~~
> - Vous serez connecté sur le `container` avec le compte suivant.

>> ~~~csh
>>  Nom d'utilisateur: admincrm
>>  Mot de passe: INF1070pass
>> ~~~
>> Le mot de passe va servir essentiellement pour les commandes `sudo`.

- Le gestionnaire de paquets utilisé dans cet énoncé est `apt` parce qu'on se base 
  sur la distribution Ubuntu.

- Rappelons qu'avant de procéder à l'installation des paquets, il faut mettre à jour 
  les informations en tapant la commande suivante.

~~~csh
$ sudo apt update
~~~


## Identification du système d'exploitation

- Commencez par mettre les informations d'identification du système d'exploitation dans le fichier ­`rapport-tp2.md`. Pour cela, exécutez la commande suivante pour les obtenir (pour plus d'info voir [https://www.cyberciti.biz/faq/how-to-check-os-version-in-linux-command-line/](https://www.cyberciti.biz/faq/how-to-check-os-version-in-linux-command-line/)). 

~~~csh
$ sudo lsb_release  -a
~~~
> - Qu'est-ce qu'on peut identifier plus précisément avec les informations fournies?

- En utilisant la commande suivante, enregistrez la liste des paquets installés initialement sur la machine :
 
 ~~~csh
 $ sudo apt list --installed > paquetsInit.txt
 ~~~

- En utilisant les commandes `tail` et `wc` ainsi que le fichier `paquetsInit.txt`, dites dans le rapport, combien de paquets sont installés initialement. 

 > Vous pouvez utiliser la commande suivante :
 >
 >~~~csh
 > $ tail -n +1 paquetsInit.txt | wc -l
 >~~~
 > 
 >Si la première ligne du fichier `paquetsInit.txt` est  du genre `En train de lister 
  ...`, alors utilisez la commande suivante.
 >
 >~~~csh
 > $ tail -n +2 paqutages0.txt | wc -l
 >~~~

## Apache -- Installation et configuration

À l'aide du gestionnaire de paquetage `apt` (`apt`, `apt-cache`, etc.):
- Installer le serveur web `apache2`
- Créer le dossier suivant et, au besoin, mettre les permissions de lecture et exécution pour tous.  Remplir le rapport `rapport-tp2.md` 
  avec les commandes exécutées.

~~~csh
/var/www/crm
~~~

- Configurer le serveur apache afin que le site web soit accessible à parir du port **4280** (cad [http://localhost:4280](http://localhost:4280)) et désservi par défaut dans le dossier (DocumentRoot) `/var/www/crm` 
- Mettre  les extraits du(des) fichier(s) de configuration modifiés  dans le rapport (`rapport-tp2.md`)
- Copier le fichier [index.htm](index.htm) fourni avec cet énoncé dans le dossier `/var/www/crm`. 
  Pour cela, exécuter la commande suivante sur la machine locale dans le dossier où 
  se trouve le fichier `index.htm`.

> ~~~csh
> sudo docker cp index.htm suitecrm:/var/www/crm/
> ~~~

>> Dans cette commande, `suitecrm` désigne le nom du `container` docker.

- Démarer le serveur apache et s'assurer que le fichier index.htm s'affiche en visitant le site ([http://localhost:4280/](http://localhost:4280/)). 
- Fournir une capture d'écran de cette page d'acceuil dans ­`rapport-tp2.md`

- Enregistrer encore une nouvelle liste des paquetages installés (`paqutages1.txt`) et  dire, au total, combien de paquetages sont installés maintenant?

- Après installation de PHP comme indiqué à la section suivante, activer le module php et redemarrer le serveur apache  

## PHP -- Installation et configuration

- Installer les packages suivants pour pouvoir installer php 7.3 sur ubuntu 20.4.

> ~~~csh
> sudo apt install software-properties-common
> sudo add-apt-repository ppa:ondrej/php
> sudo apt update
> ~~~

- Installer php 7.3 (php7.3) pour se conformer aux exigences
- Installer le module `intl` pour l'internationalisation (ex: php7.3-intl)
- Avant d'activer le module apache, faite une copie (backup) de tout le dossier `/etc` 
- Installer le module php pour apache (`libapache2-mod-php`)
- Activer le module php pour apache et redemarrer ou recharger le serveur apache.  

> ~~~csh
> sudo a2enmod php7.3
> sudo service apache2 restart 
> ~~~

- Installer le module pour `mysql`  (ex: php7.3-mysql) -- pour pouvoir se connecter à Mysql/mariadb
- Intsaller et au besoin activer les extensions et librairies requises ou recommandées reprise sur le site [https://docs.suitecrm.com/admin/installation-guide/downloading-installing/#_recommended_installation_pre_requisites](https://docs.suitecrm.com/admin/installation-guide/downloading-installing/#_recommended_installation_pre_requisites)

> php7.3, php7.3-json, php7.3-xml, php7.3-xmlrpc, php7.3-mbstring, pcregrep, 
> php7.3-curl, composer, php7.3-gd php7.3-zip, php7.3-imap,
> php7.3-intl ...

- En utilisant la commande `diff`, comparer le backup avec l'actuel `/etc` (ex: `diff -q etc_back /etc`) et indiquer dans le rapport les fichiers qui ont été modifiés. Si aucun fichier n'a été modifié suite à l'activation du module php alors l'indiquer  et au besoin, donner une explication 
- Documenter les problèmes eventuels dans fichier ­`rapport-tp2.md`
- Mettre le fichier `phpinfo.php` dans le dossier racine du site puis visiter les site [http://localhost:4280/phpinfo.php](http://localhost:4280/phpinfo.php) 
pour imprimer une copie dans un fichier pdf à remettre avec le rapport.
- Faire encore une copie de la liste des paquetages installés (`paqutages2.txt`) et donner le nombre total dans le rapport
- Ne pas oublier d'enregistrer les commandes  dans les fichier `solution-tp2.sh` et 
  de remplir le `rapport-tp2.md`.


## MariaDB -- Installation et configuration

- Installer MariaDB.

> ~~~csh
> sudo apt install mariadb-server mariadb-client php7.3-mysql
> ~~~

> **Attention:** pour démarrer mariadb, c'est le service mysql qu'il faut démarrer:

>> ~~~csh
>> sudo service mysql start
>> ~~~
 
- Activer le module php `mysql` dans le fichier `php.ini` et s'assurer de la prise en charge UTF8.
- Documenter le rapport (­`rapport-tp2.md`) avec les parties de configuration modifiées.
- Faire une copie des paquetages installés (`paqutages3.txt`) et dire le total à ce niveau.
- Dire dans quel fichier se trouve effectivement le mot de passe root initial.
- Créer une base de données et un utilisateur pour le CRM

> ~~~csh
> # se connecter avec root
>  sudo mysql -u root
> # Créer une la base de données nommée crm
>  create database crm
> # creer un utilisateur crm avec mot de passe Dbpass
> grant all privileges on crm.* TO 'crm'@'localhost' \
>  identified by 'Dbpass';
> # Appliquer les changement
>  flush privileges;
> # Quitter mysql
>  exit
> ~~~ 

- Tester que vous pouvez vous connecter avec le nouvel utilisateur

> ~~~csh
> mysql -u crm -p crm
> ~~~

>> À la demande, mettez le mot de passe: Dbpass


## Installation SuiteCRM

- Suivre la procédure donnée [https://docs.suitecrm.com/admin/installation-guide/downloading-installing/](https://docs.suitecrm.com/admin/installation-guide/downloading-installing/) 

- Prendre une copie de  SuiteCRM 7.11.15 fournie avec cet énoncé ou télécharger sur [https://github.com/salesagility/SuiteCRM/tree/v7.11.15](https://github.com/salesagility/SuiteCRM/tree/v7.11.15)

- copier les fichier /var/www/crm/index.htm et /var/www/crp/phpinfo.php à un autre 
endroit

- Décompresser le `SuiteCRM-7.11.15.zip`   dans le dossier /var/www/crm de sorte que les 
fichiers ne soient pas dans un sous dossier `SuiteCRM-7.11.15`. Au besoins décompresser 
ailleur puis copier tout le contenu dans `/var/www/crm`

- Aller dans le dossier  `/var/www/crm/` et ajuster les permissions de la manière suivante.

> ~~~csh
>  sudo chown -R www-data:www-data .
>  sudo chmod -R 755 .
>  sudo chmod -R 775 cache custom modules themes data upload
>  sudo chmod 775 config_override.php 2>/dev/null
> ~~~ 

>> Note: `www-data`est le nom d'utilisater et groupe système utilisé par le serveur 
web apache sur Ubuntu.

- Aller dans le dossier `/var/www/crm` et vérifier les dépendances avec la commande 
suivante.

> ~~~csh
> sudo -u www-data composer install
> ~~~

>> Au besoin, installer les prérequis manquant

- s'assurer que la ligne suivante du fichier `php.ini` est décommenter (pas de ; devant)

- S'assurer que d'avoir 20M ou plus pour la propriété `upload_max_filesize` dans le 
fichier php.ini (`upload_max_filesize = 20M`)

- De même, mettre la propriété `post_max_size` à au moins 20M

- Ne pas oublier de redemarrer le serveur apache après modification de php.ini

> ~~~csh
> extension=mysqli
> ~~~

- Visiter [http://localhost:4280/install.php](http://localhost:4280/install.php) avec 
un navigateur web et suivre pa procédure d'installation

- Ne pas oublier de cocher la case pour l'installation des données de démo pendant 
l'installation.

- Suivre les instructions et fournir le nom de la base de données et le mot de passe (var 
section MariaDb)

- Comme nom d'utilisateur administrateur, garder `admin` et mmettez le mot de passe 
`INF1070crm` de sorte à avoir pour administrateur:

~~~csh
#administrateur
nom d'utilisateur: admin
mot de passe: INF1070crm
~~~

- Suivre la précédure d'installation

- Se connecter comme administrateur et effectuer les tâches suivantes:

> - Créer un contact (fournir capture d'écran) 
> - Créer 2 employés (fournir capture d'écran)
> - Créer quelques activités dans le calendrier
> - Créer un document


## Crontab -- Installation configuration

- Vérifier la version `cron` disponible avec le gestionnaire des paquetages. 
- Installar `cron`.
- Programmer (planification de tâche) le cron principal Suitecrm pour qu'il s'exécute à toutes les 5 minutes 
du lundi au vendredi.
- Enregister une liste des paquetages installés (`paqutages5.txt`) et dire le total à ce niveau.
- Documenter le rapport

- Voici un exemple de cron par défaut pour SuiteCRM

> ~~~csh
> sudo crontab -e -u www-data
> ... and add the following line to the crontab file:
> *    *    *    *    *     cd /var/www/crm; php -f cron.php > /dev/null 2>&1
> ~~~



## Sauvegarde et Restauration


### Base de données



- Après avoir  et effectué toutes les configurations et terminer toutes les manipulations, faire 
une sauvegarde (backup) de la base de données.

~~~csh
$ mysqldump -u crm -p crm >~/crm.sql
~~~
> A la demande, entrer le mot de passe de l'utilisateur crm pour la base de données.


## Modalités de remise

Votre travail doit être remis au plus tard le **10 Aout 2020 à 23h55** par l'intermédiaire de la plateforme [Moodle](https://www.moodle.uqam.ca/). Vous  devez remettre un seul fichier (une archive ZIP) nommé exactement `tp2.zip`, et contenant tous les fichiers suivants:

- `solution-tp2.sh`
- `rapport-tp2.md` (avec des liens vers tous les autres fichiers)
- `paquetsInit.txt`
- Les fichiers de paquetages
- `crm.sql`
- `paquetsPrerequis.text`
- Les captures d'écrans (.png) de suiteCRM (une capture par page) : 
- Toutes les captures d'écrans doivent-être affichées dans `rapport-tp2.md`
- Autres fichiers pertinents éventuels (optionnel)

<!--
 ~~Une pénalité de **2 points** par heure de retard sera appliquée.~~ Une pénalité 
   eventuelle, en conformité avec les directives de l'université dans le contexte de COVID-19 
   sera appliquée pour les remises hors délai.
-->

**Aucune remise par courriel ne sera acceptée**, peu importe le motif. Plus précisément, si vous envoyez votre travail par courriel, il sera considéré comme non remis. Il est donc de votre responsabilité de vous assurer d'être capable de faire une remise à temps par l'intermédiaire de Moodle.

<!--
Si vous êtes en équipe de deux, un seul des deux étudiants doit effectuer la remise sur son compte Moodle.
-->

## Le format Markdown

VOUS DEVEZ écrire votre rapport (rapportTP2.md) dans le format Markdown. La documentation est dispoible sur Internet, par exemple [https://en.support.wordpress.com/markdown-quick-reference/](https://en.support.wordpress.com/markdown-quick-reference/)

## Barème de correction

Le travail est corrigé sur 100 points selon le barème suivant :

Détails le soir ...

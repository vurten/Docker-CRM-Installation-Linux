#!/bin/sh
# TP2 Été 2020
# Informations de l'auteur (CHAOUKI MOHAMED CHAM27088802)

# 1. Identification Os

docker container stop $(docker container ls -aq)

docker container rm $(docker container ls -aq)

echo y | docker system prune -a

docker images -a -q

docker rmi $(docker images -a -q)

docker build -t inf1070:suitecrm -f Dockerfile .

docker create -it --name suitecrm  -p 4280:4280 \
     --mount src=`pwd`/,target=/inf1070,type=bind \
      inf1070:suitecrm  /bin/bash

docker container start suitecrm

docker exec -i suitecrm bash << EOF

sudo -s

apt update

lsb_release  -a

cd

apt list --installed > paquetsInit.txt

cp paquetsInit.txt paqutages0.txt

tail -n +2 paqutages0.txt | wc -l

# 2. Apache

echo Y | apt install apache2

mkdir /var/www/crm

cp /inf1070/index.htm /var/www/crm/

cd /etc/apache2/

sed -i '5 a Listen 4280' ports.conf

cd /etc/apache2/sites-available/

cp 000-default.conf crm.conf

sed -i 's/html/crm\//g' crm.conf

sed -i 's/80/4280/g' crm.conf

sed -i 's/ServerAdmin webmaster@localhost/ServerAdmin admin@localhost/g' crm.conf

a2ensite crm.conf

service apache2 restart

cp paqutages1.txt /inf1070/

cd

apt list --installed > paqutages1.txt

tail -n +2 paqutages1.txt | wc -l

php --version

mkdir etc_backup/

cp /etc/ etc_backup/


# 3. PHP

echo Y | apt install software-properties-common

add-apt-repository ppa:ondrej/php

apt update

echo Y | apt install php7.3 libapache2-mod-php7.3 php7.3-common php7.3-mysql php7.3-gmp php7.3-curl php7.3-intl php7.3-mbstring php7.3-xmlrpc php7.3-gd php7.3-bcmath php7.3-imap php7.3-xml php7.3-cli php7.3-zip

apt list --installed > paqutages2.txt

cp paqutages2.txt /inf1070/

diff -q etc_back/ /etc > resultatDiff.txt

cp resultatDiff.txt /inf1070/

cp /inf1070/phpinfo.php /var/www/crm/

a2enmod php7.3

service apache2 restart

# 4. MariaDb (MySql)

echo Y | apt-get install mariadb-server mariadb-client

service mysql start

mysql -u root << EOF1

CREATE DATABASE crm;
CREATE USER 'crm'@'localhost' IDENTIFIED BY 'Dbpass';
GRANT ALL PRIVILEGES ON crm.* to crm@localhost;
FLUSH PRIVILEGES;
\q
EOF1

apt list --installed > paqutages3.txt

cp paqutages3.txt /inf1070/

tail -n +2 paqutages3.txt | wc -l

service apache2 restart

# 5. SuiteCRM

apt install curl

echo Y | apt install git

curl -sS https://getcomposer.org/installer | sudo php -- --install-dir=/usr/local/bin --filename=composer

cd /var/www/crm/

git clone https://github.com/salesagility/SuiteCRM.git

rm index.htm phpinfo.php

cd SuiteCRM/

mv ./* ../

cd ..

rm -rf SuiteCRM/

composer install --no-dev

chown -R www-data:www-data /var/www/crm/

chmod -R 755 /var/www/crm/

cd /etc/apache2/sites-available/

sed -i '12 a ServerName localhost\nServerAlias www.localhost\n<Directory \/var\/www\/crm\/>\nOptions FollowSymlinks\nAllowOverride All\nRequire all granted\n<\/Directory>' crm.conf

sed -i '28 a <Directory \/var\/www\/crm\/>\nRewriteEngine on\nRewriteBase \/\nRewriteCond %{REQUEST_FILENAME} !-f\nRewriteRule ^(.*) index.php [PT,L]\n<\/Directory>' crm.conf

cd /etc/php/7.3/apache2/

sed -i 's/short_open_tag = Off/short_open_tag = On/g' php.ini

sed -i 's/memory_limit = 128M/memory_limit = 256M/g' php.ini

sed -i 's/;date.timezone =/date.timezone = America\/Toronto/g' php.ini

sed -i 's/max_execution_time = 30/max_execution_time = 360/g' php.ini

sed -i 's/upload_max_filesize = 2M/upload_max_filesize = 100M/g' php.ini

sed -i 's/;   extension=mysqli/   extension=mysqli/g' php.ini

sed -i 's/post_max_size = 8M/post_max_size = 20M/g' php.ini

a2ensite crm.conf

a2enmod rewrite

service apache2 restart

cd

apt list --installed > paquetsPrerequis.txt

cp paquetsPrerequis.txt /inf1070/

tail -n +2 paquetsPrerequis.txt | wc -l

# 6. Crontab et Backup bd

echo Y | apt install cron

touch /var/spool/cron/crontabs/www-data

sed -i '10 a 5    *    *    *    1,2,3,4,5     cd \/var\/www\/crm; php -f cron.php > \/dev\/null 2>&1' /var/spool/cron/crontabs/www-data

cd

mysqldump -u crm -p crm >~/crm.sql << EOF3
Dbpass
EOF3

cp crm.sql /inf1070/

apt list --installed > paqutages5.txt

cp paqutages5.txt /inf1070/

tail -n +2 paqutages5.txt | wc -l

exit
EOF

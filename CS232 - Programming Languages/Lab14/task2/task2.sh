#!/bin/bash
create(){
DAY=`date +%d`
MONTH=`date +%m`
YEAR=`date +%Y`

root="bckup"

if [[ ! -d "$root" ]]; 
    then
        mkdir -p bckup
        printf "\n\nRoot Dir created\n\n"
    else
        printf "\n\nRoot Dir exists\n\n"
fi;

printf "\nName of directory to create: "
read -s dirname

newdirname="$dirname.$DAY.$MONTH.$YEAR"
echo $newdirname
if [[ ! -d "$root/$newdirname" ]]; 
    then
        mkdir -p $root/$newdirname
        printf "\n\ndirectory: $dirname created\n\n"
    else
        printf "\n\n$dirname already exists\n\n"
fi;
cd bckup/$newdirname/
touch $newdirname.txt

printf "text file created in $newdirname directory, called: $newdirname.txt \n\n"

OF="bckup$(date +%d%m%Y).tar.gz"
tar vczf $OF $PWD/$newdirname/*.txt

printf "\nzip file created in $newdirname directory, which zipped all .txt files into 1 file\n\n"


}
purge(){
        echo "purge"
}
Restore(){
        echo "Restore"
}
Time(){
        echo "time"
}
Name(){
    printf "\n\nListing by name:\n"
    cd bckup/
    ls -d -- */
    cd $OLDPWD
}

clear ; loop=y

while [ "$loop" = y ] ;
    do

    echo " Menu "
    echo "------"
    echo "C: Create backup"
    echo "P: Purge all other backups so only most recent backup remains"
    echo "R: Restore directories from backups"
    echo "T: list backups by Time"
    echo "N: list backups by Name"
    echo "Q: Quit program"

    printf "\nOption:"
    read -s option

    case $option in

        Q | q) printf "\n\nProgram Quitting\n"; loop=n ;;
        C | c) create;;
        P | p) purge;;
        R | r) Restore;;
        T | t) Time;;
        N | n) Name;;
        *) printf "\nWrong menu option, try again...\n\n\n";;

    esac
done
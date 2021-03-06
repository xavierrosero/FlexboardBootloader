#!/bin/bash
#Linker file, between eclipse IDE and python scripts to access the bootloader structure
#Developed by Carlos X. Rosero & Manel Velasco G.

#it takes the current path of files
SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  currentDir="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$currentDir/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
currentDir="$( cd -P "$( dirname "$SOURCE" )" && pwd )"


#"$1" is the first argument that is comming from the calling to the file
#in eclipse
#echo $1
#echo $2 #second argument, is the superuser keyword

#it verifies if the argument that is comming values s
echo "Linking with python scripts..."

if [ $1 == s ] #if settings required
  then
    echo "Setting tool at work..."
    echo "$2" | sudo /usr/bin/python "$currentDir"/settings.py
  else
    if [ $1 == e ] #if erasing required
      then
        echo "Erasing tool at work..."
        echo "$2" | sudo /usr/bin/python "$currentDir"/erase.py    
      else #programming required, values between 0 to 4
        if [ $1 == r ] #if resetting required
          
          then
            echo "Resetting tool at work..."
	    echo "$2" | sudo /usr/bin/python "$currentDir"/reset.py    
          else
            echo "Programming tool at work..."
	    echo "$2" | sudo /usr/bin/python "$currentDir"/serialBoot.py -s "$1" -p "$1"f -r "$1"	
        fi
    fi
fi

#echo "Done!"


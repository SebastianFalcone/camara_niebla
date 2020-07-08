#!/bin/bash

if [ $# == 1 ];
then
	stty -F /dev/ttyACM0 115200
else
	stty -F /dev/ttyACM0 $2
fi


echo_time() 
{
    echo `date "+%s"` "$@"
}

if [ $# == 0 ];
then 
	echo ""
	echo "Modo de uso del script:"
	echo "./datalog.sh [nombre del archivo] [baudrate]"
else		
	echo ""
	echo "Iniciado el log de los datos en" `pwd`/$1".txt"
 

	echo ""
	echo "Presione q para salir..."

	while true; 
	do	
		read X < /dev/ttyACM0 && echo_time "	" $X >> $1.txt 2>&1

		read -t 0.25 -N 1 input
		if [[ $input = "q" ]] || [[ $input = "Q" ]]; 
		then
        	break 
    	fi
	done
fi

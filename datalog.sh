#!/bin/bash


echo_time() 
{
    echo `date "+%s"` "$@"
}

if [ $# == 0 ];
then 
	echo ""
	echo "Modo de uso del script:"
	echo "./datalog.sh [nombre del archivo]"
else		
	echo ""
	echo "Iniciado el log de los datos en" `pwd`/$1".txt"
 

	echo ""
	echo "Presione q para salir..."

	while true; 
	do	
		read X < /dev/ttyACM0
		echo_time "	" $X >> $1.txt

		read -t 0.25 -N 1 input
		if [[ $input = "q" ]] || [[ $input = "Q" ]]; 
		then
        	break 
    	fi
	done
fi
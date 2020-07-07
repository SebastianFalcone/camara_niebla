set xdata time
set format x '%d/%m %H:%M:%S'
plot [][10:50] '< tail -n86400 test.txt'  u ($1 - 946684800-(3600*3)):2

while (1){
      replot
      pause -1
}

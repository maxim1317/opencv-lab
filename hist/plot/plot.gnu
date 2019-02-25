# set terminal svg position 0,0 size 955,540 enhanced background rgb '#263238'
set title "Luminosity Histogram"        textcolor rgb 'white'
set xlabel "Luminosity"                 textcolor rgb 'white'
set ylabel "Relative quantity of light" textcolor rgb 'white'

set border lw 2 lc rgb "white"
set key textcolor rgb "white"

set xtics textcolor rgb "white"
set ytics textcolor rgb "white"

set autoscale

# set logscale y 10
set xrange [0:255]

set style data line
plot "luminosity.txt" u 1:2 title "Luminosity" lt rgb "#E0E0E0" lw 2, \
     "luminosity.txt" u 1:3 title "Red"        lt rgb "#D72638" lw 2, \
     "luminosity.txt" u 1:4 title "Green"      lt rgb "#53DD6C" lw 2, \
     "luminosity.txt" u 1:5 title "Blue"       lt rgb "#28C6E4" lw 2

set term png size 512,512 enhanced background rgb '#263238'

set output "../steps/hist.png"
replot

# set term wxt position 0,0 size 955,540 enhanced background rgb '#263238'

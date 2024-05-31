set terminal png font "Verdana,14" size 1000, 1000
set output "first.png"
plot 'first.txt' w lines notitle, 'path.txt' pt 7 lc 7 ps 2 notitle

set terminal png font "Verdana,14" size 1000, 1000
set output "all.png"
plot 'all.txt' w lines notitle, 'path.txt' pt 7 lc 7 ps 2 notitle

set terminal png font "Verdana,14" size 1000, 1000
set output "optimal.png"
plot 'optimal.txt' w lines notitle, 'path.txt' pt 7 lc 7 ps 2 notitle
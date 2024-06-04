set terminal png font "Verdana,14" size 1000, 1000
plot [-1:3][-1:3] 'config_max.txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lc 2 notitle, 'config_max.txt' using 1:2 pt 7 notitle
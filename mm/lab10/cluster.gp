set terminal png font "Verdana,14" size 1000, 1000
set output "Cluster.png"
plot [-1:11][-1:11] 'config.txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lw 2 lc 8 notitle, 'cluster.txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lc 7 lw 3 notitle, 'seed_cluster.txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lc 2 lw 4 notitle
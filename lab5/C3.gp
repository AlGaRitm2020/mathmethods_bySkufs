set terminal png font "Times New Roman,24" size 1000, 1000
set output "C.png"
set ylabel "C/N" font "Times New Roman,28"
set xlabel "T" font "Times New Roman,28"
#plot '2x2.txt' using 1:2 with lines lw 2 title "2x2", '3x3.txt' using 1:2 with lines lw 2 title "3x3", '4x4.txt' using 1:2 with lines lw 2 title "4x4", '5x5.txt' using 1:2 with lines lw 2 title "5x5"

#plot '2x2.txt' using 1:2 with lines lw 2 title "2x2", '3x3.txt' using 1:2 with lines lw 2 title "3x3", '4x4.txt' using 1:2 with lines lw 2 title "4x4"


plot '3x3.txt' using 1:2 with lines lw 2 title "3x3"

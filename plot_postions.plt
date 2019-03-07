#gnuplot -c plot_postions.plt 3 --persist #copy to run showing 3 neighbors

splot [0:100][0:100][0:100] "Positions2.dat" every ::1::ARG1 u 1:2:3 ps 3 pt 7 lc 200 , "Positions2.dat" u 1:2:3 ps 2 pt 7 lc 4, "Positions2.dat" every ::1::1 u 1:2:3 ps 2 pt 7 lc 5
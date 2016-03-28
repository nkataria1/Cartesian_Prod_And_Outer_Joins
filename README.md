This code base returns results for Cartesian Products and Join Functions given two tables. 

Files and Descriptions :

1. cart_prod.c : File defining following functions:
   void cart_prod (char *f1[COL][ROW], char *f2[COL][ROW]);
   void left_outer_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col);
   void right_outer_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col);
   void full_outer_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col);
   void natural_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col);
   main () : Function to call cartesian_product.

2. Makefile for compiling cart_prod.c.

3. file1 and file2 defining the two tables.

Compiling and Running:
---------------------

After untarring hw_1.tar, run the "make" command. 
It will generate a binary 'cart_prod'
Run 'cart_prod' to see the results. 


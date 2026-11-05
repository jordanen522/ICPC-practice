/*  2025/2026 Regional
    International Collegiate Programming Contest

    Problem ?
    GPA Computation
    M. K. Furon.                    2025-10-23.                       */




#include  <stdio.h>
#include  <stdlib.h>




int bonuses, classcount, i, totalpoints;
double unweightedgpa, weightedgpa;
char *iostatus;
char lineimage[12];

int gradepoints[] = {4, 3, 2, 1, 0};




void abend (char *message)
{
(void) fputs (message, stderr);
(void) fputc ('\n', stderr);
exit (4);
}




int main (int argc, char *argv[], char *envp[])
{
/*  Get initial parameters.                                           */
iostatus = fgets (lineimage, 8, stdin);
if (iostatus == NULL)
   abend ("Missing initial value.");
classcount = atoi (lineimage);
bonuses = totalpoints = 0;

/*  Read each class grade and tier, accumulating the grade points.    */
for (i = 0; i < classcount; i++)
   {
   iostatus = fgets (lineimage, 8, stdin);
   if ((lineimage[0] < 'A') || (lineimage[0] > 'E'))
      abend ("Incorrect grade in input.");
   if ((lineimage[1] < '1') || (lineimage[1] > '3'))
      abend ("Incorrect tier in input.");
   totalpoints += gradepoints[(lineimage[0] - 'A')];
   /*  Accrue the bonus grade points as integers.                     */
   if ((lineimage[0] == 'A') || (lineimage[0] == 'B') ||
      (lineimage[0] == 'C'))
      {
      if (lineimage[1] == '1')
         bonuses += 2;
      else if (lineimage[1] == '2')
         bonuses++;
      }
   }

/*  Calculate the unweighted GPA, then add the bonus grade points
    after scaling.  This is an unusual approach...                    */
unweightedgpa = ((double) totalpoints) / ((double) classcount);
weightedgpa = unweightedgpa + (0.025 * ((double) bonuses));

(void) printf ("%.12f\n", weightedgpa);

return (0);
}

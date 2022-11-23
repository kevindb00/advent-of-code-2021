#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define NUM_OF_STEPS 400


int main() 
{
 
    int input_data[MAX_ROWS][MAX_COLS];
    int row_count=0;
    char input_buf[100];
    int i,j,k=0;
    int tot_flashes=0;
    int did_flash=0;
    int tmp_sync_count=0;
    int part_b_answer=0;
 
    FILE *pFile;
    pFile = fopen ("input_full.txt", "r");
//    pFile = fopen ("input.txt", "r");
    if (pFile == NULL)
    {
      printf ("error opening file");
      return 0;
    }

    while (fgets(input_buf, sizeof(input_buf),pFile)!= NULL)
    {
        for(i=0;i<MAX_COLS;i++)
        {
            input_data[row_count][i] = input_buf[i] - '0';
        } 
        row_count++;
    }

    // ===========================================================
    // Main Processing
    // - loop through the number of defined iterations
    // - loop through entire input adding 1 number to each
    // - process all the data
    //      --> while no more flashes
    //      --> loop though all data.  if flash (>9), then adjust 
    //          surrounding data +1 and set entry in question to 999 to mark as already flashed
    //      --> set all flashed (999) to 0
    // ===========================================================

    for(k=0;k<NUM_OF_STEPS;k++)
    {
        // Loop through entire data set adding 1 number to each
        printf("\nStep #%d\t --> adding 1 to all entries in data set\n",k+1);
        for (i=0;i<MAX_ROWS;i++)
        {
            for(j=0;j<MAX_COLS;j++)
            {
                input_data[i][j]++;
            }
        }

        // While no more flashes
        did_flash = 1;
        tmp_sync_count=0;
        while (did_flash == 1)
        {
            // Loop through all data.  if flash (>9), then adjust 
            //printf("DEBUG: Checking for flashes\n");
            did_flash = 0;

            for (i=0;i<MAX_ROWS;i++)
            {
                for(j=0;j<MAX_COLS;j++)
                {
                    if ((input_data[i][j] > 9) && (input_data[i][j] < 999) )
                    {
                        // Processing a flash
                        printf("\t--> Processing a Flash in row index=:%d, col index=:%d\n",i,j);
                        did_flash = 1;
                        input_data[i][j] = 999;
                        tot_flashes++;
                        tmp_sync_count++;
                        if (tot_flashes>100000){return 99;}
                        if (i==0)
                        {
                            // Process for entry on first row
                            if (j==0)
                            {
                                // Process for first column first row
                               input_data[0][j+1]++;
                               input_data[1][j]++;
                               input_data[1][j+1]++;
                            } else if (j==MAX_COLS-1)
                            {
                                // Proces for last column first row
                                input_data[0][j-1]++;
                                input_data[1][j]++;
                                input_data[1][j-1]++;

                            } else
                            {
                                // process for all other columns in first row
                                input_data[0][j-1]++;
                                input_data[0][j+1]++;
                                input_data[1][j-1]++;
                                input_data[1][j]++;
                                input_data[1][j+1]++;
                            }

                        } else if (i ==MAX_ROWS-1)
                        {
                             // Process for entry on last row
                           if (j==0)
                            {
                                // Process for first column last row
                               input_data[MAX_ROWS-1][j+1]++;
                               input_data[MAX_ROWS-2][j]++;
                               input_data[MAX_ROWS-2][j+1]++;
                            } else if (j==MAX_COLS-1)
                            {
                                // Proces for last column last row
                               input_data[MAX_ROWS-1][j-1]++;
                               input_data[MAX_ROWS-2][j]++;
                               input_data[MAX_ROWS-2][j-1]++;

                            } else
                            {
                                // process for all other columns in last row
                                input_data[MAX_ROWS-1][j-1]++;
                                input_data[MAX_ROWS-1][j+1]++;
                                input_data[MAX_ROWS-2][j-1]++;
                                input_data[MAX_ROWS-2][j]++;
                                input_data[MAX_ROWS-2][j+1]++;
                            }


                        }else 
                        {
                             // Process for entry on middle rows.
                            if (j==0)
                            {
                                // Process for first column middle row

                                input_data[i-1][0]++;
                                input_data[i-1][1]++;
                                input_data[i][1]++;
                                input_data[i+1][0]++;
                                input_data[i+1][1]++;
                            } else if (j==MAX_COLS-1)
                            {
                                // Proces for last column middle row
                                input_data[i-1][j-1]++;
                                input_data[i-1][j]++;
                                input_data[i][j-1]++;
                                input_data[i+1][j-1]++;
                                input_data[i+1][j]++;


                            } else
                            {
                                // process for all other columns in middle row
                                input_data[i-1][j-1]++;
                                input_data[i-1][j]++;
                                input_data[i-1][j+1]++;
                                input_data[i][j-1]++;
                                input_data[i][j+1]++;
                                input_data[i+1][j-1]++;
                                input_data[i+1][j]++;
                                input_data[i+1][j+1]++;
                            }

                        }
                    }                    
                }
            }

            // still within the while loop.
            // dump the array


        }

        // After main while loop finished Loop through entire data set setting all previously flashed to =
        printf("%d Flashes this round\n",tmp_sync_count);
        if ( (tmp_sync_count==(MAX_COLS*MAX_ROWS)) && (part_b_answer ==0)){
            part_b_answer = k+1;
        }
            for (i=0;i<MAX_ROWS;i++)
        {
            for(j=0;j<MAX_COLS;j++)
            {
                if(input_data[i][j] >= 999)
                {
                    input_data[i][j] = 0;
                }
            }
        }
/*  
        for (i=0;i<MAX_ROWS;i++)
            {
                for(j=0;j<MAX_COLS;j++)
                {
                    printf("%d,",input_data[i][j]);
                }
                printf("\n");
            }
*/
    }

    printf("Total Flashes =: %d\n",tot_flashes);
    printf("Partb answer = %d",part_b_answer);
    return 0;

}

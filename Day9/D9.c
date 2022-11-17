#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_input_rows 100   
#define max_input_cols 100

int basin_check(int, int[][max_input_cols], int, int,int);

int main()
{
    int basin_size=0;
    int total_rows=0;
    int max_1=0;
    int max_2=0;
    int max_3=0;
    int count=0;
    int risk_level = 0;
    int i,j=0;

    char buf[500];
    int data_set[max_input_rows][max_input_cols];
    int basins_set[max_input_rows][max_input_cols];
    int buf_line_0[max_input_cols];
    int buf_line_1[max_input_cols];
    int buf_line_2[max_input_cols];


    
    printf("Sonar - Day 9\n");

    // Read in the initial dataset 
    FILE *pFile;
    pFile = fopen ("input_full.txt", "r");
    if (pFile == NULL)
    {
      printf ("error opening file");
      return 0;
    }


    fgets(buf, sizeof(buf),pFile);
    for (i = 0; i < max_input_cols; i++) {
        buf_line_0[i] = buf[i] - '0';
        data_set[total_rows][i] = buf_line_0[i];
    }
    total_rows++;
    
    fgets(buf, sizeof(buf),pFile);
    {
        for (i = 0; i < max_input_cols; i++) {
            buf_line_1[i] = buf[i] - '0';
            data_set[total_rows][i] = buf_line_1[i];
        }
        total_rows++;

    }
    
    //Process Row #1 (i.e. data from first 2 rows)
    printf("Processing the first row.\n");
    for (i = 0; i < max_input_cols; i++) {
        switch (i)
        {
            case 0:
                if ((buf_line_0[i] < buf_line_0[i+1]) && (buf_line_0[i] < buf_line_1[i]) ) 
                {
                    //low spot
                   risk_level = risk_level + 1 + buf_line_0[i];
                   basins_set[0][i] = 1;
                    printf("Low spot in row: %d, position: %d\n",total_rows-1,i+1);
                } else { basins_set[0][i] = 0;}
                break;

            case max_input_cols-1: 
                if ((buf_line_0[i] < buf_line_0[i-1])  && (buf_line_0[i] < buf_line_1[i]) ) 
                {
                    //low spot
                    risk_level = risk_level + 1 + buf_line_0[i];
                   basins_set[0][i] = 1;
                   printf("Low spot in row: %d, position: %d\n",total_rows-1,i+1);
                } else { basins_set[0][i] = 0;}
                break;

            default:
                if ((buf_line_0[i] < buf_line_0[i-1]) && (buf_line_0[i] < buf_line_0[i+1]) && (buf_line_0[i] < buf_line_1[i]) ) 
                {
                    //low spot
                    risk_level = risk_level + 1 + buf_line_0[i];
                   basins_set[0][i] = 1; 
                   printf("Low spot in row: %d, position: %d\n",total_rows-1,i+1);
                } else {basins_set[0][i] = 0;}
                break;

        }
    }
    
    
    // Process groups of 3 rows.
    while (fgets(buf, sizeof(buf),pFile)!= NULL)
    {
        for (i = 0; i < max_input_cols; i++) {
            buf_line_2[i] = buf[i] - '0';
            data_set[total_rows][i] = buf_line_2[i];
        }
        total_rows++;
        
        //printf("Processing row #%d (full set of 3 rows).\n", total_rows-1);
        for (i = 0; i < max_input_cols; i++) {
            switch (i)
            {
                case 0:
                    if (
                    (buf_line_1[i] < buf_line_1[i+1]) && 
                    (buf_line_1[i] < buf_line_2[i]) && 
                    (buf_line_1[i] < buf_line_0[i]) 
                    )   {
                        //low spot
                        risk_level = risk_level + 1 + buf_line_1[i];
                        basins_set[total_rows-2][i] = 1;
                        printf("Low spot in row: %d, position: %d\theight value =:%d\n",total_rows-1,i+1,buf_line_1[i]);
                    } else {basins_set[total_rows-2][i] = 0;}
                break;

                case max_input_cols-1: 
                    if (
                    (buf_line_1[i] < buf_line_1[i-1]) && 
                    (buf_line_1[i] < buf_line_2[i]) && 
                    (buf_line_1[i] < buf_line_0[i]) 
                    )   {
                        //low spot
                        risk_level = risk_level + 1 + buf_line_1[i];
                        basins_set[total_rows-2][i] = 1;
                        printf("Low spot in row: %d, position: %d\theight value =:%d\n",total_rows-1,i+1,buf_line_1[i]);
                    } else {basins_set[total_rows-2][i] = 0;}
                break;

                default:
                    if (
                    (buf_line_1[i] < buf_line_1[i-1]) && 
                    (buf_line_1[i] < buf_line_1[i+1]) && 
                    (buf_line_1[i] < buf_line_2[i]) && 
                    (buf_line_1[i] < buf_line_0[i]) 
                    )   {
                        //low spot
                        risk_level = risk_level + 1 + buf_line_1[i];
                       basins_set[total_rows-2][i] = 1;
                        printf("Low spot in row: %d, position: %d\theight value =:%d\n",total_rows-1,i+1,buf_line_1[i]);
                    } else {basins_set[total_rows-2][i] = 0;}
                    
                break;
            }
        }
           
        
        // Setup for next read
        for (i = 0; i < max_input_cols; i++) 
        {
            buf_line_0[i] = buf_line_1[i];
            buf_line_1[i] = buf_line_2[i];
        }

   
    }

    //Process Last Row (i.e. last 2 rows)
    //printf("Processing row #%d (Last 2 rows).\n", total_rows);
    for (i = 0; i < max_input_cols; i++) {
        //printf("DEBUG: buf_line_1[%d]=:%d\ti=:%d\n",i-1,buf_line_1[i-1],i);
        switch (i)
        {
            case 0:
                if ((buf_line_1[i] < buf_line_1[i+1]) && (buf_line_1[i] < buf_line_0[i]) ) 
                {
                    //low spot
                    risk_level = risk_level + 1 + buf_line_1[i];
                   basins_set[total_rows-1][i] = 1;
                   printf("Low spot in row: %d, position: %d\n",total_rows,i+1);
                } else {basins_set[total_rows-1][i] = 0;}
            break;

            case max_input_cols-1:
                if ((buf_line_1[i] < buf_line_1[i-1])  && (buf_line_1[i] < buf_line_0[i]) ) 
                {
                    //low spot
                    risk_level = risk_level + 1 + buf_line_1[i];
                   basins_set[total_rows-1][i] = 1;
                   printf("Low spot in row: %d, position: %d\n",total_rows,i+1);
                } else {basins_set[total_rows-1][i] = 0;}
            break;
            
            default: 
                if ((buf_line_1[i] < buf_line_1[i-1]) && (buf_line_1[i] < buf_line_1[i+1]) && (buf_line_1[i] < buf_line_0[i]) ) 
                {
                    //low spot
                    risk_level = risk_level + 1 + buf_line_1[i];
                    basins_set[total_rows-1][i] = 1;
                    printf("Low spot in row: %d, position: %d\n",total_rows,i+1);
                } else {basins_set[total_rows-1][i] = 0;}
            break;



        }

    }
    

    for (i=0;i< max_input_rows;i++){
        for(j=0;j<max_input_cols;j++) 
        {
            if (basins_set[i][j] == 1)
            {
                basin_size = basin_check(data_set[i][j],data_set, i,j,0);
                //printf("FINAL: Basin at row %d col %d is :\t%d\n",i+1,j+1, basin_size);
                if (basin_size > max_1) {
                    max_3 = max_2;
                    max_2 = max_1;
                    max_1 = basin_size;
                } else if (basin_size > max_2)
                {
                    max_3 = max_2;
                    max_2 = basin_size;
                } else if (basin_size > max_3)
                {
                    max_3 = basin_size;
                }
                basin_size =0;

            }
        }
    }  
// loop through each low spot.
// recursively move and total.

/*
    printf("\n================ dump data set ==================\n");
    for (i=0;i< max_input_rows;i++){
        for(j=0;j<max_input_cols;j++) 
        {
            printf("%d",data_set[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

*/


    //=======================================================================
    // ======= Print totoals
    //=======================================================================
    printf("\n\nRows of data: %d\n",total_rows);
    printf("Part A answer = %i\n",risk_level);
    printf(" Max_1: %d\n",max_1);
    printf(" Max_2: %d\n",max_2);
    printf(" Max_3: %d\n",max_3);

    printf("Part B answer = %i\n",max_1 * max_2 * max_3);

   
    return 0;
}

int  basin_check(int value, int data_set[][max_input_cols], int row, int col, int total)
{

//printf("Entering <Basin Check> at row: %d col: %d and value=:%d\n",row+1,col+1,value);
if (row <0 || row > max_input_rows-1 || col> max_input_cols-1 || col < 0 ||data_set[row][col] == 9)
{
    return total;
}

//printf("Marking row/col : %d,%d as processed\n", row+1,col+1);
data_set[row][col] = 9;
total++;

    total = basin_check(data_set[row][col], data_set, row +1, col, total);
    total = basin_check(data_set[row][col], data_set, row -1, col, total);
    total = basin_check(data_set[row][col], data_set, row, col+1, total);
    total = basin_check(data_set[row][col], data_set, row, col-1, total);


return total;


}

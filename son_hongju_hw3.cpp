/*
Name: hongju Son
Date: Jun 27 2023
Description: to make a map with randonm numbers after the user input the width, height, radius, power and number of drops.
Usage: Command: ./exe -s seed number
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>                                                                                                                                                                                
#include <string.h>
#include <time.h>
//#include "hw3.h"

void dropDirtBall(int** landmass, int maxWidth, int maxHeight,int centerX, int centerY, int radius, int power);
bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy );
void printLand(int** landmass, int maxWidth, int maxHeight);
int findMax(int** map, int width, int height);
void normalizeMap(int** map, int width, int height, int maxVal);
char** finalizeMap(int** map, char** finalMap, int maxX, int maxY, int waterLine);
void printMap(char** map,int maxWidth, int maxHeight );
double frand();

int main(int argc, char** argv){


    FILE* outfileRawLandmass; 
    FILE* outfileNormalized; 
    FILE* outfileFinal;
    int maxWidth;
    int maxHeight;
    int radius;
    int numDirtballs;
    int centerX;
    int centerY;
    int power;
    int waterLine;

    outfileRawLandmass = fopen("raw_landmass.txt","w");
    outfileNormalized = fopen("normalized_landmass.txt", "w");
    outfileFinal = fopen("final_landmass.txt" , "w");

    if(strcmp(argv[1],"-s") == 0){
    int seed = atoi(argv[2]);
    //printf("%d" , seed);
     srand(seed);
    }
     else{
      srand(time_t(0));
     }

    



    printf("Enter grid width:\n");
    scanf("%d",&maxWidth);
    printf("Enter grid heigth:\n");
    scanf("%d", &maxHeight);
    printf("Enter value for waterline (40-200)\n");
    scanf("%d", &waterLine);
    printf("Enter dirtball radius (minimum 2):\n");
    scanf("%d", &radius);
    printf("Enter dirtball power rating (minimum = radius):\n");
    scanf("%d", &power);
    printf("Enter number of dirtballs to drop:\n");
    scanf("%d", &numDirtballs);

    int** landmass;
 
    landmass = (int **) malloc((maxWidth*maxHeight)*sizeof(int*));

    for(int i = 0; i < maxWidth; i++){
        landmass[i] = (int *) malloc((maxHeight)*sizeof(int));
     }

     for(int i = 0; i< maxWidth; i++){
        for(int j = 0; j <maxHeight; j++){
            landmass[i][j] = 0;
        }
    }

    for(int n = 0; n<numDirtballs; n++){

        centerX = frand() * maxWidth;
        centerY = frand() * maxHeight;        
        dropDirtBall(landmass, maxWidth,  maxHeight, centerX,  centerY,  radius,  power);
    }

    for(int i = 0; i< maxHeight; i++){
        for(int j = 0; j < maxWidth; j++){
            fprintf(outfileRawLandmass, "%4d", landmass[j][i]);
        }
        fprintf(outfileRawLandmass, "\n");
    }
    printLand(landmass, maxWidth, maxHeight);

    printf("\n");
    printf("\n");

    normalizeMap(landmass, maxWidth, maxHeight, findMax(landmass, maxWidth, maxHeight));

    for(int i = 0; i< maxHeight; i++){
        for(int j = 0; j < maxWidth; j++){
            fprintf(outfileNormalized, "%4d", landmass[j][i]);
        }
        fprintf(outfileNormalized, "\n");
    }

    char** finalMap= (char **) malloc((maxWidth*maxHeight)*sizeof(char*));

    for(int i = 0; i < maxWidth ; i++){
        finalMap[i] = (char *) malloc((maxHeight*sizeof(char)));
     }

    finalizeMap(landmass, finalMap,maxWidth, maxHeight, waterLine);

    printLand(landmass, maxWidth, maxHeight);

    printf("\n");
    printf("\n");

    printMap(finalMap , maxWidth, maxHeight );

     for(int i = 0; i< maxHeight; i++){
        for(int j = 0; j < maxWidth; j++){
            fprintf(outfileFinal, "%c", finalMap[j][i]);
        }
        fprintf(outfileFinal, "\n");
    }

    fclose(outfileFinal);
    fclose(outfileNormalized);
    fclose (outfileRawLandmass);

    for(int i = 0; i< maxWidth; i++){
        
            free(landmass[i]);
    }
    free(landmass);

    for(int i = 0; i< maxWidth; i++){
        
            free(finalMap[i]);
    }
    free(finalMap);
    

}


void dropDirtBall(int** landmass, int maxWidth, int maxHeight,int centerX, int centerY, int radius, int power){

                                                                                                                                                                                            
    int x;
    int y;
    int impactValue;

        for(int a = -radius; a<= radius; a++){
         for(int b = -radius; b<= radius; b++){
            x = centerX + a;
            y = centerY + b;

                if(boundsCheck(x,y,0,0,maxWidth,maxHeight) == true){
                    double distance = sqrt(pow((x-centerX),2)+pow((y-centerY),2));
                        if(distance <= radius){
                            impactValue = power - floor(distance);
                            landmass[x][y] += impactValue;
                        }
                }
            }
    }
}

bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy ){

 if( x < minx || y < miny){
    return false;
 }
 else if(x >= maxx || y >= maxy){
    return false;
 }
 else{
    return true;
 }

}

void printLand(int** landmass,int maxWidth, int maxHeight ){

    for(int i = 0; i < maxWidth; i++){
        for(int j = 0; j< maxHeight; j++){
            printf("%3d  ", landmass[i][j]);

        }
        printf("\n");

    }

}

int findMax(int** map, int width, int height){

    int maxValue = 0;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            if(maxValue < map[i][j]){
                maxValue = map[i][j];
            }
        }
    }
    return maxValue;
}

void normalizeMap(int** map, int width, int height, int maxVal){
    for(int i = 0; i< width; i++){
        for(int j = 0; j < height; j++){
            map[i][j] = ((float)map[i][j] / maxVal) * 255;
        }
    }
}

char** finalizeMap(int** map, char** finalMap, int maxX, int maxY, int waterLine ){

    float landZone  = 255 - waterLine;


    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){
            if(map[i][j] < waterLine/2 ){
                finalMap[i][j] = '#';
            }
            else if(map[i][j] >= waterLine/2 && map[i][j] <= waterLine ){
                finalMap[i][j] = '~';
            }
            
            else if(waterLine < map[i][j] && map[i][j] < waterLine + floor(landZone*0.15)){
                finalMap[i][j] = '.';
            }
            else if(map[i][j] >= waterLine + floor(landZone*0.15) && map[i][j] < waterLine + floor(landZone*0.4)){
                finalMap[i][j] = '-';
            }
            else if(map[i][j] >= waterLine + (landZone*0.4) && map[i][j] < waterLine + (landZone*0.8)){
                finalMap[i][j] = '*';
            }
            else{
                finalMap[i][j] = '^';
            }
            
            
        }
    }

    return finalMap;

}

void printMap(char** map,int maxWidth, int maxHeight ){

    for(int i = 0; i < maxWidth; i++){
        for(int j = 0; j< maxHeight; j++){
            printf("%c  ", map[i][j]);

        }
        printf("\n");

    }

}

double frand()
{
    return (double)rand() / ((double)RAND_MAX+1);
}
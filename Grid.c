#include<raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 10
#define COLS 10

typedef struct{
	int i;
	int j;
	int count;
}Tile;
Tile grid[COLS][ROWS];

typedef struct{
	int x;
	int y;
}randomIndex;
int ibug = 5;
int jbug = 6;

const int tileWidth=50;
const int tileHeight=50;

const int imove[8] = {-1,0,1,1,1,0,-1,-1};
const int jmove[8] = {1,1,1,0,-1,-1,-1,0};


const int numberOfTiles = 100;


void drawTiles(Tile);
randomIndex generateRandomNumber();
randomIndex checkWallCondition(randomIndex,int,int);
randomIndex makeMove(randomIndex,int,int,int,int,int []);
void walkRandom(randomIndex);

void drawTiles(Tile tile){
	DrawRectangleLines(tile.i*tileWidth,tile.j*tileHeight,tileWidth,tileHeight,BLACK);
}

randomIndex generateRandomNumber(){
    srand(time(NULL));
	int randNum1 = rand() % 8;
	int randNum2 = rand() % 8;
	randomIndex randomXY;
	randomXY.x = randNum1;
	randomXY.y = randNum2;
	return randomXY;
}



randomIndex checkWallCondition(randomIndex coOrdinates,int ibug,int jbug){
	int x = coOrdinates.x;
	int y = coOrdinates.y;
	if( ((ibug+imove[x]) > 0) && ((ibug+imove[x]) < ROWS) && ((jbug+jmove[y]) > 0) && ((jbug+jmove[y] < COLS))){
		return coOrdinates;
	}else{
		randomIndex axis = generateRandomNumber();
		checkWallCondition(axis,ibug,jbug);
	}
}

randomIndex makeMove(randomIndex coOrdinates,int ibug,int jbug,int legalMoves,int totalMoves,int arrayCount[]){
	ibug = ibug+imove[coOrdinates.x];
	jbug = jbug+jmove[coOrdinates.y];
	if((arrayCount[ibug+jbug])==0){
		arrayCount[ibug+jbug]+=1;
		legalMoves+=1;
	}else{
		totalMoves+=1;
	}
		printf("%d",legalMoves);
		
	totalMoves+=1;
	coOrdinates.x = ibug;
	coOrdinates.y = jbug;
	return coOrdinates;
}
void walkRandom(randomIndex coOrdinates){

	int ibug,jbug,wallX,wallY,upper,lower;

	ibug = coOrdinates.x*50;
	jbug = coOrdinates.y*50;
	wallX = ibug+50;
	wallY = jbug+50;
	
	if(wallX>wallY){
		upper=wallX;
		lower=wallY;
	}else{
		upper=wallY;
		lower=wallX;
	}
	int randNo1 = (rand() % (upper - lower + 1)) + lower; 
	int randNo2 = (rand() % (upper - lower + 1)) + lower;
	DrawCircle(randNo1, randNo2, 4, DARKBLUE);  
		
}
int main() {
  	InitWindow(500, 500, "My window");
	int arrayCount[100]={0};
	int legalMoves=0;
	int totalMoves=0;
	
	
	
  	for(int i=0;i<COLS;i++){
		for(int j=0;j<ROWS;j++){
		   	//Floor[i][j]= (Tile){
			//	.i=i,int arrayCount[10][10]={0};
				//.j=j
		   	//};
		   	grid[i][j].i = i;
		   	grid[i][j].j = j;
			
		}
	}	

	
	SetTargetFPS(60);
	while (!WindowShouldClose()){
			
	   	for(int i=0;i<COLS;i++){
			for(int j=0;j<ROWS;j++){
			   	drawTiles(grid[i][j]);
			}
		}
		if(legalMoves!=numberOfTiles){
			randomIndex bugXY = generateRandomNumber();
			randomIndex bugWallXY = checkWallCondition(bugXY,ibug,jbug);
			randomIndex makeMoveXY = makeMove(bugWallXY,ibug,jbug,legalMoves,totalMoves,arrayCount);
			walkRandom(makeMoveXY);
		}
		
		ClearBackground(WHITE);
		EndDrawing();
        }
	CloseWindow();
  	return 0;
}

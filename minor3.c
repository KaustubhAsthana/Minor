//minor3.c is the final file
//here we need to print the separate distances being generated for each path
//WE ARE CONSIDERING THE TIME IN 24 HOUR FORMAT
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>//library included for the formation of time

#define V 10
#define INF 9999 
int value=0;
int D[V][V];//D will be the array that will be used for printing the distances 
int main(){
	FILE *fptr;
	char filename[100];
	int i1,s,t,ss,mm,hh,season;//s straight ke liye and t turns ke liye ss,mm and hh is used for storing the time in 24 hr format
	//printf("Enter the hour min and seconds format of the time");
	//scanf("%d:%d:%d", &hh, &mm, &ss);
	// the above two lines are being written down so as to avoid the user from entering the wrong time and proceeding with the whole program
	printf("Enter the season: 1-3 for summer, 4-7 for rainy and 7-10 for winter");
	scanf("%d",&season);
	struct adjListNode
{
	int dest;
	struct adjListNode *next;
};

struct adjList
{
	struct adjListNode *head;
};

struct graph
{
	int vetices;
	struct adjList *array;
};

struct adjListNode *newAdjListNode(int dest)
{
	struct adjListNode *newNode = (struct adjListNode*)malloc(sizeof(struct adjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

struct graph *creategraph(int vertices)
{
	struct graph *g = (struct graph*)malloc(vertices * sizeof(struct graph));
	g->vetices = vertices;
	g->array = (struct adjList*)malloc(vertices * sizeof(struct adjList));
	
	int i;
	for(i=0;i<vertices;i++)
	{
		g->array[i].head = NULL;
	}
	return g;
}

void edge(struct graph *g, int src,int dest)
{
	struct adjListNode *newNode = newAdjListNode(dest);
	newNode->next = g->array[src].head;
	g->array[src].head = newNode;
}

void printGraph(struct graph *g)//this is printing the adjacent nodes of a particular node
{
	int vertex;
	for(vertex=0; vertex<g->vetices ; ++vertex)
	{
		struct adjListNode *a = g->array[vertex].head;
		printf("\n start node %d",vertex);
		while(a)
		{
			printf("\n adjacent nodes : ");
			printf("->%d",a->dest);
			a = a->next;
		}
		printf("\n");
	}
}

//function to return the min value of the edge
int findMin(int x, int y) 
{
  if (x < y) 
  {
    return x;
  }
  return y;
}

//function to check if the vertex is marked
int isMarked(int v, int markedVertices[], int markedVerticesIdx) 
{
	int i = 0;
  	for (i = 0; i < markedVerticesIdx; i++) 
	{
    	if (v == markedVertices[i]) 
		{
      		return 1;
    	}
  	}
	return 0;
}

//function to find shortest path between source and destination vertex
int dijkstra(int graph[V][V], int src, int dest)//iss function mein change krna hain iss function mein marked wale ki value change krni hain
{
  int i,r,c,tmpC,min,currVertex,edgeWt = 0,destValue = 0,markedValue = 0,wtTableR = 0,markedVerticesIdx = 0;

  int shortestPathVertices[V] = {-1};
  int shortestPathVerticesIdx = 0;

  int weightTable[V][V];
  for (r = 0; r < V; r++) 
  {
    for (c = 0; c < V; c++) 
	{
      weightTable[r][c] = INF;
    }
  }
  weightTable[wtTableR++][src] = 0;

  int markedVertices[V] = {-1};
  markedVertices[markedVerticesIdx++] = src;
  currVertex = src;

  while(currVertex != dest) 
  {
  	for (i = 0; i < markedVerticesIdx; i++) 
	{
      c = markedVertices[i];
      weightTable[wtTableR][c] = weightTable[wtTableR - 1][c];
    }

    for (c = 0; c < V; c++) 
	{
		if (c != currVertex && !isMarked(c, markedVertices, markedVerticesIdx)) 
		{
			edgeWt = graph[currVertex][c];
	        destValue = weightTable[wtTableR - 1][c];
	        markedValue = weightTable[wtTableR][currVertex];
			min = findMin(destValue, markedValue + edgeWt);
			weightTable[wtTableR][c] = min;
		}
    }

    min = INF;
    for (c = 0;c<V;c++) 
	{
		if (!isMarked(c,markedVertices,markedVerticesIdx)) 
		{
        	if (weightTable[wtTableR][c] < min) 
			{
				min = weightTable[wtTableR][c];
          		tmpC = c;
			}
		}
	}

    markedVertices[markedVerticesIdx++] = tmpC;
    currVertex = tmpC;
	wtTableR++;
  }

  //compute shortest path vertices

  c = dest;
  shortestPathVertices[shortestPathVerticesIdx++] = c;
  markedValue = weightTable[wtTableR - 1][dest];
  for (r = wtTableR - 2; r >= 0; r--) {

    if (weightTable[r][c] != markedValue) {
      c = markedVertices[r];
      markedValue = weightTable[r][c];
      shortestPathVertices[shortestPathVerticesIdx++] = c;
    }

  }

  //display the weight and shortest path
  printf("Shortest Path between %d and %d\n", src, dest);
  for (i = shortestPathVerticesIdx-1; i >= 0; i--) 
  {
    printf("%d", shortestPathVertices[i]);
    if (i > 0) 
	{
      printf(" --> ");
      value++;
    }
  }
  printf("\n");
  printf("Total Shortest Distance Travelled : %d\n", weightTable[wtTableR-1][dest]);//weightTable array ki iss particular cell ki value mein change krna pdega 
	//return (weightTable[wtTableR-1][dest]/5); iss line mein bhi ek change kr rhe hain try krke dekhte hain
	return (value);
}
	int w[V][V];
	printf("\n Welcome to the Shortest Safest route finder ");
	printf("\n =============================================== ");
	
	// 0-Not an adjacent node
	// 1-Is an adjacent node
	
	int A[V][V] = 
	{
		{0,1,1,0,0,0,0,0,1,0},
		{1,0,1,0,0,0,0,0,0,0},
		{1,1,0,1,1,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,0,1,1,0,0,0},
		{1,0,0,1,0,0,0,0,0,1},
		{0,1,0,0,1,0,0,0,1,0}
	};
	struct graph *g = creategraph(V);
	
	int z=1,src,dest,i,j; 
	if(V==0)
		printf("\n No vertices of graph present.... ");
	else 
	{
		for(i=0;i<V;i++)
		{
			for(j=0;j<V;j++)
			{
				if(A[i][j]==1)
				{
					//w[i][j]=5; this is one of the probable lines that i am trying to change i am not sure about this at the moment
					// in place of simply writing w[i][j]=5 i will be running a loop to generate random nos. try krke dekhte hain
					//in case of any errors we will be deleting these lines
					//line 231 mein changes maare hain
					w[i][j]=(rand() % 
           (9 - 1 + 1)) + 1;
           			//the question ya yun khe ki problem yha aa rhi hain ki value variable ki value use krni hain for counting the 
           			//no. of nodes but yha pr since variable distance hain so simple division nhi ho pa rha hain
           			//need the value of variable at any cost uske baad apna program perfect hain
					D[i][j]=w[i][j];
					edge(g,i,j);
				}
				else{
					D[i][j]=0;
					w[i][j]=INF;
				}
			}
		}
		printGraph(g);
	}
		
	printf("\n Enter the source (0-9):");
    scanf("%d",&src);
    printf("\n Enter the destination (0-9):");
    scanf("%d",&dest);
    
	int k=dijkstra(w, src, dest);
	t=1;// we have fixed the value of t so that the program could work we now need to modify it so that the program can work
	s=k-t;
	do{//This loop will run unless and until the user enters a valid time 
		printf("Enter the hour min and seconds format of the time");
		scanf("%d:%d:%d", &hh, &mm, &ss);
		if((hh<25 && hh>=00) && (mm>=00 && mm<=59) && (ss>=00 && ss<=59)){//checking the time validity
		printf("Time : %d : %d : %d\n", hh, mm, ss);
	}else{
		printf("Kindly enter a real time\n");
	}
	}while((hh>24 || hh<00) || (mm<00 || mm>59) || (ss<00 || ss>59));
	/*if((hh<25 && hh>=00) && (mm>=00 && mm<=59) && (ss>=00 && ss<=59)){//checking the time validity
		printf("Time : %d : %d : %d\n", hh, mm, ss);
	}else{
		printf("Kindly enter a real time");
	}*/
	float d=0.0,e=0.0,f=0.0,g1=0.0;
	printf("Enter the day of the travel of the user");
	scanf("%d",&i1);
	if(i1==1){
		if((season>=1 && season<=3)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-mor-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-noon-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-night-summer.txt","r");
		}
		else if((season>=4 && season<=7)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-night-rainy.txt","r");
		}
		else if((season>=8 && season<=10) && (hh>=07 && hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-mor-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=12 && hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-noon-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Monday//mon-night-winter.txt","r");
		}
		}
	if(i1==2){
		if((season>=1 && season<=3)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-mor-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-noon-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-night-summer.txt","r");
		}
		else if((season>=4 && season<=7)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-night-rainy.txt","r");
		}
		else if((season>=8 && season<=10) && (hh>=07 && hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-mor-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=12 && hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-noon-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Tuesday//tue-night-winter.txt","r");
		}
		}
	if(i1==3){
		if((season>=1 && season<=3)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-mor-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-noon-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-night-summer.txt","r");
		}
		else if((season>=4 && season<=7)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-night-rainy.txt","r");
		}
		else if((season>=8 && season<=10) && (hh>=07 && hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-mor-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=12 && hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-noon-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Wednesday//wed-night-winter.txt","r");
		}
		}
	if(i1==4){
		if((season>=1 && season<=3)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-mor-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-noon-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-night-summer.txt","r");
		}
		else if((season>=4 && season<=7)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-night-rainy.txt","r");
		}
		else if((season>=8 && season<=10) && (hh>=07 && hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-mor-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=12 && hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-noon-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Thursday//thu-night-winter.txt","r");
		}
		}
	if(i1==5){
		if((season>=1 && season<=3)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-mor-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-noon-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-night-summer.txt","r");
		}
		else if((season>=4 && season<=7)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-night-rainy.txt","r");
		}
		else if((season>=8 && season<=10) && (hh>=07 && hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-mor-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=12 && hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-noon-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Friday//fri-night-winter.txt","r");
		}
		}
	if(i1==6){
		if((season>=1 && season<=3)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-mor-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-noon-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-night-summer.txt","r");
		}
		else if((season>=4 && season<=7)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-night-rainy.txt","r");
		}
		else if((season>=8 && season<=10) && (hh>=07 && hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-mor-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=12 && hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-noon-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Saturday//sat-night-winter.txt","r");
		}
	}
	if(i1==7){
		if((season>=1 && season<=3)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-mor-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-noon-summer.txt","r");
		}
		else if((season>=1 && season<=3)&&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-night-summer.txt","r");
		}
		else if((season>=4 && season<=7)&&(hh>=07&&hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=12&&hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-noon-rainy.txt","r");
		}
		else if((season>=4 && season<=7) && (hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-night-rainy.txt","r");
		}
		else if((season>=8 && season<=10) && (hh>=07 && hh<=12)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-mor-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=12 && hh<=18)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-noon-winter.txt","r");
		}
		else if((season>=8 && season<=10) &&(hh>=18 || hh<=06)){
			fptr=fopen("C://Users//HP//Desktop//Programs//c programs//Minor//Sunday//sun-night-winter.txt","r");
		}
		}
	if(fptr==NULL){
			printf("Cannot open file\n");
			return 0;
		}
	int count=0;
	while(fscanf(fptr, "%s\n",&filename)>0){//we are reading the various parameters from the mentioned file
		d=atof(filename);
		++count;
		if(count==1){
			e=d;
		}
		if(count==2){
			f=d;
		}
		if(count==3){
			g1=d;
		}
		//printf("%0.2f",d);
	}
	for(i=0;i<V;i++){
		for(j=0;j<V;j++){
			if(D[i][j]!=0){
				printf("%d-->%d : %d\t", i, j, D[i][j]);
			}
		}
		printf("\n");
	}
	/*printf("%0.2f\n",e);
	printf("%0.2f\n",f);
	printf("%0.2f",g);*/
	float safety=s*e+t*f;//safety is calculating the total safety parameter question arises s and t ki values kaise decide ho rhi hain
	printf("%0.2f\n",safety);
	if(safety>4.40){
		printf("\nWe would advise that you follow this path as the danger parameter does not exceeds the desired value it is: %0.2f",safety);
	}else{
		printf("This is the safest path possible");
	}
	float fspeed;
	if(g1>0.0 && g1<=10.0){
		fspeed=35.0;
	}	
	if(g1>10.0 && g1<=25.0){
		fspeed=25.0;
	}
	if(g1>25.0){
		fspeed=15.0;
	}
	printf("\nwe would advise the vehicular speed to be: %0.2f km/hr",fspeed);
	fclose(fptr);
	return 0;
}

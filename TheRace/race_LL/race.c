#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "simulator.h"
#include "ping.h"
#include"simpletools.h"
#include"abdrive.h"

#define W 40            //side length of a square in cm
#define W_tick 40/0.325 //side length of a square in tick
#define thetaNeg -25  //angle in ticks the robot turns each time
#define thetaPos 26   //angle in ticks the robot turns each time
#define minD 40       //minimun distance in cm to say there 
                                            //is a junction in that direction 


/**********************************************************************/
                      /*linked-list elements*/
/**********************************************************************/

struct node{
    int direction;//The final facing direction in the square(0:North,1:E,2:S,3:W)
    int squareX;
    int squareY;
    struct node *previous;
    struct node *next;
}*nodeTail=NULL;   //*nodeHead is defined in run()

struct junction{            
    struct node *juncNode;
    int front;
    int right;
    int left;
    struct junction *next;
    struct junction *previous;
}*juncHead=NULL;             //stack structure

struct route{
    struct node *pathHead;
    struct node *pathTail;
    struct route *next;
}*firstRoute=NULL,*lastRoute=NULL;

/**********************************************************************/
                      /*robot behavior*/
/**********************************************************************/
void toLeftDirection()
{
    /*turn anticlockwise(90 degree)*/
    drive_goto(thetaNeg,thetaPos);
}
void toRightDirection()
{
    /*turn cloclwise(90 degree)*/
    drive_goto(thetaPos,thetaNeg);
}
void checkDirectionWhenFinishingPoint()
{
    int dist=ping_cm(8);
    if(dist>minD)
    drive_goto(2*thetaPos,2*thetaNeg);
}
void checkDirectionWhenStartingPoint()
{
    int dist=ping_cm(8);
    if(dist<minD)
    drive_goto(2*thetaPos,2*thetaNeg);
}
int forWard(struct node *routeHead,struct node *current_square,struct node *end)
{
    /*move forward from the square where the robot is currently at 
    \to the given finishing node along the given route.
    \If no node in this list exit, the function will directly terminate and return 1.
    \If the stop node is not in this list, an error message will be print 
    \out and the function will end with a return value 1.
    \(normally exit with 0)
    \Note:the end node is BEHIND the current square.
    */
    if(routeHead==NULL) //This route is an empty list!
	return 1;
	printf("\n......forward......\n");
	struct node* p=current_square;
    
	while(p!=end)
	{
        if(p==nodeTail) //the end node not in this list
		break;		
        drive_goto(W_tick,W_tick);

        if((p->direction-p->next->direction==-1)||(p->direction-p->next->direction==3))
        toRightDirection();
        else if((p->direction-p->next->direction==1)||(p->direction-p->next->direction==-3))
        toLeftDirection();        

        p=p->next;
	}
    if((p->direction-p->previous->direction==-1)||(p->direction-p->previous->direction==3))
    toRightDirection();
    else if((p->direction-p->previous->direction==1)||(p->direction-p->previous->direction==-3))
    toLeftDirection();  
    printf(".......finish......\n\n");
	return 0;
}
int forWard_faster(struct node *routeHead,struct node *current_square,struct node *end)
{
    if(routeHead==NULL) //This route is an empty list!
	return 1;
	int straightD=1;
	struct node* p=current_square;
	while(p!=end)
	{
        if((p->direction-p->next->direction)%2==0)
        {
            straightD++;
        }
        else
        {
            drive_goto(straightD*W_tick,straightD*W_tick);
            if((p->direction-p->next->direction==-1)||(p->direction-p->next->direction==3))
            toRightDirection();
            else if((p->direction-p->next->direction==1)||(p->direction-p->next->direction==-3))
            toLeftDirection(); 

            straightD=1;
        }

        p=p->next;
	}
    drive_goto((straightD-1)*W_tick,(straightD-1)*W_tick);
	return 0;
}
int backward(struct node *routeHead,struct node *current_square,struct node *end)
{
    /*move backward from the square where the robot is currently at to the 
    \given finishing node along the given route.
    \If no node in this list, the function will directly terminate and return 1. 
    \If the stop node is not in this list,the robot will back to the starting 
    \square of this route.And the function will end with a return value 1.
    \(normally exit with 0)
    \Note:the end node should be went throught BEFORE the current square
    */
    if(routeHead==NULL) //no node in this list
	return 1;
	printf("\n......backward......\n");
	struct node* p=current_square;
	while(p!=end)
	{
        if(p==routeHead) //the stop node not in this list
		break;
        if((p->direction-p->previous->direction==1)||(p->direction-p->previous->direction==-3))
        toLeftDirection();
        else if((p->direction-p->previous->direction==-1)||(p->direction-p->previous->direction==3))
        toRightDirection();

        drive_goto(-W_tick,-W_tick);

        p=p->previous;
	}
    printf(".......finish.......\n\n");
    if(p==routeHead)
    {
        checkDirectionWhenStartingPoint();
    }
    else
    {
        if((p->direction-p->previous->direction==1)||(p->direction-p->previous->direction==-3))
            toLeftDirection();
        else if((p->direction-p->previous->direction==-1)||(p->direction-p->previous->direction==3))
            toRightDirection();
    }
	return 0;
}
int leftJunc()
{
    /*If the robot can go left,then return 1; 0 otherwise.*/
    //drive_goto(thetaNeg,thetaPos);
    //int dist=ping_cm(8);
    //drive_goto(thetaPos,thetaNeg);
    int dist = 0;
    for(int dacVal = 0; dacVal <= 160; dacVal += 8)  
    {                                               
        dac_ctr(26, 0, dacVal);                      
        freqout(11, 1, 38000);                       
        dist += input(10);
    }
    if (dist>0.48*minD)
    return 1;
    else
    return 0;
}
int frontJunc()
{
    /*If the robot can go forward,then return 1; 0 otherwise.*/
    int dist= ping_cm(8);
    if (dist>minD)
    return 1;
    else
    return 0;
}
int rightJunc()
{
    /*If the robot can go right,then return 1; 0 otherwise.*/
    //drive_goto(thetaPos,thetaNeg);
    //int dist=ping_cm(8);
    //drive_goto(thetaNeg,thetaPos);
    int dist = 0;
    for(int dacVal = 0; dacVal <= 160; dacVal += 8) 
    {                                              
        dac_ctr(27, 1, dacVal);                      
        freqout(1, 1, 38000);                        
        dist += input(2);
    }
    if (dist>0.48*minD)
    return 1;
    else
    return 0;
}



/**********************************************************************/
                      /*nodes operation*/
/**********************************************************************/
void turnLeft(struct node *aNode)
{
    aNode->direction--;
    if(aNode->direction==-1)
    aNode->direction=3;
}
void turnRight(struct node *aNode)
{
    aNode->direction++;
    if(aNode->direction==4)
    aNode->direction=0;
}
int getPositionX(struct node *previous_node)
{
    int x=0;
    switch (previous_node->direction)
    {
        case 0:x=previous_node->squareX;break;
        case 1:x=previous_node->squareX+W;break;
        case 2:x=previous_node->squareX;break;
        case 3:x=previous_node->squareX-W;break;
        default:printf("ERROR: Direction of robot in the previous square is invalid.\n");
    }
    return x;
}
int getPositionY(struct node *previous_node)
{
    int y=0;
    switch (previous_node->direction)
    {
        case 0:y=previous_node->squareY+W;break;
        case 1:y=previous_node->squareY;break;
        case 2:y=previous_node->squareY-W;break;
        case 3:y=previous_node->squareY;break;
        default:printf("ERROR: Direction of robot in the previous square is invalid.\n");
    }
    return y;
}
int isAtPoint1(struct node *ANode)
{
    /*If robot reaches point1,return 1; 0 otherwise.*/
    printf("\nx=%d,y=%d\n",ANode->squareX,ANode->squareY);
    if((ANode->squareX==20)&&(ANode->squareY==180))
    {
        return 1;
    }
    
    else
    {
        return 0;
    }
    
}
int isAtPoint2(struct node *ANode)
{
    /*If robot reaches point2,return 1; 0 otherwise.*/
    if((ANode->squareX==140)&&(ANode->squareY==60))
    return 1;
    else
    return 0;
}
int isAtPoint3(struct node *ANode)
{
    /*If robot reaches point3,return 1; 0 otherwise.*/
    if((ANode->squareX==140)&&(ANode->squareY==180))
    return 1;
    else
    return 0;
}

/*methods of node linked-list*/
struct node* createNodeList(int direction,int x,int y)
{
    /*create head node(with the given parameters) of a new node list*/
    struct node *head=(struct node*)malloc(sizeof(struct node));
	if (head==NULL)
	printf("Fail to allocate memory.");
	
	head->direction=direction;
    head->squareX=x;
    head->squareY=y;
	
	head->previous=NULL;
	head->next=NULL;
	nodeTail=head;

	return head;
}
struct node* addNode(struct node* current_node,struct node* head)
{
    /*add a node to the tail of an exist node list*/
    nodeTail->next=current_node;
    current_node->next=NULL;
    nodeTail=current_node;
    return head;
}
struct node* removeNode(struct node* startNode,struct node* stopNode,struct node* head)
{
    /*Remove nodes from an exist node list from the given 
    \start node to the stop node(exclude the stop node itself).
    \If the stop node is not in this list then the function will delete all nodes
    \excluding the head.
    \Note:startNode must be the tail of this route.
    */
    if(head==NULL)  //If there is no node in this node list
	return NULL;

	struct node* p=NULL;
	while(startNode!=stopNode)
	{
		if(startNode==head) 
		break;
		p=startNode;
		startNode=startNode->previous;
		startNode->next=NULL;
		free(p);
	}
	nodeTail=startNode;  //After while loop the startNode is the tail of this list
	return head;
}
int compareTwoNode(struct node* nodeA,struct node* nodeB)
{
    /*If they are the same node,return 1, else 0.*/
    //int directionD=nodeA->direction-nodeB->direction;
    int dx=nodeA->squareX-nodeB->squareX;
    int dy=nodeA->squareY-nodeB->squareY;
    if(dx==0&&dy==0)
    return 1;
    else
    return 0;
}
struct node* copyNodesToThisRoute(struct node* thisNodeHead,struct route* 
                routeBeingCopied,struct node* startNode,struct node* endNode)
{
    /*Add nodes(including the "endNode") to the tail of "thisNodeHead"(current route)
    \Note:the routeBeingCopied must be in a correct order
    \And the startNode should behind the endNode along the latter route*/
    struct node *p=startNode;
    while(p!=endNode->next)
    {
        struct node *p_copy=(struct node*)malloc(sizeof(struct node));
        p_copy->direction=p->direction;
        p_copy->squareX=p->squareX;
        p_copy->squareY=p->squareY;
        p_copy->previous=nodeTail;
        thisNodeHead=addNode(p_copy,thisNodeHead);        p=p->next;
        if(p==routeBeingCopied->pathTail->next)//to in case the endNode is not in the latter route
        break;
    }
    
    return thisNodeHead;
}

/*methods of junction linked-list*/
void pushAJunction(struct junction* aJunction)
{
    /*push a junction node into the junction nodes list(stack)*/
    if(juncHead!=NULL)
    juncHead->previous=aJunction;

    aJunction->next=juncHead;
    aJunction->previous=NULL;
    juncHead=aJunction;
}
struct junction* popAJunction()
{
    /*pop a junction node out of the junction nodes list(stack)
    \If the junction list is empty then return NULL.
    */
    if(juncHead==NULL)
    return NULL;
    struct junction* nearestJunction=juncHead;
    juncHead=juncHead->next;
    if(juncHead!=NULL)
    juncHead->previous=NULL;
    return nearestJunction;
}
struct junction* popJunctionTail()
{
    struct junction* tail=juncHead;

    if(tail==NULL)  //junction list is empty
    return NULL;

    if(tail->next==NULL) //only has one junction
    {
        juncHead=NULL;
    }
    else  //more than one junction
    {
        while(tail->next!=NULL)
        tail=tail->next;

        tail->previous->next=NULL;
        tail->previous=NULL;
    }
    
    return tail;
}
struct junction* getThisJunction(struct node* itsNode)
{
    /*find the junction using given node coordinates.
    \Return NULL if it's not in the list.*/
    int itsX=itsNode->squareX;
    int itsY=itsNode->squareY;
    struct junction *p=juncHead;
    int otherX=0,otherY=0;
    while(p!=NULL)
    {
        otherX=p->juncNode->squareX;
        otherY=p->juncNode->squareY;
        if(itsX==otherX&&itsY==otherY)
        break;

        p=p->next;
    }
    return p;
}
struct junction* updateThisJunction(struct junction* aJunction,
                                                    struct node* preNode)
{
    /*Note:should only be called when meet a dead end or a visited junction
    \Change the direction that the last time 
    \the robot choose to travel when at a junction square to 0;
    \
    \The preNode will has value only when meet a visited junction 
    \Otherwise it should be NULL;
    \
    \If there is no other direction that can be choosed at that junction,
    \then remove it from the junction list. 
    */
    aJunction->right%=2;
    aJunction->front%=2;
    aJunction->left%=2;

    int r=aJunction->right;
    int f=aJunction->front;
    int l=aJunction->left;

    if(getThisJunction(aJunction->juncNode)==NULL)    
    {
        if(!((r>0&&f==0&&l==0)||(r==0&&f>0&&l==0)||(r==0&&f==0&&l>0)))
        pushAJunction(aJunction);
    }
    else if(preNode!=NULL)
    {
        int dx=preNode->squareX-aJunction->juncNode->squareX;
        int dy=preNode->squareY-aJunction->juncNode->squareY;
        int directionD=preNode->direction-aJunction->juncNode->previous->direction;

        if (dx==0&&dy>0)
        {
            switch(directionD)
            {
                case -1:aJunction->right=2;break;
                case 1:aJunction->left=2;break;
                case 2:aJunction->front=2;break;
                default:printf("junction ERROR 1\n");
            }
        }
        else if(dx==0&&dy<0)
        {
            switch(directionD)
            {
                case 1:aJunction->right=2;break;
                case -3:aJunction->left=2;break;
                case 2:aJunction->front=2; break;
                default:printf("junction ERROR 2\n");
            }
        }
        else if(dx<0&&dy==0)
        {
            switch(directionD)
            {
                case 1:aJunction->left=2;break;
                case -1:aJunction->right=2;break;
                case -2:aJunction->front=2;break;
                default:printf("junction ERROR 3\n");
            }
        }
        else if(dx>0&&dy==0)
        {
            switch(directionD)
            {
                case 3:aJunction->right=2;break;
                case 1:aJunction->left=2;break;
                case 2:aJunction->front=2;break;
                default:printf("junction ERROR 4\n");
            }
        }
        else
        printf("\nUnknown ERROR!\n");
    }

    return aJunction;
}

struct node* chooseADirection(struct junction* juncNode,struct node* aNode)
{
    /*Choose direction with "right-front-left" order to make sure that the robot
    \reaches the point3 in its first route before meeting a visited junction.
    */
    if(juncNode->right==1)
    {
        juncNode->right=2;
        toRightDirection(); 
        turnRight(aNode);
    }
    else if(juncNode->front==1)
    juncNode->front=2;
    else if(juncNode->left==1)
    {
        juncNode->left=2;
        toLeftDirection();
        turnLeft(aNode);
    }
    else
    printf("ERROR!! No other direction can be choosed in this junction, which should not occur.");

    return aNode;
}
struct junction* updateJunctionList(struct junction* head)
{
    /*To check if all elements in this list are junctions*/
    struct junction *aJunction=head;
    struct junction *p=NULL;
    int r=0,f=0,l=0;

    while(aJunction!=NULL)
    {
        r=aJunction->right;
        f=aJunction->front;
        l=aJunction->left;

        if((r==2&&f==0&&l==0)||(r==0&&f==2&&l==0)||(r==0&&f==0&&l==2)||(r+f+l)==0)
        {
            p=aJunction;
            if(aJunction->previous==NULL)
            {
                if(aJunction->next!=NULL)
                aJunction->next->previous=NULL;
                aJunction=aJunction->next;
                head=aJunction;
            }    
            else
            {
                aJunction->previous->next=aJunction->next;
                if(aJunction->next!=NULL)
                aJunction->next->previous=aJunction->previous;
                aJunction=aJunction->next;
            }
            free(p);
        } 
        else
        aJunction=aJunction->next;       
    }
    return head;
}
int isInvisitedJunction(struct node* juncToBeChecked)
{
    /*If it is invisited,return 1; 0 otherwise.
    */
    if (getThisJunction(juncToBeChecked)==NULL)
    return 1;
    else
    return 0;
}

/*methods of route linked-list*/
struct route* createRouteList(struct node *nodeHead,struct node *nodeTail)
{
    /*create head node(with the given parameters) of a new node list*/
    struct route *head=(struct route*)malloc(sizeof(struct route));
	if (head==NULL)
	printf("Fail to allocate memory.");
	
	head->pathHead=nodeHead;
    head->pathTail=nodeTail;
	
	head->next=NULL;
	lastRoute=head;

	return head;
}
struct route* addRoute(struct node* nodeHead,struct node* nodeTail)
{
    /*add a route to the tail of an route list*/
    struct route *aRoute=(struct route*)malloc(sizeof(struct route));
    if (aRoute==NULL)
	printf("Fail to allocate memory to a new route.\n");

    aRoute->pathHead=nodeHead;
    aRoute->pathTail=nodeTail;

    lastRoute->next=aRoute;
    aRoute->next=NULL;
    lastRoute=aRoute;

    return firstRoute;
}

struct route* routeContainThisNode(struct node* aNode)
{
    struct route* aRoute=firstRoute;
    struct node* otherNode=NULL;
    int n=1;
    while(aRoute!=NULL)
    {
        otherNode=aRoute->pathHead;
        while(otherNode!=NULL)
        {
            if(compareTwoNode(otherNode,aNode))
            return aRoute;

            otherNode=otherNode->next;
        }
        aRoute=aRoute->next;
    }
    return NULL;
}
struct route* removeIncompleteRoutes(struct route* firstRoute)
{
    int start[2]={20,20};
    int finish[2]={140,180};
    struct route *aRoute=firstRoute,*preRoute=firstRoute;
    struct route *p=NULL;
    int headX=0,headY=0,tailX=0,tailY=0;
    while(aRoute!=NULL)
    {
        headX=aRoute->pathHead->squareX;
        headY=aRoute->pathHead->squareY;
        if(!(((headX==start[0])&&(headY==start[1])&&(tailX=finish[0])&&(tailY=finish[1]))||((headX==finish[0])&&(headY==finish[1])&&(tailX=start[0])&&(tailY=start[1]))))
        {
            p=aRoute;
            aRoute=preRoute;
            preRoute->next=aRoute->next;
            free(p);
        }
        preRoute=aRoute;
        aRoute=aRoute->next;
    }
    return firstRoute;
}
struct route* getShortestRoute(struct route* firstRoute)
{
    firstRoute=removeIncompleteRoutes(firstRoute);
    struct route *aRoute=firstRoute;
    struct node *aNode=NULL;
    int step=0;
    int minStep=0;
    int routeCounter=1;
    struct route *shortestRoute=aRoute;
    while(aRoute!=NULL)
    {
        aNode=aRoute->pathHead;
        while(aNode!=aRoute->pathTail)
        {
            step++;
            step+=abs((aNode->direction-aNode->next->direction)%2);

            aNode=aNode->next;
        }        
        step++;
        if(aRoute==firstRoute)
        minStep=step;

        printf("route %d requires %d steps\n",routeCounter,step);
        if(step<minStep)
        {
            minStep=step;
            shortestRoute=aRoute;
        }
        step=0;
        aRoute=aRoute->next;
        routeCounter++;
    }
    printf("minStep:%d\n",minStep);
    return shortestRoute;
}
void showAllRoutes()
{
    struct route *aRoute=firstRoute;
    int routeCounter=1;
    while(aRoute!=NULL)
    {
        printf("route %d goes through following nodes:\n",routeCounter);
        struct node *aNode=aRoute->pathHead;
        while(aNode!=aRoute->pathTail->next)
        {
            printf("(%d,%d,%d)\n",aNode->direction,
                    aNode->squareX,aNode->squareY);
            aNode=aNode->next;
        }
        printf("\n\n");
        aRoute=aRoute->next;
        routeCounter++;
    }

}

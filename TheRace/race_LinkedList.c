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
#define minD 50       //minimun distance in cm to say there 
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
int forWard(struct node *firstRoute,struct node *current_square,struct node *end)
{
    /*move forward from the square where the robot is currently at 
    \to the given finishing node along the given route.
    \If no node in this list exit, the function will directly terminate and return 1.
    \If the stop node is not in this list, an error message will be print 
    \out and the function will end with a return value 1.
    \(normally exit with 0)
    \Note:the end node is BEHIND the current square.
    */
    if(firstRoute==NULL) //no node in this list
	return 1;
	
	struct node* p=current_square;
	while(p!=end)
	{
		if(p==firstRoute) //the end node not in this list
		{
            printf("ERROR:In this route robot didn't go through the node(%d,%d).\n",end->squareX,end->squareY);
            return 1;
        }
        drive_goto(W_tick,W_tick);

        if(p->direction-p->next->direction==1)
        toRightDirection();
        else if(p->direction-p->next->direction==-1)
        toLeftDirection();        

        p=p->next;
	}
	return 0;
}
int backward(struct node *firstRoute,struct node *current_square,struct node *end)
{
    /*move backward from the square where the robot is currently at to the 
    \given finishing node along the given route.
    \If no node in this list, the function will directly terminate and return 1. 
    \If the stop node is not in this list,the robot will back to the starting 
    \square of this route.And the function will end with a return value 1.
    \(normally exit with 0)
    \Note:the end node should be went throught BEFORE the current square
    */
    if(firstRoute==NULL) //no node in this list
	return 1;
	
	struct node* p=current_square;
	while(p!=end)
	{
		if(p==firstRoute) //the stop node not in this list
		return 1;

        if(p->direction-p->previous->direction==1)
        toLeftDirection();
        else if(p->direction-p->previous->direction==-1)
        toRightDirection();

        drive_goto(-W_tick,-W_tick);

        p=p->previous;
	}
	return 0;
}
int leftJunc()
{
    /*If the robot can go left,then return 1; 0 otherwise.*/
    drive_goto(thetaNeg,thetaPos);
    int dist=ping_cm(8);
    drive_goto(thetaPos,thetaNeg);
    if (dist>minD)
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
    drive_goto(thetaPos,thetaNeg);
    int dist=ping_cm(8);
    drive_goto(thetaNeg,thetaPos);
    if (dist>minD)
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
}
void turnRight(struct node *aNode)
{
    aNode->direction++;
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
        default:printf("ERROR: Direction of robot in the previous square is invalid.");
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
        default:printf("ERROR: Direction of robot in the previous square is invalid.");
    }
    return y;
}
int isAtPoint1(struct node *ANode)
{
    /*If robot reaches point1,return 1; 0 otherwise.*/
    if(ANode->squareX==20&&ANode->squareY==180)
    return 1;
    else
    return 0;
}
int isAtPoint2(struct node *ANode)
{
    /*If robot reaches point2,return 1; 0 otherwise.*/
    if(ANode->squareX==140&&ANode->squareY==20)
    return 1;
    else
    return 0;
}
int isAtPoint3(struct node *ANode)
{
    /*If robot reaches point3,return 1; 0 otherwise.*/
    if(ANode->squareX==140&&ANode->squareY==180)
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
    \Note:startNode must be behind the stopNode.
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
    int directionD=nodeA->direction-nodeB->direction;
    int dx=nodeA->squareX-nodeB->squareX;
    int dy=nodeA->squareY-nodeB->squareY;
    if(directionD+dx+dy==0)
    return 1;
    else
    return 0;
}
struct node* copyNodesToThisRoute(struct node* thisNodeHead,struct route* 
                routeBeingCopied,struct node* startNode,struct node* endNode)
{
    /*Note:the routeBeingCopied must be in a correct order
    \And the startNode should behind the endNode along the latter route*/
    struct node *p=startNode;
    while(p!=endNode->previous)
    {
        struct node *p_copy=(struct node*)malloc(sizeof(struct node));
        p_copy->direction=p->direction;
        p_copy->squareX=p->squareX;
        p_copy->squareY=p->squareY;
        p_copy->previous=nodeTail;
        thisNodeHead=addNode(p_copy,thisNodeHead);

        p=p->previous;

        if(p==routeBeingCopied->pathHead->previous)
        break;
    }
    return thisNodeHead;
}

/*methods of junction linked-list*/
void pushAJunction(struct junction* aJunction)
{
    /*push a junction node into the junction nodes list(stack)*/
    aJunction->next=juncHead;
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
    return nearestJunction;
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
        int direction=aJunction->juncNode->previous->direction;
        if (dx==0&&dy>0)
        {
            switch(direction-2)
            {
                case -1:aJunction->left=2;break;
                case 1:aJunction->right=2;break;
                default:aJunction->front=2;
            }
        }
        else if(dx==0&&dy<0)
        {
            switch(direction-2)
            {
                case -1:aJunction->right=2;break;
                case 1:aJunction->left=2;break;
                default:aJunction->front=2;
            }
        }
        else if(dx<0&&dy==0)
        {
            switch(direction-2)
            {
                case 0:aJunction->left=2;break;
                case -2:aJunction->right=2;break;
                default:aJunction->front=2;
            }
        }
        else
        {
            switch(direction-2)
            {
                case 0:aJunction->right=2;break;
                case -2:aJunction->left=2;break;
                default:aJunction->front=2;
            }
        }
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
    struct junction *preJunction=head;
    struct junction *p=NULL;
    int r=0,f=0,l=0;
    while(aJunction!=NULL)
    {
        r=aJunction->right;
        f=aJunction->front;
        l=aJunction->left;
        if((r>0&&f==0&&l==0)||(r==0&&f>0&&l==0)||(r==0&&f==0&&l>0))
        {
            p=aJunction;
            aJunction=preJunction;
            preJunction->next=aJunction->next;
            free(p);
        }
        preJunction=aJunction;
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
struct route* addRoute(struct node* nodeHead)
{
    /*add a route to the tail of an route list*/
    struct route *aRoute=(struct route*)malloc(sizeof(struct route));
    if (aRoute==NULL)
	printf("Fail to allocate memory.");

    aRoute->pathHead=nodeHead;
    aRoute->pathTail=nodeTail;


    if(firstRoute==NULL)
    {
        aRoute->next=NULL;
        firstRoute=aRoute;
    }
    else
    {
        lastRoute->next=aRoute;
        aRoute->next=NULL;   
    }
    lastRoute=aRoute;
    return firstRoute;
}
struct route* correctOrder(struct route* aRoute)
{
    int startX=20,startY=20,endX=140,endY=180;
    int headX=aRoute->pathHead->squareX;
    int headY=aRoute->pathHead->squareY;
    int tailX=aRoute->pathTail->squareX;
    int tailY=aRoute->pathTail->squareY;
    if(headX==endX&&headY==endY&&tailX==startX&&tailY==startY)
    {
        struct node *aNode=aRoute->pathHead;
        struct node *temp=NULL,*next=NULL;
        while(aNode!=NULL)
        {
            next=aNode->next;

            temp=aNode->previous;
            aNode->previous=aNode->next;
            aNode->next=temp;

            aNode=next;
        }
        temp=aRoute->pathHead;
        aRoute->pathHead=aRoute->pathTail;
        aRoute->pathTail=temp;
        
        temp=next=NULL;
    }
    return aRoute;
}
struct route* routeContainThisNode(struct node* aNode)
{
    struct route* aRoute=firstRoute;
    struct node* otherNode=NULL;
    while(aRoute!=NULL)
    {
        otherNode=aRoute->pathHead;
        while(otherNode!=NULL)
        {
            if(compareTwoNode(otherNode,aNode))
            break;

            otherNode=otherNode->next;
        }
        aRoute=aRoute->next;
    }

    return correctOrder(aRoute);
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

/**********************************************************************/
                      /*For phase2*/
/**********************************************************************/
struct route* getShortestRoute(struct route* firstRoute)
{
    firstRoute=removeIncompleteRoutes(firstRoute);
    struct route *aRoute=firstRoute;
    struct node *aNode=NULL;
    int step=0;
    int minStep=0;
    struct route *shortestRoute=aRoute;
    while(aRoute!=NULL)
    {
        aNode=aRoute->pathHead;
        while(aNode!=aRoute->pathTail)
        {
            step++;
            step+=(aNode->direction-aNode->next->direction)%2;

            aNode=aNode->next;
        }        
        if(step<minStep)
        {
            minStep=step;
            shortestRoute=aRoute;
        }
        step=0;
        aRoute=aRoute->next;
    }
    return shortestRoute;
}

/**********************************************************************/
                      /*main function*/
/**********************************************************************/

void phase1()
{
    /*set primitive variables*/
    int reachPoint3=0;  //how many times the robot has reached point3
    int A=0,B=0,C=0; //check points
    int left=0,front=0,right=0;

    /*set linked-lists*/
    struct node *nodeHead=createNodeList(0,20,20);

    /*graph traversal*/
    while(A==0||B==0||C==0||juncHead!=NULL)
    {
        //move forward by a square
        drive_goto(W_tick,W_tick);

        //get environment information of current square 
        left=leftJunc();
        front=frontJunc();
        right=rightJunc();  //left/front/right only has two values:0 or 1
        printf("left=%d,front=%d,right=%d\n",left,front,right);
        
        //create a node and add it to the list
        struct node *current_node=(struct node*)malloc(sizeof(struct node));
        if(current_node==NULL)
        printf("Failed to allocate memory to a new node.");
        current_node->previous=nodeTail;
        current_node->direction=current_node->previous->direction;  //temporary
        current_node->squareX=getPositionX(current_node->previous);
        current_node->squareY=getPositionY(current_node->previous);
        nodeHead=addNode(current_node,nodeHead);

        printf("head:%d,%d,%d\n",nodeHead->direction,nodeHead->squareX,nodeHead->squareY);
        printf("previous:%d,%d,%d\n",current_node->previous->direction,current_node->previous->squareX,current_node->previous->squareY);
        printf("current:%d,%d,%d\n",current_node->direction,current_node->squareX,current_node->squareY);
        printf("tail:%d,%d,%d\n",nodeTail->direction,nodeTail->squareX,nodeTail->squareY);
        printf("-----------------------\n\n");
        

        //square recognize
        A=isAtPoint1(current_node);
        B=isAtPoint2(current_node);
        C=isAtPoint3(current_node);
        
        if(left+front+right-1>0)  //a junction
        {
            if(isInvisitedJunction(current_node))
            {
                struct junction *aJunction=(struct junction*)malloc
                                                    (sizeof(struct junction));
                aJunction->juncNode=current_node;
                aJunction->right=right;
                aJunction->front=front;
                aJunction->left=left;
                pushAJunction(aJunction);

                current_node=chooseADirection(aJunction,current_node);
                continue;
            }
            else if(reachPoint3>0)//a visited junction and have reached point3
            {
                struct junction *visitedJunc=getThisJunction(current_node);
                struct route *routeContainTheJunction=
                                routeContainThisNode(visitedJunc->juncNode);
                if(routeContainTheJunction==NULL)
                {
                    printf("ERROR:No route contain this junction.");
                    break;
                }
                visitedJunc=updateThisJunction(visitedJunc,current_node->previous);
                nodeHead=copyNodesToThisRoute(nodeHead,routeContainTheJunction,
                            visitedJunc->juncNode->previous,NULL);
                backward(nodeHead,current_node,NULL);
                juncHead=updateJunctionList(juncHead);
                C=1;
            }
            else  //meet a visited junction but didn't reach point 3
            {
                printf("Sorry.Can't handle this situation(meet a visited junction but didn't reach point 3)");
                backward(nodeHead,current_node,nodeHead);
                current_node=nodeHead;
                break;
            }
        }                
        if(C==1)
        {
            reachPoint3++;
            firstRoute=addRoute(nodeHead);
            nodeHead=nodeTail=NULL;  
            struct junction *nearestJunction=popAJunction();
            if(nearestJunction!=NULL)
            {
                struct route *routeContainTheJunction=
                                routeContainThisNode(nearestJunction->juncNode);
                int direction=routeContainTheJunction->pathTail->direction;
                int x=routeContainTheJunction->pathTail->squareX;
                int y=routeContainTheJunction->pathTail->squareY;
                struct node *copyStartNode=routeContainTheJunction
                                                        ->pathTail->previous;
                struct node *copyEndNode=nearestJunction->juncNode;
                nodeHead=createNodeList(direction,x,y);
                nodeHead=copyNodesToThisRoute(nodeHead,routeContainTheJunction,
                                            copyStartNode,copyEndNode);
                backward(nodeHead,current_node,nearestJunction->juncNode);
                updateThisJunction(nearestJunction,NULL);
                current_node=nearestJunction->juncNode;
                current_node=chooseADirection(nearestJunction,current_node);
                juncHead=updateJunctionList(juncHead);
            }
            break;
        }

        if(left==front==right==0)           //a dead end
        {
            struct junction* nearestJunction=popAJunction();
            if(nearestJunction==NULL)
            {
                printf("Unknown error occur!\n");
                printf("Description:Didn't complete graph traversal,meet a dead end but no more junctions in the list.");
                break;
            }
            backward(nodeHead,current_node,nearestJunction->juncNode);
            nodeHead=removeNode(current_node,nearestJunction->juncNode,nodeHead);
            current_node=nodeTail;
            nearestJunction=updateThisJunction(nearestJunction,NULL);
            current_node=chooseADirection(nearestJunction,current_node);
        }
        else if((left+front+right)%3==1)   //not a junction
        {
            if(left)
            {
                toLeftDirection();  //robot's behavior
                turnLeft(current_node);  //data handle
            }
            if(right)
            {
                toRightDirection();
                turnRight(current_node);
            }
        }
        else
        printf("ERROR: Unknown condition");
        
    }
}
void phase2()
{
    struct route* shortestRoute=getShortestRoute(firstRoute);
    printf("\n------------------phase2 start---------------------\n");
    forWard(shortestRoute,shortestRoute->pathHead,shortestRoute->pathTail);

}

int main()
{
    drive_setRampStep(32);
    drive_speed(25,25);
    simulator_startNewSmokeTrail();
    printf("\n--------------------Preparing----------------------\n");
    drive_goto(0.25*W_tick,0.25*W_tick);  //to get to the center of the start point 
    printf("\n------------------phase1 start---------------------\n");
    phase1();
    printf("\n------------------Calculating---------------------\n");
    phase2();
    simulator_stopSmokeTrail();
    return 0;
}
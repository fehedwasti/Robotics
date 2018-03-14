#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "simulator.h"
#include "ping.h"

#define W 40            //side length of a square in cm
#define W_tick 40/0.325 //side length of a square in tick
#define theta 90*0.284  //angle in ticks the robot turns each time
#define minD 20/0.325   //minimun distance in ticks to say there 
                                            //is a junction in that direction 


/**********************************************************************/
                      /*linked-list elements*/
/**********************************************************************/

struct node{
    int direction;//The final facing direction in current square(0:North,1:E,2:S,3:W)
    int squareX;
    int squareY;
    struct node *previous;
    struct node *next;
}*nodeTail;   //*nodeHead is defined in run()

struct junction{            
    struct node *juncNode;
    int front;
    int right;
    int left;
    struct junction *next;
}*juncHead;             //stack structure

struct route{
    struct node *pathHead;
    struct node *pathTail;
    struct route *next;
};

/**********************************************************************/
                      /*robot behavior*/
/**********************************************************************/
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
    if(routeHead==NULL) //no node in this list
	return 1;
	
	struct node* p=current_square;
	while(p!=end)
	{
		if(p==routeHead) //the end node not in this list
		{
            printf("ERROR:In this route robot didn't go through 
                     the node(%d,%d).\n",stopNode->squareX,stopNode->squareY);
            return 1;
        }
        if(p->direction-p->next->direction==1)
        toRightDirection();
        else if(p->direction-p->next->direction==-1)
        toLeftDirection();

        drive_goto(W_tick,W_tick);

        p=p->next;
	}
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
	
	struct node* p=current_square;
	while(p!=end)
	{
		if(p==routeHead) //the stop node not in this list
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
void toLeftDirection()
{
    /*turn anticlockwise(90 degree)*/
    drive_goto(-theta,theta);
}
void toRightDirection()
{
    /*turn cloclwise(90 degree)*/
    drive_goto(theta,-theta);
}
int leftJunc()
{
    /*If the robot can go left,then return 1; 0 otherwise.*/
    drive_goto(-theta,theta);
    int dist=ping_cm(8);
    drive_goto(theta,-theta);
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
    drive_goto(theta,-theta);
    int dist=ping_cm(8);
    drive_goto(-theta,theta);
    if (dist>minD)
    return 1;
    else
    return 0;
}

/**********************************************************************/
                      /*For phase2*/
/**********************************************************************/
struct route* shortestPath(struct route* routeHead)
{
    ;
}

/**********************************************************************/
                      /*nodes operation*/
/**********************************************************************/
void turnLeft(struct node *aNode)
{
    aNode->direction--;
}
void turnRight(struct node *node_being_changed)
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
        default:printf("ERROR: Direction of robot in the previous square is invalid.")
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
        default:printf("ERROR: Direction of robot in the previous square is invalid.")
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
    current_node->previous=nodeTail;
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
struct node* copyNodesToThisRoute(struct node* thisNodeHead,struct node* 
                routeHeadToCopied,struct node* startNode,struct node* endNode)
{
;
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
struct junction* updateThisJunction(struct junction* juncNode)
{
    /*Note:should only be called when meet a dead end or a visited junction
    \Change the direction that the last time 
    \the robot choose to travel when at a junction square to 0;
    \And if there is no other direction that can be choosed at that junction,
    \then remove it from the junction list. 
    */
    juncNode->right%=2;
    juncNode->front%=2;
    junction->left%=2;

    int r=juncNode->right;
    int f=juncNode->front;
    int l=juncNode->left;
    if(!((r==2&&f==0&&l==0)||(r==0&&f==2&&l==0)||(r==0&&f==0&&l==2)))
    pushAJunction(juncNode);

    return juncNode
}

int chooseADirection(struct junction* juncNode,struct node* aNode)
{
    /*Choose direction with "right-front-left" order to make sure that the robot
    \reaches the point3 in its first route before meeting a visited junction.
    */
    if(juncNode->right==1)
    {
        juncNode->right=2;
        toRightDirection(); //robot's behavior.
        turnRight(aNode);  //data handle.
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
    printf("ERROR!! No other direction can be choosed 
                                in this junction, which should not occur.");

    return aNode;
}
struct junction* updateJunctionList(struct junction* head)
{
    ;
    return head;
}
int isInvisitedJunction(struct node* juncToBeChecked)
{
    /*traverse the junction list to check whether this junction is visited.
    \If it is invisited,return 1; 0 otherwise.
    */
    struct node *p=juncHead;
    while(p!=NULL)
    {
        if(p->juncNode==juncToBeChecked->juncNode)
        return 1;

        p=p->next;
    }
    return 0;
}

/*methods of route linked-list*/
struct route* createRouteList(struct route *routeHead)
{
    return routeHead;
}
struct route* getTailOfOneRoute(struct route* routesHead,int index)
{
    if(index==1)
    return routesHead->pathTail;
}

/**********************************************************************/
                      /*main function*/
/**********************************************************************/

void run()
{
    /*set primitive variables*/
    int reachPoint3=0;  //how many times the robot has reached point3
    int A=0,B=0,C=0; //check points
    int left=0,front=0,right=0;

    /*set linked-lists*/
    struct node *nodeHead=createNodeList(0,20,20);
    juncHead=NULL; //already been declared at top(with the declaration of struct junction)
    struct route *routeHead=createRouteList();

    /*graph traversal*/
    while((A!=0&&B!=0&&C!=0)||juncHead!=NULL)
    {
        //move forward by a square
        drive_goto(W_tick,W_tick);

        //get environment information of current square 
        left=leftJunc();
        front=frontJunc();
        right=rightJunc();  //left/front/right only has two values:0 or 1
        
        //create a node and add it to the list
        struct node *current_node=(struct node*)malloc(sizeof(struct node));
        current_node->direction=current_node->previous->direction;  //temporary
        current_node->squareX=getPositionX(current_node->previous);
        current_node->squareY=getPositionY(currency_node->previous);
        nodeHead=addNode(current_node,nodeHead);

        //square recognize
        A=isAtPoint1(current_node);
        B=isAtPoint2(current_node);
        C=isAtPoint3(current_node);
        reachPoint3+=C;
        
        if(left==front==right==0)           //a dead end
        {
            struct junction* nearestJunction=popAJunction();
            if(nearestJunction==NULL)
            {
                printf("Unknown error occur!\n");
                printf("Description:Didn't complete graph traversal,
                        meet a dead end but no more junctions in the list.");
                break;
            }
            backward(nodeHead,nearestJunction);
            nodeHead=removeNode(current_node,nearestJunction,nodeHead);
            current_node=nodeTail;
            nearestJunction=updateThisJunction(nearestJunction);
            current_node=chooseDirection(nearestJunction,current_node);
        }
        else if((left+front+right)%3==1)   //not a junction
        {
            if(left)
            {
                toLeftDirection();
                turnLeft(current_node);
            }
            if(right)
            {
                toRightDirection();
                turnRight(current_node);
            }
        }
        else                               //a junction
        {
            if (isInvisitedJunction(current_node))
            {
                struct junction *aJunction=(struct junction*)malloc
                                                    (sizeof(struct junction));
                aJunction->juncNode=current_node;
                aJunction->right=right;
                aJunction->front=front;
                aJunction->left=left;
                pushAJunction(aJunction);

                current_node=chooseADirection(aJunction,current_node);
            }
            else if((!isInvisitedJunction())&&reachPoint3>0)
            {
                struct junction *nearestJunction=popAJunction();
                backward(nodeHead,current_node,nearestJunction);
                if (reachPoint3==1)//first route after reaching the finish point
                {
                    /*
                    struct node *1stRoute_tail=getTailOfOneRoute(routeHead,1);
                    int direction=1stRoute_tail->direction;
                    int x=1stRoute_tail->squareX;
                    int y=1stRoute_tail->squareY;
                    struct node *another_nodeHead=createNodeList(direction,x,y);
                    another_nodeHead=copyNodesToThisRoute();
                    */
                }
                else
                {
                    //forWard(path,start,end);
                    reachPoint3+=1;
                    //...
                }
                //...
            }
            else
            printf("Error. Can't hanle this situation");
        }

        //.....
        
    }

    
}


int main()
{
    drive_goto(0.25*W_tick,0.25*W_tick);  //to get to the center of the start point 
    run();
    return 0;
}
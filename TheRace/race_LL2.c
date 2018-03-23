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
	printf("forwarding......\n");
	struct node* p=current_square;
    
	while(p!=end)
	{
        if(p==nodeTail) //the end node not in this list
		break;

        printf("(%d,%d,%d)\n",p->direction,p->squareX,p->squareY);
		
        drive_goto(W_tick,W_tick);

        if((p->direction-p->next->direction==-1)||(p->direction-p->next->direction==3))
        toRightDirection();
        else if((p->direction-p->next->direction==1)||(p->direction-p->next->direction==-3))
        toLeftDirection();        

        p=p->next;
        printf("one movement finished\n");
	}
    if((p->direction-p->previous->direction==-1)||(p->direction-p->previous->direction==3))
    toRightDirection();
    else if((p->direction-p->previous->direction==1)||(p->direction-p->previous->direction==-3))
    toLeftDirection();  

	return 0;
}
int forWard_faster(struct node *routeHead,struct node *current_square,struct node *end)
{
    if(routeHead==NULL) //This route is an empty list!
	return 1;
	int straightD=0;
	struct node* p=current_square;
	while(p!=end)
	{
		if(p==routeHead) //the end node not in this list
		{
            printf("ERROR:In this route robot didn't go through the node(%d,%d).\n",end->squareX,end->squareY);
            return 1;
        }

        if((p->direction-p->next->direction)%2==0)
        {
            straightD++;
        }
        else
        {
            drive_goto(straightD*W_tick,straightD*W_tick);
            if(p->direction-p->next->direction==1)
            toRightDirection();
            else if(p->direction-p->next->direction==-1)
            toLeftDirection();   

            straightD=0;
        }

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
	 printf("bacwarding......\n");
	struct node* p=current_square;
	while(p!=end)
	{
        printf("(%d,%d,%d)\n",p->direction,p->squareX,p->squareY);
		
        if(p==routeHead) //the stop node not in this list
		break;
        printf("routeHead(%d,%d,%d)\n",routeHead->direction,
                    routeHead->squareX,routeHead->squareY);
        if((p->direction-p->previous->direction==1)||(p->direction-p->previous->direction==-3))
        toLeftDirection();
        else if((p->direction-p->previous->direction==-1)||(p->direction-p->previous->direction==3))
        toRightDirection();

        drive_goto(-W_tick,-W_tick);

        p=p->previous;
	}
    printf("---end---\n");
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
    
    printf("heallllllllo\n");
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
        printf("previousDirection:%d, directionD:%d\n",
                preNode->direction,directionD);
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
    struct junction *p=NULL,*test=head;
    int r=0,f=0,l=0;
    while(test!=NULL)
    {
        printf("(%d,%d)\n",test->juncNode->squareX,test->juncNode->squareY);
        test=test->next;
    }
    while(aJunction!=NULL)
    {
        r=aJunction->right;
        f=aJunction->front;
        l=aJunction->left;
        printf("checking the junction(%d,%d)\n",
                aJunction->juncNode->squareX,aJunction->juncNode->squareY);
        printf("r=%d,f=%d,l=%d\n",r,f,l);

        if((r==2&&f==0&&l==0)||(r==0&&f==2&&l==0)||(r==0&&f==0&&l==2)||(r+f+l)==0)
        {
            printf("start removing a junction\n");
            p=aJunction;
            if(aJunction->previous==NULL)
            {
                printf("This junction is a head\n");
                if(aJunction->next!=NULL)
                aJunction->next->previous=NULL;
                aJunction=aJunction->next;
                head=aJunction;
            }    
            else
            {
                printf("not a head\n");
                aJunction->previous->next=aJunction->next;
                if(aJunction->next!=NULL)
                aJunction->next->previous=aJunction->previous;
                aJunction=aJunction->next;
            }
            free(p);
            printf("removed a junction\n");
        } 
        else
        aJunction=aJunction->next;       
    }
    test=head;
    while(test!=NULL)
    {
        printf("(%d,%d)\n",test->juncNode->squareX,test->juncNode->squareY);
        test=test->next;
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
struct route* correctOrder(struct route* aRoute)
{
    if(aRoute==NULL)
    return NULL;

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
struct node* correctDirection(struct node* nodeHead,struct node* start,struct node* end)
{
    /*after meeting a visited junction, correct the direction from
    this visited junction to the tempLastJunction,then store into route list.
    */
    if(nodeHead==NULL)
    return NULL;

    struct node* p=start;
    while(p!=end->previous)
    {
        p->direction-=2;

        if(p->direction==-1)
        p->direction=3;
        else if(p->direction==-2)
        p->direction=2;

        printf("changing direction to:(%d,%d,%d)",p->direction,p->squareX,p->squareY);
        p=p->previous;
    }
    return nodeHead;
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
void showAllRoutes()
{
    struct route *aRoute=firstRoute;
    while(aRoute!=NULL)
    {
        struct node *aNode=aRoute->pathHead;
        while(aNode!=aRoute->pathTail->next)
        {
            printf("(%d,%d,%d)\n",aNode->direction,
                    aNode->squareX,aNode->squareY);
            aNode=aNode->next;
        }
        printf("\n\n");
        aRoute=aRoute->next;
    }

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
    int squaresNumber=0;

    /*set linked-lists*/
    struct node *nodeHead=createNodeList(0,20,20);
    struct node *current_node=NULL;
    /*graph traversal*/
    while(A==0||B==0||reachPoint3==0||juncHead!=NULL||squaresNumber<17)
    {
        printf("A=%d,B=%d,C=%d\n",A,B,C);
        //move forward by a square
        drive_goto(W_tick,W_tick);

        //get environment information of current square 
        left=leftJunc();
        front=frontJunc();
        right=rightJunc();  //left/front/right only has two values:0 or 1
        printf("left=%d,front=%d,right=%d\n",left,front,right);
        
        //create a node and add it to the list
        current_node=(struct node*)malloc(sizeof(struct node));
        if(current_node==NULL)
        printf("Failed to allocate memory to a new node.\n");
        current_node->previous=nodeTail;
        current_node->direction=current_node->previous->direction;  //temporary
        current_node->squareX=getPositionX(current_node->previous);
        current_node->squareY=getPositionY(current_node->previous);
        nodeHead=addNode(current_node,nodeHead);
        squaresNumber++;

        printf("head:%d,%d,%d\n",nodeHead->direction,nodeHead->squareX,nodeHead->squareY);
        printf("previous:%d,%d,%d\n",current_node->previous->direction,current_node->previous->squareX,current_node->previous->squareY);
        printf("current:%d,%d,%d\n",current_node->direction,current_node->squareX,current_node->squareY);
        printf("tail:%d,%d,%d\n",nodeTail->direction,nodeTail->squareX,nodeTail->squareY);        

        //square recognize
        A+=isAtPoint1(current_node);
        B+=isAtPoint2(current_node);
        C=isAtPoint3(current_node);
        printf("6.A=%d,B=%d,C=%d\n",A,B,C);
        
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
                printf("\nThis is an invisited junction.\n");
                printf("-----------------------\n\n");
                continue;
            }
            else if(reachPoint3>0)//a visited junction and have reached point3
            {   
                printf("\nThis is a visited junction.\n");
                struct junction *visitedJunc=getThisJunction(current_node);
                printf("get visited junc(%d,%d,%d)\n",
                                    visitedJunc->juncNode->direction,
                visitedJunc->juncNode->squareX,visitedJunc->juncNode->squareY);

                struct route *routeContainTheJunction=
                                routeContainThisNode(visitedJunc->juncNode);
                printf("\nThe route contain it:start(%d,%d),end(%d,%d)\n",
                            routeContainTheJunction->pathHead->squareX,
                            routeContainTheJunction->pathHead->squareY,
                            routeContainTheJunction->pathTail->squareX,
                            routeContainTheJunction->pathTail->squareY);

                if(routeContainTheJunction==NULL)
                {
                    printf("\nERROR:No route contain this junction.\n");
                    break;
                }
                visitedJunc=updateThisJunction(visitedJunc,current_node->previous);
                printf("update visited junc info\n");

                backward(nodeHead,current_node,NULL);
                printf("backwards\n");
                

                nodeHead=copyNodesToThisRoute(nodeHead,routeContainTheJunction,
                            visitedJunc->juncNode->previous,
                            routeContainTheJunction->pathHead);
                printf("copy the rest path\n");          
                
                
                //checkDirectionWhenFinishingPoint();
                juncHead=updateJunctionList(juncHead);
                printf("finish update whole junction list");
                C=1;
                current_node=nodeHead;
                
            }
            else  //meet a visited junction but didn't reach point 3
            {
                printf("\nSorry.Can't handle this situation(meet a visited junction but didn't reach point 3)\n");
                backward(nodeHead,current_node,nodeHead);
                current_node=nodeHead;
                break;
            }
        }                
        if(C==1)
        {
            printf("\nThis is the finishing point.\n");
            printf("-----------------------\n\n");
            printf("-------------------------------------------------------\n");
            reachPoint3++;
            printf("reach point=%d\n",reachPoint3);

            backward(nodeHead,current_node,nodeHead);

            if(reachPoint3==1)
            firstRoute=createRouteList(nodeHead,nodeTail);
            else
            firstRoute=addRoute(nodeHead,nodeTail);

            printf("One route complete: start(%d,%d),end(%d,%d)\n",
                    lastRoute->pathHead->squareX,lastRoute->pathHead->squareY,
                    lastRoute->pathTail->squareX,lastRoute->pathTail->squareY);

            nodeHead=nodeTail=NULL;  

            struct junction *firstJunction=popJunctionTail();
            
            if(firstJunction!=NULL)
            {
                printf("first junction is at (%d,%d)\n",
                                    firstJunction->juncNode->squareX,
                                    firstJunction->juncNode->squareY);

                struct route *routeContainTheJunction=
                                routeContainThisNode(firstJunction->juncNode);
                if (routeContainThisNode==NULL)
                {
                    printf("ERROR when search a route containing the nearest junction!");
                    break;
                }
                printf("The route contain the nearest junction: start(%d,%d),end(%d,%d)\n",
                                    routeContainTheJunction->pathHead->squareX,
                                    routeContainTheJunction->pathHead->squareY,
                                    routeContainTheJunction->pathTail->squareX,
                                    routeContainTheJunction->pathTail->squareY);

                int direction=routeContainTheJunction->pathHead->direction;
                int x=routeContainTheJunction->pathHead->squareX;
                int y=routeContainTheJunction->pathHead->squareY;
                nodeHead=createNodeList(direction,x,y);
                current_node=nodeHead;
                nodeTail=nodeHead;

                printf("route contain this junction___\n");
                struct node *testNode=routeContainTheJunction->pathHead;
                while(testNode!=NULL)
                {
                    printf("(%d,%d,%d)-->\n",testNode->direction,
                                testNode->squareX,testNode->squareY);
                    testNode=testNode->next;
                }

                printf("A new route started: start at(%d,%d)\n",
                                        nodeHead->squareX,nodeHead->squareY);

                struct node *copyStartNode=routeContainTheJunction->pathHead->next;
                struct node *copyEndNode=firstJunction->juncNode; 
                
                nodeHead=copyNodesToThisRoute(nodeHead,routeContainTheJunction,
                                            copyStartNode,copyEndNode);

                if(current_node!=nodeHead)
                {
                    printf("some error happens\n");
                    printf("current_node(%d,%d,%d)\n",current_node->direction,
                                        current_node->squareX,current_node->squareY);
                    printf("nodeHead(%d,%d,%d)\n",nodeHead->direction,nodeHead->squareX
                                        ,nodeHead->squareY);
                    printf("current_node->next(%d,%d,%d)\n",current_node->next->direction,
                                        current_node->next->squareX,current_node->next->squareY);
                    exit(1);
                }                
                forWard(nodeHead,current_node,nodeTail);  
                printf("forward complete\n");
                printf("nodeHead(%d,%d,%d)\n",nodeHead->direction,
                                nodeHead->squareX,nodeHead->squareY);
                printf("nodeTail(%d,%d,%d)\n",nodeTail->direction,
                                nodeTail->squareX,nodeTail->squareY);
                current_node=nodeTail;
                current_node->direction=firstJunction->juncNode->previous->direction;
                current_node=chooseADirection(firstJunction,current_node);
                updateThisJunction(firstJunction,NULL);
                juncHead=updateJunctionList(juncHead);
            }
            printf("-------------------------------------------------------\n");
            continue;
        }

        if(left==front==right==0)           //a dead end
        {
            printf("\nThis is a dead end.\n");
            struct junction* nearestJunction=popAJunction();
            if(nearestJunction==NULL)
            {
                backward(nodeHead,current_node,nodeHead);
                break;
            }
            backward(nodeHead,current_node,nearestJunction->juncNode);
            nodeHead=removeNode(current_node,nearestJunction->juncNode,nodeHead);
            current_node=nodeTail;
            current_node->direction=current_node->previous->direction;
            nearestJunction=updateThisJunction(nearestJunction,NULL);
            current_node=chooseADirection(nearestJunction,current_node);
        }
        else if((left+front+right)%3==1)   //not a junction
        {
            printf("\nThis is not a junction.\n");
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
        printf("\nERROR: Unknown condition\n");
        printf("-----------------------\n\n");
    }
    printf("-----------------------------\n");
    printf("  Graph Traversal Completed  \n");
    printf("-----------------------------\n");
    printf("Returning to the start point.\n");
    printf("hellllo\n");
    //backward(lastRoute->pathHead,current_node,lastRoute->pathHead);
    printf("2222222\n");
    printf("3333333\n");
    printf("\n------------------phase1 finish---------------------\n");
}
void phase2()
{
    printf("\n------------------Calculating---------------------\n");
    showAllRoutes();
    struct route* shortestRoute=getShortestRoute(firstRoute);
    printf("\n------------------phase2 start---------------------\n");
    drive_setRampStep(64);
    drive_speed(32,32);
    forWard(shortestRoute->pathHead,shortestRoute->pathHead,shortestRoute->pathTail);   
    printf("Reached finishing point.");
}

int main()
{
    drive_speed(128,128);
    simulator_startNewSmokeTrail();
    printf("\n--------------------Preparing----------------------\n");
    drive_goto(0.25*W_tick,0.25*W_tick);  //to get to the center of the start point 
    printf("          Reached center of the start square.          ");
    printf("\n------------------phase1 start---------------------\n");
    phase1();
    pause(500);
    phase2();
    printf("\n------------------phase2 finish---------------------\n");
    simulator_stopSmokeTrail();
    return 0;
}
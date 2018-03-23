#include "race.c"

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
        //move forward by a square
        drive_goto(W_tick,W_tick);

        //get environment information of current square 
        left=leftJunc();
        front=frontJunc();
        right=rightJunc();  //left/front/right only has two values:0 or 1
       
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

        //square recognize
        A+=isAtPoint1(current_node);
        B+=isAtPoint2(current_node);
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
                printf("\nThis is an invisited junction.\n");
                printf("-----------------------\n\n");
                continue;
            }
            else if(reachPoint3>0)//a visited junction and have reached point3
            {   
                printf("\nThis is a visited junction.\n");
                printf("-----------------------\n\n");
                struct junction *visitedJunc=getThisJunction(current_node);

                struct route *routeContainTheJunction=
                                routeContainThisNode(visitedJunc->juncNode);

                if(routeContainTheJunction==NULL)
                {
                    printf("\nERROR:No route contain this junction.\n");
                    break;
                }
                visitedJunc=updateThisJunction(visitedJunc,current_node->previous);

                nodeHead=copyNodesToThisRoute(nodeHead,routeContainTheJunction,
                            visitedJunc->juncNode->next,
                            routeContainTheJunction->pathTail);
                
                juncHead=updateJunctionList(juncHead);
                C=1;
                
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
            reachPoint3++;
            if(reachPoint3==1)
            {
                printf("\nThat is the finishing point.\n");
                printf("-----------------------\n\n");
                firstRoute=createRouteList(nodeHead,nodeTail);
            }            
            else
            firstRoute=addRoute(nodeHead,nodeTail);
            printf("-------Current route list: %d routes stored---------------\n",reachPoint3);
            

            struct junction *firstJunction=popJunctionTail();
            
            if(firstJunction!=NULL)
            {
                int mark=0;
                struct route *routeContainTheJunction=
                                routeContainThisNode(firstJunction->juncNode);
                if (routeContainTheJunction==lastRoute)
                {
                    backward(nodeHead,current_node,firstJunction->juncNode); 
                }
                else
                {
                    backward(nodeHead,current_node,nodeHead);
                    mark++;
                }

                int direction=routeContainTheJunction->pathHead->direction;
                int x=routeContainTheJunction->pathHead->squareX;
                int y=routeContainTheJunction->pathHead->squareY;
                nodeHead=createNodeList(direction,x,y);
                current_node=nodeHead;
                nodeTail=nodeHead;                

                printf("\n----------A new route start---------------\n");

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
                if(mark==1)   
                forWard(nodeHead,current_node,nodeTail);  
                current_node=nodeTail;
                current_node->direction=firstJunction->juncNode->previous->direction;
                current_node=chooseADirection(firstJunction,current_node);
                updateThisJunction(firstJunction,NULL);
                juncHead=updateJunctionList(juncHead);
            }
            continue;
        }
        if(left==front==right==0&&C==0)           //a dead end
        {
            printf("\nThis is a dead end.\n");
            struct junction* nearestJunction=popAJunction();            
            if(nearestJunction==NULL)
            {
                printf("-----------------------\n\n");
                backward(nodeHead,current_node,nodeHead);
                current_node=nodeHead;
                break;
            }
            struct route *theRoute=routeContainThisNode(nearestJunction->juncNode);
            if(theRoute==NULL)
            {
                backward(nodeHead,current_node,nearestJunction->juncNode);
                nodeHead=removeNode(current_node,nearestJunction->juncNode,nodeHead);                
            }
            else
            {
                backward(nodeHead,current_node,NULL);
                nodeHead=removeNode(current_node,nodeHead,nodeHead);
                forWard(theRoute->pathHead,theRoute->pathHead,nearestJunction->juncNode);
                nodeHead=copyNodesToThisRoute(nodeHead,theRoute,theRoute->pathHead->next,nearestJunction->juncNode);
            }
            theRoute=NULL;
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
    backward(nodeHead,current_node,nodeHead);
    printf("\n------------------------------------------------------\n");
    printf("\n              Graph Traversal Completed               \n");
    //printf("\n------------------PHASE 1 FINISH----------------------\n");
}

void phase2()
{
    printf("\n-------------Searching the Shortest Route-----------\n");
    showAllRoutes();
    struct route* shortestRoute=getShortestRoute(firstRoute);
    printf("\n------------------PHASE 2 START---------------------\n");
    forWard(shortestRoute->pathHead,shortestRoute->pathHead,shortestRoute->pathTail);   
}
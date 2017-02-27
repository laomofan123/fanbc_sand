/***************************************************************
*2个结构体一个是存放链表头、链表尾和当前数据数量，一个是链表的结
*构体，存放数据。定义队列结构体的指针，创建队列的时候create函数
*malloc动态空间，给定义的队列空间分配实体。具体的函数有创建函数
*头显示，尾部加上，头读取，判空，判满*************************/
#include <stdio.h>
#include <stdlib.h>

#define Error( str )  FatalError( str )
#define FatalError( str ) fprintf( stderr, "%s\n", str),exit(1)

typedef int ElementType;
#define MAXQUEUE 10

typedef struct node
{
	ElementType data;
	struct node* nextNode;
}Node;

typedef struct queue
{
	Node* front;
	Node* rear;
	int items;
}*ptrQueue;
typedef ptrQueue Queue;
int IsEmpty(Queue q);
int IsFull(Queue q);
Queue CreateQueue(void);
void DisposeQueue(Queue q);
void MakeEmpty(Queue q);
void Enqueue(ElementType x,Queue q);
ElementType Front(Queue q);
void Dequeue(Queue q);
ElementType FrontAndDequeue(Queue q);

int main(void)
{
	Queue sqQueue;
	sqQueue = CreateQueue();//定义的都是指针，malloc给其分配空间
	if(IsEmpty(sqQueue))
		printf("created empty queue!\n");
	int value = 0;
	printf("data of queue is front->rear: \n");	
	while(!IsFull(sqQueue))
	{
		Enqueue(value*value,sqQueue);
		printf("%d\n",value*value);
		value++;
	}
	printf("queue is full!\n");
	printf("items = %d\n",sqQueue->items);
	ElementType frontQueue;
	while(sqQueue->items)
	{
		frontQueue = Front(sqQueue);
		printf("front of queue:%d\n",frontQueue);
		Dequeue(sqQueue);
		printf("items = %d\n",sqQueue->items);
	}

	
	frontQueue = Front(sqQueue);
	printf("after runned dequeue,front of queue is :%d\n",frontQueue);
	DisposeQueue(sqQueue);
	
	printf("test is over!\n");
	return 0;
}

/************shi fou wei empty********************/
int IsEmpty(Queue q)
{
	return q->items == 0;
}

/************shi fou wei full*********************/
int IsFull(Queue q)
{
	return q->items == MAXQUEUE;
}

/*************create queue*************************/
Queue CreateQueue(void)
{
	Queue q;
	q = (Queue )malloc(sizeof(struct queue));
	if(NULL == q)
		Error("kong jian bu zu");
	q->front = (Node*)malloc(sizeof(Node));
	if(NULL == q->front)
		Error("kong jian bu zu");
	q->rear = (Node*)malloc(sizeof(Node));
	if(NULL == q->rear)
		Error("kong jian bu zu");
	q->items = 0;
	return q;
}
/***********release queue**********************/
void DisposeQueue(Queue q)
{
	MakeEmpty(q);
	free(q);
	q = NULL;
}

/*********empty queue********************************/
void MakeEmpty(Queue q)
{
	if(q == NULL)
		Error("must createqueue at first\n");
	while(!IsEmpty(q))
		Dequeue(q);
	//printf("where duan error\n");
}
/****************out of queue*************************/
void Dequeue(Queue q)
{
	if(IsEmpty(q))
		Error("queue is empty\n");
	Node* pnode;
	pnode = q->front;
	q->front = q->front->nextNode;
	free(pnode);
	
	q->items--;
	if(q->items == 0);
	
	return;
}

/***************join in queue**************************/
void Enqueue(ElementType x,Queue q)
{
	if(IsFull(q))
		Error("queue is full\n");
	Node* pnode;
	pnode = (Node*)malloc(sizeof(Node));
	if(NULL == pnode)
		Error("kong jian bu zu\n");
	pnode->data = x;
	pnode->nextNode = NULL;
	if(IsEmpty(q))
		q->front = pnode;
	else 
		q->rear->nextNode = pnode;
	q->rear = pnode;
	q->items++;
	printf("save in queue is ok!\n");
	return;
}

/******************return data of front queu***********/
ElementType Front(Queue q)
{
	if(!IsEmpty(q))
		return q->front->data;
	Error("queue is empty\n");
	return 0;
}
/**************return data of front queue and dequeue the data*****/
ElementType FrontAndDequeue(Queue q)
{
	ElementType x = 0;
	if(IsEmpty(q))
		Error("queue is empty\n");
	else
	{
		q->items--;
		x = q->front->data;
		q->front = q->front->nextNode;
	}
	
	return x;
}

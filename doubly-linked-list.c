/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [jinyounglee] [2020039063] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


/*initialize에서 이중포인터를 매개변수로 받는 이유는 h가 가리키는 *h의 값을 동적할당하는 등 직접 변경하기 위해서이다.
singly-linked-list의 initialize에서는 h값을 변경할 필요가 없어 싱글포인터를 매개변수로 받는다. 
대신, 새로운 headNode형 단일포인터를 생성하고 메모리를 할당한 후, 그 단일포인터를 반환한다. */
int initialize(headNode** h) {

	//리스트 자체가 존재하면
	if(*h!=NULL)    
		freeList(*h);

	//헤드노드 메모리 할당 
	*h=(headNode*)malloc(sizeof(headNode));
	(*h)->first=NULL;
	return 1;
}


/*freeList에서 싱글포인터를 매개변수로 받은 이유는 initialize와 달리 h를 동적할당하는 등 변경할 필요가 없기 때문이다.*/
int freeList(headNode* h){
	listNode* p=h->first;

	//헤드노드가 존재하면, 메모리 해제하기
	while(p->rlink!=NULL)
	{	
		p=p->rlink;
		free(p->llink);		//이전 노드 메모리 해제 
	}
	//p가 마지막노드일 때
	free(p);	//마지막노드 메모리 해제 
	free(h);    //헤드노드 메모리 해제    
	return 0;
}


/* 리스트 출력하는 함수 */
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	//노드가 없을 경우 
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	//노드가 있을 경우, 모든 노드의 값 출력 
	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	//노드가 존재하지 않을 때   
	if(h->first==NULL) 
	{
		h->first=newnode; 	//새로운 노드를 헤드노드로 설정 
		return 0;
	}
	
	//노드가 1개일 때 
	else if(h->first->rlink==NULL)
	{
		//입력받은 key보다 헤드노드의 데이터가 더 클 때, newnode를 맨 앞에 삽입
		if((h->first->key)>key) 
		{
			newnode->rlink=h->first;	//newnode의 rlink가 헤드노드를 가리키도록 설정
			h->first->llink=newnode;	//헤드노드의 llink가 newnode를 가리키도록 설정
			h->first=newnode;			//헤드포인터를 newnode포인터로 설정(헤드노드를 newnode로 변경)
			return 0;
		}
		//입력받은 key가 헤드노드의 데이터보다 작거나 같을때, newnode를 맨 뒤에 삽입 
		else
		{
			newnode->llink=h->first;	//newnode의 llink가 헤드노드를 가리키도록 설정
			h->first->rlink=newnode;	//헤드노드의 rlink가 newnode를 가리키도록 설정
			return 0;
		}
	}

	//노드가 2개이상일 때
	else
	{
		//헤드노드의 값이 key보다 클 때 
		if((h->first->key)>key)
		{
			newnode->rlink=h->first;	//newnode의 rlink가 헤드노드를 가리키도록 설정
			h->first->llink=newnode;	//헤드노드의 llink가 newnode를 가리키도록 설정
			h->first=newnode;			//헤드포인터를 newnode포인터로 설정(헤드노드를 newnode로 변경)
			return 0;
		}
		else
		{
			listNode* p=h->first;   
			while((p->rlink)!=NULL)
			{
				//중간에 노드의 값이 key보다 클 때 
				if((p->key)>key)
				{
					newnode->rlink=p;
					newnode->llink=p->llink;
					p->llink->rlink=newnode;
					p->llink=newnode;
					return 0;
				}
				else
					p=p->rlink;  //조건에 해당되지 않으면, p는 다음노드를 가리키도록 설정
			}
			//p가 마지막 노드일 때 
			//key보다 큰 노드가 존재하지 않을 때->맨 뒤에 newnode삽입 
			if(key>(p->key)) 
			{
				newnode->llink=p;	
				p->rlink=newnode;
				return 0;
			}  
			else
			{
				newnode->rlink=p;
				newnode->llink=p->llink;
				p->llink->rlink=newnode;
				p->llink=newnode;
				return 0;
			}
		}
	}
}


/**
 * list에 key에 대한 노드하나를 마지막에 추가
 */
int insertLast(headNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	
	//노드가 존재하지 않을 때  
	if(h->first==NULL) 
	{
		h->first=newnode;  	//헤드노드를 newnode로 설정
		return 0;
	}
	
	//노드가 1개일 때 
	else if(h->first->rlink==NULL)
	{
		newnode->llink=h->first; 
		h->first->rlink=newnode; 
		return 0;
	}

	//노드가 2개이상일 때 
	else
	{
		listNode* p=h->first;   
		//p가 마지막노드를 가리키지 전까지 반복
		while(p->rlink!=NULL)
		{
			p=p->rlink;  //다음노드를 가리키도록 설정 
		}
		//p가 마지막 노드를 가리킬 때
		p->rlink=newnode;
		newnode->llink=p;
		return 0;
	}
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	//노드가 존재하지 않을 때  
	if(h->first==NULL) 
	{
		h->first=newnode;  	//헤드노드를 newnode로 설정 
		return 0;
	}
	
	//노드가 존재할 때
	else
	{
		h->first->llink=newnode;
		newnode->rlink=h->first;
		h->first=newnode; 	//헤드노드를 newnode로 설정 
		return 0;
	}
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* deleted=NULL;		//삭제할 노드를 가리키는 포인터 생성
	deleted=h->first;			//삭제할 노드를 헤드노드로 설정 

	//노드가 존재하지 않을 때
	if(h->first==NULL)  
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	//노드가 1개일 때
	else if(h->first->rlink==NULL)
	{
		//key에 대한 노드 존재하지 않을 때
		if((h->first->key)!=key)  
		{
			printf("ERROR: There is no node to remove.\n");
			return -1;
		}
		//key에 대한 노드 존재할 때
		else
		{
			h->first=NULL; //헤드노드포인터를 NULL로 설정(리스트에 노드가 존재하지 않은 상태)  
			free(deleted); //노드 삭제(메모리 해제)
			return 1;
		}
	}

	/*노드가 2개이상일 때
		-key에 대한 노드가 존재할 때
			1. 처음노드가 key에 대한 노드일 때
			2. 중간노드가 key에 대한 노드일 때
			3. 마지막노드가 key에 대한 노드일 때 
		-key에 대한 노드가 존재하지 않을 때*/
	else
	{
		//노드가 존재할 때까지 반복 
		while((deleted->rlink)!=NULL)
		{
			if((deleted->key)==key)
			{
				//1. 처음노드가 key에 대한 노드일 때
				if(deleted==(h->first))
				{
					h->first=h->first->rlink; //헤드노드를 다음노드로 변경 
					h->first->llink=NULL; 
					free(deleted);			//노드 삭제(메모리 해제)
					return 1;
				}
				//2. 중간노드가 key에 대한 노드일 때
				else
				{
					deleted->llink->rlink=deleted->rlink;
					deleted->rlink->llink=deleted->llink;
					free(deleted);	//노드 삭제(메모리 해제)
					return 1;
				}
			}
			//key에 대한 노드가 아닐 때
			else	
				deleted=deleted->rlink;  //삭제할 노드를 다음노드로 변경 
		}
		//마지막노드일때
		//3. 마지막노드가 key에 대한 노드일 때
		if(deleted->key==key)
		{
			deleted->llink->rlink=NULL;
			free(deleted);	//노드 삭제(메모리 해제)
			return 1;
		}
		//key에 대한 노드가 존재하지 않을 때 -> 삭제할 노드가 존재하지 않으므로 에러 발생
		else
		{
			printf("ERROR: There is no node to remove.\n");
			return -1;
		}
	}
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* deleted=NULL;		//삭제할 노드를 가리키는 포인터 생성
	deleted=h->first;			//삭제할 노드를 헤드노드로 설정 

	//노드가 존재하지 않을 때
	if(h->first==NULL)  
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	//노드가 1개 존재할 때
	else if(h->first->rlink==NULL)
	{
		h->first=NULL; //헤드노드포인터를 NULL로 설정(리스트에 노드가 존재하지 않은 상태)  
		free(deleted); //노드 삭제(메모리 해제)
		return 0;
	}

	//노드가 2개 이상 존재할 때
	else
	{
		//마지막 노드가 아닐 때
		while(deleted->rlink!=NULL)
		{
			deleted=deleted->rlink;   //삭제노드를 다음노드로 변경
		}
		//deleted가 마지막 노드일 때
		deleted->llink->rlink=NULL;  //마지막노드의 전노드의 rlink를 NULL로 설정 
		free(deleted);  //노드 삭제(메모리 해제)
		return 0;
	}
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* deleted=NULL;		//삭제할 노드를 가리키는 포인터 생성
	deleted=h->first;			//삭제할 노드를 헤드노드로 설정 

	//노드가 존재하지 않을 때 -> 삭제할 노드가 없으므로 에러 발생 
	if(h->first==NULL)  
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	//노드가 1개 존재할 때
	else if(h->first->rlink==NULL)
	{
		h->first=NULL; //헤드노드포인터를 NULL로 설정(리스트에 노드가 존재하지 않은 상태)   
		free(deleted); //노드 삭제(메모리 해제)
		return 0;
	}

	//노드가 2개 이상 존재할 때
	else  
	{
		h->first=h->first->rlink;  //헤드노드를 다음노드로 변경   
		h->first->llink=NULL; //헤드노드의 llink는 NULL로 설정 
		free(deleted);  //노드 삭제(메모리 해제)
		return 0;
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	//listNode형 포인터 2개 필요(이유: 하나만 존재시, 연속적으로 역순으로 재배치가 불가능하다.)
	listNode* tail=h->first;
	listNode* lead=h->first->rlink;  


	//노드가 없을 때와 노드가 1개일 때는 역순으로 재배치할 노드가 없음(기존과 동일한 순서)
	if(((h->first)==NULL)||((h->first->rlink)==NULL))
		return -1;
	
	//노드가 2개 이상일 때
	else
	{
		while(lead)
		{
			tail->rlink=tail->llink;	//tail의 rlink가 가리키는 주소를 tail의 llink가 가리키는 주소로 변경
			tail->llink=lead;			//tail의 llink가 가리키는 주소를 다음노드의 주소로 변경 
			 
			tail=lead;			//tail을 다음노드로 변경 
			lead=lead->rlink; 	//lead를 다음노드로 변경
		}
		//마지막 노드일 때 
		tail->rlink=tail->llink;
		tail->llink=lead;
		h->first=tail;   		//헤드노드 재설정 
		return 0;
	}
}

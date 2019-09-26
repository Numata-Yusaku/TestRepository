#include <stdio.h>
#include <memory.h>

static int gsiStatus = 0;

/* _c */
enum EN_EVENT
{
	E_EVENT_001 = 0,
	E_EVENT_002,

	E_EVENT_NUM,
	E_EVENT_INVALID = -1,
};

enum EN_STATUS
{
	E_STATUS_001 = 0,
	E_STATUS_002,
	E_STATUS_003,

	E_STATUS_NUM,
	E_STATUS_INVALID = -1,
};

/* _s */
typedef void( *F_ACTIONFUNCPTR )( void* );

typedef struct
{
	F_ACTIONFUNCPTR pFunc;
	int iStatus;
}S_STATUS_TABLE;

typedef struct
{
	int iAaa;
	int iBbb;
}S_INDATA;

/* _p */
void Action( int iEvent, int iStatus, void* vpIndata );
void getActionInfo( int iEvent, int iStatus, S_STATUS_TABLE* spInfo );
void setStatus( int iStatus );
int getStatus( void );
void func001_001( void* vpIndata );
void func002_002( void* vpIndata );
void func002_003( void* vpIndata );

/* _t */
S_STATUS_TABLE T_STATUS_TABLE[E_EVENT_NUM][E_STATUS_NUM] =
{
	/* E_EVENT_001 */
	{ 
		{	func001_001,	E_STATUS_002		},
		{	NULL,			E_STATUS_INVALID	},
		{	NULL,			E_STATUS_INVALID	},
	},
	/* E_EVENT_002 */
	{ 
		{	NULL,			E_STATUS_INVALID	},
		{	func002_002,	E_STATUS_003		},
		{	func002_003,	E_STATUS_002		},
	},
};


int main(void)
{
	S_INDATA stIndata;
	memset( &stIndata, 0x00, sizeof(S_INDATA) );
	
	/* アクション */
	Action( E_EVENT_001, getStatus(), (void*)(&stIndata) );
	Action( E_EVENT_002, getStatus(), (void*)(&stIndata) );
	Action( E_EVENT_002, getStatus(), (void*)(&stIndata) );
	return 0;
}

/* action */
void Action( int iEvent, int iStatus, void* vpIndata )
{
	S_STATUS_TABLE stInfo;
	memset( &stInfo, 0x00, sizeof(S_STATUS_TABLE) );
	
	/* アクション情報取得 */
	getActionInfo( iEvent, iStatus, &stInfo );
	
	/* 処理関数実行 */
	if( (F_ACTIONFUNCPTR)NULL != stInfo.pFunc )
	{
		stInfo.pFunc( vpIndata );
	}
	
	/* 状態遷移 */
	if( E_STATUS_INVALID != stInfo.iStatus )
	{
		setStatus( stInfo.iStatus );
	}
	
	printf("%d\n",getStatus() );
	
	return;
}

void getActionInfo( int iEvent, int iStatus, S_STATUS_TABLE* spInfo )
{
	S_STATUS_TABLE stInfo;
	memset( &stInfo, 0x00, sizeof(S_STATUS_TABLE) );
	
	stInfo.pFunc = T_STATUS_TABLE[iEvent][iStatus].pFunc;
	stInfo.iStatus = T_STATUS_TABLE[iEvent][iStatus].iStatus;
	
	memcpy( spInfo, &stInfo, sizeof(S_STATUS_TABLE)  );
	return;
}

/* status */
void setStatus( int iStatus )
{
	gsiStatus = iStatus;
	return;
}

int getStatus( void )
{
	return gsiStatus;
}

void func001_001( void* vpIndata )
{
	printf("func001_001\n");
	return;
}

void func002_002( void* vpIndata )
{
	printf("func002_002\n");
	return;
}

void func002_003( void* vpIndata )
{
	printf("func002_003\n");
	return;
}
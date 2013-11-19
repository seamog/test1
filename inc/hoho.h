/* set tabstop=4 */
/***************************************************************************
 *                                                                         *
 *  2008-2009 Mirae Technology, co                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *  seamog@gmail.com                                                       *
 *  khjeon@mirae-tech.co.kr                                                *
 *                                                                         *
 ***************************************************************************

 MODULE NAME: mirae_type.h

 REVISION HISTORY:

 Date        Version    Name       Description
 ---------------------------------------------------------------------------
 2008/05/20  1.0        khjeon     created
 2010/02/09  1.1        khjeon     manage errcode added
 2013/10/28  1.2		khjeon	   for new prod system
............................................................................
............................................................................

 DESCRIPTION:

 define macros, constant, typedef and error code

............................................................................
*/

#ifndef __MIRAE_TYPE_H__
#define __MIRAE_TYPE_H__

/** ******************************************************************** **
 ** macros
 ** ******************************************************************** **/


/** ******************************************************************** **/


/** ******************************************************************** **
 ** defines
 ** ******************************************************************** **/
#ifndef _MIRAE_TYPES
#define _MIRAE_TYPES
	#define	uchar	unsigned char
	#define uint8   unsigned char
	#define uint16	unsigned short int
	#define uint    unsigned int
	#define uint32  unsigned int

	#define BYTE	unsigned char
	#define WORD	unsigned short
	#define DWORD	unsigned int

	#define PTR		unsigned char *
#endif	/* MIRAE_TYPES */

#ifndef MAX_PATH
#define MAX_PATH			1024
#endif	/* MAX_PATH */

#define TRUE				1
#define FALSE				0

#define true				1
#define false				0

/* auth method */
#define AUTH_INIT			1
#define AUTH_NORM			2
#define	AUTH_LONG			3

/* pin type */
#define HW_PIN				1
#define SW_PIN				2

/* alg type */
#define ALG_MD5				1
#define ALG_HMAC_SHA1		2

/* key file */
#define CSUM_LEN			20
#define DATE_LEN			8
/** ******************************************************************** **/


/** ******************************************************************** **
 ** typedefs
 ** ******************************************************************** **/
/* autentication policy cfg */
typedef struct {
	int		NORM_AUTH_TM_SKEW;		/* 정상인증 허용범위        */
    int		USER_SYNC_TM_SKEW;		/* 사용자보정 허용범위      */
    int		ADMIN_SYNC_TM_SKEW;		/* 관리자보정 허용범위      */
    int		INIT_AUTH_TM_SKEW;		/* 초기인증 허용범위        */
    int		LONG_AUTH_TM_SKEW;		/* 장기미사용인증 허용 범위 */
    int		LONG_TERM;				/* 장기미사용 적용기간      */
    int		SERVER_TM_SKEW;			/* 서버 시간 보정           */
    int     MAX_AUTH_FAIL_CNT;		/* 허용인증오류횟수         */
    char 	LOG_PATH[255+1];		/* 로그 경로                */
} POLICY_CONTEXT;


/* token info context */
/*
1. 토큰키 (64byte)
2. 내부기관코드 (2byte)
3. 기기타입구분 (2byte)
4. 알고리즘구분 (1byte)
5. OTP변경주기 (1byte)
*/
typedef struct {
	char	key[64];				/* hex ciphered token key */
	uint16	org;
	int		type;
	int		alg;
	int		cycle;
} TOKEN_INFO;

/******************************************************************************/
/* TTK 2.x                                                                    */
/******************************************************************************/
/* token file header information */
typedef struct {
	char start[4];
	char ver[2];
	char org[5];
	char ext_org[5];
	char digit[2];
	char pinfail[2];
	char fsn[10];
	char lsn[10];
	char crdate[DATE_LEN];
	char expdate[DATE_LEN];
	char token_t[2];
	char pin_t;
	char alg_t;
	char use_t;
	char comment[80];
	char cycle;			/* OTP change cycle ('0':60sec,
	                                         '1':30sec,
	                                         '2':15sec) */
	char exp_yn;		/* '0':만료기간미적용, '1':만료기간적용(농협등) */
	char reserved[37];
	unsigned char csum[CSUM_LEN];
} T_HEADER ;

/* token file body information */
typedef struct {
	unsigned int  id;
	unsigned char key[32];
	unsigned char reserved[44];
	unsigned char csum[CSUM_LEN];
} T_BODY;

/* token file tail information */
typedef struct {
	char  end[4];
	unsigned char reserved[96];
} T_TAIL;
/******************************************************************************/


/******************************************************************************/
/* TTK 1.x                                                                    */
/******************************************************************************/
/* token file header information */
typedef struct {
	char start[4];
	char ver[2];
	char org[4];
	char digit[2];
	char pinfail[2];
	char fsn[10];
	char lsn[10];
	char crdate[DATE_LEN];
	char token_t[2];
	char pin_t;
	char alg_t;
	char reserved[8];
	char csum[4];
	char crlf[2];
} T1_HEADER ;

/* token file body information */
typedef struct {
	char id[10];
	char key[64];
	char csum[4];
	char crlf[2];
} T1_BODY;

/* token file tail information */
typedef struct {
	char  end[4];
	char  crlf[2];
} T1_TAIL;
/******************************************************************************/




/******************************************************************************/
/* header info response format                                                */
/******************************************************************************/
typedef struct {
	int	 cnt;				/* body record count */
	char org	[ 5+1];		/* org code      */
	char fsaorg [ 5+1];		/* fsa org code  */
	char fsn	[ 9+1];		/* first serial num  */
	char lsn	[ 9+1];		/* last serial num  */
	char sdate	[ 8+1];		/* guarantee begin date  */
	char edate	[ 8+1];		/* guarantee end date  */
	char type	[ 2+1];		/* OTP model type code */
	char alg	[ 1+1];		/* algorithm type code */
	char use_t	[ 1+1];		/* OTP 사용구분 */
	char cycle	[ 1+1];		/* OTP change cycle */
	char exp_yn [ 1+1];		/* 만료기간적용 여부 */
	char memo   [80+1];		/* comment */
	char digit  [ 2+1];		/* 일련번호 자릿수 */
	char pinfail[ 2+1];		/* PIN 잠김 오류횟수 */
	char pintype[ 1+1];		/* PIN type (sw, hw) */
} TTK_HEADER ;

/* body info response format */
typedef struct {
	char sn		[ 9+1];		/* OTP device serial number */
	char key	[64+1];		/* OTP generation key(seed) */
} TTK_BODY ;
/******************************************************************************/



/** ******************************************************************** **
 ** error code
 ** ******************************************************************** **/
/*
------------------------------------------
code    detail
------------------------------------------
6000	인증실패
6001	인증실패 (동일 OTP)
6002	보정필요
6003	보정실패
6004	보정실패 (동일 OTP)
6005	미정의 오류
6006	해당 OTP 기기일련번호 없음
6007	전문입력값오류
6008	DB에러
6009	잠김해제실패
6010	OTP응답값 입력형식 오류
------------------------------------------
 */

/* error code */
#define ERR_SUCCESS					    0000
#define ERR_AUTH_SUCC				    0000
#define ERR_SYNC_SUCC				    0000
#define ERR_UNLOCK_SUCC				    0000
#define ERR_RSYNC_SUCC				    0000

/* 벤더 */
#define ERR_AUTH_FAIL					6000
#define	ERR_AUTH_EQL_OTP				6001
#define ERR_SYNC_NEED					6002
#define ERR_SYNC_FAIL					6003
#define ERR_SYNC_EQL_OTP				6004
#define ERR_UNDEFINED					6005
#define ERR_TOKEN_NOT_FOUND 			6006
#define ERR_INVALID_INPUT   			6007
#define ERR_DB_FAIL						6008
#define ERR_UNLOCK_FAIL					6009
#define ERR_INVALID_OTP					6010	/* otp digit & format error */
#define ERR_POLICY_NOT_SET				6011	/* auth policy not setup */

/* 추가 오류 코드  */

#define ERR_FILE_OPEN_FAIL				6012
#define ERR_FILE_READ_FAIL				6013
#define ERR_CSUM_FAIL					6014
#define ERR_PIN_INVALID					6015
#define ERR_NOT_DISUSE_TOKEN			6020	/* 폐기 등록된 토큰이 아님 (센터 미포함) */


/* 관리업무 */
#define ERR_AUTH_FAIL_OVER				3100	/* 허용 인증 오류 횟수 초과 */
#define ERR_UNREGISTERED_TOKEN			3118	/* 미 발급 토큰임 */
#define ERR_REGISTERED_TOKEN			3117	/* 이미 발급된 토큰임 */
#define ERR_LOST_TOKEN					3112	/* 분실 등록된 토큰임 */
#define ERR_DISUSE_TOKEN				3111	/* 폐기 등록된 토큰임 */
#define ERR_NOT_LOST_TOKEN				3113	/* 분실 등록된 토큰이 아님 */

#define ERR_ALREADY_SET					3999	/* 기처리 */


/*********************************************************************** **/

#endif /* __MIRAE_TYPE_H__ */

/* end of mirae_type.h */


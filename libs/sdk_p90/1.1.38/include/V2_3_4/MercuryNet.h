/*#########################################################################
                 Amoi Tech Mercury Application Build System
                 All Rights Reserved 2017
                 Author:
#########################################################################*/

#ifndef __MERCURY_NETWORK_H__
#define __MERCURY_NETWORK_H__

#include "MercuryDef.h"

//#define htons(s) ((((s) & 0xff00) >> 8) |(((s) & 0x00ff) << 8))


// Address families.
#define AF_UNSPEC       0           /* unspecified */
#define AF_NS           1           /* local to host (pipes, portals) */
#define AF_INET         2           /* internetwork: UDP, TCP, etc. */
#define AF_INET6    3     /* IPv6 */
#define AF_MAX          (AF_INET6 +  1)

//PDP type
typedef enum {
    PDP_TYPE_IPV4 = (unsigned char)0,
    PDP_TYPE_IPV6 = (unsigned char)1,
    PDP_TYPE_IPV4V6 = (unsigned char)2,

    PDP_TYPE_MAX
} gprs_pdp_type;

// Socket state bits
#define SS_NOFDREF          0x0001  /* no file table ref any more */
#define SS_ISCONNECTED      0x0002  /* socket connected to a peer */
#define SS_ISCONNECTING     0x0004  /* in process of connecting to peer */
#define SS_ISDISCONNECTING  0x0008  /*  in process  of disconnecting */
#define SS_CANTSENDMORE     0x0010  /* can't send more data to peer */
#define SS_CANTRCVMORE      0x0020  /* can't receive more data from peer */
#define SS_RCVATMARK        0x0040  /* at mark on input */
#define SS_PRIV             0x0080  /* privileged for broadcast, raw... */
#define SS_NBIO             0x0100  /* non-blocking ops */
#define SS_ASYNC            0x0200  /* async i/o notify */
#define SS_UPCALLED         0x0400  /* zerocopy data has been upcalled (for select) */
#define SS_INUPCALL         0x0800  /* inside zerocopy upcall (reentry guard) */
#define SS_UPCFIN           0x1000  /* inside zerocopy upcall (reentry guard) */
#define SS_WASCONNECTING    0x2000  /* SS_ISCONNECTING w/possible pending error */

// socket error code
#define ENOBUFS            1
#define ETIMEDOUT        2
#define EISCONN            3
#define EOPNOTSUPP      4
#define ECONNABORTED    5
#define EWOULDBLOCK     6
#define ECONNREFUSED    7
#define ECONNRESET      8
#define ENOTCONN        9
#define EALREADY        10
#define EINVAL          11
#define EMSGSIZE        12
#define EPIPE           13
#define EDESTADDRREQ    14
#define ESHUTDOWN       15
#define ENOPROTOOPT     16
#define EHAVEOOB        17
#define ENOMEM          18
#define EADDRNOTAVAIL   19
#define EADDRINUSE      20
#define EAFNOSUPPORT    21
#define EINPROGRESS     22
#define ELOWER          23          /* lower layer (IP) error */
#define ENOTSOCK        24          /* Includes sockets which closed while blocked */
#define EIEIO           27          /* bad input/output on Old Macdonald's farm :-) */
#define ETOOMANYREFS    28
#define EFAULT          29
#define ENETUNREACH     30

typedef int TCPIP_SOCKET_T;
typedef  unsigned int     TCPIP_IPADDR_T;
typedef  uint32     TCPIP_HOST_HANDLE;          /* async gethostbyname request handle */

typedef struct
{
    TCPIP_IPADDR_T  ipaddr;     /* host IP */
    TCPIP_IPADDR_T  snmask;     /* subnet mask */
    TCPIP_IPADDR_T  gateway;    /* gateway */
    TCPIP_IPADDR_T  dns1;       /* primary DNS */
    TCPIP_IPADDR_T  dns2;       /* secondary DNS */
} TCPIP_NETIF_IPADDR_T;

// TCPIP IPv6 address, 128 bit
#define TCPIP_IP6_ADDR_LEN_BYTES    16
typedef struct {
    union {
        uint8   u6_addr8[TCPIP_IP6_ADDR_LEN_BYTES];
        uint16  u6_addr16[TCPIP_IP6_ADDR_LEN_BYTES>>1];
        uint32  u6_addr32[TCPIP_IP6_ADDR_LEN_BYTES>>2];
    } u6_addr;
} TCPIP_IPADDR6_T;

typedef enum
{
    PLMN_NO_SERVICE = 0 ,          // no service
    PLMN_NORMAL_GSM_ONLY = 0x01 ,     // voice service available
    PLMN_NORMAL_GPRS_ONLY = 0x02 ,    // data service available
    PLMN_NORMAL_GSM_GPRS_BOTH = 0x03 ,// voice and data service available

    PLMN_NORMAL_CS_ONLY = 0x01 ,     // voice service available
    PLMN_NORMAL_PS_ONLY = 0x02 ,    // data service availabe
    PLMN_NORMAL_CS_PS_BOTH = 0x03 ,// voice and data service available

    PLMN_EMERGENCY_ONLY = 0x04,       // emergency service available

    PLMN_EMERGENCY_SIM_INVALID = 0x05,        /* emergency; MM in limited service state and
                                               no further PLMN access allowed until power
                                             off or new SIM inserted */
    PLMN_EMERGENCY_GPRS_ONLY = 0x06,      // data service availabe but emergency; MM in limited service state
    PLMN_EMERGENCY_SIM_INVALID_GPRS_ONLY = 0x07,   /* data service availabe but emergency; MM in limited service state and
                                                  no further PLMN access allowed until power
                                               off or new SIM inserted */

    PLMN_REGISTER_SERVICE = 0x08,    //attaching after camping on
    PLMN_REGISTER_GPRS_ONLY = 0x09, // data service availabe but attaching;
    PLMN_FULL_PS_SERVICE = 0x0A,       /*full PS service, no cs service*/
    MERCURY_ENUM_PHONEPLMN_MAX = 0x7fffffff
} MERCURY_PHONE_PLMN_STATUS_E;

typedef enum
{
	MN_INVALID_STATE, /* this field is invalid */
	MN_ATTACHED_STATE, /* cs or ps has been attached */
	MN_DETACHED_SATE, /* cs or ps has been detached */
	MN_NO_SERVICE,  /* no service for cs or ps */
	MERCURY_ENUM_ATTACH_MAX = 0x7fffffff
} MERCURY_ATTACH_STATE_E;


typedef struct
{
    MERCURY_PHONE_PLMN_STATUS_E  plmn_status;        // plmn statue
    BOOL                plmn_is_roaming;    // if plmn is roaming plmn
    WORD                  mcc;
    WORD                  mnc;
    WORD                  mnc_digit_num;
    WORD                  lac;
    WORD                  cell_id;
}MERCURY_NETWORK_STATUS_T;

typedef enum
{
    SOCKET_TYPE_TCP = 0,
    SOCKET_TYPE_UDP,
    SOCKET_TYPE_RAWDATA,
    SOCKET_TYPE_UNKNOWN = 0x7fffffff,
    MERCURY_ENUM_SOCKETTYPE_MAX = 0x7fffffff
}SOCKET_TYPE_E;

typedef enum
{
    SOCKET_TXDATA=0,  /* get count of bytes in sb_snd */
    SOCKET_RXDATA,     /* get count of bytes in sb_rcv */
    SOCKET_MYADDR,    /* return my IP address */
    SOCKET_ACK,       /*peer acked bytes in current TCP connection*/
    SOCKET_OPT_MAX,
    MERCURY_ENUM_SOCKETOPT_MAX = 0x7fffffff
}SOCKET_OPT_E;

typedef enum
{
    PDP_ID0=1,
    PDP_ID1,
    PDP_ID2,
    MERCURY_ENUM_PDPID_MAX = 0x7fffffff
}PDP_ID_E;

typedef struct
{
    unsigned short  port;           /* port number */
    unsigned long   ip_addr;        /* ip address */
}SOCKET_ADDR_S;

/* Berkeley style "Socket address" */
typedef struct sci_sockaddr
{
    unsigned short  family;         /* address family */
    unsigned short  port;           /* port number */
    unsigned long   ip_addr;        /* ip address */
    char            sa_data[8];     /* up to 14 bytes of direct address */
}SOCKET_ADDR_EXT_S;

typedef struct
{
    unsigned short  port;           /* port number */
    unsigned char   ip_addr[16];        /* ip address */
}V6_SOCKET_ADDR_S;

/* the definitions to support the select() function. These are about
 * as UNIX-like as we can make 'em on embedded code. They are also
 * fairly compatable with WinSock's select() definitions.
 */
typedef struct    /* the select socket array manager */
{
    unsigned        fd_count;       /* how many are SET? */
    long            fd_array[12];   /* an array of SOCKETs, define FD_SETSIZE 12 tcpip internal definition */
} MERCURY_FD_SET_S;

typedef struct
{
    uint32 cell_exist;
    uint16  arfcn;
    uint8   bsic;
    uint8   rxlev;
    uint16  mcc;
    uint16  mnc;
    uint16  mnc_digit_num;
    uint16  lac;
    uint16  cell_id;
} NCELLS_INFO_T;

typedef struct
{
    uint32 cell_exist;
    uint16  arfcn;
    uint8   bsic;
    uint8   rxlev;
    uint16  mcc;
    uint16  mnc;
    uint16  mnc_digit_num;
    uint16  lac;
    uint16  cell_id;
} SCELL_INFO_T;

typedef struct
{
    NCELLS_INFO_T ncells[6];
    SCELL_INFO_T      scell;
}MERCURY_CELLS_INFO_T;

typedef enum
{
    AUTH_PAP       = 0,
    AUTH_CHAP      = 1,
    AUTH_PAP_CHAP  = 2,
    AUTH_NONE = 3
} PCO_AUTH_TYPE_E;

// PING result type
typedef enum
{
    PINGRES_SUCCESS         = 0,    /* ping OK, received ping echo reply */
    PINGRES_DNS_TIMEOUT     = 1,    /* ping fail, DNS timeout */
    PINGRES_DNS_ERROR       = 2,    /* ping fail, DNS error */
    PINGRES_ICMP_TIMEOUT    = 3,    /* ping fail, icmp timeout */
    PINGRES_ICMP_ERROR      = 4     /* ping fail, icmp error */
}TCPIP_PING_RESULT_E;

// PING result callback function
typedef void (*TCPIP_PING_CALLBACK_FPTR)(
    TCPIP_PING_RESULT_E     res,            /* ping result, 0 - succeed; other - fail */
    uint32                  time_delay,     /* ping time delay, only valid when success, unit: ms */
    uint16       ping_handle );  /* ping handle */

typedef void (*TCPIP_PING_CALLBACK_EX_FPTR)(
    TCPIP_PING_RESULT_E     res,            /* ping result, 0 - succeed; other - fail */
    uint32                  time_delay,     /* ping time delay, only valid when success, unit: ms */
    uint16       ping_handle,  /* ping handle */
    uint8             ttl,
    char*            ipaddr);

typedef void (*TCPIP_DHCP_CALLBACK_FPTR)(
    int                       res,        /* DHCP result - 0: OK; else - error */
    const TCPIP_NETIF_IPADDR_T* addr_ptr,   /* ip addresses pointer */
    TCPIP_IPADDR_T              dhcp_addr,  /* DHCP server address pointer */
    uint32               netid );    /* net interface ID */

int NetworkGetState(MERCURY_NETWORK_STATUS_T* pstatus);
/*
rssi level
0        -113dBm or less
1        -111 dBm
2...30   -109...-53dBm
31       -51dBm or greater
99       unknown or not detectable
*/
int NetworkGetSignalQuality(BYTE* prssi,WORD* prxfull);
/*
id form PDP_ID0 to PDP_ID2
if apn is null then user the default apn
if user and password are null then we think it is not need password
*/
int NetworkSetAPN(BYTE id,BYTE* apn,BYTE* user, BYTE* password);

int NetworkOpenPDP(BYTE id);
int NetworkClosePDP(BYTE id);

extern TCPIP_SOCKET_T  SocketCreate(SOCKET_TYPE_E type);
extern int SocketConnect(TCPIP_SOCKET_T so,SOCKET_ADDR_S* addr_ptr, int addr_len);
extern int SocketSend( TCPIP_SOCKET_T so, char* buf, int len);
extern int SocketSendTo(TCPIP_SOCKET_T so, char* buf, int len, SOCKET_ADDR_S* to );
extern int SocketRecv(TCPIP_SOCKET_T so, char* buf, int len);
extern int SocketRecvFrom(TCPIP_SOCKET_T so, char* buf, int len,SOCKET_ADDR_S* from );
extern int SocketClose(TCPIP_SOCKET_T so);
extern int SocketErrNo(TCPIP_SOCKET_T so);
extern int INetAtoN( char* ip_str, TCPIP_IPADDR_T* ipaddr_ptr );
extern char* INetNtoA( TCPIP_IPADDR_T ipaddr );
/*
time_out uint ms
return 0 -- faile   other --- request handle
*/
extern TCPIP_HOST_HANDLE NetworkGetHostByName(char* name_ptr,uint32  time_out);
extern int FlightModeSet(BOOLEAN enable);
extern int GprsAttach(void);
extern int GprsDetach(void);
extern int SocketGetOpt(TCPIP_SOCKET_T so, SOCKET_OPT_E opt, uint32* pdata);
extern int SocketGetState( TCPIP_SOCKET_T so, short* state_ptr);
extern BOOLEAN Network_GetPDPStatus(void);
/*
获取临近基站与主基站信息
cell_exist = 1 代表获取到相应的基站信息
最多可以获取6个临近基站信息
*/
extern uint32 Network_BaseStationInfoGet(MERCURY_CELLS_INFO_T* cell);
/*
在pdp已激活前提下可使用此接口
参数置为NULL表示不获取该项值
*/
extern int Network_NetAddrGet(char *pszIp, char *pszMask, char *pszGateway, char *pszDns);
extern void Network_ForceCampon(uint16 arfcn);
extern void Network_CancelForceCampon(void);
/*****************************************************************************/
//uint32 penalty_time表示禁止时间，单位为s
//uint8 retransmit_num代表最大重传次数
/*****************************************************************************/
extern int Network_SetGprsMassRetransmitParam(uint32 penalty_time, uint8 retransmit_num);
extern int Network_SetAuthType(PCO_AUTH_TYPE_E type);

#define NET_BAND_GSM                       0x00
#define NET_BAND_DCS                       0x01
#define NET_BAND_GSM_DCS                   0x02
#define NET_BAND_PCS                       0x03
#define NET_BAND_GSM850                    0x04
#define NET_BAND_GSM_PCS                   0x05
#define NET_BAND_GSM850_DCS                0x06
#define NET_BAND_GSM850_PCS                0x07
#define NET_BAND_GSM850_GSM                0x08
#define NET_BAND_GSM850_GSM_PCS            0x09
#define NET_BAND_GSM850_GSM_DCS            0x0a
#define NET_BAND_GSM_DCS_PCS               0x0b
#define NET_BAND_GSM850_GSM_DCS_PCS        0x0c
#define NET_BAND_DCS_PCS                   0x0d
#define NET_BAND_GSM850_DCS_PCS            0x0e
extern int Network_SelectBand(int userBand);
extern uint16 Network_PingRequest(char * faddr_ptr,uint32 data_size,uint32 time_out,TCPIP_PING_CALLBACK_FPTR callback_fptr);
extern void Network_PingCancel(uint16 pingHandle);
extern uint8 Network_GetTaPwr(uint8* pTa, uint8* pPwr);
extern int SocketSetOpt(TCPIP_SOCKET_T so, int opt, uint32* pdata);

extern uint16 Network_PingV4Request(char* faddr_ptr,uint32 data_size,uint32 time_out,TCPIP_PING_CALLBACK_EX_FPTR    callback_fptr);
extern uint16 Network_PingV6Request(char* faddr_ptr,uint32 data_size,uint32 time_out,TCPIP_PING_CALLBACK_EX_FPTR    callback_fptr);

extern int NetworkSetPdpType(gprs_pdp_type type);

/*
ipv4 与 ipv6大部分socket操作api是相同的
在使用ipv6时，create/connect/sendto/rcvfrom这几个有区别，需要用下面的接口
*/
extern TCPIP_SOCKET_T  SocketCreateV6(SOCKET_TYPE_E type);
extern int SocketConnectV6(TCPIP_SOCKET_T so,V6_SOCKET_ADDR_S* addr_ptr, int addr_len);
extern int SocketSendToV6(TCPIP_SOCKET_T so, char* buf, int len, V6_SOCKET_ADDR_S* to );
extern int SocketRecvFromV6(TCPIP_SOCKET_T so, char* buf, int len,V6_SOCKET_ADDR_S* from );

/***********************************************************************************
mercury 平台底层集成了9051网卡的驱动。
需要app指定spi cs逻辑id 及 用于控制9051的相关gpio(rst 和 INT)
使用顺序:
1、ETH_RegInterface 返回nei_id
2、ETH_DhcpRequest
3、ETH_SocketCreate (除create特殊外，其余的socket接口同gprs)
***********************************************************************************/
extern TCPIP_SOCKET_T  ETH_SocketCreate(SOCKET_TYPE_E type,uint32 netID);
/*
ipv6Flag 为0 则表示不启用ipv6 非零值表示启用ipv6并且同时表示地址前缀长度
返回值为该承载的netid
*/
extern uint32 ETH_RegInterface(uint32 spiID, uint32 gpioRst, uint32 gpioInt, uint8* mac, uint32 ipv6Flag);
extern void ETH_DeRegInterface(uint32 netid);
/*
ipv4情景下，当承载注册成功后，ip获取有两种方式
1、通过dhcp获取(ETH_DhcpRequest)
2、通过手动配置ip(ETH_SetIpAddress)

ipv6情景下，ip的获取tcpip会自主发起RS报文去获取，无需配置
*/
extern int ETH_DhcpRequest(TCPIP_DHCP_CALLBACK_FPTR callback_fptr,uint32 time_out,uint32 net_id );
extern void ETH_DhcpCancel(uint32 net_id);
extern int ETH_SetIpAddress(const TCPIP_NETIF_IPADDR_T*	addr_ptr, uint32 net_id );
extern BOOLEAN ETH_GetIpAddress( TCPIP_NETIF_IPADDR_T*	 addr_ptr,uint32  net_id );

/*
Network_SetDnsV6 与 Network_GetIpv6Address
接口gprs链路承载和其他链路承载(DM9051)都适用
DM9851承载 -- netid填入相应承载链路id
gprs承载 -- net_id 填-1
*/
extern int Network_SetDnsV6(TCPIP_IPADDR6_T* dns,uint32  net_id);
extern BOOLEAN Network_GetIpv6Address(TCPIP_IPADDR6_T* ip6addr_ptr,TCPIP_IPADDR6_T* localaddr_ptr,TCPIP_IPADDR6_T* dns_ptr,uint32 net_id );
/*
其他链路承载(DM9051) ping接口
*/
extern uint16 ETH_PingV4Request(char* faddr_ptr,uint32 data_size,uint32 time_out,TCPIP_PING_CALLBACK_EX_FPTR    callback_fptr,uint32 netid);
extern uint16 ETH_PingV6Request(char* faddr_ptr,uint32 data_size,uint32 time_out,TCPIP_PING_CALLBACK_EX_FPTR    callback_fptr,uint32 netid);

extern int SocketBind(TCPIP_SOCKET_T so, struct sci_sockaddr* addr_ptr, int addr_len);
extern int SocketListen( TCPIP_SOCKET_T so, int backlog);
extern TCPIP_SOCKET_T SocketAccept(TCPIP_SOCKET_T so, struct sci_sockaddr* addr_ptr, int* addr_len);
extern int SocketSelect(MERCURY_FD_SET_S* in,  MERCURY_FD_SET_S* out,MERCURY_FD_SET_S* ex, long tv);

extern void FdClr( TCPIP_SOCKET_T so, MERCURY_FD_SET_S* set);
extern void FdSet( TCPIP_SOCKET_T so, MERCURY_FD_SET_S* set);
extern int   FdIsSet( TCPIP_SOCKET_T so, MERCURY_FD_SET_S* set);
extern void FdZero(MERCURY_FD_SET_S* set);


#endif //__MERCURY_NETWORK_H__


#include <assert.h>
#include <sys/time.h>
#include <string.h>
#include "common.h"
#include "prads.h"
#include "cxt.h"
#include "sys_func.h"
#include "config.h"
#include "output-plugins/log.h"
#include "assets.h"
#include "local.h"
#include <CONNAC.h>


extern globalconfig config;
extern pthread_mutex_t ActionEntryLock;
extern pthread_mutex_t AssetEntryLock; 

uint64_t cxtrackerid;
static pthread_t action_thread;
static void *action_sender(void *arg);
connection *bucket[BUCKET_SIZE];

void cxt_init()
{
    cxtrackerid = 0;
}



int local_action_put_perflow(ShareState* recv_state){
	
    printf("receive action state, begin to putPerFlow\n");
    pthread_mutex_lock(&ActionEntryLock);
    connection *cxt = NULL;
    cxt =(connection*)malloc(sizeof(connection));


    struct in6_addr ips;
    struct in6_addr ipd;
    ips.s6_addr32[0] = recv_state->s_ip;
    ipd.s6_addr32[0] = recv_state->d_ip;
    cxt->s_ip = ips;
    cxt->d_ip = ipd;

    cxt->s_port = recv_state->s_port;
    cxt->d_port = recv_state->d_port;

    cxt->hw_proto = recv_state->hw_proto;
    cxt->proto = recv_state->proto;

    cxt->start_time = recv_state->start_time;
    cxt->last_pkt_time = recv_state->last_pkt_time;

    uint64_t cxid = recv_state->cxid;
    cxt->cxid = cxid;
    //set a right number of cxtrackerid
    if(cxid > cxtrackerid){
	cxtrackerid = cxid;
    }


    cxt->reversed = recv_state->reversed;
    cxt->af = recv_state->af;
    cxt->s_total_pkts = recv_state->s_total_pkts;
    cxt->s_total_bytes= recv_state->s_total_bytes;
    cxt->d_total_pkts = recv_state->d_total_pkts;
    cxt->d_total_bytes = recv_state->d_total_bytes;
    cxt->s_tcpFlags = recv_state->s_tcpflags;
    cxt->__pad__ = recv_state->pad;
    cxt->d_tcpFlags = recv_state->d_tcpflags;  
    cxt->check = recv_state->check;
    uint32_t hash = recv_state->hash;
    cxt->hash = hash;  
	
    connection* head = bucket[hash];

    // Add to linked list
    cxt->prev = NULL;
    if (head != NULL)
    {
        head->prev = cxt;
        cxt->next = head;
    }
    else
    { cxt->next = NULL; }
    bucket[hash] = cxt;
    
    //pthread_mutex_unlock(&ActionEntryLock);
    // If asset structure is present push it into the asset list.
    
    if(recv_state->c_asset != NULL){
	//printf("\n--------------c_asset exits--------------------\n");
	asset* c_asset = (asset*)malloc(sizeof(asset));
	put_asset(c_asset, recv_state->c_asset);

    }
    if(recv_state->s_asset != NULL){
	//printf("\n--------------s_asset exits--------------------\n");
	asset* s_asset = (asset*)malloc(sizeof(asset));
	put_asset(s_asset, recv_state->s_asset);
    }
    
//+++
    connac_notify_flow_created();
//+++
    //showAllCxid();
    pthread_mutex_unlock(&ActionEntryLock);
	
    //action_state->c_asset = NULL; 
    //action_state->s_asset = NULL;  
  
    return 1;
}

void put_asset(asset* ori_asset, Asset *in_asset){

	//printf("\n--------------check put asset--------------------\n");
	//pthread_mutex_lock(&ActionEntryLock); 
        
	if(in_asset == NULL){
		//printf("in_asset\n");
	}
	if(in_asset->first_seen == NULL){
		//printf("in_asset->first_seen\n");
	}
	ori_asset->first_seen = in_asset->first_seen;   	
	ori_asset->last_seen = in_asset->last_seen;
	ori_asset->i_attempts = in_asset->i_attempts;
	ori_asset->af = in_asset->af;
	ori_asset->vlan = in_asset->vlan;
	ori_asset->ip_addr.s6_addr32[0] = in_asset->s_ip;
	ori_asset->last_seen = in_asset->last_seen;
	//ori_asset->removed = 1;
	serv_asset* services;
	os_asset* os_ori;

	if(in_asset->services != NULL){
		services = (serv_asset*)malloc(sizeof(serv_asset));
		//printf("\n--------------check put services init--------------------\n");

		services->first_seen= in_asset->services->first_seen;
		services->last_seen= in_asset->services->last_seen;
		services->i_attempts= in_asset->services->i_attempts;
		services->proto= in_asset->services->proto;
		services->port= in_asset->services->port;
		services->ttl= in_asset->services->ttl;

		bstring service;
		if(in_asset->services->bservice != NULL){
			bstring service= (bstring)malloc(sizeof(tagBstring));
			service->mlen= in_asset->services->bservice->mlen;
			service->slen= in_asset->services->bservice->slen;
			service->data= in_asset->services->bservice->data;
			services->service =service;
		}

		bstring application;
		if(in_asset->services->bapplication != NULL){
			bstring application= (bstring)malloc(sizeof(tagBstring));
			application->mlen= in_asset->services->bapplication->mlen;
			application->slen= in_asset->services->bapplication->slen;
			application->data= in_asset->services->bapplication->data;
			services->application =application;
		}		

		services->role= in_asset->services->role;
		services->unknown= in_asset->services->unknown;
  		//printf("\n--------------check put services finished--------------------\n");

	}
	ori_asset->services = services;
	
	if(in_asset->os != NULL){
		os_ori = (os_asset*)malloc(sizeof(os_asset));
		//printf("\n--------------check put os init --------------------\n");
		os_ori->first_seen= in_asset->os->first_seen;
		os_ori->last_seen= in_asset->os->last_seen;
		os_ori->i_attempts= in_asset->os->i_attempts;

		bstring bos;
		if(in_asset->os->bos != NULL){
			bstring os_string= (bstring)malloc(sizeof(tagBstring));
			os_string->mlen= in_asset->os->bos->mlen;
			os_string->slen= in_asset->os->bos->slen;
			os_string->data= in_asset->os->bos->data;
			os_ori->os = os_string;
		}
	
		bstring bvendor;
		if(in_asset->os->bvendor != NULL){
			bstring vendor= (bstring)malloc(sizeof(tagBstring));
			vendor->mlen= in_asset->os->bvendor->mlen;
			vendor->slen= in_asset->os->bvendor->slen;
			vendor->data= in_asset->os->bvendor->data;
			os_ori->vendor = vendor;
		}


		os_ori->detection= in_asset->os->detection;

		bstring raw_fp;
		if(in_asset->os->raw_fp != NULL){
			bstring raw_fp= (bstring)malloc(sizeof(tagBstring));
			raw_fp->mlen= in_asset->os->raw_fp->mlen;
			raw_fp->slen= in_asset->os->raw_fp->slen;
			raw_fp->data= in_asset->os->raw_fp->data;
			os_ori->raw_fp = raw_fp;
		}		
		
		
		bstring matched_fp;
		if(in_asset->os->matched_fp != NULL){
			bstring matched_fp= (bstring)malloc(sizeof(tagBstring));
			matched_fp->mlen= in_asset->os->matched_fp->mlen;
			matched_fp->slen= in_asset->os->matched_fp->slen;
			matched_fp->data= in_asset->os->matched_fp->data;
			os_ori->matched_fp = matched_fp;
		}

		os_ori->match_os= in_asset->os->match_os;
		os_ori->match_desc= in_asset->os->match_desc;
  
		os_ori->port= in_asset->os->port;
		os_ori->ttl= in_asset->os->ttl;
		os_ori->mtu= in_asset->os->mtu;
		os_ori->uptime= in_asset->os->uptime;

		//printf("\n--------------check put os finished --------------------\n");
		
	}
	ori_asset->os = os_ori;

	//printf("\n--------------check put asset before put asset per sip--------------------\n");
	put_asset_per_sip(in_asset->s_ip, ori_asset);

	//printf("\n--------------check put asset after put asset per sip--------------------\n");
	//pthread_mutex_unlock(&ActionEntryLock); 
	
}



int local_get_one_sharestate(connection* cxt){
        printf("local get one action per flow\n");	
        pthread_mutex_lock(&ActionEntryLock);
		
	ProtoObject *proto_object = serialize_cxt_state(cxt);
	uint8_t* buf = proto_object->buf;
	int len = proto_object->length;

	int result = action_send_perflow(buf, len);    
       	if(result < 0){
		return -1;
	}

	printf("local get one action per flow ---send successful\n");
	free(proto_object);
		

	//printf("action end----------------------\n");
	pthread_mutex_unlock(&ActionEntryLock);
	//printf("local get one action per flow ---unlock\n");
	
	return 1;
}

static void *cxt_sender(void *arg){
	printf("start a conn sender\n");
	
	connection* cxt = (connection*)arg;
	int send_conn = local_get_one_sharestate(cxt);
	if(send_conn < 0){
		printf("send failed");
	}

	
}

int local_action_get_perflow(Key key){
     printf("start action get perflow\n");
     printf("local  key.dl_type %x\n", key.dl_type);
     printf("key.nw_proto %u\n",key.nw_proto);
 
    int count = 0;
    int h = 0;
    for (h = 0; h < BUCKET_SIZE; h++)
    {        
        pthread_mutex_lock(&ActionEntryLock);
        connection *cxt = bucket[h];

        while (cxt != NULL)
        {
		//printf("while begin\n");
		if (!(key.wildcards & WILDCARD_DL_TYPE) && cxt->hw_proto != ntohs(key.dl_type))
			{
		        	cxt = cxt->next;
		                continue;
		        }
		
		            // Check nw_proto
		if ((!(key.wildcards & WILDCARD_NW_PROTO)) &&((cxt->proto) != key.nw_proto))
			{
		               cxt = cxt->next;
		                continue;
		        }
		
	    //printf("create thread begin\n");
	    int err;
	     if((err = pthread_create(&action_thread, NULL, cxt_sender, (void*)cxt))!=0)
             {
             	perror("pthread_create error");
             }
	     

	     count++;		        
           // Move on to next connection
           cxt = cxt->next;
        }
        pthread_mutex_unlock(&ActionEntryLock);
    }
    return count;

}



//+++
void showCxtState(connection* cxt){
    //struct sockaddr_in sa;
    char src_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(cxt->s_ip), src_str, INET_ADDRSTRLEN);
   
    //struct sockaddr_in sa;
    char dst_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(cxt->d_ip), dst_str, INET_ADDRSTRLEN);
    


    printf("---------------cxt------------------\n");

    printf("src_ip %s\n", src_str);
    printf("ds_ip %s\n", dst_str);
    printf("s_port %u\n",cxt->s_port);
    printf("d_port %u\n",cxt->d_port);
    printf("hw_proto %u\n",cxt->hw_proto);
    printf("proto %u\n",cxt->proto);
   
    printf("start_time %lu\n",cxt->start_time );
    printf("last_pkt_time %lu\n", cxt->last_pkt_time);
    printf("cxid: %lu\n",cxt->cxid);
    printf("reversed: %u\n",cxt->reversed);
    printf("af %u\n",cxt->af);
    printf("s_total_pkts  %lu\n",cxt->s_total_pkts);
    printf("s_total_bytes %lu\n",cxt->s_total_bytes);
    printf("d_total_pkts %lu\n",cxt->d_total_pkts);
    printf("d_total_bytes %lu\n",cxt->d_total_bytes);
    printf("s_tcpFlags %u\n",cxt->s_tcpFlags);
    printf("d_tcpFlags  %u\n",cxt->d_tcpFlags);
    printf("check %u\n",cxt->check);
    
    printf("---------------cxt------------------\n");

}



void showAllState(){
 int h;
 uint64_t cxts[100];
 memset(cxts, 0, sizeof(cxts));
 
 int count_cxt =0;
 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        connection *cxt = bucket[h];
        
	while (cxt != NULL)
        {     
            printf("-----------cxt---h%d------------\n",h);
	    showCxtState(cxt); 
            cxts[count_cxt] = cxt->cxid; 
            count_cxt++;     
            // Move on to next connection
            cxt = cxt->next;
        }             
    }
    printf("\n");
   
    printf("count_cxt %d\n",count_cxt);
    printf("------------------------------------\n");
    
    int n;
    for(3; n<= count_cxt; n++){
	printf("%lu,",cxts[n]);
    }


}

void showAllCxid(){
 int h;
 uint64_t cxts[100];
 int count_cxt =0;

 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        connection *cxt = bucket[h];
       
	while (cxt  != NULL)
        {      
            cxts[count_cxt] = cxt ->hash; 
            count_cxt++;     
            // Move on to next connection
            cxt = cxt->next;
        }          
    }
    
    printf("----------------cxtrackerid:%lu--------------------\n",cxtrackerid);
    printf("count_cxt %d\n",count_cxt);
    
    int n;
    for(n = 0; n<= count_cxt; n++){
	printf("%lu,",cxts[n]);
    }
    printf("\n");
    printf("----------------cxtrackerid:%lu--------------------\n",cxtrackerid);
    

}


//+++

/* freshly smelling connection :d */
connection *cxt_new(packetinfo *pi)
{
    struct in6_addr ips;
    struct in6_addr ipd;
    connection *cxt;
    cxtrackerid++;
    cxt = (connection *) calloc(1, sizeof(connection));
    assert(cxt);
    cxt->cxid = cxtrackerid;
//+++
    connac_notify_flow_created();
//+++

    cxt->af = pi->af;
    if(pi->tcph) cxt->s_tcpFlags = pi->tcph->t_flags;
    //cxt->s_tcpFlags |= (pi->tcph ? pi->tcph->t_flags : 0x00);//why??
    //cxt->d_tcpFlags = 0x00;
    cxt->s_total_bytes = pi->packet_bytes;
    cxt->s_total_pkts = 1;
    cxt->start_time = pi->pheader->ts.tv_sec;
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi-> af== AF_INET6){
        cxt->s_ip = PI_IP6SRC(pi);
        cxt->d_ip = PI_IP6DST(pi);
    }else {
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        cxt->s_ip = ips;
        cxt->d_ip = ipd;
    }

    cxt->hash = pi->hash;
    cxt->s_port = pi->s_port;
    cxt->d_port = pi->d_port;
    cxt->proto = pi->proto;
    cxt->hw_proto = ntohs(pi->eth_type);

    cxt->check = 0x00;
    cxt->c_asset = NULL;
    cxt->s_asset = NULL;
    cxt->reversed = 0;

    return cxt;
}

int connection_tracking(packetinfo *pi)
{
    static char ip_addr_s[INET6_ADDRSTRLEN];
    static char ip_addr_d[INET6_ADDRSTRLEN];
    cx_track(pi);

    if(config.cflags & CONFIG_CONNECT){
        log_connection(pi->cxt, CX_EXCESSIVE);
    }
    return 0;
}

int cxt_update_client(connection *cxt, packetinfo *pi)
{
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) cxt->s_tcpFlags |= pi->tcph->t_flags;
    cxt->s_total_bytes += pi->packet_bytes;
    cxt->s_total_pkts += 1;

    pi->cxt = cxt;
    pi->sc = SC_CLIENT;
    if(!cxt->c_asset)
        cxt->c_asset = pi->asset; // connection client asset
    if (cxt->s_total_bytes > MAX_BYTE_CHECK
        || cxt->s_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont Check!
    }
    return SC_CLIENT;
}

int cxt_update_server(connection *cxt, packetinfo *pi)
{
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) cxt->d_tcpFlags |= pi->tcph->t_flags;
    cxt->d_total_bytes += pi->packet_bytes;
    cxt->d_total_pkts += 1;

    pi->cxt = cxt;
    pi->sc = SC_SERVER;
    if(!cxt->s_asset)
        cxt->s_asset = pi->asset; // server asset
    if (cxt->d_total_bytes > MAX_BYTE_CHECK
        || cxt->d_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont check!
    }
    return SC_SERVER;

}

/* return value: client or server?
 *** USED TO BE: 0 = dont check, 1 = client, 2 = server
 * now returns 0, SC_CLIENT(=1), SC_SERVER(=2)
 */

int cx_track(packetinfo *pi) {
    struct in6_addr *ip_src;
    struct in6_addr *ip_dst;
    struct in6_addr ips;
    struct in6_addr ipd;
    uint16_t src_port = pi->s_port;
    uint16_t dst_port = pi->d_port;
    int af = pi->af;
    connection *cxt = NULL;
    connection *head = NULL;
    uint32_t hash;


    if(af== AF_INET6){
        ip_src = &PI_IP6SRC(pi);
        ip_dst = &PI_IP6DST(pi);
    }else {
        // ugly hack :(
        // the way we do ip4/6 is DIRTY
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        ip_src = &ips;
        ip_dst = &ipd;
    }

    // find the right connection bucket
    if (af == AF_INET) {
        hash = CXT_HASH4(IP4ADDR(ip_src),IP4ADDR(ip_dst),src_port,dst_port,pi->proto);
    } else if (af == AF_INET6) {
        hash = CXT_HASH6(ip_src,ip_dst,src_port,dst_port,pi->proto);
    }
    pi->hash = hash;
    cxt = bucket[hash];
    head = cxt;

    // search through the bucket
    while (cxt != NULL) {
        // Two-way compare of given connection against connection table
        if (af == AF_INET) {
            if (CMP_CXT4(cxt,IP4ADDR(ip_src),src_port,IP4ADDR(ip_dst),dst_port)){
                // Client sends first packet (TCP/SYN - UDP?) hence this is a client
                return cxt_update_client(cxt, pi);
            } else if (CMP_CXT4(cxt,IP4ADDR(ip_dst),dst_port,IP4ADDR(ip_src),src_port)) {
                // This is a server (Maybe not when we start up but in the long run)
                return cxt_update_server(cxt, pi);
            }
        } else if (af == AF_INET6) {
            if (CMP_CXT6(cxt,ip_src,src_port,ip_dst,dst_port)){
                return cxt_update_client(cxt, pi);
            } else if (CMP_CXT6(cxt,ip_dst,dst_port,ip_src,src_port)){
                return cxt_update_server(cxt, pi);
            }
        }
        cxt = cxt->next;
    }
    // bucket turned upside down didn't yeild anything. new connection
    cxt = cxt_new(pi);
    log_connection(cxt, CX_NEW);

    /* * New connections are pushed on to the head of bucket[s_hash] */
    cxt->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = cxt;
    }
    bucket[hash] = cxt;
    pi->cxt = cxt;

    /* * Return value should be 1, telling to do client service fingerprinting */
    return 1;
}

void reverse_pi_cxt(packetinfo *pi)
{
    uint8_t tmpFlags;
    uint64_t tmp_pkts;
    uint64_t tmp_bytes;
    struct in6_addr tmp_ip;
    uint16_t tmp_port;
    connection *cxt;

    cxt = pi->cxt;

    /* First we chang the cxt */
    /* cp src to tmp */
    tmpFlags = cxt->s_tcpFlags;
    tmp_pkts = cxt->s_total_pkts;
    tmp_bytes = cxt->s_total_bytes;
    tmp_ip = cxt->s_ip;
    tmp_port = cxt->s_port;

    /* cp dst to src */
    cxt->s_tcpFlags = cxt->d_tcpFlags;
    cxt->s_total_pkts = cxt->d_total_pkts;
    cxt->s_total_bytes = cxt->d_total_bytes;
    cxt->s_ip = cxt->d_ip;
    cxt->s_port = cxt->d_port;

    /* cp tmp to dst */
    cxt->d_tcpFlags = tmpFlags; 
    cxt->d_total_pkts = tmp_pkts;
    cxt->d_total_bytes = tmp_bytes;
    cxt->d_ip = tmp_ip;
    cxt->d_port = tmp_port;

    /* Not taking any chances :P */
    cxt->c_asset = cxt->s_asset = NULL;
    cxt->check = 0x00;

    /* Then we change pi */
    if (pi->sc == SC_CLIENT)
       pi->sc = SC_SERVER;
    else
       pi->sc = SC_CLIENT;
}

/*
 This sub marks sessions as ENDED on different criterias:

 XXX: May be the fugliest code in PRADS :-(
*/

void end_sessions()
{

    connection *cxt;
    int iter;
    int cxstatus = CX_NONE;
    int ended, expired = 0;
    uint32_t curcxt = 0;
    time_t check_time = time(NULL);

    log_rotate(check_time);
    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        cxt = bucket[iter];
        while (cxt != NULL) {
            curcxt++;
            /* TCP */
            if (cxt->proto == IP_PROTO_TCP) {
                /* * FIN from both sides */
                if (cxt->s_tcpFlags & TF_FIN && cxt->d_tcpFlags & TF_FIN
                    && (check_time - cxt->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                } /* * RST from either side */
                else if ((cxt->s_tcpFlags & TF_RST
                          || cxt->d_tcpFlags & TF_RST)
                          && (check_time - cxt->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                }
                else if ((check_time - cxt->last_pkt_time) > TCP_TIMEOUT) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* UDP */
            else if (cxt->proto == IP_PROTO_UDP
                     && (check_time - cxt->last_pkt_time) > 60) {
                cxstatus = CX_EXPIRE;
            }
            /* ICMP */
            else if (cxt->proto == IP_PROTO_ICMP
                     || cxt->proto == IP6_PROTO_ICMP) {
                if ((check_time - cxt->last_pkt_time) > 60) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* All Other protocols */
            else if ((check_time - cxt->last_pkt_time) > TCP_TIMEOUT) {
                cxstatus = CX_EXPIRE;
            }

            if (cxstatus == CX_ENDED || cxstatus == CX_EXPIRE) {
                /* remove from the hash */
                if (cxt->prev)
                    cxt->prev->next = cxt->next;
                if (cxt->next)
                    cxt->next->prev = cxt->prev;
                connection *tmp = cxt;

                log_connection(cxt, cxstatus);
                cxstatus = CX_NONE;

                cxt = cxt->prev;

                del_connection(tmp, &bucket[iter]);
                if (cxt == NULL) {
                    bucket[iter] = NULL;
                }
            } else {
                cxt = cxt->prev;
            }
        } // end while cxt
    } // end for buckets
}

void log_connection_all()
{
    int i;
    connection *cxt;
    if(! (config.cflags & CONFIG_CXWRITE))
        return;
    for(i = 0; i < BUCKET_SIZE; i++) {
        cxt = bucket[i];
        while(cxt) {
            log_connection(cxt, CX_HUMAN);
            cxt = cxt->next;
        }
    }
}

void del_connection(connection * cxt, connection ** bucket_ptr)
{
    connection *prev = cxt->prev;       /* OLDER connections */
    connection *next = cxt->next;       /* NEWER connections */

    if (prev == NULL) {
        // beginning of list
        *bucket_ptr = next;
        // not only entry
        if (next)
            next->prev = NULL;
    } else if (next == NULL) {
        // at end of list!
        prev->next = NULL;
    } else {
        // a node.
        prev->next = next;
        next->prev = prev;
    }

    /*
     * Free and set to NULL 
     */
    free(cxt);
    cxt = NULL;
}

void end_all_sessions()
{
    connection *cxt;
    int cxkey;
    FILE *cxtFile = NULL;

    log_rotate(time(NULL));
    for (cxkey = 0; cxkey < BUCKET_SIZE; cxkey++) {
        cxt = bucket[cxkey];
        while (cxt != NULL) {
            connection *tmp = cxt;

            log_connection(cxt, CX_ENDED);
            cxt = cxt->next;
            del_connection(tmp, &bucket[cxkey]);
            if (cxt == NULL) {
                bucket[cxkey] = NULL;
            }
        }
    }
    if (cxtFile != NULL) {
        fclose(cxtFile);
    }
}

void cxt_log_buckets(int dummy)
{
    connection *cxt = NULL;
    FILE *logfile = NULL;
    int i;
    int len;

    logfile = fopen("/tmp/prads-buckets.log", "w");
    if (!logfile)
        return;

    dlog("Recieved SIGUSR1 - Dumping bucketlist to logfile\n");
    for (i = 0; i < BUCKET_SIZE; i++) {
        len = 0;
        for (cxt = bucket[i]; cxt; cxt = cxt->next)
            len++;
        if (len > 0)
            fprintf(logfile, "%d in bucket[%5d]\n", len, i);
    }

    fflush(logfile);
    fclose(logfile);
}



/* vector comparisons to speed up cx tracking.
 * meaning, compare source:port and dest:port at the same time.
 *
 * about vectors and potential improvements:
 * * all 64bit machines have at least SSE2 instructions * *BUT* there is no guarantee we won't loose time on
 * copying the vectors around.
 * ... indeed, a quick objdump shows us that
 * there is a shitton of mov instructions to align the addresses.
 *
 * Needs support to give improvements: 
 * the addresses should already be aligned as a 128-bit word
 * in the connection tracking bucket.
 *
 * note, we can employ the same technique for ipv6 addresses, but
 * one address at a time.
 */
#ifdef VECTOR_CXTRACKER
// vector fill: srcprt,dstprt,srcip,dstip = 96 bytes. rest is 0
#define VEC_FILL(vec, _ipsrc,_ipdst,_portsrc,_portdst) do {\
    vec.s[0] = (_portsrc); \
    vec.s[1] = (_portdst); \
    vec.w[1] = (_ipsrc); \
    vec.w[2] = (_ipdst); \
    vec.w[3] = 0; \
} while (0)

inline void cx_track_simd_ipv4(packetinfo *pi)
{
    connection *cxt = NULL;
    connection *head = NULL;
    uint32_t hash;

    // add to packetinfo ? dont through int32 around :)
    hash = make_hash(pi);
    cxt = bucket[hash];
    head = cxt;

    ip6v incoming;
    ip6v compare;
    VEC_FILL(incoming,
        pi->ip_src.__u6_addr.__u6_addr32[0],
        pi->ip_dst.__u6_addr.__u6_addr32[0],
        pi->s_port,
        pi->d_port);
    while (cxt != NULL) {
        VEC_FILL(compare,
        cxt->s_ip.__u6_addr.__u6_addr32[0],
        cxt->d_ip.__u6_addr.__u6_addr32[0],
        cxt->s_port,
        cxt->d_port);

        // single-instruction compare -msse2
        compare.v = __builtin_ia32_pcmpeqd128(incoming.v,compare.v);
        // same thing, really. c == v iff c ^ v == 0
        //compare.v = compare.v ^ incoming.v;

        // 64-bit compare reduce
        if(!(compare.i[0] & compare.i[1])){
            //ok
            dlog("[*] Updating src connection: %lu\n",cxt->cxid);
            cxt_update_src(cxt,pi);
            return;
        }

        // compare the other direction
        VEC_FILL(compare,
        cxt->d_ip.__u6_addr.__u6_addr32[0],
        cxt->s_ip.__u6_addr.__u6_addr32[0],
        cxt->d_port,
        cxt->s_port);

        compare.v = __builtin_ia32_pcmpeqd128(incoming.v,compare.v);
        if(!(compare.i[0] & compare.i[1])){
            dlog("[*] Updating dst connection: %lu\n",cxt->cxid);
            cxt_update_dst(cxt,pi);
            return;
        }
        cxt = cxt->next;
    }
    if (cxt == NULL) {
        cxt = (connection *) connection_alloc();
        //cxt = (connection *) calloc(1, sizeof(connection));
        if (head != NULL) {
            head->prev = cxt;
        }
        cxt = cxt_new(pi);
        dlog("[*] New connection: %lu\n",cxt->cxid);
        cxt->next = head;
        bucket[hash] = cxt;
        return;
    }
    printf("[*] Error in session tracking...\n");
    exit (1);
}

#endif

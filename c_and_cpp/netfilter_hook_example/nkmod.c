#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
 
static struct nf_hook_ops hk; 
struct sk_buff *sock_buff;
struct udphdr *udp_header;
struct tcphdr *tcp_header;
struct iphdr *ip_header;    

/************************  
    Drop icmp packets
*************************/
/*unsigned int nf_hook_ex(const struct nf_hook_ops *ops, 
                        struct sk_buff *skb, 
                        const struct net_device *in, 
                        const struct net_device *out, 
                        int (*okfn)(struct sk_buff *)){
        sock_buff = (struct sk_buff *) skb;
        ip_header = (struct iphdr *)skb_network_header(sock_buff);

        if(!sock_buff) { return NF_ACCEPT;}
        char srcip[16];
        snprintf(srcip, 16, "%pI4", &ip_header->saddr);
        if (ip_header->protocol==IPPROTO_ICMP) {
                printk(KERN_INFO "Drop ICMP packet from %s\n", srcip);
                return NF_DROP;
        }
    return NF_ACCEPT;
}*/

/********************* 
    Drop udp packets
**********************/
/*unsigned int nf_hook_ex(const struct nf_hook_ops *ops, 
                        struct sk_buff *skb, 
                        const struct net_device *in, 
                        const struct net_device *out, 
                        int (*okfn)(struct sk_buff *)){
 
        sock_buff = (struct sk_buff *) skb;
        ip_header = (struct iphdr *)skb_network_header(sock_buff);
        if(!sock_buff) { return NF_ACCEPT;}
        char srcip[16];
        snprintf(srcip, 16, "%pI4", &ip_header->saddr);
        if (ip_header->protocol==IPPROTO_UDP) {
            udp_header = (struct udphdr *)skb_transport_header(sock_buff);
            printk(KERN_INFO "Drop UDP packet from %s\n", srcip);
            return NF_DROP;
        }
    return NF_ACCEPT;
}*/

/******************************************* 
    Drop packet from 192.168.x.10
********************************************/
/*int check_source(const char* src)
{
    char buffer[4];
    int i,j;
    for(i=0;i<3;i++)
    {
        if (src[i] == '.') return 0;
        buffer[i] = src[i];
    }
    buffer[i] = '\0';
    if (memcmp(buffer, "192", 4) != 0) return 0;
    j = 4;
    for(i=0;i<3;i++)
    {
        if (src[j] == '.') return 0;
        buffer[i] = src[j];
        j++;
    }
    buffer[i] = '\0';
    if (memcmp(buffer, "168", 4) != 0) return 0;
    j = strlen(src) - 1;
    i = 0;
    while(src[j] != '.')
    {
        buffer[i] = src[j];
        j--;
        i++;
    }
    buffer[i] = '\0';
    printk(KERN_INFO "%s", buffer);
    if (strlen(buffer) != 2) return 0;
    if (memcmp(buffer, "01", 2) != 0) return 0;
    return 1;
}

unsigned int nf_hook_ex(const struct nf_hook_ops *ops, 
                        struct sk_buff *skb, 
                        const struct net_device *in, 
                        const struct net_device *out, 
                        int (*okfn)(struct sk_buff *)){
 
    sock_buff = (struct sk_buff *) skb;
 
    ip_header = (struct iphdr *)skb_network_header(sock_buff);
       
    if(!sock_buff) { return NF_ACCEPT;}
 
        
    char srcip[16];
    snprintf(srcip, 16, "%pI4", &ip_header->saddr);
    // printk(KERN_INFO "%s", srcip);
    if (check_source(srcip) == 1)
    {
        printk(KERN_INFO "Drop packet from %s\n", srcip);
        return NF_DROP;
    }
    return NF_ACCEPT;
}*/

/***********************************  
    Drop packets to port 80
************************************/
/*unsigned int nf_hook_ex(const struct nf_hook_ops *ops, 
						struct sk_buff *skb, 
						const struct net_device *in, 
						const struct net_device *out, 
						int (*okfn)(struct sk_buff *)){
 
    sock_buff = (struct sk_buff *) skb;
    ip_header = (struct iphdr *)skb_network_header(sock_buff);
    char srcip[16];
    snprintf(srcip, 16, "%pI4", &ip_header->saddr);
    if(!sock_buff) { return NF_ACCEPT;}
    if (ip_header->protocol == IPPROTO_TCP)
    {
        tcp_header = (struct tcphdr *)skb_transport_header(sock_buff);
        if (ntohs(tcp_header->dest) == 80)
        {
            printk(KERN_INFO "Drop TCP packet port 80 from %s\n", srcip);
            return NF_DROP;
        }
    }
    if (ip_header->protocol == IPPROTO_UDP)
    {
        udp_header = (struct udphdr *)skb_transport_header(sock_buff);
        if (ntohs(udp_header->dest) == 80)
        {
            printk(KERN_INFO "Drop UDP packet port 80 from %s\n", srcip);
            return NF_DROP;
        }
    }
	return NF_ACCEPT;
}*/


/***********************************************************
    Accept packets to 118.69.123.142, drop all
************************************************************/
/*unsigned int nf_hook_ex(const struct nf_hook_ops *ops, 
                        struct sk_buff *skb, 
                        const struct net_device *in, 
                        const struct net_device *out, 
                        int (*okfn)(struct sk_buff *)){
 
    sock_buff = (struct sk_buff *) skb;
 
    ip_header = (struct iphdr *)skb_network_header(sock_buff);
       
    if(!sock_buff) { return NF_ACCEPT;}
 
        
    char srcip[16];
    snprintf(srcip, 16, "%pI4", &ip_header->daddr);
    // printk(KERN_INFO "%s", srcip);
    if (strlen(srcip) != 14) return NF_DROP;
    if (memcmp(srcip, "118.69.123.142", 14) == 0)
    {
        printk(KERN_INFO "Accept packets to 118.69.123.142 \n");
        return NF_ACCEPT;
    }
    printk(KERN_INFO "Accept packets to %s \n", srcip);
    return NF_DROP;
}
*/
int kmod_init(void){
        hk = (struct nf_hook_ops){
                .hook = (nf_hookfn*)nf_hook_ex, 
                .hooknum = NF_INET_PRE_ROUTING,
                //.hooknum = NF_INET_LOCAL_OUT,
                .pf = PF_INET, 
                .priority = NF_IP_PRI_FIRST
        };
        nf_register_hook(&hk); 
 
  return 0;
}
 
void kmod_exit(void){
        nf_unregister_hook(&hk);
}
 
module_init(kmod_init);
module_exit(kmod_exit);
MODULE_LICENSE("GPL");

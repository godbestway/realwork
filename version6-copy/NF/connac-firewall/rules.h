#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED
#include "packets.h"

typedef enum{PASS, BLOCK} rule_type_t;

struct rule {
    u_char* src_ip; //source ip
    u_char* dst_ip; //destination ip
    u_char* src_port; //source port
    u_char* dst_port; //destination port
    rule_type_t rule_type; //the rule type
    struct rule* next; //pointer to the next rule in the list
};

struct rule *rule_list;

void print_rules(struct rule *rule_chain);
void parse_rules();
rule_type_t get_firewall_action(struct rule *rule_chain, u_char* saddr, u_char* dadder, u_short src_port, u_short dst_port);
#endif

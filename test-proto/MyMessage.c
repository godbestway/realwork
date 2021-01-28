#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyMessage.pb-c.h"

int main() {
    int use_syn;
    scanf("%d", &use_syn);
    puts(use_syn? "use_syn": "use_person");

    Syn syn;
    syn__init(&syn);
    syn.host = "syn_host";
    syn.has_pid = 1;
    syn.pid = 123456;

    Person  person;
    person__init(&person);
    person.name = "person_name";
    person.address = "person_address";
    person.has_age = 1;
    person.age = 18;

    MyMessage mes;
    my_message__init(&mes);
    if(use_syn) {
        mes.data_type = MY_MESSAGE__DATA_TYPE__SynType;
        mes.message_case = MY_MESSAGE__MESSAGE_SYN;
        mes.syn = &syn;
    }
    else {
        mes.data_type = MY_MESSAGE__DATA_TYPE__PersonType;
        mes.message_case = MY_MESSAGE__MESSAGE_PERSON;
        mes.person = &person;
    }

    int len = my_message__get_packed_size(&mes);
    printf("size of MyMessage : %u\n", len);
    void *buf = malloc(len);
    my_message__pack(&mes, buf);

    mes = *my_message__unpack(NULL, len, buf);
    if(mes.data_type == MY_MESSAGE__DATA_TYPE__SynType) {
        printf("syn host = %s\n", mes.syn->host);
        if(mes.syn->has_pid)
            printf("syn pid = %u\n", mes.syn->pid);
    }
    else {
        printf("person name = %s\n", mes.person->name);
        if(mes.person->has_age)
            printf("person age = %d\n", mes.person->age);
        printf("person address = %s\n", mes.person->address);
    }

    return 0;
}

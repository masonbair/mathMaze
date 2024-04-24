NodeList* concatenate(NodeList* one, NodeList* two){
    NodeList *arg = one;
    do{
        arg->prev = arg;
        arg = arg->next;
    }while(arg->next != one);
    arg->next = two;
    do{
        agr->prev = arg;
        arg = arg->next;
    }while(arg->next != two);
    arg->next = one;
    return arg;
}


void reverse(NodeList* list){
    NodeList* rev = list;
    do{
        rev = rev->prev;
    }while(rev != list)
}


double perCalc(NodeList* list){
    int number_of_students_external = 0;
    int number_of_students_in_total = 0;
    NodeList *arg = list;
    do{
        if(arg->data->reference == extRef){
            number_of_students_external++;
        }
        number_of_students_in_total++;
        arg = arg->next;
    }while(arg->next != list);

    double percantage_external = (double)(number_of_students_external)/(double)(number_of_students_in_total);
    return percantage_external;
}
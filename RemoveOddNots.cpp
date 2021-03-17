#include "IntList.h"


void IntList::removeOdds() {
    if (head->next == nullptr){
        if (head->value % 2 != 0){
            delete head;
            head = nullptr;
        }
    } else {
        IntNode* prev = head;
        IntNode* curr = head->next;
        if (head->value % 2 != 0){
            head = head->next;
            delete prev;
            prev = head;
        }
        while (curr){
            if (curr->value % 2 != 0){
                IntNode* temp = curr;
                prev->next = curr->next;
                delete temp;
                curr = curr->next;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

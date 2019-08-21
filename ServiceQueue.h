#ifndef ServiceQueue_hpp
#define ServiceQueue_hpp

#include <stdio.h>

#endif /* ServiceQueue_hpp */
#ifndef _SERVICE_QUEUE_H
#define _SERVICE_QUEUE_H

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class ServiceQueue {
    
private:
    struct buzz{
        int number; // buzzer number .. check
        buzz *next; // front pointer
        buzz *prev; // back pointer
    };
    
    // queue to store the front and back
    struct trackQueue{
        buzz *front; // pointer to front of the queue
        buzz *back; // pointer to back of queue
        int length; // length of the buzzerQueue
    };
    
    // vector of pointers
    vector <buzz*> pointerVector; // vector of pointers keeping track of buzzers for direct access
    
    // creating an object to keep track of front and back
    trackQueue *tQueueList;
    // creating an object for buzzer bin
    trackQueue *tQueueBin;
    // creating new nodes
    buzz queue;
    
public:
    
    ServiceQueue() {
        // initializing nodes in queue
        queue.next = nullptr;
        queue.prev = nullptr;
        // initializing front and back pointer
        tQueueList = new trackQueue;
        tQueueList->front = nullptr;
        tQueueList->back = nullptr;
        // initializing bucket tracker list to empty
        tQueueBin = new trackQueue;
        tQueueBin->front = nullptr;
        tQueueBin->back = nullptr;
    }
    
    ~ServiceQueue() {
        // traverse through the vector and make delete it.. confirm this
        for (int i = 0; i < pointerVector.size(); i++){
            delete pointerVector.at(i);
        }
        
        delete tQueueBin;
        delete tQueueList;
    }
    
    void snapshot(std::vector<int> &buzzers) {
        buzzers.clear();   // you don't know the history of the
        //   buzzers vector, so we had better
        //   clear it first.
        buzz *temp = tQueueList->front;
        while (temp != nullptr){
            buzzers.push_back(temp -> number);
            temp = temp -> next;
        }
    }
    int length() {
        return tQueueList->length; // returns length of buzzer queue
    }
    
    int  give_buzzer() {
        if (tQueueBin->front == nullptr){
            buzz *node = new buzz;
            node -> number = (int)pointerVector.size(); // made number unsigned long to silence error.. check
            node->next = nullptr;
            node->prev = nullptr;
            
            if(tQueueList->front == nullptr){
                tQueueList->front = node; // link the first node to the main linked list
                tQueueList->back = node;
            }
            else{
                node->prev = tQueueList->back;
                tQueueList->back->next = node;
                tQueueList->back = node;
            }
            pointerVector.push_back(node); // pushes node to vector of pointers
            delete node->next;
            delete node->prev;
            delete node;
        }
        else
        {
            buzz *t = new buzz;
            t = tQueueBin->front;
            tQueueBin->front = t->next;
            t->next = nullptr;
            t->prev = tQueueList->back;
            if(tQueueBin->front != nullptr)
                tQueueBin->front->prev = nullptr;
            tQueueList->back->next = t;
            tQueueList->back = t;
            //delete t;
        }
        tQueueList->length++;
        return tQueueList->back->number;
    }
    
    
    int seat() {
        // if queue is empty, then returning false
        if (tQueueList->front == nullptr){
            return -1;
        }
        else{
            
            buzz *temp = new buzz;
            temp = tQueueList->front;
            tQueueList->front = tQueueList->front->next;
            tQueueList->front->prev = nullptr;
            temp->next = nullptr;
            temp->prev = nullptr;
            
            buzz *t = tQueueBin->front;
            if(t!=nullptr)
            {
                t->prev = temp;
                temp->next = t;
                tQueueBin->front = temp;
            }
            else
            {
                tQueueBin->front = temp;
            }
            
            tQueueList->length --;
            //delete temp;
        }
        
        return tQueueBin->front->number;  // placeholder
        
    }
    
    bool kick_out(int buzzer) {
        // if the trouble causer doesn't exist in queue, then I return false
        if (pointerVector.at(buzzer) == nullptr){
            return false;  // placeholder
        }
        else
        {
            buzz *temp = pointerVector.at(buzzer);
            
            //if buzz is at end of queue - change back of queue
            if(temp->next == nullptr)
            {
                tQueueList->back = tQueueList->back->prev;
                tQueueList->back->next = nullptr;
            }
            else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            
            temp->prev = nullptr;
            temp->next = nullptr;
            
            buzz *t = tQueueBin->front;
            if(t!=nullptr)
            {
                t->prev = temp;
                temp->next = t;
                tQueueBin->front = temp;
            }
            else
            {
                tQueueBin->front = temp;
            }
            //delete t;
            //delete temp;
        }
        
        tQueueList->length--;
        return true;
    }
    
    bool take_bribe(int buzzer) {
        // if buzzer not there in queue
        if (pointerVector.at(buzzer) == NULL){
            return false;
        }
        else
        {
            buzz *temp = pointerVector.at(buzzer);
            // if buzz is at the end
            if(temp->next == nullptr)
            {
                tQueueList->back = tQueueList->back->prev;
                tQueueList->back->next = nullptr;
            }
            else
            {
                // break link
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            
            // put it in front
            tQueueList->front->prev = temp;
            temp->next = tQueueList->front;
            tQueueList->front = temp;
            //delete temp;
            
        }
        return true;  // placeholder
        
    }
    
};   // end ServiceQueue class

#endif

#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

void enqueue(struct queue *q, struct game_state state) {
    struct linked_list list = q -> data;
    struct linked_list * listptr = &list;
    insert_at_head(listptr, serialize(state));
}

struct game_state dequeue(struct queue *q) { 
    struct linked_list list = q -> data;
    struct linked_list * listptr = &list;
    struct game_state new_state = deserialize(remove_from_tail(listptr));
    return new_state;
}

int number_of_moves(struct game_state start) {
    struct game_state solved = {.tiles = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}};
    
    struct list_node * node = malloc(sizeof(struct list_node));
    if(node == NULL) {
      return -1;
    }
    node -> value = serialize(start);
    node -> next = NULL;
    //below not working for some reason, so copied internals above
    //struct list_node * node = new_node(serialize(start));
    struct linked_list list = {.head = node};
    struct queue q = {.data = list};
    struct queue * qptr = &q;
    while(q.data.head != NULL) {
        struct game_state curr_state;
        struct game_state * curr_state_ptr = &curr_state;
        curr_state = dequeue(qptr);
        if(serialize(solved) == serialize(curr_state)) {
            return curr_state.num_steps;
        }
        else {
            move_up(curr_state_ptr);
            enqueue(qptr, curr_state);
            move_down(curr_state_ptr);
            enqueue(qptr, curr_state);
            move_left(curr_state_ptr);
            enqueue(qptr, curr_state);
            move_right(curr_state_ptr);
            enqueue(qptr, curr_state);
        }
    }
    return -1;
}

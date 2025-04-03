#include "queue.h"
#include "tile_game.h"
int isSolved(struct game_state state);
void print_state(struct game_state state);
int in_visited(struct linked_list * visited, struct game_state state);


void enqueue(struct queue *q, struct game_state state) {
    insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) { 
    return deserialize(remove_from_head(&q->data));
}

int number_of_moves(struct game_state start) {
    //uint64_t solved = serialize((struct game_state){.tiles = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}, .empty_row = 3, .empty_col = 3});
    
    struct queue q = {.data = NULL};
    enqueue(&q, start);

    struct linked_list visited = {.head = NULL};

    while(q.data.head != NULL) {
        struct game_state curr_state = dequeue(&q);
        //print_state(curr_state);

        if(isSolved(curr_state)) {
            free_list(q.data);
            return curr_state.num_steps;
        }
        else {
            struct game_state new_state = curr_state;
            move_up(&new_state);
            if(!in_visited(&visited, new_state)) {
                insert_at_head(&visited, serialize(new_state));
                enqueue(&q, new_state);
            }
            new_state = curr_state;
            move_down(&new_state); 
            if(!in_visited(&visited, new_state)) {
                insert_at_head(&visited, serialize(new_state));
                enqueue(&q, new_state);
            }
            new_state = curr_state;
            move_left(&new_state);
            if(!in_visited(&visited, new_state)) {
                insert_at_head(&visited, serialize(new_state));
                enqueue(&q, new_state);
            }
            new_state = curr_state;
            move_right(&new_state);
            if(!in_visited(&visited, new_state)) {
                insert_at_head(&visited, serialize(new_state));
                enqueue(&q, new_state);
            }
        }
    }
    free_list(q.data);
    return -1;
}

int isSolved(struct game_state state) {
    int solved = 1; //true
    int solved_mat[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(state.tiles[i][j] != solved_mat[i][j]) {
                solved = 0; //false
            }
        }
    }
    return solved;
}

void print_state(struct game_state state) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%2d ", state.tiles[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int in_visited(struct linked_list * visited, struct game_state state) {
        if(visited -> head == NULL) {
          return 0; //false
        }
        else {
          int state_val = serialize(state);
          struct list_node * currnode = visited -> head;
          if(currnode->value == state_val) {
            return 1; //true
          } 
          while(currnode -> next != NULL) {
            currnode = currnode -> next;
            if(currnode->value == state_val) {
                return 1; //true
            } 
          }
          return 0; //false
        }
}





/*
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
    */
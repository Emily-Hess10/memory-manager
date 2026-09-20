/*
 * Memory Manager Assignment
 * Computer Science XII - Computer Systems
 *
 * This program implements a dynamic game inventory system to practice
 * manual memory management using malloc, calloc, realloc, and free.
 */

#include <stdio.h>
#include <stdlib.h>

// PART 1: Create Inventory
void create_inventory() {
    printf("\n=== PART 1: CREATE INVENTORY ===\n");

    int inventory_size = 5;

    int *item_ids = malloc(inventory_size * sizeof(int));
    int *quantities = malloc(inventory_size * sizeof(int));

    if (item_ids == NULL || quantities == NULL) {
        printf("Memory allocation failed!\n");
        free(item_ids);
        free(quantities);
        return;
    }

    for (int i = 0; i < inventory_size; i++) {
        item_ids[i] = 100 + i;
        quantities[i] = (i + 1) * 10;

        printf("  Item %d: quantity %d\n",
               item_ids[i], quantities[i]);
    }

    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}


// PART 2: Expand Inventory
void expand_inventory() {
    printf("\n=== PART 2: EXPAND INVENTORY ===\n");

    int initial_size = 3;
    int expanded_size = 6;

    int *item_ids = malloc(initial_size * sizeof(int));
    int *quantities = malloc(initial_size * sizeof(int));

    if (item_ids == NULL || quantities == NULL) {
        printf("Memory allocation failed!\n");
        free(item_ids);
        free(quantities);
        return;
    }

    for (int i = 0; i < initial_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);

        printf("  Item %d: quantity %d\n",
               item_ids[i], quantities[i]);
    }

    int *new_item_ids =
        realloc(item_ids, expanded_size * sizeof(int));

    if (new_item_ids == NULL) {
        printf("Failed to expand item IDs!\n");
        free(item_ids);
        free(quantities);
        return;
    }

    item_ids = new_item_ids;

    int *new_quantities =
        realloc(quantities, expanded_size * sizeof(int));

    if (new_quantities == NULL) {
        printf("Failed to expand quantities!\n");
        free(item_ids);
        free(quantities);
        return;
    }

    quantities = new_quantities;

    for (int i = initial_size; i < expanded_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
    }

    printf("\nExpanded inventory:\n");

    for (int i = 0; i < expanded_size; i++) {
        printf("  Item %d: quantity %d\n",
               item_ids[i], quantities[i]);
    }

    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}


// PART 3A: Memory Leak Demonstration
void memory_leak_demo() {
    printf("\n=== PART 3A: MEMORY LEAK DEMONSTRATION ===\n");
    printf("Allocating memory in a loop WITHOUT freeing...\n");

    for (int i = 0; i < 1000; i++) {

        int *temp_item = malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        temp_item[0] = 300 + i;

        // Intentionally NOT freeing this memory.
        // This demonstrates a memory leak.
    }

    printf("Loop complete. Leaked approximately %zu KB of memory.\n",
           (1000 * 1000 * sizeof(int)) / 1024);

    printf("This memory cannot be reused until the program ends.\n");
}


// PART 3B: Fixed Memory Leak
void memory_leak_fixed() {
    printf("\n=== PART 3B: FIXED VERSION - NO MEMORY LEAK ===\n");
    printf("Allocating memory in a loop WITH proper freeing...\n");

    for (int i = 0; i < 1000; i++) {

        int *temp_item = malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        temp_item[0] = 300 + i;

        free(temp_item);
    }

    printf("Loop complete. Memory properly freed after each use.\n");

    printf("Total memory allocated and freed: %zu KB\n",
           (1000 * 1000 * sizeof(int)) / 1024);
}


// PART 4: Safe Pointer Handling
void safe_pointer_handling() {
    printf("\n=== PART 4: SAFE POINTER HANDLING ===\n");

    int *player_health = malloc(sizeof(int));

    if (player_health == NULL) {
        printf("Allocation failed!\n");
        return;
    }

    *player_health = 100;

    printf("Player health: %d\n", *player_health);

    free(player_health);

    printf("Health memory freed.\n");

    player_health = NULL;

    if (player_health != NULL) {
        printf("Player health: %d\n", *player_health);
    } else {
        printf("Health data not available\n");
    }

    printf("Safe pointer handling complete.\n");
}


// MAIN
int main() {

    printf("========================================\n");
    printf("       MEMORY MANAGER ASSIGNMENT\n");
    printf("========================================\n");

    create_inventory();

    expand_inventory();

    memory_leak_demo();

    memory_leak_fixed();

    safe_pointer_handling();

    printf("\n========================================\n");
    printf("       PROGRAM COMPLETE\n");
    printf("========================================\n");

    return 0;
}
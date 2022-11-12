#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "cmd.h"
#include "adrbook.h"

void evidence_vcard_new() {
    vcard *tvc1 = vcard_new("thornsby", "th@uc.edu", "t", "h", "940");
    printf("===Evidence: VCard New ===\n\n");
    printf("Case 1: Making a VCard with the following information:\n");
    printf("Case 1: thornsby, th@uc.edu, t, h, 940\n");
    vcard_show(stderr, tvc1);
}

void evidence_singleton() {
    vcard *tvc1 = vcard_new("chornsby", "ch@uc.edu", "c", "h", "840");
    bst *tbst1 = bst_singleton(tvc1);
    printf("===Evidence: Singleton ===\n\n");
    printf("Case 1: Making a VCard with the following information:\n");
    printf("Case 1: chornsby, ch@uc.edu, c, h, 840\n");
    vcard_show(stderr, tbst1->c);
}

void evidence_insert() {
    vcard *tvc1 = vcard_new("bhornsby", "bh@uc.edu", "b", "h", "940");
    vcard *tvc2 = vcard_new("ahornsay", "ah@uc.edu", "a", "h", "840");
    vcard *tvc3 = vcard_new("dhornsby", "dh@ud.edu", "d", "h", "740");
    vcard *tvc4 = vcard_new("chornsby", "ch@ud.edu", "c", "h", "640");


    bst *tbbst = bst_singleton(tvc1); // parent element
    bst *tabst = bst_singleton(tvc2); // left element
    // bst *tcbst = bst_singleton(tvc3); // right element

    // setting left element of parent
    tbbst->left = tabst;

    bst_insert(tbbst, tvc3); // insert d element
    printf("===Evidence: Insert Right ===\n\n");
    printf("Case 1: Making a VCard with the following information:\n");
    printf("Case 1: dhornsby, dh@ud.edu, d, h, 740\n");
    vcard_show(stderr, tbbst->right->c); // c


    bst_insert(tbbst, tvc4); // insert c element

    
    printf("Case 2: Making a VCard with the following information:\n");
    printf("Case 2: chornsby, ch@uc.edu, c, h, 840\n");
    vcard_show(stderr, tbbst->right->c); // c
    printf("Case 2: should display d elements below i. e. rightmost part of tree\n");
    vcard_show(stderr, tbbst->right->right->c); // d

}

void evidence_num_entries() {
    vcard *tvc1 = vcard_new("bhornsby", "bh@uc.edu", "b", "h", "940");
    vcard *tvc2 = vcard_new("ahornsay", "ah@uc.edu", "a", "h", "840");
    vcard *tvc3 = vcard_new("dhornsby", "dh@ud.edu", "d", "h", "740");
    vcard *tvc4 = vcard_new("chornsby", "ch@ud.edu", "c", "h", "640");


    bst *tbbst = bst_singleton(tvc1); // parent element
    bst *tabst = bst_singleton(tvc2); // left element
    // bst *tcbst = bst_singleton(tvc3); // right element

    // setting left element of parent
    tbbst->left = tabst;

    printf("===Evidence: Number of Entries ===\n\n");
    printf("Case 1: Expecting 2, Recieved %d\n", bst_num_entries(tbbst));
    bst_insert(tbbst, tvc3); // insert d element
    printf("Case 2: Expecting 3, Recieved %d\n", bst_num_entries(tbbst));
    bst_insert(tbbst, tvc4); // insert c element
    printf("Case 3: Expecting 4, Recieved %d\n", bst_num_entries(tbbst));
}

void evidence_height() {
    vcard *tvc1 = vcard_new("bhornsby", "bh@uc.edu", "b", "h", "940");
    vcard *tvc2 = vcard_new("ahornsay", "ah@uc.edu", "a", "h", "840");
    vcard *tvc3 = vcard_new("dhornsby", "dh@ud.edu", "d", "h", "740");
    vcard *tvc4 = vcard_new("chornsby", "ch@ud.edu", "c", "h", "640");


    bst *tbbst = bst_singleton(tvc1); // parent element
    bst *tabst = bst_singleton(tvc2); // left element
    // bst *tcbst = bst_singleton(tvc3); // right element

    // setting left element of parent
    tbbst->left = tabst;

    /*
    tree structure
        b
      /   \
     a      

    */

    printf("=== Evidence: Height ===\n\n");
    printf("Case 1: Expecting 2, Recieved %d\n", bst_height(tbbst));
    bst_insert(tbbst, tvc3); // insert d element
    printf("Case 2: Expecting 2, Recieved %d\n", bst_height(tbbst));
    bst_insert(tbbst, tvc4); // insert c element
    printf("Case 3: Expecting 3, Recieved %d\n", bst_height(tbbst));
}

void evidence_search() {
    vcard *tvc1 = vcard_new("bhornsby", "bh@uc.edu", "b", "h", "940");
    vcard *tvc2 = vcard_new("ahornsay", "ah@uc.edu", "a", "h", "840");
    vcard *tvc3 = vcard_new("dhornsby", "dh@ud.edu", "d", "h", "740");
    vcard *tvc4 = vcard_new("chornsby", "ch@ud.edu", "c", "h", "640");


    bst *tbbst = bst_singleton(tvc1); // parent element
    bst *tabst = bst_singleton(tvc2); // left element
    // bst *tcbst = bst_singleton(tvc3); // right element

    // setting left element of parent
    tbbst->left = tabst;

    /*
    tree structure
        b
      /   \
     a      

    */
    int n_cmps = 0;
    vcard *ts1 = bst_search(tbbst, "ahornsay", &n_cmps);
    printf("=== Evidence: Search ===\n\n");
    printf("Case 1: Expecting ahornsay, 2. Recieved %s, %d\n", ts1->cnet, n_cmps);
    bst_insert(tbbst, tvc3); // insert d element
    n_cmps = 0;
    vcard *ts2 = bst_search(tbbst, "dhornsby", &n_cmps);
    printf("Case 2: Expecting chornsby, 2. Recieved %s, %d\n", ts2->cnet, n_cmps);
    bst_insert(tbbst, tvc4); // insert c element
     n_cmps = 0;
    vcard *ts3 = bst_search(tbbst, "dhornsby", &n_cmps);
    printf("Case 3: Expecting dhornsby, 3. Recieved %s, %d\n", ts3->cnet, n_cmps);
}

void evidence_c() {
    vcard *tvc1 = vcard_new("bhornsby", "bh@uc.edu", "b", "h", "940");
    vcard *tvc2 = vcard_new("ahornsay", "ah@uc.edu", "a", "h", "840");
    vcard *tvc3 = vcard_new("dhornsby", "dh@ud.edu", "d", "h", "740");
    vcard *tvc4 = vcard_new("dable", "ch@ud.edu", "c", "h", "640");
    vcard *tvc5 = vcard_new("dzble", "ch@ud.edu", "c", "h", "640");
    vcard *tvc6 = vcard_new("dhble", "ch@ud.edu", "c", "h", "640");



    bst *tbbst = bst_singleton(tvc1); // parent element
    bst *tabst = bst_singleton(tvc2); // left element
    // bst *tcbst = bst_singleton(tvc3); // right element

    // setting left element of parent
    tbbst->left = tabst;

    /*
    tree structure
        b
      /   \
     a     da
            \
             dh

    */
    bst_insert(tbbst, tvc3); // insert d element
    bst_insert(tbbst, tvc4); // insert c element

    printf("=== Evidence: CNet Printer ===\n\n");
    printf("Case 1: Expecting dable, dhornsby. Recieved: \n");
    bst_c(stderr, tbbst, 'd');
    bst_insert(tbbst, tvc5); // insert dz element
    bst_insert(tbbst, tvc6); // insert dh element
    
    printf("Case 2: Expecting dable, dhble, dhornsby, dzble. Recieved: \n");
    bst_c(stderr, tbbst, 'd');
}

void evidence_free(){
    
}

int main() {
    // evidence_vcard_new();
    // evidence_singleton();
    // evidence_insert();
    // evidence_num_entries();
    // evidence_height();
    // evidence_search();
    // evidence_c();
    // evidence_single();
    // evidence_insert();
}
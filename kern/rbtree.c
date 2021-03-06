int jsw_remove ( struct jsw_tree *tree, int data )
 {
   if ( tree->root != NULL ) {
     struct jsw_node head = {0}; /* False tree root */
     struct jsw_node *q, *p, *g; /* Helpers */
     struct jsw_node *f = NULL;  /* Found item */
     int dir = 1;
 
     /* Set up helpers */
     q = &head;
     g = p = NULL;
     q->link[1] = tree->root;
 
     /* Search and push a red down */
     while ( q->link[dir] != NULL ) {
       int last = dir;
 
       /* Update helpers */
       g = p, p = q;
       q = q->link[dir];
       dir = q->data < data;
 
       /* Save found node */
       if ( q->data == data )
         f = q;
 
       /* Push the red node down */
       if ( !is_red ( q ) && !is_red ( q->link[dir] ) ) {
         if ( is_red ( q->link[!dir] ) )
           p = p->link[last] = jsw_single ( q, dir );
         else if ( !is_red ( q->link[!dir] ) ) {
           struct jsw_node *s = p->link[!last];
 
           if ( s != NULL ) {
             if ( !is_red ( s->link[!last] ) && !is_red ( s->link[last] ) ) {
               /* Color flip */
               p->red = 0;
               s->red = 1;
               q->red = 1;
             }
             else {
               int dir2 = g->link[1] == p;
 
               if ( is_red ( s->link[last] ) )
                 g->link[dir2] = jsw_double ( p, last );
               else if ( is_red ( s->link[!last] ) )
                 g->link[dir2] = jsw_single ( p, last );
 
               /* Ensure correct coloring */
               q->red = g->link[dir2]->red = 1;
               g->link[dir2]->link[0]->red = 0;
               g->link[dir2]->link[1]->red = 0;
             }
           }
         }
       }
     }
 
     /* Replace and remove if found */
     if ( f != NULL ) {
       f->data = q->data;
       p->link[p->link[1] == q] =
         q->link[q->link[0] == NULL];
       free ( q );
     }
 
     /* Update root and make it black */
     tree->root = head.link[1];
     if ( tree->root != NULL )
       tree->root->red = 0;
   }
 
   return 1;
 }

int jsw_insert ( struct jsw_tree *tree, int data )
{
   if ( tree->root == NULL ) {
     /* Empty tree case */
    tree->root = make_node ( data );
    if ( tree->root == NULL )
       return 0;
   }
   else {
     struct jsw_node head = {0}; /* False tree root */
 
     struct jsw_node *g, *t;     /* Grandparent & parent */
     struct jsw_node *p, *q;     /* Iterator & parent */
     int dir = 0, last;
 
     /* Set up helpers */
     t = &head;
     g = p = NULL;
     q = t->link[1] = tree->root;
 
     /* Search down the tree */
     for ( ; ; ) {
       if ( q == NULL ) {
         /* Insert new node at the bottom */
         p->link[dir] = q = make_node ( data );
         if ( q == NULL )
           return 0;
       }
       else if ( is_red ( q->link[0] ) && is_red ( q->link[1] ) ) {
         /* Color flip */
         q->red = 1;
         q->link[0]->red = 0;
         q->link[1]->red = 0;
       }
 
       /* Fix red violation */
       if ( is_red ( q ) && is_red ( p ) ) {
         int dir2 = t->link[1] == g;
 
         if ( q == p->link[last] )
           t->link[dir2] = jsw_single ( g, !last );
         else
           t->link[dir2] = jsw_double ( g, !last );
       }
 
      /* Stop if found */
       if ( q->data == data )
         break;
 
       last = dir;
       dir = q->data < data;
 
       /* Update helpers */
       if ( g != NULL )
         t = g;
       g = p, p = q;
       q = q->link[dir];
     }
 
     /* Update root */
     tree->root = head.link[1];
   }

   /* Make root black */
   tree->root->red = 0;
 
   return 1;
}

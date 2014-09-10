
struct env * ready_queue;
struct env * blocked_queue;
struct env * terminated;
struct env * current;

int
init_queue(struct env ** q)
{
    *q = malloc(sizeof*(*q)));
    memset(*q, 0, sizeof*(*q)));
    *q->next = *q;
    return 0; 
}

int
insert_env(struct env * e, struct env * q)
{
    e->next = q->next;
    q->next = e;
    return 0;
}

int
syscall_yield()
{

}

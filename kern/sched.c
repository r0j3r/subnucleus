#include "env.h"
#include "quantum.h"
#include "cpu.h"

unsigned int cur_quant;
const int NUM_CPU = 2;
struct cpu cpu_ctx[2]; 

void
init_quantum_vec(void) {
    for (int i = 0; i < NUM_CPU; i++) {
        struct cpu * c = &cpu_ctx[i];
        for(int j = 0; j < (1 << 7); j++) {
            c->q_no[j] = j; 
        }
    }
}

int
init_queue(struct env ** q) {
    *q = malloc(sizeof*(*q)));
    memset(*q, 0, sizeof*(*q)));
    *q->next = *q;
    return 0; 
}

int
insert_env(struct env * e, struct env * q) {
    e->next = q->next;
    q->next = e;
    return 0;
}

int
syscall_yield() {

}

int
sched_next(void) {
    cur_quant = (cur_quant + 1) & ((1 << 7) - 1);
    if (!cur_quant) {
        a = active;
        active = expired;
        expired = a;
        cur_quant = 1; 
    }
}

void
sched_intr(int trapno) {
    now = get_time();
    ev = dequeue();
    while(now > ev->expiry) {
        if (ev->timer) {
            process_timer(now);
        } else if (ev->quantum) {
            active[cur_quant] = 0;
            expired[cur_quant] = 8;
            sched_next();
            enqueue_quantum(cur_quant);
        } 
    }
    get_next_timeout();
    intr_return();
}

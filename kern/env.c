struct env *
create_env()
{
    struct env * e;

    e = malloc(sizeof(*e));
    memset(e, 0, sizeof(*e));

    get_random(b, 8);
    create_mapping();
    return e;
}

int
delete_env(struct env * e)
{
    return free(e); 
}

int 
syscall_create_env()
{}

int syscall_destroy_env()
{}

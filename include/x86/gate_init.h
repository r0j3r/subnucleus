struct gate_init_entry
{
    unsigned entrypoint;
    unsigned short vector;
    unsigned short type;
};

void gate_init(struct x86_gate *, const struct gate_init_entry *, unsigned);

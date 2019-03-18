struct task
{
    int              taskid;
    char             type[25];
    char             desc[80];
    struct record*   next;

};
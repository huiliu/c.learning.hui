#include <stdio.h>

//存储结构

typedef struct node
{
  int x;
  unsigned u_i;
  char * pc_station;
  node * p_next;
} node ;

typedef struct
{
    node * head;
    node * tail;
    node * cur;
    unsigned u_len;
} List;

node append (node *N)
{
    N->p_next = cur->p_next;
    cur->p_next = &N;
    u_len++;
}

node find (char *data)
{
    node *tmp = List->head;

    while (&tmp->p_next != NULL)
    {
        if (&(tmp->pc_station) == &data)
            return &tmp;
    }
    return NULL;
}

void display()
{
    node *tmp = head;
    while (tmp->p_next != NULL)
    {
        printf("%s",&(tmp->pc_station));
    }
}


int main (void)
{
    List list;
    node *data;
    data->pc_station = "石桥湾加油站";
    append(data);
    display();
}

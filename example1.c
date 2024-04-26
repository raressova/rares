#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct graph
{
    int num_vertices;
    int *visited;
    struct Node **adj_list;
} GPH;

typedef struct stack
{
    int top;
    int cap;
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = g->adj_list[src];
    g->adj_list[src] = new_node;
    new_node = create_node(src);
    new_node->next = g->adj_list[dest];
    g->adj_list[dest] = new_node;
}

GPH *create_graph(int v)
{
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->num_vertices = v;
    g->adj_list = malloc(v * sizeof(NODE *));
    g->visited = malloc(v * sizeof(int));

    for (i = 0; i < v; i++)
    {
        g->adj_list[i] = NULL;
        g->visited[i] = 0;
    }
    return g;
}

STK *create_stack(int cap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(cap * sizeof(int));
    s->top = -1;
    s->cap = cap;

    return s;
}

void push(int item, STK *s)
{
    s->top = s->top + 1;
    s->arr[s->top] = item;
}

void DFS(GPH *g, STK *s, int v_nr)
{
    NODE *adj_list = g->adj_list[v_nr];
    NODE *aux = adj_list;
    g->visited[v_nr] = 1;
    push(v_nr, s);
    while (aux != NULL)
    {
        int adj_vertex = aux->data;
        if (g->visited[adj_vertex] == 0)
            DFS(g, s, adj_vertex);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest, i;
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->visited[i] = 0;
    }
}

void canbe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        for (int j = 0; j < nrv; j++)
        {
            if (i != j)
            {
                STK *s1 = create_stack(2 * nrv);
                STK *s2 = create_stack(2 * nrv);
                DFS(g, s1, i);
                wipe(g, nrv);
                DFS(g, s2, j);
                if (g->visited[i] && g->visited[j])
                    printf("1 ");
                else
                    printf("0 ");
                free(s1->arr);
                free(s1);
                free(s2->arr);
                free(s2);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int main()
{
    int num_vertices;
    int num_edges;

    printf("Câte noduri are graful? ");
    scanf("%d", &num_vertices);

    printf("Câte muchii are graful? ");
    scanf("%d", &num_edges);

    GPH *g = create_graph(num_vertices);

    insert_edges(g, num_edges, num_vertices);

    canbe(g, num_vertices);

    for (int i = 0; i < num_vertices; i++)
    {
        NODE *node = g->adj_list[i];
        while (node != NULL)
        {
            NODE *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(g->adj_list);
    free(g->visited);
    free(g);

    return 0;
}

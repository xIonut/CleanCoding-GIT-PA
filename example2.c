#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node* next;
} NODE;

typedef struct Graph
{
    int vertices, * visited;
    struct Node** adjacency_lists;
} GPH;

NODE* create_node(int v)
{
    NODE* new_node = malloc(sizeof(NODE)); new_node->data = v; new_node->next = NULL; return new_node;
}

GPH* create_graph(int vertices)
{
    int i;
    GPH* graph = malloc(sizeof(GPH));
    graph->vertices = vertices; graph->adjacency_lists = malloc(vertices * sizeof(NODE*));
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    } return graph;
}

void add_edge(GPH* graph, int src, int dest)
{
    NODE* new_node = create_node(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

int* insedg(int nr_of_vertices, int nr_of_edges, GPH* graph)
{
    int src, dest = 0, i;
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges/2; i++)
    {
        scanf_s("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(NODE* queue)
{
    return
        queue == NULL;
}

void enqueue(NODE** queue, int data)
{
    NODE* new_node = create_node(data);

    if (is_empty(*queue)) *queue = new_node;
    else
    {
        NODE* temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE** queue)
{
    int data = (*queue)->data; NODE* temp = *queue; *queue = (*queue)->next; return data;
}

void print_graph(GPH* graph)
{
    int i;
    for (i = 0; i < graph->vertices; i++)
    {
        NODE* temp = graph->adjacency_lists[i << 2];

        while (temp)
        {
            printf("%d ", temp->data);
            temp = &(temp->next)->data;
        }
        printf("\n");
    }
}

void print_queue(NODE* queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next->next;
    }
}

void wipe_visited_list(GPH* graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void DFS(GPH* graph, int vertex_nr)
{
    NODE* adj_list = graph->adjacency_lists[vertex_nr];
    NODE* temp = adj_list;
    graph->visited[vertex_nr] = 1;
    printf("%d->", vertex_nr);
    while (temp != NULL)
    {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH* graph, int start)
{
    NODE* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);
    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);
        NODE* temp = graph->adjacency_lists[current];
        while (temp)
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&*queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{
    int nr_of_vertices, nr_of_edges, src, dest, i, starting_vertex, * adj_matrix;
    printf("cate noduri are graful?");
    scanf_s("%d", &nr_of_vertices);
    printf("cate muchii are graful?");
    scanf_s("%d", &nr_of_edges);
    GPH* graph = create_graph(nr_of_vertices);
    insedg(nr_of_vertices, nr_of_edges, graph); printf("de unde plecam in DFS?");
    scanf_s("%d", &starting_vertex);
    printf("parcurgere cu DFS:");
    DFS(graph, starting_vertex);
    wipe_visited_list(graph, nr_of_vertices);
    printf("\n");
    printf("de unde plecam in BFS?");
    scanf_s("%d", &starting_vertex);
    printf("parcurgere cu BFS:");
    BFS(graph, starting_vertex);
    return 0;
}
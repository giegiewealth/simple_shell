#include "shell.h"

/**
 * add_node - adds a node to the start of the list.......
 * @head: address of pointer to head node.......
 * @str: str field of node.......
 * @num: node index used by history.......
 *
 * Return: size of list.......
 */
list_t *add_node(list_t **head, const char *str, int num)
{
    list_t *new_head_list;

    if (!head)
        return (NULL);
    new_head_list = malloc(sizeof(list_t));
    if (!new_head_list)
        return (NULL);
    _memset((void *)new_head_list, 0, sizeof(list_t));
    new_head_list->num = num;
    if (str)
    {
        new_head_list->str = _strdup(str);
        if (!new_head_list->str)
        {
            free(new_head_list);
            return (NULL);
        }
    }
    new_head_list->next = *head;
    *head = new_head_list;
    return (new_head_list);
}

/**
 * add_node_end - adds a node to the end of the list......
 * @head: address of pointer to head node......
 * @str: str field of node......
 * @num: node index used by history......
 *
 * Return: size of list......
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node_list, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node_list = malloc(sizeof(list_t));
    if (!new_node_list)
        return (NULL);
    _memset((void *)new_node_list, 0, sizeof(list_t));
    new_node_list->num = num;
    if (str)
    {
        new_node_list->str = _strdup(str);
        if (!new_node_list->str)
        {
            free(new_node_list);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node_list;
    }
    else
        *head = new_node_list;
    return (new_node_list);
}

/**
 * print_list_str - prints only the str element of a list_t linked list......
 * @h: pointer to first node......
 *
 * Return: size of list......
 */
size_t print_list_str(const list_t *h)
{
    size_t index = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        index++;
    }
    return (index);
}

/**
 * delete_node_at_index - deletes node at given index......
 * @head: address of pointer to first node......
 * @index: index of node to delete......
 *
 * Return: 1 on success, 0 on failure......
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *node_list, *prev_node_list;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node_list = *head;
        *head = (*head)->next;
        free(node_list->str);
        free(node_list);
        return (1);
    }
    node_list = *head;
    while (node_list)
    {
        if (i == index)
        {
            prev_node_list->next = node_list->next;
            free(node_list->str);
            free(node_list);
            return (1);
        }
        i++;
        prev_node_list = node_list;
        node_list = node_list->next;
    }
    return (0);
}

/**
 * free_list - frees all nodes of a list....
 * @head_ptr: address of pointer to head node....
 *
 * Return: void....
 */
void free_list(list_t **head_ptr)
{
    list_t *node_list, *next_node_list, *head;

    if (!head_ptr || !*head_ptr)
        return;
    head = *head_ptr;
    node_list = head;
    while (node_list)
    {
        next_node_list = node_list->next;
        free(node_list->str);
        free(node_list);
        node_list = next_node_list;
    }
    *head_ptr = NULL;
}

#include "shell.h"

alias_t *alias_adder_end(alias_t **head, char *name, char *value);
void alias_list_freer(alias_t *head);
list_t *node_adder_end(list_t **head, char *dir);
void list_freer(list_t *head);
char *name;

/**
* alias_adder_end - Adds a node to the end of a alias_t linked list.
* @head: A pointer to the head of the list_t list.
* @name: The name of the new alias to be added.
* @value: The value of the new alias to be added.
*
* Return: If an error occurs - NULL.
*         Otherwise - a pointer to the new node.
*/
alias_t *alias_adder_end(alias_t **head, char *name, char *value)
{
alias_t *new_nd = malloc(sizeof(alias_t));
alias_t *last;

if (!new_nd)
return (NULL);

new_nd->next = NULL;
new_nd->name = malloc(sizeof(char) * (_strlen(name) + 1));
if (!new_nd->name)
{
free(new_nd);
return (NULL);
}
new_nd->value = value;
_strcpy(new_nd->name, name);

if (*head)
{
last = *head;
while (last->next != NULL)
last = last->next;
last->next = new_nd;
}
else
*head = new_nd;

return (new_nd);
}

/**
* node_adder_end - Adds a node to the end of a list_t linked list.
* @head: A pointer to the head of the list_t list.
* @dir: The directory path for the new node to contain.
*
* Return: If an error occurs - NULL.
*         Otherwise - a pointer to the new node.
*/
list_t *node_adder_end(list_t **head, char *dir)
{
list_t *new_nd = malloc(sizeof(list_t));
list_t *last;

if (!new_nd)
return (NULL);

new_nd->dir = dir;
new_nd->next = NULL;

if (*head)
{
last = *head;
while (last->next != NULL)
last = last->next;
last->next = new_nd;
}
else
*head = new_nd;

return (new_nd);
}

/**
* alias_list_freer - Frees a alias_t linked list.
* @head: THe head of the alias_t list.
*/
void alias_list_freer(alias_t *head)
{
alias_t *next;

while (head)
{
next = head->next;
free(head->name);
free(head->value);
free(head);
head = next;
}
}

/**
* list_freer - Frees a list_t linked list.
* @head: The head of the list_t list.
*/
void list_freer(list_t *head)
{
list_t *next;

while (head)
{
next = head->next;
free(head->dir);
free(head);
head = next;
}
}

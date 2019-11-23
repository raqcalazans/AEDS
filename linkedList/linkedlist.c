struct Node
{
  /* data */
};

struct LinkedList
{
  Node *first;
};

LinkedList *init();

Node *add(LinkedList *list, char *nome, char *numero, char *agencia, int tipo);

Node *get(LinkedList *list, char *numero, char *agencia);

int delete (LinkedList *list, char *numero, char *agencia);

void printAll(LinkedList *list);

int debitar(LinkedList *list, char *numero, char *agencia, float valor);

int depositar(LinkedList *list, char *numero, char *agencia, float valor);

int transferencia(LinkedList *list, char *numOrigem, char *agOrigem, char *numDestino, char *agDestino, float valor);

void lerArquivo(LinkedList *list);

void escreverArquivo(LinkedList *list);
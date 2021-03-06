#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node {
  struct Node *left;
  struct Node *right;
  char val;
};

char operands[] = "+-*/%";
int inserted = 0;

void insert (char val, struct Node *t){
  if(strchr(operands, t -> val)){
    printf("Where to go?\n");
    if(t -> left == 0){
      printf("Trying to insert %c to the LEFT of %c\n", val, t->val);
      struct Node *temp = (struct Node *) malloc( sizeof (struct Node));
      temp -> left = 0;
      temp -> right = 0;
      temp -> val = val;
      t -> left = temp;
      inserted = 1;
    }else if(t -> left != 0 && strchr (operands, t -> left -> val)){
      insert(val, t -> left);
    }
    if (t -> right == 0 && !inserted) {
      printf("Trying to insert %c to the RIGHT of %c\n", val, t->val);
      struct Node *temp = (struct Node *) malloc( sizeof (struct Node));
      temp -> left = 0;
      temp -> right = 0;
      temp -> val = val;
      t -> right = temp;
      inserted = 1;
    }else if(t -> right != 0 && strchr (operands, t -> right -> val)){
      insert(val, t -> right);
    }
  }
}

void printNodes(struct Node *t){
  if(t->left) printNodes(t->left);
  if(t->right) printNodes(t->right);
  printf("%c\n",t->val);
}

int level = 0;
void evalNodes(struct Node *t){
  if (strchr(operands, t -> right -> val)) {
    level++;
    evalNodes(t -> right);
  }else{
    printf("L %c\n", t-> right -> val);
    char inst;
    switch (t -> val) {
      case '+':
        inst = 'A'; break;
      case '-':
        inst = 'S'; break;
      case '*':
        inst = 'M'; break;
      case '/':
        inst = 'D'; break;
      case '%':
        inst = 'R'; break;
    }
    printf("%c %c\n",inst, t -> left -> val );
    printf("ST $%c\n", level+'0');
    level--;
  }
  if (strchr(operands, t -> left -> val)) {
    level++;
    evalNodes(t -> left);
    level--;
  }

}

int main(int argc, char const *argv[]) {
  if(argc < 2){
    printf("No code to generate.\n");
    return 0;
  }

  char words[] = "LASMDRX";

  printf("Decomposing string... %s\n", argv[1]);
  const char *code = argv[1];
  int i;

  // Debug Purposes
  for (i = strlen(argv[1])-1; i >= 0; i--) {
    printf("%c", code[i]);
    if (strchr(operands, code[i])) {
      printf(" is an operand.\n");
    }else{
      printf("\n");
    }
  }
  // End Debug

  struct Node *root = (struct Node *) malloc( sizeof (struct Node));
  root -> left = 0;
  root -> right = 0;
  root -> val = code[strlen(argv[1])-1];

  printf("Node value is %c \n", root -> val );
  for (i = strlen(argv[1])-2; i >= 0; i--) {
    printf("Trying to insert value... %c\n", code[i]);
    inserted = 0;
    insert(code[i], root);
  }
  printNodes(root);

  evalNodes(root);

  return 0;
}

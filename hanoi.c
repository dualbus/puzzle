#include <stdlib.h>
#include <stdio.h>

enum movements {
  MVMT_AB, MVMT_AC,
  MVMT_BC, MVMT_CB,
  MVMT_CA, MVMT_BA
};

struct movement {
  unsigned long disk;
  enum movements poles;
};

struct movement_list {
  struct movement node;
  struct movement_list *next;
};

struct movement_bintree {
  struct movement node;
  struct movement_bintree *left;
  struct movement_bintree *right;
};

int compute_children(struct movement_bintree*);
struct movement_bintree* compute_tree(struct movement_bintree*,
    unsigned long
    );
void traverse_tree(struct movement_bintree*);


const char *movements_string[] = {
  "ab", "ac",
  "bc", "cb",
  "ca", "ba",
};

enum movements movements_table[][2] = {
  {MVMT_CB, MVMT_AC}, {MVMT_BC, MVMT_AB},
  {MVMT_AC, MVMT_BA}, {MVMT_AB, MVMT_CA},
  {MVMT_BA, MVMT_CB}, {MVMT_CA, MVMT_BC},
};


int
main(int argc, char **argv)
{
  struct movement_bintree *root = NULL;
  if(argc > 1) {
    long i = atol(argv[1]);
    if(i < 0) {
      exit(EXIT_FAILURE);
    }
    root = compute_tree(root, (unsigned long)i);
    traverse_tree(root);
    exit(EXIT_SUCCESS);
  }
  exit(EXIT_FAILURE);
}


int
compute_children(struct movement_bintree* tree)
{
#ifdef DEBUG
  puts("call compute_children");
#endif

  /* allocate memory for our children */
  tree->left  = (struct movement_bintree*)malloc(
      sizeof(struct movement_bintree)
      );

  tree->right = (struct movement_bintree*)malloc(
      sizeof(struct movement_bintree)
      );

  /* insufficient memory, halt! */
  if(tree->left == NULL || tree->right == NULL) {
    /* brainfart */
  }

  tree->left->node.poles =  movements_table[tree->node.poles][0];
  tree->right->node.poles = movements_table[tree->node.poles][1];

  return 1;
}


struct movement_bintree*
compute_tree(struct movement_bintree* root, unsigned long level)
{
#ifdef DEBUG
  puts("call compute_tree");
#endif

  if(level <= 0) {
    return NULL;
  }

  if(root == NULL) {
    root = (struct movement_bintree*)malloc(
        sizeof(struct movement_bintree)
        );

    if(root == NULL) {
      /* brainfart */
    }

    root->node.poles = MVMT_AC;
  }

  root->node.disk = level;

  if(level > 1) {
    compute_children(root);
    compute_tree(root->left,  level-1);
    compute_tree(root->right, level-1);
  }

  return root;
}


void
traverse_tree(struct movement_bintree* tree)
{
#ifdef DEBUG
  puts("call traverse_tree");
#endif

  if(tree == NULL) {
    return;
  }

  traverse_tree(tree->right);
  printf("%lu%s\n",
      tree->node.disk,
      movements_string[tree->node.poles]
      );
  traverse_tree(tree->left);
}

struct node *newNode(int item)
{
  struct node *temp = (struct node *) malloc(sizeof(struct node));
  temp->key = item;
  temp->left = 0;
  temp->right = 0;
  return temp;
}


/*** DEPENDENCIES:
struct node
{
  int key;
  struct node *left;
  struct node *right;
}
----------------------------
***/


struct node *minValueNode(struct node *node)
{
  struct node *current = node;
  unsigned int current_idx = 0;
  while ((&current[current_idx]) && (current->left != 0))
    current_idx = current_idx->left;

  return current;
}


/*** DEPENDENCIES:
struct node
{
  int key;
  struct node *left;
  struct node *right;
}
----------------------------
***/


void inorder(struct node *root)
{
  if (root != 0)
  {
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
  }
}


/*** DEPENDENCIES:
struct node
{
  int key;
  struct node *left;
  struct node *right;
}
----------------------------
***/


struct node *insert(struct node *node, int key)
{
  if (node == 0)
  {
    return newNode(key);
  }
  if (key < node->key)
  {
    node->left = insert(node->left, key);
  }
  else
    node->right = insert(node->right, key);
  return node;
}


/*** DEPENDENCIES:
struct node
{
  int key;
  struct node *left;
  struct node *right;
}
----------------------------
struct node *newNode(int item)
{
  struct node *temp = (struct node *) malloc(sizeof(struct node));
  temp->key = item;
  temp->left = 0;
  temp->right = 0;
  return temp;
}


----------------------------
***/


struct node *deleteNode(struct node *root, int key)
{
  if (root == 0)
  {
    return root;
  }
  if (key < root->key)
  {
    root->left = deleteNode(root->left, key);
  }
  else
    if (key > root->key)
  {
    root->right = deleteNode(root->right, key);
  }
  else
  {
    if (root->left == 0)
    {
      struct node *temp = root->right;
      free(root);
      return temp;
    }
    else
      if (root->right == 0)
    {
      struct node *temp = root->left;
      free(root);
      return temp;
    }
    struct node *temp = minValueNode(root->right);
    root->key = temp->key;
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}


/*** DEPENDENCIES:
struct node
{
  int key;
  struct node *left;
  struct node *right;
}
----------------------------
struct node *minValueNode(struct node *node)
{
  struct node *current = node;
  unsigned int current_idx = 0;
  while ((&current[current_idx]) && (current->left != 0))
    current_idx = current_idx->left;

  return current;
}


----------------------------
***/



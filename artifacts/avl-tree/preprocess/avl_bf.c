# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.h"
enum avlbf {
 LEFTHEAVY = -1,
 BALANCED = 0,
 RIGHTHEAVY = 1
};

enum avltraversal {
 PREORDER,
 INORDER,
 POSTORDER
};

typedef struct avlnode {
 struct avlnode *left;
 struct avlnode *right;
 struct avlnode *parent;
 char bf;
 void *data;
} avlnode;

typedef struct {
 int (*compare)(const void *, const void *);
 void (*print)(void *);
 void (*destroy)(void *);

 avlnode root;
 avlnode nil;


 avlnode *min;

} avltree;
# 59 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.h"
avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *));
void avl_destroy(avltree *avlt);

avlnode *avl_find(avltree *avlt, void *data);
avlnode *avl_successor(avltree *avlt, avlnode *node);

int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order);
void avl_print(avltree *avlt, void (*print_func)(void *));

avlnode *avl_insert(avltree *avlt, void *data);
void *avl_delete(avltree *avlt, avlnode *node, int keep);

int avl_check_order(avltree *avlt, void *min, void *max);
int avl_check_height(avltree *avlt);
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c" 2

static avlnode *rotate_left(avltree *avlt, avlnode *x);
static avlnode *rotate_right(avltree *avlt, avlnode *x);

static avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p);

static int check_order(avltree *avlt, avlnode *n, void *min, void *max);
static int check_height(avltree *avlt, avlnode *n);

static void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label);
static void destroy(avltree *avlt, avlnode *n);





avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *))
{
 avltree *avlt;

 avlt = (avltree *) malloc(sizeof(avltree));
 if (avlt == 0)
  return 0;

 avlt->compare = compare_func;
 avlt->destroy = destroy_func;


 avlt->nil.left = avlt->nil.right = avlt->nil.parent = (&(avlt)->nil);
 avlt->nil.bf = 0;
 avlt->nil.data = 0;


 avlt->root.left = avlt->root.right = avlt->root.parent = (&(avlt)->nil);
 avlt->root.bf = 0;
 avlt->root.data = 0;


 avlt->min = 0;


 return avlt;
}




void avl_destroy(avltree *avlt)
{
 destroy(avlt, ((avlt)->root.left));
 free(avlt);
}





avlnode *avl_find(avltree *avlt, void *data)
{
 avlnode *p;

 p = ((avlt)->root.left);

 while (p != (&(avlt)->nil)) {
  int cmp;
  cmp = avlt->compare(data, p->data);
  if (cmp == 0)
   return p;
  p = (cmp < 0) ? p->left : p->right;
 }

 return 0;
}





avlnode *avl_successor(avltree *avlt, avlnode *node)
{
 avlnode *p;

 p = node->right;

 if (p != (&(avlt)->nil)) {

  for ( ; p->left != (&(avlt)->nil); p = p->left) ;
 } else {

  for (p = node->parent; node == p->right; node = p, p = p->parent) ;

  if (p == (&(avlt)->root))
   p = 0;
 }

 return p;
}





int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order)
{
 int err;

 if (node != (&(avlt)->nil)) {
  if (order == PREORDER && (err = func(node->data, cookie)) != 0)
   return err;
  if ((err = avl_apply(avlt, node->left, func, cookie, order)) != 0)
   return err;
  if (order == INORDER && (err = func(node->data, cookie)) != 0)
   return err;
  if ((err = avl_apply(avlt, node->right, func, cookie, order)) != 0)
   return err;
  if (order == POSTORDER && (err = func(node->data, cookie)) != 0)
   return err;
 }

 return 0;
}




void avl_print(avltree *avlt, void (*print_func)(void *))
{
 printf("\n--\n");
 print(avlt, ((avlt)->root.left), print_func, 0, "T");
 printf("\nheight = %d\n", check_height(avlt, ((avlt)->root.left)));
}




int avl_check_order(avltree *avlt, void *min, void *max)
{
 return check_order(avlt, ((avlt)->root.left), min, max);
}




int avl_check_height(avltree *avlt)
{
 int height;
 height = check_height(avlt, ((avlt)->root.left));

 return (height < 0) ? 0 : 1;
}





avlnode *avl_insert(avltree *avlt, void *data)
{
 avlnode *current, *parent;
 avlnode *new_node;



 current = ((avlt)->root.left);
 parent = (&(avlt)->root);

 while (current != (&(avlt)->nil)) {
  int cmp;
  cmp = avlt->compare(data, current->data);
# 189 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
  parent = current;
  current = (cmp < 0) ? current->left : current->right;
 }



 current = new_node = (avlnode *) malloc(sizeof(avlnode));
 if (current == 0)
  return 0;

 current->left = current->right = (&(avlt)->nil);
 current->parent = parent;
 current->bf = 0;
 current->data = data;

 if (parent == (&(avlt)->root) || avlt->compare(data, parent->data) < 0)
  parent->left = current;
 else
  parent->right = current;


 if (avlt->min == 0 || avlt->compare(current->data, avlt->min->data) < 0)
  avlt->min = current;
# 223 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
 while (current != ((avlt)->root.left)) {
  if (current == parent->left) {
   if (parent->bf == 1) {




    parent->bf = 0;
    break;
   } else if (parent->bf == 0) {



    parent->bf = -1;
   } else if (parent->bf == -1) {




    fix_insert_leftimbalance(avlt, parent);
    break;
   }
  } else {
   if (parent->bf == -1) {




    parent->bf = 0;
    break;
   } else if (parent->bf == 0) {



    parent->bf = 1;
   } else if (parent->bf == 1) {




    fix_insert_rightimbalance(avlt, parent);
    break;
   }
  }


  current = parent;
  parent = current->parent;
 }

 return new_node;
}





void *avl_delete(avltree *avlt, avlnode *node, int keep)
{
 avlnode *current, *parent;
 avlnode *target;
 void *data;

 data = node->data;



 if (node->left == (&(avlt)->nil) || node->right == (&(avlt)->nil)) {
  target = node;


  if (avlt->min == target)
   avlt->min = avl_successor(avlt, target);

 } else {
  target = avl_successor(avlt, node);

  node->data = target->data;





 }
# 318 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
 current = target;
 parent = current->parent;

 while (current != ((avlt)->root.left)) {
  if (current == parent->left) {
   if (parent->bf == -1) {



    parent->bf = 0;
   } else if (parent->bf == 0) {




    parent->bf = 1;
    break;
   } else if (parent->bf == 1) {





    parent = fix_delete_rightimbalance(avlt, parent);
    if (parent->bf == -1)
     break;

   }
  } else {
   if (parent->bf == 1) {



    parent->bf = 0;
   } else if (parent->bf == 0) {




    parent->bf = -1;
    break;
   } else if (parent->bf == -1) {





    parent = fix_delete_leftimbalance(avlt, parent);
    if (parent->bf == 1)
     break;

   }
  }


  current = parent;
  parent = current->parent;
 }



 avlnode *child;

 child = (target->left == (&(avlt)->nil)) ? target->right : target->left;

 if (child != (&(avlt)->nil))
  child->parent = target->parent;

 if (target == target->parent->left)
  target->parent->left = child;
 else
  target->parent->right = child;

 free(target);



 if (keep == 0) {
  avlt->destroy(data);
  data = 0;
 }

 return data;
}





avlnode *rotate_left(avltree *avlt, avlnode *x)
{
 avlnode *y;

 y = x->right;


 x->right = y->left;
 if (x->right != (&(avlt)->nil))
  x->right->parent = x;


 y->parent = x->parent;
 if (x == x->parent->left)
  x->parent->left = y;
 else
  x->parent->right = y;


 y->left = x;
 x->parent = y;

 return y;
}





avlnode *rotate_right(avltree *avlt, avlnode *x)
{
 avlnode *y;

 y = x->left;


 x->left = y->right;
 if (x->left != (&(avlt)->nil))
  x->left->parent = x;


 y->parent = x->parent;
 if (x == x->parent->left)
  x->parent->left = y;
 else
  x->parent->right = y;


 y->right = x;
 x->parent = y;

 return y;
}





avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p)
{


 if (p->left->bf == p->bf) {
  p = rotate_right(avlt, p);
  p->bf = p->right->bf = 0;
 } else {
  int oldbf;
  oldbf = p->left->right->bf;
  rotate_left(avlt, p->left);
  p = rotate_right(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}





avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p)
{
 if (p->right->bf == p->bf) {
  p = rotate_left(avlt, p);
  p->bf = p->left->bf = 0;
 } else {
  int oldbf;
  oldbf = p->right->left->bf;
  rotate_right(avlt, p->right);
  p = rotate_left(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}





avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p)
{
 if (p->left->bf == -1) {
  p = rotate_right(avlt, p);
  p->bf = p->right->bf = 0;
 } else if (p->left->bf == 0) {
  p = rotate_right(avlt, p);
  p->bf = 1;
  p->right->bf = -1;
 } else if (p->left->bf == 1) {
  int oldbf;
  oldbf = p->left->right->bf;
  rotate_left(avlt, p->left);
  p = rotate_right(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}





avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p)
{
 if (p->right->bf == 1) {
  p = rotate_left(avlt, p);
  p->bf = p->left->bf = 0;
 } else if (p->right->bf == 0) {
  p = rotate_left(avlt, p);
  p->bf = -1;
  p->left->bf = 1;
 } else if (p->right->bf == -1) {
  int oldbf;
  oldbf = p->right->left->bf;
  rotate_right(avlt, p->right);
  p = rotate_left(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}




int check_order(avltree *avlt, avlnode *n, void *min, void *max)
{
 if (n == (&(avlt)->nil))
  return 1;


 if (avlt->compare(n->data, min) < 0 || avlt->compare(n->data, max) > 0)



  return 0;

 return check_order(avlt, n->left, min, n->data) && check_order(avlt, n->right, n->data, max);
}




int check_height(avltree *avlt, avlnode *n)
{
 int lh, rh, cmp;

 if (n == (&(avlt)->nil))
  return 0;

 lh = check_height(avlt, n->left);
 if (lh < 0)
  return lh;

 rh = check_height(avlt, n->right);
 if (rh < 0)
  return rh;

 cmp = rh - lh;
 if (cmp < -1 || cmp > 1 || cmp != n->bf)
  return -1;

 return 1 + ((lh > rh) ? lh : rh);
}




void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label)
{
 if (n != (&(avlt)->nil)) {
  print(avlt, n->right, print_func, depth + 1, "R");
  printf("%*s", 8 * depth, "");
  if (label)
   printf("%s: ", label);
  print_func(n->data);
  printf(" (%s%d)\n", (n->bf >= 0) ? "+" : "", n->bf);
  print(avlt, n->left, print_func, depth + 1, "L");
 }
}




void destroy(avltree *avlt, avlnode *n)
{
 if (n != (&(avlt)->nil)) {
  destroy(avlt, n->left);
  destroy(avlt, n->right);
  avlt->destroy(n->data);
  free(n);
 }
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.h"
enum avlbf {
 LEFTHEAVY = -1,
 BALANCED = 0,
 RIGHTHEAVY = 1
};

enum avltraversal {
 PREORDER,
 INORDER,
 POSTORDER
};

typedef struct avlnode {
 struct avlnode *left;
 struct avlnode *right;
 struct avlnode *parent;
 char bf;
 void *data;
} avlnode;

typedef struct {
 int (*compare)(const void *, const void *);
 void (*print)(void *);
 void (*destroy)(void *);

 avlnode root;
 avlnode nil;


 avlnode *min;

} avltree;
# 59 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.h"
avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *));
void avl_destroy(avltree *avlt);

avlnode *avl_find(avltree *avlt, void *data);
avlnode *avl_successor(avltree *avlt, avlnode *node);

int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order);
void avl_print(avltree *avlt, void (*print_func)(void *));

avlnode *avl_insert(avltree *avlt, void *data);
void *avl_delete(avltree *avlt, avlnode *node, int keep);

int avl_check_order(avltree *avlt, void *min, void *max);
int avl_check_height(avltree *avlt);
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c" 2

static avlnode *rotate_left(avltree *avlt, avlnode *x);
static avlnode *rotate_right(avltree *avlt, avlnode *x);

static avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p);

static int check_order(avltree *avlt, avlnode *n, void *min, void *max);
static int check_height(avltree *avlt, avlnode *n);

static void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label);
static void destroy(avltree *avlt, avlnode *n);





avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *))
{
 avltree *avlt;

 avlt = (avltree *) malloc(sizeof(avltree));
 if (avlt == 0)
  return 0;

 avlt->compare = compare_func;
 avlt->destroy = destroy_func;


 avlt->nil.left = avlt->nil.right = avlt->nil.parent = (&(avlt)->nil);
 avlt->nil.bf = 0;
 avlt->nil.data = 0;


 avlt->root.left = avlt->root.right = avlt->root.parent = (&(avlt)->nil);
 avlt->root.bf = 0;
 avlt->root.data = 0;


 avlt->min = 0;


 return avlt;
}




void avl_destroy(avltree *avlt)
{
 destroy(avlt, ((avlt)->root.left));
 free(avlt);
}





avlnode *avl_find(avltree *avlt, void *data)
{
 avlnode *p;

 p = ((avlt)->root.left);

 while (p != (&(avlt)->nil)) {
  int cmp;
  cmp = avlt->compare(data, p->data);
  if (cmp == 0)
   return p;
  p = (cmp < 0) ? p->left : p->right;
 }

 return 0;
}





avlnode *avl_successor(avltree *avlt, avlnode *node)
{
 avlnode *p;

 p = node->right;

 if (p != (&(avlt)->nil)) {

  for ( ; p->left != (&(avlt)->nil); p = p->left) ;
 } else {

  for (p = node->parent; node == p->right; node = p, p = p->parent) ;

  if (p == (&(avlt)->root))
   p = 0;
 }

 return p;
}





int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order)
{
 int err;

 if (node != (&(avlt)->nil)) {
  if (order == PREORDER && (err = func(node->data, cookie)) != 0)
   return err;
  if ((err = avl_apply(avlt, node->left, func, cookie, order)) != 0)
   return err;
  if (order == INORDER && (err = func(node->data, cookie)) != 0)
   return err;
  if ((err = avl_apply(avlt, node->right, func, cookie, order)) != 0)
   return err;
  if (order == POSTORDER && (err = func(node->data, cookie)) != 0)
   return err;
 }

 return 0;
}




void avl_print(avltree *avlt, void (*print_func)(void *))
{
 printf("\n--\n");
 print(avlt, ((avlt)->root.left), print_func, 0, "T");
 printf("\nheight = %d\n", check_height(avlt, ((avlt)->root.left)));
}




int avl_check_order(avltree *avlt, void *min, void *max)
{
 return check_order(avlt, ((avlt)->root.left), min, max);
}




int avl_check_height(avltree *avlt)
{
 int height;
 height = check_height(avlt, ((avlt)->root.left));

 return (height < 0) ? 0 : 1;
}





avlnode *avl_insert(avltree *avlt, void *data)
{
 avlnode *current, *parent;
 avlnode *new_node;



 current = ((avlt)->root.left);
 parent = (&(avlt)->root);

 while (current != (&(avlt)->nil)) {
  int cmp;
  cmp = avlt->compare(data, current->data);
# 189 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
  parent = current;
  current = (cmp < 0) ? current->left : current->right;
 }



 current = new_node = (avlnode *) malloc(sizeof(avlnode));
 if (current == 0)
  return 0;

 current->left = current->right = (&(avlt)->nil);
 current->parent = parent;
 current->bf = 0;
 current->data = data;

 if (parent == (&(avlt)->root) || avlt->compare(data, parent->data) < 0)
  parent->left = current;
 else
  parent->right = current;


 if (avlt->min == 0 || avlt->compare(current->data, avlt->min->data) < 0)
  avlt->min = current;
# 223 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
 while (current != ((avlt)->root.left)) {
  if (current == parent->left) {
   if (parent->bf == 1) {




    parent->bf = 0;
    break;
   } else if (parent->bf == 0) {



    parent->bf = -1;
   } else if (parent->bf == -1) {




    fix_insert_leftimbalance(avlt, parent);
    break;
   }
  } else {
   if (parent->bf == -1) {




    parent->bf = 0;
    break;
   } else if (parent->bf == 0) {



    parent->bf = 1;
   } else if (parent->bf == 1) {




    fix_insert_rightimbalance(avlt, parent);
    break;
   }
  }


  current = parent;
  parent = current->parent;
 }

 return new_node;
}





void *avl_delete(avltree *avlt, avlnode *node, int keep)
{
 avlnode *current, *parent;
 avlnode *target;
 void *data;

 data = node->data;



 if (node->left == (&(avlt)->nil) || node->right == (&(avlt)->nil)) {
  target = node;


  if (avlt->min == target)
   avlt->min = avl_successor(avlt, target);

 } else {
  target = avl_successor(avlt, node);

  node->data = target->data;





 }
# 318 "/home/enumclass/Documents/C2RustTranslation/bkp/avl-tree/avl_bf.c"
 current = target;
 parent = current->parent;

 while (current != ((avlt)->root.left)) {
  if (current == parent->left) {
   if (parent->bf == -1) {



    parent->bf = 0;
   } else if (parent->bf == 0) {




    parent->bf = 1;
    break;
   } else if (parent->bf == 1) {





    parent = fix_delete_rightimbalance(avlt, parent);
    if (parent->bf == -1)
     break;

   }
  } else {
   if (parent->bf == 1) {



    parent->bf = 0;
   } else if (parent->bf == 0) {




    parent->bf = -1;
    break;
   } else if (parent->bf == -1) {





    parent = fix_delete_leftimbalance(avlt, parent);
    if (parent->bf == 1)
     break;

   }
  }


  current = parent;
  parent = current->parent;
 }



 avlnode *child;

 child = (target->left == (&(avlt)->nil)) ? target->right : target->left;

 if (child != (&(avlt)->nil))
  child->parent = target->parent;

 if (target == target->parent->left)
  target->parent->left = child;
 else
  target->parent->right = child;

 free(target);



 if (keep == 0) {
  avlt->destroy(data);
  data = 0;
 }

 return data;
}





avlnode *rotate_left(avltree *avlt, avlnode *x)
{
 avlnode *y;

 y = x->right;


 x->right = y->left;
 if (x->right != (&(avlt)->nil))
  x->right->parent = x;


 y->parent = x->parent;
 if (x == x->parent->left)
  x->parent->left = y;
 else
  x->parent->right = y;


 y->left = x;
 x->parent = y;

 return y;
}





avlnode *rotate_right(avltree *avlt, avlnode *x)
{
 avlnode *y;

 y = x->left;


 x->left = y->right;
 if (x->left != (&(avlt)->nil))
  x->left->parent = x;


 y->parent = x->parent;
 if (x == x->parent->left)
  x->parent->left = y;
 else
  x->parent->right = y;


 y->right = x;
 x->parent = y;

 return y;
}





avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p)
{


 if (p->left->bf == p->bf) {
  p = rotate_right(avlt, p);
  p->bf = p->right->bf = 0;
 } else {
  int oldbf;
  oldbf = p->left->right->bf;
  rotate_left(avlt, p->left);
  p = rotate_right(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}





avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p)
{
 if (p->right->bf == p->bf) {
  p = rotate_left(avlt, p);
  p->bf = p->left->bf = 0;
 } else {
  int oldbf;
  oldbf = p->right->left->bf;
  rotate_right(avlt, p->right);
  p = rotate_left(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}





avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p)
{
 if (p->left->bf == -1) {
  p = rotate_right(avlt, p);
  p->bf = p->right->bf = 0;
 } else if (p->left->bf == 0) {
  p = rotate_right(avlt, p);
  p->bf = 1;
  p->right->bf = -1;
 } else if (p->left->bf == 1) {
  int oldbf;
  oldbf = p->left->right->bf;
  rotate_left(avlt, p->left);
  p = rotate_right(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}





avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p)
{
 if (p->right->bf == 1) {
  p = rotate_left(avlt, p);
  p->bf = p->left->bf = 0;
 } else if (p->right->bf == 0) {
  p = rotate_left(avlt, p);
  p->bf = -1;
  p->left->bf = 1;
 } else if (p->right->bf == -1) {
  int oldbf;
  oldbf = p->right->left->bf;
  rotate_right(avlt, p->right);
  p = rotate_left(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}




int check_order(avltree *avlt, avlnode *n, void *min, void *max)
{
 if (n == (&(avlt)->nil))
  return 1;


 if (avlt->compare(n->data, min) < 0 || avlt->compare(n->data, max) > 0)



  return 0;

 return check_order(avlt, n->left, min, n->data) && check_order(avlt, n->right, n->data, max);
}




int check_height(avltree *avlt, avlnode *n)
{
 int lh, rh, cmp;

 if (n == (&(avlt)->nil))
  return 0;

 lh = check_height(avlt, n->left);
 if (lh < 0)
  return lh;

 rh = check_height(avlt, n->right);
 if (rh < 0)
  return rh;

 cmp = rh - lh;
 if (cmp < -1 || cmp > 1 || cmp != n->bf)
  return -1;

 return 1 + ((lh > rh) ? lh : rh);
}




void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label)
{
 if (n != (&(avlt)->nil)) {
  print(avlt, n->right, print_func, depth + 1, "R");
  printf("%*s", 8 * depth, "");
  if (label)
   printf("%s: ", label);
  print_func(n->data);
  printf(" (%s%d)\n", (n->bf >= 0) ? "+" : "", n->bf);
  print(avlt, n->left, print_func, depth + 1, "L");
 }
}




void destroy(avltree *avlt, avlnode *n)
{
 if (n != (&(avlt)->nil)) {
  destroy(avlt, n->left);
  destroy(avlt, n->right);
  avlt->destroy(n->data);
  free(n);
 }
}

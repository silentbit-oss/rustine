#include <genann.h>
#include <math.h>
#include <minctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct genann;
typedef double (*genann_actfun)(const struct genann *ann, double a);
typedef struct genann
{
  int inputs;
  int hidden_layers;
  int hidden;
  int outputs;
  genann_actfun activation_hidden;
  genann_actfun activation_output;
  int total_weights;
  int total_neurons;
  double *weight;
  double *output;
  double *delta;
} genann;
genann *genann_init(int inputs, int hidden_layers, int hidden, int outputs);
genann *genann_read(FILE *in);
void genann_randomize(genann *ann);
genann *genann_copy(const genann *ann);
void genann_free(genann *ann);
const double *genann_run(const genann *ann, const double *inputs);
void genann_train(const genann *ann, const double *inputs, const double *desired_outputs, double learning_rate);
void genann_write(const genann *ann, FILE *out);
void genann_init_sigmoid_lookup(const genann *ann);
double genann_act_sigmoid(const genann *ann, double a);
double genann_act_sigmoid_cached(const genann *ann, double a);
double genann_act_threshold(const genann *ann, double a);
double genann_act_linear(const genann *ann, double a);
static int ltests = 0;
static int lfails = 0;
void basic()
{
  genann *ann = genann_init(1, 0, 0, 1);
  do
  {
    ltests += 1;
    if (ann->total_weights != 2)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 37, ann->total_weights, 2);
    }
  }
  while (0);
  double a;
  a = 0;
  ann->weight[0] = 0;
  ann->weight[1] = 0;
  do
  {
    ltests += 1;
    if (fabs(((double) 0.5) - ((double) (*genann_run(ann, &a)))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 44, (double) 0.5, (double) (*genann_run(ann, &a)));
    }
  }
  while (0);
  a = 1;
  do
  {
    ltests += 1;
    if (fabs(((double) 0.5) - ((double) (*genann_run(ann, &a)))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 47, (double) 0.5, (double) (*genann_run(ann, &a)));
    }
  }
  while (0);
  a = 11;
  do
  {
    ltests += 1;
    if (fabs(((double) 0.5) - ((double) (*genann_run(ann, &a)))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 50, (double) 0.5, (double) (*genann_run(ann, &a)));
    }
  }
  while (0);
  a = 1;
  ann->weight[0] = 1;
  ann->weight[1] = 1;
  do
  {
    ltests += 1;
    if (fabs(((double) 0.5) - ((double) (*genann_run(ann, &a)))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 55, (double) 0.5, (double) (*genann_run(ann, &a)));
    }
  }
  while (0);
  a = 10;
  ann->weight[0] = 1;
  ann->weight[1] = 1;
  do
  {
    ltests += 1;
    if (fabs(((double) 1.0) - ((double) (*genann_run(ann, &a)))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 60, (double) 1.0, (double) (*genann_run(ann, &a)));
    }
  }
  while (0);
  a = -10;
  do
  {
    ltests += 1;
    if (fabs(((double) 0.0) - ((double) (*genann_run(ann, &a)))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 63, (double) 0.0, (double) (*genann_run(ann, &a)));
    }
  }
  while (0);
  genann_free(ann);
}

void xor()
{
  genann *ann = genann_init(2, 1, 2, 1);
  ann->activation_hidden = genann_act_threshold;
  ann->activation_output = genann_act_threshold;
  do
  {
    ltests += 1;
    if (ann->total_weights != 9)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 74, ann->total_weights, 9);
    }
  }
  while (0);
  ann->weight[0] = .5;
  ann->weight[1] = 1;
  ann->weight[2] = 1;
  ann->weight[3] = 1;
  ann->weight[4] = 1;
  ann->weight[5] = 1;
  ann->weight[6] = .5;
  ann->weight[7] = 1;
  ann->weight[8] = -1;
  double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  double output[4] = {0, 1, 1, 0};
  do
  {
    ltests += 1;
    if (fabs(((double) output[0]) - ((double) (*genann_run(ann, input[0])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 95, (double) output[0], (double) (*genann_run(ann, input[0])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[1]) - ((double) (*genann_run(ann, input[1])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 96, (double) output[1], (double) (*genann_run(ann, input[1])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[2]) - ((double) (*genann_run(ann, input[2])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 97, (double) output[2], (double) (*genann_run(ann, input[2])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[3]) - ((double) (*genann_run(ann, input[3])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 98, (double) output[3], (double) (*genann_run(ann, input[3])));
    }
  }
  while (0);
  genann_free(ann);
}

void backprop()
{
  genann *ann = genann_init(1, 0, 0, 1);
  double input;
  double output;
  input = .5;
  output = 1;
  double first_try = *genann_run(ann, &input);
  genann_train(ann, &input, &output, .5);
  double second_try = *genann_run(ann, &input);
  do
  {
    ltests += 1;
    if (!(fabs(first_try - output) > fabs(second_try - output)))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 114);
    }
  }
  while (0);
  genann_free(ann);
}

void train_and()
{
  double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  double output[4] = {0, 0, 0, 1};
  genann *ann = genann_init(2, 0, 0, 1);
  int i;
  int j;
  for (i = 0; i < 50; i += 1)
  {
    for (j = 0; j < 4; j += 1)
    {
      genann_train(ann, input[j], output + j, .8);
    }

  }

  ann->activation_output = genann_act_threshold;
  do
  {
    ltests += 1;
    if (fabs(((double) output[0]) - ((double) (*genann_run(ann, input[0])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 135, (double) output[0], (double) (*genann_run(ann, input[0])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[1]) - ((double) (*genann_run(ann, input[1])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 136, (double) output[1], (double) (*genann_run(ann, input[1])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[2]) - ((double) (*genann_run(ann, input[2])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 137, (double) output[2], (double) (*genann_run(ann, input[2])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[3]) - ((double) (*genann_run(ann, input[3])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 138, (double) output[3], (double) (*genann_run(ann, input[3])));
    }
  }
  while (0);
  genann_free(ann);
}

void train_or()
{
  double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  double output[4] = {0, 1, 1, 1};
  genann *ann = genann_init(2, 0, 0, 1);
  genann_randomize(ann);
  int i;
  int j;
  for (i = 0; i < 50; i += 1)
  {
    for (j = 0; j < 4; j += 1)
    {
      genann_train(ann, input[j], output + j, .8);
    }

  }

  ann->activation_output = genann_act_threshold;
  do
  {
    ltests += 1;
    if (fabs(((double) output[0]) - ((double) (*genann_run(ann, input[0])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 160, (double) output[0], (double) (*genann_run(ann, input[0])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[1]) - ((double) (*genann_run(ann, input[1])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 161, (double) output[1], (double) (*genann_run(ann, input[1])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[2]) - ((double) (*genann_run(ann, input[2])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 162, (double) output[2], (double) (*genann_run(ann, input[2])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[3]) - ((double) (*genann_run(ann, input[3])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 163, (double) output[3], (double) (*genann_run(ann, input[3])));
    }
  }
  while (0);
  genann_free(ann);
}

void train_xor()
{
  double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  double output[4] = {0, 1, 1, 0};
  genann *ann = genann_init(2, 1, 2, 1);
  int i;
  int j;
  for (i = 0; i < 500; i += 1)
  {
    for (j = 0; j < 4; j += 1)
    {
      genann_train(ann, input[j], output + j, 3);
    }

  }

  ann->activation_output = genann_act_threshold;
  do
  {
    ltests += 1;
    if (fabs(((double) output[0]) - ((double) (*genann_run(ann, input[0])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 186, (double) output[0], (double) (*genann_run(ann, input[0])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[1]) - ((double) (*genann_run(ann, input[1])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 187, (double) output[1], (double) (*genann_run(ann, input[1])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[2]) - ((double) (*genann_run(ann, input[2])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 188, (double) output[2], (double) (*genann_run(ann, input[2])));
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) output[3]) - ((double) (*genann_run(ann, input[3])))) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 189, (double) output[3], (double) (*genann_run(ann, input[3])));
    }
  }
  while (0);
  genann_free(ann);
}

void persist()
{
  genann *first = genann_init(1000, 5, 50, 10);
  FILE *out = fopen("persist.txt", "w");
  genann_write(first, out);
  fclose(out);
  FILE *in = fopen("persist.txt", "r");
  genann *second = genann_read(in);
  fclose(in);
  do
  {
    ltests += 1;
    if (first->inputs != second->inputs)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 208, first->inputs, second->inputs);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->hidden_layers != second->hidden_layers)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 209, first->hidden_layers, second->hidden_layers);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->hidden != second->hidden)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 210, first->hidden, second->hidden);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->outputs != second->outputs)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 211, first->outputs, second->outputs);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->total_weights != second->total_weights)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 212, first->total_weights, second->total_weights);
    }
  }
  while (0);
  int i;
  for (i = 0; i < first->total_weights; i += 1)
  {
    do
    {
      ltests += 1;
      if (!(first->weight[i] == second->weight[i]))
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 216);
      }
    }
    while (0);
  }

  genann_free(first);
  genann_free(second);
}

void copy()
{
  genann *first = genann_init(1000, 5, 50, 10);
  genann *second = genann_copy(first);
  do
  {
    ltests += 1;
    if (first->inputs != second->inputs)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 229, first->inputs, second->inputs);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->hidden_layers != second->hidden_layers)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 230, first->hidden_layers, second->hidden_layers);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->hidden != second->hidden)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 231, first->hidden, second->hidden);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->outputs != second->outputs)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 232, first->outputs, second->outputs);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (first->total_weights != second->total_weights)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 233, first->total_weights, second->total_weights);
    }
  }
  while (0);
  int i;
  for (i = 0; i < first->total_weights; i += 1)
  {
    do
    {
      ltests += 1;
      if (fabs(((double) first->weight[i]) - ((double) second->weight[i])) > 0.001)
      {
        lfails += 1;
        printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 237, (double) first->weight[i], (double) second->weight[i]);
      }
    }
    while (0);
  }

  genann_free(first);
  genann_free(second);
}

void sigmoid()
{
  double i = -20;
  const double max = 20;
  const double d = .0001;
  while (i < max)
  {
    do
    {
      ltests += 1;
      if (fabs(((double) genann_act_sigmoid(0, i)) - ((double) genann_act_sigmoid_cached(0, i))) > 0.001)
      {
        lfails += 1;
        printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/genann/test.c", 251, (double) genann_act_sigmoid(0, i), (double) genann_act_sigmoid_cached(0, i));
      }
    }
    while (0);
    i += d;
  }

}

int main(int argc, char *argv[])
{
  printf("GENANN TEST SUITE\n");
  srand(100);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "basic");
    basic();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "xor");
    xor();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "backprop");
    backprop();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "train and");
    train_and();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "train or");
    train_or();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "train xor");
    train_xor();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "persist");
    persist();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "copy");
    copy();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-14s", "sigmoid");
    sigmoid();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    if (lfails == 0)
    {
      printf("ALL TESTS PASSED (%d/%d)\n", ltests, ltests);
    }
    else
    {
      printf("SOME TESTS FAILED (%d/%d)\n", ltests - lfails, ltests);
    }
  }
  while (0);
  return lfails != 0;
}


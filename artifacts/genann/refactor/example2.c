#include <example2.c>
#include <genann.h>
#include <math.h>
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
int main(int argc, char *argv[])
{
  printf("GENANN example 2.\n");
  printf("Train a small ANN to the XOR function using random search.\n");
  srand(time(0));
  const double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  const double output[4] = {0, 1, 1, 0};
  int i;
  genann *ann = genann_init(2, 1, 2, 1);
  unsigned int ann_idx = 0;
  double err;
  double last_err = 1000;
  int count = 0;
  do
  {
    count += 1;
    if ((count % 1000) == 0)
    {
      genann_randomize(ann);
      last_err = 1000;
    }
    genann *save = genann_copy(ann);
    for (i = 0; i < ann->total_weights; i += 1)
    {
      ann->weight[i] += (((double) rand()) / 32767) - 0.5;
    }

    err = 0;
    err += pow((*genann_run(ann, input[0])) - output[0], 2.0);
    err += pow((*genann_run(ann, input[1])) - output[1], 2.0);
    err += pow((*genann_run(ann, input[2])) - output[2], 2.0);
    err += pow((*genann_run(ann, input[3])) - output[3], 2.0);
    if (err < last_err)
    {
      genann_free(save);
      last_err = err;
    }
    else
    {
      genann_free(ann);
      ann_idx = save;
    }
  }
  while (err > 0.01);
  printf("Finished in %d loops.\n", count);
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[0][0], input[0][1], *genann_run(ann, input[0]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[1][0], input[1][1], *genann_run(ann, input[1]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[2][0], input[2][1], *genann_run(ann, input[2]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[3][0], input[3][1], *genann_run(ann, input[3]));
  genann_free(ann);
  return 0;
}


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
int main(int argc, char *argv[])
{
  printf("GENANN example 2.\n");
  printf("Train a small ANN to the XOR function using random search.\n");
  srand(time(0));
  const double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  const double output[4] = {0, 1, 1, 0};
  int i;
  genann *ann = genann_init(2, 1, 2, 1);
  unsigned int ann_idx = 0;
  double err;
  double last_err = 1000;
  int count = 0;
  do
  {
    count += 1;
    if ((count % 1000) == 0)
    {
      genann_randomize(ann);
      last_err = 1000;
    }
    genann *save = genann_copy(ann);
    for (i = 0; i < ann->total_weights; i += 1)
    {
      ann->weight[i] += (((double) rand()) / 32767) - 0.5;
    }

    err = 0;
    err += pow((*genann_run(ann, input[0])) - output[0], 2.0);
    err += pow((*genann_run(ann, input[1])) - output[1], 2.0);
    err += pow((*genann_run(ann, input[2])) - output[2], 2.0);
    err += pow((*genann_run(ann, input[3])) - output[3], 2.0);
    if (err < last_err)
    {
      genann_free(save);
      last_err = err;
    }
    else
    {
      genann_free(ann);
      ann_idx = save;
    }
  }
  while (err > 0.01);
  printf("Finished in %d loops.\n", count);
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[0][0], input[0][1], *genann_run(ann, input[0]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[1][0], input[1][1], *genann_run(ann, input[1]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[2][0], input[2][1], *genann_run(ann, input[2]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[3][0], input[3][1], *genann_run(ann, input[3]));
  genann_free(ann);
  return 0;
}


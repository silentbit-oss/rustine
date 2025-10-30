#include <example4.c>
#include <genann.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
const char *iris_data = "example/iris.data";
double *input;
double *class;
int samples;
const char *class_names[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};
void load_data()
{
  FILE *in = fopen("example/iris.data", "r");
  if (!in)
  {
    printf("Could not open file: %s\n", iris_data);
    exit(1);
  }
  char line[1024];
  while ((!feof(in)) && fgets(line, 1024, in))
  {
    samples += 1;
  }

  fseek(in, 0, 0);
  printf("Loading %d data points from %s\n", samples, iris_data);
  input = malloc(((sizeof(double)) * samples) * 4);
  class = malloc(((sizeof(double)) * samples) * 3);
  int i;
  int j;
  for (i = 0; i < samples; i += 1)
  {
    helper_load_data_1(&j, in, line, i);
  }

  fclose(in);
}

int main(int argc, char *argv[])
{
  printf("GENANN example 4.\n");
  printf("Train an ANN on the IRIS dataset using backpropagation.\n");
  srand(time(0));
  load_data();
  genann *ann = genann_init(4, 1, 4, 3);
  int i;
  int j;
  int loops = 5000;
  printf("Training for %d loops over data.\n", loops);
  for (i = 0; i < loops; i += 1)
  {
    for (j = 0; j < samples; j += 1)
    {
      genann_train(ann, input + (j * 4), class + (j * 3), .01);
    }

  }

  int correct = 0;
  for (j = 0; j < samples; j += 1)
  {
    const double *guess = genann_run(ann, input + (j * 4));
    if (class[(j * 3) + 0] == 1.0)
    {
      if ((guess[0] > guess[1]) && (guess[0] > guess[2]))
      {
        correct += 1;
      }
    }
    else
      if (class[(j * 3) + 1] == 1.0)
    {
      if ((guess[1] > guess[0]) && (guess[1] > guess[2]))
      {
        correct += 1;
      }
    }
    else
      if (class[(j * 3) + 2] == 1.0)
    {
      if ((guess[2] > guess[0]) && (guess[2] > guess[1]))
      {
        correct += 1;
      }
    }
    else
    {
      printf("Logic error.\n");
      exit(1);
    }
  }

  printf("%d/%d correct (%0.1f%%).\n", correct, samples, (((double) correct) / samples) * 100.0);
  genann_free(ann);
  free(input);
  free(class);
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
const char *iris_data = "example/iris.data";
double *input;
double *class;
int samples;
const char *class_names[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};
void load_data()
{
  FILE *in = fopen("example/iris.data", "r");
  if (!in)
  {
    printf("Could not open file: %s\n", iris_data);
    exit(1);
  }
  char line[1024];
  while ((!feof(in)) && fgets(line, 1024, in))
  {
    samples += 1;
  }

  fseek(in, 0, 0);
  printf("Loading %d data points from %s\n", samples, iris_data);
  input = malloc(((sizeof(double)) * samples) * 4);
  class = malloc(((sizeof(double)) * samples) * 3);
  int i;
  int j;
  for (i = 0; i < samples; i += 1)
  {
    double *p = input + (i * 4);
    double *c = class + (i * 3);
    c[0] = (c[1] = (c[2] = 0.0));
    if (fgets(line, 1024, in) == 0)
    {
      perror("fgets");
      exit(1);
    }
    char *split = strtok(line, ",");
    unsigned int split_idx = 0;
    for (j = 0; j < 4; j += 1)
    {
      p[j] = atof(split);
      split_idx = strtok(0, ",");
    }

    split[(strlen(split) - 1) + split_idx] = 0;
    if (strcmp(split, class_names[0]) == 0)
    {
      c[0] = 1.0;
    }
    else
      if (strcmp(split, class_names[1]) == 0)
    {
      c[1] = 1.0;
    }
    else
      if (strcmp(split, class_names[2]) == 0)
    {
      c[2] = 1.0;
    }
    else
    {
      printf("Unknown class %s.\n", split);
      exit(1);
    }
  }

  fclose(in);
}

int main(int argc, char *argv[])
{
  printf("GENANN example 4.\n");
  printf("Train an ANN on the IRIS dataset using backpropagation.\n");
  srand(time(0));
  load_data();
  genann *ann = genann_init(4, 1, 4, 3);
  int i;
  int j;
  int loops = 5000;
  printf("Training for %d loops over data.\n", loops);
  for (i = 0; i < loops; i += 1)
  {
    for (j = 0; j < samples; j += 1)
    {
      genann_train(ann, input + (j * 4), class + (j * 3), .01);
    }

  }

  int correct = 0;
  for (j = 0; j < samples; j += 1)
  {
    const double *guess = genann_run(ann, input + (j * 4));
    if (class[(j * 3) + 0] == 1.0)
    {
      if ((guess[0] > guess[1]) && (guess[0] > guess[2]))
      {
        correct += 1;
      }
    }
    else
      if (class[(j * 3) + 1] == 1.0)
    {
      if ((guess[1] > guess[0]) && (guess[1] > guess[2]))
      {
        correct += 1;
      }
    }
    else
      if (class[(j * 3) + 2] == 1.0)
    {
      if ((guess[2] > guess[0]) && (guess[2] > guess[1]))
      {
        correct += 1;
      }
    }
    else
    {
      printf("Logic error.\n");
      exit(1);
    }
  }

  printf("%d/%d correct (%0.1f%%).\n", correct, samples, (((double) correct) / samples) * 100.0);
  genann_free(ann);
  free(input);
  free(class);
  return 0;
}

void helper_load_data_1(int * const j_ref, FILE * const in, char line[1024], int i)
{
  int j = *j_ref;
  double *p = input + (i * 4);
  double *c = class + (i * 3);
  c[0] = (c[1] = (c[2] = 0.0));
  if (fgets(line, 1024, in) == 0)
  {
    perror("fgets");
    exit(1);
  }
  char *split = strtok(line, ",");
  unsigned int split_idx = 0;
  for (j = 0; j < 4; j += 1)
  {
    p[j] = atof(split);
    split_idx = strtok(0, ",");
  }

  split[(strlen(split) - 1) + split_idx] = 0;
  if (strcmp(split, class_names[0]) == 0)
  {
    c[0] = 1.0;
  }
  else
    if (strcmp(split, class_names[1]) == 0)
  {
    c[1] = 1.0;
  }
  else
    if (strcmp(split, class_names[2]) == 0)
  {
    c[2] = 1.0;
  }
  else
  {
    printf("Unknown class %s.\n", split);
    exit(1);
  }
  *j_ref = j;
}


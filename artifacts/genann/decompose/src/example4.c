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


/*** DEPENDENCIES:
const char *class_names[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"}
----------------------------
int samples
----------------------------
double *input
----------------------------
const char *iris_data = "example/iris.data"
----------------------------
double *class
----------------------------
***/


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


/*** DEPENDENCIES:
genann *genann_init(int inputs, int hidden_layers, int hidden, int outputs)
{
  if (hidden_layers < 0)
  {
    return 0;
  }
  if (inputs < 1)
  {
    return 0;
  }
  if (outputs < 1)
  {
    return 0;
  }
  if ((hidden_layers > 0) && (hidden < 1))
  {
    return 0;
  }
  const int hidden_weights = (hidden_layers) ? (((inputs + 1) * hidden) + (((hidden_layers - 1) * (hidden + 1)) * hidden)) : (0);
  const int output_weights = ((hidden_layers) ? (hidden + 1) : (inputs + 1)) * outputs;
  const int total_weights = hidden_weights + output_weights;
  const int total_neurons = (inputs + (hidden * hidden_layers)) + outputs;
  const int size = (sizeof(genann)) + ((sizeof(double)) * ((total_weights + total_neurons) + (total_neurons - inputs)));
  genann *ret = malloc(size);
  if (!ret)
  {
    return 0;
  }
  ret->inputs = inputs;
  ret->hidden_layers = hidden_layers;
  ret->hidden = hidden;
  ret->outputs = outputs;
  ret->total_weights = total_weights;
  ret->total_neurons = total_neurons;
  ret->weight = (double *) (((char *) ret) + (sizeof(genann)));
  ret->output = ret->weight + ret->total_weights;
  ret->delta = ret->output + ret->total_neurons;
  genann_randomize(ret);
  ret->activation_hidden = genann_act_sigmoid_cached;
  ret->activation_output = genann_act_sigmoid_cached;
  genann_init_sigmoid_lookup(ret);
  return ret;
}


----------------------------
const double *genann_run(const genann *ann, const double *inputs)
{
  const double *w = ann->weight;
  unsigned int w_idx = 0;
  double *o = ann->output + ann->inputs;
  const double *i = ann->output;
  unsigned int i_idx = 0;
  memcpy(ann->output, inputs, (sizeof(double)) * ann->inputs);
  int h;
  int j;
  int k;
  if (!ann->hidden_layers)
  {
    double *ret = o;
    for (j = 0; j < ann->outputs; j += 1)
    {
      double sum = w[w_idx] * (-1.0);
      w_idx += 1;
      for (k = 0; k < ann->inputs; k += 1)
      {
        sum += w[w_idx] * i[k + i_idx];
        w_idx += 1;
      }

      *(o++) = genann_act_output_indirect(ann, sum);
    }

    return ret;
  }
  for (j = 0; j < ann->hidden; j += 1)
  {
    double sum = w[w_idx] * (-1.0);
    w_idx += 1;
    for (k = 0; k < ann->inputs; k += 1)
    {
      sum += w[w_idx] * i[k + i_idx];
      w_idx += 1;
    }

    *(o++) = genann_act_hidden_indirect(ann, sum);
  }

  i_idx += ann->inputs;
  for (h = 1; h < ann->hidden_layers; h += 1)
  {
    for (j = 0; j < ann->hidden; j += 1)
    {
      double sum = w[w_idx] * (-1.0);
      w_idx += 1;
      for (k = 0; k < ann->hidden; k += 1)
      {
        sum += w[w_idx] * i[k + i_idx];
        w_idx += 1;
      }

      *(o++) = genann_act_hidden_indirect(ann, sum);
    }

    i_idx += ann->hidden;
  }

  const double *ret = o;
  for (j = 0; j < ann->outputs; j += 1)
  {
    double sum = w[w_idx] * (-1.0);
    w_idx += 1;
    for (k = 0; k < ann->hidden; k += 1)
    {
      sum += w[w_idx] * i[k + i_idx];
      w_idx += 1;
    }

    *(o++) = genann_act_output_indirect(ann, sum);
  }

  assert(((&w[w_idx]) - ann->weight) == ann->total_weights);
  assert((o - ann->output) == ann->total_neurons);
  return ret;
}


----------------------------
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


----------------------------
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
} genann
----------------------------
int samples
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
double *input
----------------------------
void genann_train(const genann *ann, const double *inputs, const double *desired_outputs, double learning_rate)
{
  genann_run(ann, inputs);
  int h;
  int j;
  int k;
  {
    helper_genann_train_2(&j, ann, desired_outputs);
  }
  for (h = ann->hidden_layers - 1; h >= 0; h -= 1)
  {
    helper_genann_train_1(&j, &k, ann, h);
  }

  {
    const double *d = ann->delta + (ann->hidden * ann->hidden_layers);
    unsigned int d_idx = 0;
    double *w = ann->weight + ((ann->hidden_layers) ? (((ann->inputs + 1) * ann->hidden) + (((ann->hidden + 1) * ann->hidden) * (ann->hidden_layers - 1))) : (0));
    unsigned int w_idx = 0;
    const double * const i = ann->output + ((ann->hidden_layers) ? (ann->inputs + (ann->hidden * (ann->hidden_layers - 1))) : (0));
    for (j = 0; j < ann->outputs; j += 1)
    {
      w[w_idx] += (d[d_idx] * learning_rate) * (-1.0);
      w_idx += 1;
      for (k = 1; k < (((ann->hidden_layers) ? (ann->hidden) : (ann->inputs)) + 1); k += 1)
      {
        w[w_idx] += (d[d_idx] * learning_rate) * i[k - 1];
        w_idx += 1;
      }

      ++(&d[d_idx]);
    }

    assert(((&w[w_idx]) - ann->weight) == ann->total_weights);
  }
  for (h = ann->hidden_layers - 1; h >= 0; h -= 1)
  {
    const double *d = ann->delta + (h * ann->hidden);
    unsigned int d_idx = 0;
    const double *i = ann->output + ((h) ? (ann->inputs + (ann->hidden * (h - 1))) : (0));
    double *w = ann->weight + ((h) ? (((ann->inputs + 1) * ann->hidden) + (((ann->hidden + 1) * ann->hidden) * (h - 1))) : (0));
    unsigned int w_idx = 0;
    for (j = 0; j < ann->hidden; j += 1)
    {
      w[w_idx] += (d[d_idx] * learning_rate) * (-1.0);
      w_idx += 1;
      for (k = 1; k < (((h == 0) ? (ann->inputs) : (ann->hidden)) + 1); k += 1)
      {
        w[w_idx] += (d[d_idx] * learning_rate) * i[k - 1];
        w_idx += 1;
      }

      ++(&d[d_idx]);
    }

  }

}


----------------------------
double *class
----------------------------
pub time: Time
----------------------------
***/



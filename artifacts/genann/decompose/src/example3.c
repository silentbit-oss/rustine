int main(int argc, char *argv[])
{
  printf("GENANN example 3.\n");
  printf("Load a saved ANN to solve the XOR function.\n");
  FILE *saved = fopen(save_name, "r");
  if (!saved)
  {
    printf("Couldn't open file: %s\n", save_name);
    exit(1);
  }
  genann *ann = genann_read(saved);
  fclose(saved);
  if (!ann)
  {
    printf("Error loading ANN from file: %s.", save_name);
    exit(1);
  }
  const double input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[0][0], input[0][1], *genann_run(ann, input[0]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[1][0], input[1][1], *genann_run(ann, input[1]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[2][0], input[2][1], *genann_run(ann, input[2]));
  printf("Output for [%1.f, %1.f] is %1.f.\n", input[3][0], input[3][1], *genann_run(ann, input[3]));
  genann_free(ann);
  return 0;
}


/*** DEPENDENCIES:
genann *genann_read(FILE *in)
{
  int inputs;
  int hidden_layers;
  int hidden;
  int outputs;
  int rc;
  errno = 0;
  rc = fscanf(in, "%d %d %d %d", &inputs, &hidden_layers, &hidden, &outputs);
  if ((rc < 4) || (errno != 0))
  {
    perror("fscanf");
    return 0;
  }
  genann *ann = genann_init(inputs, hidden_layers, hidden, outputs);
  int i;
  for (i = 0; i < ann->total_weights; i += 1)
  {
    errno = 0;
    rc = fscanf(in, " %le", ann->weight + i);
    if ((rc < 1) || (errno != 0))
    {
      perror("fscanf");
      genann_free(ann);
      return 0;
    }
  }

  return ann;
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
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
const char *save_name = "example/xor.ann"
----------------------------
***/



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


/*** DEPENDENCIES:
genann *genann_copy(const genann *ann)
{
  const int size = (sizeof(genann)) + ((sizeof(double)) * ((ann->total_weights + ann->total_neurons) + (ann->total_neurons - ann->inputs)));
  genann *ret = malloc(size);
  if (!ret)
  {
    return 0;
  }
  memcpy(ret, ann, size);
  ret->weight = (double *) (((char *) ret) + (sizeof(genann)));
  ret->output = ret->weight + ret->total_weights;
  ret->delta = ret->output + ret->total_neurons;
  return ret;
}


----------------------------
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
void genann_randomize(genann *ann)
{
  int i;
  for (i = 0; i < ann->total_weights; i += 1)
  {
    double r = ((double) rand()) / 32767;
    ann->weight[i] = r - 0.5;
  }

}


----------------------------
pub time: Time
----------------------------
***/



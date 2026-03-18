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


/*** DEPENDENCIES:
static int ltests = 0
----------------------------
static int lfails = 0
----------------------------
double genann_act_sigmoid(const genann *ann, double a)
{
  if (a < (-45.0))
  {
    return 0;
  }
  if (a > 45.0)
  {
    return 1;
  }
  return 1.0 / (1 + exp(-a));
}


----------------------------
double genann_act_sigmoid_cached(const genann *ann, double a)
{
  assert(!isnan(a));
  if (a < sigmoid_dom_min)
  {
    return lookup[0];
  }
  if (a >= sigmoid_dom_max)
  {
    return lookup[4096 - 1];
  }
  size_t j = (size_t) (((a - sigmoid_dom_min) * interval) + 0.5);
  if (__builtin_expect(!(!(j >= 4096)), 0))
  {
    return lookup[4096 - 1];
  }
  return lookup[j];
}


----------------------------
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
double genann_act_threshold(const struct genann *ann, double a)
{
  return a > 0;
}


----------------------------
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


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
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
void genann_write(const genann *ann, FILE *out)
{
  fprintf(out, "%d %d %d %d", ann->inputs, ann->hidden_layers, ann->hidden, ann->outputs);
  int i;
  for (i = 0; i < ann->total_weights; i += 1)
  {
    fprintf(out, " %.20e", ann->weight[i]);
  }

}


----------------------------
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
double genann_act_threshold(const struct genann *ann, double a)
{
  return a > 0;
}


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
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
double genann_act_threshold(const struct genann *ann, double a)
{
  return a > 0;
}


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
***/


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
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void genann_free(genann *ann)
{
  free(ann);
}


----------------------------
double genann_act_threshold(const struct genann *ann, double a)
{
  return a > 0;
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
***/


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


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
***/



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
/*** DEPENDENCIES:
typedef double (*genann_actfun)(const struct genann *ann, double a)
----------------------------
***/


void genann_randomize(genann *ann)
{
  int i;
  for (i = 0; i < ann->total_weights; i += 1)
  {
    double r = ((double) rand()) / 32767;
    ann->weight[i] = r - 0.5;
  }

}


/*** DEPENDENCIES:
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
***/


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


/*** DEPENDENCIES:
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
***/


void genann_free(genann *ann)
{
  free(ann);
}


/*** DEPENDENCIES:
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
***/


void genann_write(const genann *ann, FILE *out)
{
  fprintf(out, "%d %d %d %d", ann->inputs, ann->hidden_layers, ann->hidden, ann->outputs);
  int i;
  for (i = 0; i < ann->total_weights; i += 1)
  {
    fprintf(out, " %.20e", ann->weight[i]);
  }

}


/*** DEPENDENCIES:
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
***/


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


/*** DEPENDENCIES:
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
***/


double genann_act_threshold(const struct genann *ann, double a)
{
  return a > 0;
}


/*** DEPENDENCIES:
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
***/


double genann_act_linear(const struct genann *ann, double a)
{
  return a;
}


/*** DEPENDENCIES:
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
***/


double genann_act_hidden_indirect(const struct genann *ann, double a)
{
  return ann->activation_hidden(ann, a);
}


/*** DEPENDENCIES:
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
***/


double genann_act_output_indirect(const struct genann *ann, double a)
{
  return ann->activation_output(ann, a);
}


/*** DEPENDENCIES:
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
***/


// hint:  ['j_ref is a mutable refrence to int', 'k_ref is a mutable refrence to int']
void helper_genann_train_1(int * const j_ref, int * const k_ref, const genann * const ann, int h)
{
  int j = *j_ref;
  int k = *k_ref;
  const double *o = (ann->output + ann->inputs) + (h * ann->hidden);
  unsigned int o_idx = 0;
  double *d = ann->delta + (h * ann->hidden);
  unsigned int d_idx = 0;
  const double * const dd = ann->delta + ((h + 1) * ann->hidden);
  const double * const ww = (ann->weight + ((ann->inputs + 1) * ann->hidden)) + (((ann->hidden + 1) * ann->hidden) * h);
  for (j = 0; j < ann->hidden; j += 1)
  {
    double delta = 0;
    for (k = 0; k < ((h == (ann->hidden_layers - 1)) ? (ann->outputs) : (ann->hidden)); k += 1)
    {
      const double forward_delta = dd[k];
      const int windex = (k * (ann->hidden + 1)) + (j + 1);
      const double forward_weight = ww[windex];
      delta += forward_delta * forward_weight;
    }

    d[d_idx] = (o[o_idx] * (1.0 - o[o_idx])) * delta;
    d_idx += 1;
    o_idx += 1;
  }

  *j_ref = j;
  *k_ref = k;
}


/*** DEPENDENCIES:
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
***/


void genann_init_sigmoid_lookup(const genann *ann)
{
  const double f = (sigmoid_dom_max - sigmoid_dom_min) / 4096;
  int i;
  interval = 4096 / (sigmoid_dom_max - sigmoid_dom_min);
  for (i = 0; i < 4096; i += 1)
  {
    lookup[i] = genann_act_sigmoid(ann, sigmoid_dom_min + (f * i));
  }

}


/*** DEPENDENCIES:
const double sigmoid_dom_max = 15.0
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
const double sigmoid_dom_min = -15.0
----------------------------
double interval
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
double lookup[4096]
----------------------------
***/


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


/*** DEPENDENCIES:
const double sigmoid_dom_max = 15.0
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
const double sigmoid_dom_min = -15.0
----------------------------
double interval
----------------------------
double lookup[4096]
----------------------------
***/


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


/*** DEPENDENCIES:
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
void genann_init_sigmoid_lookup(const genann *ann)
{
  const double f = (sigmoid_dom_max - sigmoid_dom_min) / 4096;
  int i;
  interval = 4096 / (sigmoid_dom_max - sigmoid_dom_min);
  for (i = 0; i < 4096; i += 1)
  {
    lookup[i] = genann_act_sigmoid(ann, sigmoid_dom_min + (f * i));
  }

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


/*** DEPENDENCIES:
void genann_free(genann *ann)
{
  free(ann);
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
***/


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


/*** DEPENDENCIES:
double genann_act_output_indirect(const struct genann *ann, double a)
{
  return ann->activation_output(ann, a);
}


----------------------------
double genann_act_hidden_indirect(const struct genann *ann, double a)
{
  return ann->activation_hidden(ann, a);
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
***/


// hint:  ['j_ref is a mutable refrence to int']
void helper_genann_train_2(int * const j_ref, const genann * const ann, const double * const desired_outputs)
{
  int j = *j_ref;
  const double *o = (ann->output + ann->inputs) + (ann->hidden * ann->hidden_layers);
  unsigned int o_idx = 0;
  double *d = ann->delta + (ann->hidden * ann->hidden_layers);
  unsigned int d_idx = 0;
  const double *t = desired_outputs;
  unsigned int t_idx = 0;
  if ((genann_act_output_indirect == genann_act_linear) || (ann->activation_output == genann_act_linear))
  {
    for (j = 0; j < ann->outputs; j += 1)
    {
      d[d_idx] = t[t_idx] - o[o_idx];
      o_idx += 1;
      t_idx += 1;
      d_idx += 1;
    }

  }
  else
  {
    for (j = 0; j < ann->outputs; j += 1)
    {
      d[d_idx] = ((t[t_idx] - o[o_idx]) * o[o_idx]) * (1.0 - o[o_idx]);
      d_idx += 1;
      o_idx += 1;
      ++(&t[t_idx]);
    }

  }
  *j_ref = j;
}


/*** DEPENDENCIES:
double genann_act_output_indirect(const struct genann *ann, double a)
{
  return ann->activation_output(ann, a);
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
double genann_act_linear(const struct genann *ann, double a)
{
  return a;
}


----------------------------
***/


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


/*** DEPENDENCIES:
void helper_genann_train_2(int * const j_ref, const genann * const ann, const double * const desired_outputs)
{
  int j = *j_ref;
  const double *o = (ann->output + ann->inputs) + (ann->hidden * ann->hidden_layers);
  unsigned int o_idx = 0;
  double *d = ann->delta + (ann->hidden * ann->hidden_layers);
  unsigned int d_idx = 0;
  const double *t = desired_outputs;
  unsigned int t_idx = 0;
  if ((genann_act_output_indirect == genann_act_linear) || (ann->activation_output == genann_act_linear))
  {
    for (j = 0; j < ann->outputs; j += 1)
    {
      d[d_idx] = t[t_idx] - o[o_idx];
      o_idx += 1;
      t_idx += 1;
      d_idx += 1;
    }

  }
  else
  {
    for (j = 0; j < ann->outputs; j += 1)
    {
      d[d_idx] = ((t[t_idx] - o[o_idx]) * o[o_idx]) * (1.0 - o[o_idx]);
      d_idx += 1;
      o_idx += 1;
      ++(&t[t_idx]);
    }

  }
  *j_ref = j;
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
void helper_genann_train_1(int * const j_ref, int * const k_ref, const genann * const ann, int h)
{
  int j = *j_ref;
  int k = *k_ref;
  const double *o = (ann->output + ann->inputs) + (h * ann->hidden);
  unsigned int o_idx = 0;
  double *d = ann->delta + (h * ann->hidden);
  unsigned int d_idx = 0;
  const double * const dd = ann->delta + ((h + 1) * ann->hidden);
  const double * const ww = (ann->weight + ((ann->inputs + 1) * ann->hidden)) + (((ann->hidden + 1) * ann->hidden) * h);
  for (j = 0; j < ann->hidden; j += 1)
  {
    double delta = 0;
    for (k = 0; k < ((h == (ann->hidden_layers - 1)) ? (ann->outputs) : (ann->hidden)); k += 1)
    {
      const double forward_delta = dd[k];
      const int windex = (k * (ann->hidden + 1)) + (j + 1);
      const double forward_weight = ww[windex];
      delta += forward_delta * forward_weight;
    }

    d[d_idx] = (o[o_idx] * (1.0 - o[o_idx])) * delta;
    d_idx += 1;
    o_idx += 1;
  }

  *j_ref = j;
  *k_ref = k;
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
***/



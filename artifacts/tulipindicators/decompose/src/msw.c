int ti_msw_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


// hint:  ['sine_idx_ref is a mutable refrence to unsigned int', 'weight_ref is a mutable refrence to double', 'phase_ref is a mutable refrence to double', 'rp_ref is a mutable refrence to double', 'ip_ref is a mutable refrence to double', 'j_ref is a mutable refrence to int']
void helper_ti_msw_1(unsigned int * const sine_idx_ref, double * const weight_ref, double * const phase_ref, double * const rp_ref, double * const ip_ref, int * const j_ref, const double * const input, double * const sine, double * const lead, const int period, const double pi, const double tpi, int i)
{
  unsigned int sine_idx = *sine_idx_ref;
  double weight = *weight_ref;
  double phase = *phase_ref;
  double rp = *rp_ref;
  double ip = *ip_ref;
  int j = *j_ref;
  rp = 0;
  ip = 0;
  for (j = 0; j < period; j += 1)
  {
    weight = input[i - j];
    rp = rp + (cos((tpi * j) / period) * weight);
    ip = ip + (sin((tpi * j) / period) * weight);
  }

  if (fabs(rp) > .001)
  {
    phase = atan(ip / rp);
  }
  else
  {
    phase = (tpi / 2.0) * ((ip < 0) ? (-1.0) : (1.0));
  }
  if (rp < 0.0)
  {
    phase += pi;
  }
  phase += pi / 2.0;
  if (phase < 0.0)
  {
    phase += tpi;
  }
  if (phase > tpi)
  {
    phase -= tpi;
  }
  sine[sine_idx] = sin(phase);
  sine_idx += 1;
  *(lead++) = sin(phase + (pi / 4.0));
  *sine_idx_ref = sine_idx;
  *weight_ref = weight;
  *phase_ref = phase;
  *rp_ref = rp;
  *ip_ref = ip;
  *j_ref = j;
}


/*** DEPENDENCIES:
***/


int ti_msw(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *sine = outputs[0];
  unsigned int sine_idx = 0;
  double *lead = outputs[1];
  const int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_msw_start(options))
  {
    return 0;
  }
  const double pi = 3.1415926;
  const double tpi = 2 * pi;
  double weight = 0;
  double phase;
  double rp;
  double ip;
  int i;
  int j;
  for (i = period; i < size; i += 1)
  {
    helper_ti_msw_1(&sine_idx, &weight, &phase, &rp, &ip, &j, input, sine, lead, period, pi, tpi, i);
  }

  assert(((&sine[sine_idx]) - outputs[0]) == (size - ti_msw_start(options)));
  assert((lead - outputs[1]) == (size - ti_msw_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_msw_start(const double *options)
{
  return (int) options[0];
}


----------------------------
void helper_ti_msw_1(unsigned int * const sine_idx_ref, double * const weight_ref, double * const phase_ref, double * const rp_ref, double * const ip_ref, int * const j_ref, const double * const input, double * const sine, double * const lead, const int period, const double pi, const double tpi, int i)
{
  unsigned int sine_idx = *sine_idx_ref;
  double weight = *weight_ref;
  double phase = *phase_ref;
  double rp = *rp_ref;
  double ip = *ip_ref;
  int j = *j_ref;
  rp = 0;
  ip = 0;
  for (j = 0; j < period; j += 1)
  {
    weight = input[i - j];
    rp = rp + (cos((tpi * j) / period) * weight);
    ip = ip + (sin((tpi * j) / period) * weight);
  }

  if (fabs(rp) > .001)
  {
    phase = atan(ip / rp);
  }
  else
  {
    phase = (tpi / 2.0) * ((ip < 0) ? (-1.0) : (1.0));
  }
  if (rp < 0.0)
  {
    phase += pi;
  }
  phase += pi / 2.0;
  if (phase < 0.0)
  {
    phase += tpi;
  }
  if (phase > tpi)
  {
    phase -= tpi;
  }
  sine[sine_idx] = sin(phase);
  sine_idx += 1;
  *(lead++) = sin(phase + (pi / 4.0));
  *sine_idx_ref = sine_idx;
  *weight_ref = weight;
  *phase_ref = phase;
  *rp_ref = rp;
  *ip_ref = ip;
  *j_ref = j;
}


----------------------------
***/



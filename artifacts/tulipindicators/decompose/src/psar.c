int ti_psar_start(const double *options)
{
  (void) options;
  return 1;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'lng_ref is a mutable refrence to int', 'sar_ref is a mutable refrence to double', 'extreme_ref is a mutable refrence to double', 'accel_ref is a mutable refrence to double']
void helper_ti_psar_1(unsigned int * const output_idx_ref, int * const lng_ref, double * const sar_ref, double * const extreme_ref, double * const accel_ref, const double * const high, const double * const low, const double accel_step, const double accel_max, double * const output, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int lng = *lng_ref;
  double sar = *sar_ref;
  double extreme = *extreme_ref;
  double accel = *accel_ref;
  sar = ((extreme - sar) * accel) + sar;
  if (lng)
  {
    if ((i >= 2) && (sar > low[i - 2]))
    {
      sar = low[i - 2];
    }
    if (sar > low[i - 1])
    {
      sar = low[i - 1];
    }
    if ((accel < accel_max) && (high[i] > extreme))
    {
      accel += accel_step;
      if (accel > accel_max)
      {
        accel = accel_max;
      }
    }
    if (high[i] > extreme)
    {
      extreme = high[i];
    }
  }
  else
  {
    if ((i >= 2) && (sar < high[i - 2]))
    {
      sar = high[i - 2];
    }
    if (sar < high[i - 1])
    {
      sar = high[i - 1];
    }
    if ((accel < accel_max) && (low[i] < extreme))
    {
      accel += accel_step;
      if (accel > accel_max)
      {
        accel = accel_max;
      }
    }
    if (low[i] < extreme)
    {
      extreme = low[i];
    }
  }
  if ((lng && (low[i] < sar)) || ((!lng) && (high[i] > sar)))
  {
    accel = accel_step;
    sar = extreme;
    lng = !lng;
    if (!lng)
    {
      extreme = low[i];
    }
    else
      extreme = high[i];
  }
  output[output_idx] = sar;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *lng_ref = lng;
  *sar_ref = sar;
  *extreme_ref = extreme;
  *accel_ref = accel;
}


/*** DEPENDENCIES:
***/


int ti_psar(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double accel_step = options[0];
  const double accel_max = options[1];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (accel_step <= 0)
  {
    return 1;
  }
  if (accel_max <= accel_step)
  {
    return 1;
  }
  if (size < 2)
  {
    return 0;
  }
  int lng;
  if ((high[0] + low[0]) <= (high[1] + low[1]))
  {
    lng = 1;
  }
  else
    lng = 0;
  double sar;
  double extreme;
  if (lng)
  {
    extreme = high[0];
    sar = low[0];
  }
  else
  {
    extreme = low[0];
    sar = high[0];
  }
  double accel = accel_step;
  int i;
  for (i = 1; i < size; i += 1)
  {
    helper_ti_psar_1(&output_idx, &lng, &sar, &extreme, &accel, high, low, accel_step, accel_max, output, i);
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_psar_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_psar_start(const double *options)
{
  (void) options;
  return 1;
}


----------------------------
void helper_ti_psar_1(unsigned int * const output_idx_ref, int * const lng_ref, double * const sar_ref, double * const extreme_ref, double * const accel_ref, const double * const high, const double * const low, const double accel_step, const double accel_max, double * const output, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int lng = *lng_ref;
  double sar = *sar_ref;
  double extreme = *extreme_ref;
  double accel = *accel_ref;
  sar = ((extreme - sar) * accel) + sar;
  if (lng)
  {
    if ((i >= 2) && (sar > low[i - 2]))
    {
      sar = low[i - 2];
    }
    if (sar > low[i - 1])
    {
      sar = low[i - 1];
    }
    if ((accel < accel_max) && (high[i] > extreme))
    {
      accel += accel_step;
      if (accel > accel_max)
      {
        accel = accel_max;
      }
    }
    if (high[i] > extreme)
    {
      extreme = high[i];
    }
  }
  else
  {
    if ((i >= 2) && (sar < high[i - 2]))
    {
      sar = high[i - 2];
    }
    if (sar < high[i - 1])
    {
      sar = high[i - 1];
    }
    if ((accel < accel_max) && (low[i] < extreme))
    {
      accel += accel_step;
      if (accel > accel_max)
      {
        accel = accel_max;
      }
    }
    if (low[i] < extreme)
    {
      extreme = low[i];
    }
  }
  if ((lng && (low[i] < sar)) || ((!lng) && (high[i] > sar)))
  {
    accel = accel_step;
    sar = extreme;
    lng = !lng;
    if (!lng)
    {
      extreme = low[i];
    }
    else
      extreme = high[i];
  }
  output[output_idx] = sar;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *lng_ref = lng;
  *sar_ref = sar;
  *extreme_ref = extreme;
  *accel_ref = accel;
}


----------------------------
***/



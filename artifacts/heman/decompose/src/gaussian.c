void generate_gaussian_row(int *target, int fwidth)
{
  assert(fwidth > 0);
  int nbytes = fwidth * (sizeof(int));
  int *tmp = malloc(nbytes);
  target[0] = (tmp[0] = 1);
  for (int col = 1; col < fwidth; col += 1)
  {
    target[col] = 0;
    tmp[col] = 0;
  }

  for (int row = 1; row < fwidth; row += 1)
  {
    for (int col = 1; col <= row; col += 1)
    {
      target[col] = tmp[col] + tmp[col - 1];
    }

    for (int col = 1; col <= row; col += 1)
    {
      tmp[col] = target[col];
    }

  }

  free(tmp);
}


/*** DEPENDENCIES:
***/


void generate_gaussian_splat(float *target, int fwidth)
{
  int *gaussian_row = malloc(fwidth * (sizeof(int)));
  generate_gaussian_row(gaussian_row, fwidth);
  int shift = 1 << (fwidth - 1);
  float scale = 1.0 / (shift * shift);
  float *gptr = target;
  unsigned int gptr_idx = 0;
  for (int j = 0; j < fwidth; j += 1)
  {
    for (int i = 0; i < fwidth; i += 1)
    {
      gptr[gptr_idx] = (gaussian_row[i] * gaussian_row[j]) * scale;
      gptr_idx += 1;
    }

  }

  free(gaussian_row);
}


/*** DEPENDENCIES:
void generate_gaussian_row(int *target, int fwidth)
{
  assert(fwidth > 0);
  int nbytes = fwidth * (sizeof(int));
  int *tmp = malloc(nbytes);
  target[0] = (tmp[0] = 1);
  for (int col = 1; col < fwidth; col += 1)
  {
    target[col] = 0;
    tmp[col] = 0;
  }

  for (int row = 1; row < fwidth; row += 1)
  {
    for (int col = 1; col <= row; col += 1)
    {
      target[col] = tmp[col] + tmp[col - 1];
    }

    for (int col = 1; col <= row; col += 1)
    {
      tmp[col] = target[col];
    }

  }

  free(tmp);
}


----------------------------
***/



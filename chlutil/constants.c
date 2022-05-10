static double gravity            = 9.81;
static double manning_conversion = 1;

double
chl_const_gravity (void)
{
  return gravity;
}

double
chl_const_manning (void)
{
  return manning_conversion;
}

void
chl_const_set_gravity (double g)
{
  gravity = g;
}

void
chl_const_set_manning (double k)
{
  manning_conversion = k;
}

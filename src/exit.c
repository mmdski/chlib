#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool expected = false;
bool called   = false;
int  status;

void
chl_exit_expected_set (void)
{
  expected = true;
}

void
chl_exit_expected_clear (void)
{
  expected = false;
}

void
chl_exit (int exit_status)
{
  if (expected)
    {
      called = true;
      status = exit_status;
    }
  else if (called)
    {
      fputs ("chl_exit() has been previously called\n", stderr);
      exit (EXIT_FAILURE);
    }
  else
    {
      fputs ("Unexpected call to chl_exit()\n", stderr);
      exit (exit_status);
    }
}

bool
chl_exit_called (void)
{
  return called;
}

void
chl_exit_called_clear (void)
{
  called = false;
}

int
chl_exit_status (void)
{
  return status;
}

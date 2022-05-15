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
      puts ("Caught expected call to chl_exit()");
      called = true;
      status = exit_status;
    }
  else if (called)
    {
      fputs ("Fatal Error: chl_exit() call flag already set", stderr);
      exit (EXIT_FAILURE);
    }
  else
    {
      fputs ("Fatal Error: Unexpected call to chl_exit()", stderr);
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

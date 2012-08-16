#include "hs.h"
#include <stdio.h>
#include <stdlib.h>

static void
print_safe (const char *s)
{
  if (s) printf ("%s\n", s);
  else printf ("(null)\n");
}

void
array_test (void)
{
  int n = 1;
  array_t *a = array_from_str ("0x1xx0x1");
  array_t *b = array_from_str ("01xx10x1");
  array_isect (a, b, n, a);
  char *s = array_to_str (a, n, false);
  print_safe (s);
  free (s);
  free (a);
  free (b);

  a = array_from_str ("01xx0011,xxxx1011");
  s = array_to_str (a, 2, false);
  print_safe (s);
  free (s);
  free (a);

  a = array_from_str ("11000001,10001000,00011111,001101xx");
  s = array_to_str (a, 4, true);
  print_safe (s);
  free (s);
  free (a);
}

void
hs_test (void)
{
  array_t *arr;
  struct hs *a = hs_create (1);
  hs_add (a, array_from_str ("0011xx00"));
  hs_add (a, array_from_str ("10100x0x"));
  arr = array_from_str ("10100x01");
  hs_diff (a, arr);
  hs_print (a);
  struct hs *b = hs_copy_a (a);
  hs_print (b);
  hs_free (b);
  free (arr);

  b = hs_create (1);
  hs_add (b, array_from_str ("xxxx1x00"));
  hs_add (b, array_from_str ("xxxxx1x0"));
  hs_print (b);
  hs_isect (b, a);
  hs_print (b);
  hs_free (b);
  hs_free (a);

  a = hs_create (1);
  hs_add (a, array_from_str ("10xxxxxx"));
  hs_add (a, array_from_str ("xxxxxx10"));
  arr = array_from_str ("11111111");
  hs_diff (a, arr);
  hs_print (a);
  hs_cmpl (a);
  hs_print (a);
  hs_free (a);

  a = hs_create (1);
  hs_add (a, array_from_str ("10xxxxxx"));
  hs_add (a, array_from_str ("xxxxxx10"));
  b = hs_create (1);
  hs_add (b, array_from_str ("11111111"));
  hs_minus (a, b);
  hs_print (a);
  hs_free (a);
  hs_free (b);

  a = hs_create (1);
  hs_add (a, array_from_str ("1xxxxxxx"));
  hs_add (a, array_from_str ("xxxxxxx1"));
  hs_diff (a, arr);
  hs_print (a);
  hs_comp_diff (a);
  hs_print (a);
  hs_free (a);
  free (arr);
}

int
main (void)
{
  printf ("%s\n", array_to_str (array_from_str ("11111111,00000000"), 2, true));
  //array_test ();
  hs_test ();
  return 0;
}


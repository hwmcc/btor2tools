#include "btorsimhelpers.h"

void die (const char* m, ...)
{
  fflush (stdout);
  fputs ("*** 'btorsim' error: ", stderr);
  va_list ap;
  va_start (ap, m);
  vfprintf (stderr, m, ap);
  va_end (ap);
  fprintf (stderr, "\n");
  exit (1);
}


void msg (int32_t level, const char* m, ...)
{
  if (level > verbosity) return;
  assert (m);
  printf ("[btorsim] ");
  va_list ap;
  va_start (ap, m);
  vprintf (m, ap);
  va_end (ap);
  printf ("\n");
}

// this would ideally be in btorsimbv.c but that's C and doesn't know std::string
std::string btorsim_bv_to_string (const BtorSimBitVector *bv)
{
  std::string sval("");
  for (int j = bv->width - 1; j >= 0; j--)
    sval += std::to_string(btorsim_bv_get_bit (bv, j));
  return sval;
}

Btor2Sort *get_sort(Btor2Line* l, Btor2Parser *model)
{
  Btor2Sort *sort;
  switch (l->tag) {
    case BTOR2_TAG_output:
    case BTOR2_TAG_bad:
    case BTOR2_TAG_constraint:
    case BTOR2_TAG_fair:
    // case BTOR2_TAG_justice:
      {
        Btor2Line *ls = btor2parser_get_line_by_id (model, l->args[0]);
        sort = &(ls->sort);
      }
      break;
    default:
      sort = &(l->sort);
      break;
  }
  assert(sort);
  assert(sort->id);
  return sort;
}
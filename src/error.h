#ifndef __ERR_H__
#define __ERR_H__

#define RAISE_NULL_ERR_INT                                                     \
  {                                                                            \
    chl_err_raise (NULL_ARGUMENT_ERROR, "", __FILE__, __LINE__);               \
    return -1;                                                                 \
  }

#define RAISE_ARG_ERR_NULL                                                     \
  {                                                                            \
    chl_err_raise (INVALID_ARGUMENT_ERROR, "", __FILE__, __LINE__);            \
    return NULL;                                                               \
  }

#endif

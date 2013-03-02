// This is SGLIB version 0.0.1
//
// (C) by Marian Vittek, Bratislava, http://www.xref-tech.com, 2003.
//
// License Conditions: This software is free for non commercial use.
// It can be used also in commercial software under Open Source Software
// license. For other license conditions, contact the author.
//

#ifndef _SGLIB__h_
#define _SGLIB__h_


#include <assert.h>


/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */
/* -                           LEVEL - 0  IMPLEMENTATION                      - */
/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */


/* ----------------------------------- arrays --------------------------------- */

/*               HEAP - SORT  (level 0)           */

#define SGLIB_ARRAY_SINGLE_HEAP_SORT(type, a, max, comparator) {\
  SGLIB_ARRAY_HEAP_SORT(type, a, max, comparator, SGLIB_ARRAY_ELEMENTS_EXCHANGER);\
}

#define SGLIB_ARRAY_HEAP_SORT(type, a, max, comparator, elem_exchanger) {\
  int   _k_;\
  for(_k_=(max)/2; _k_>=0; _k_--) {\
    SGLIB___ARRAY_HEAP_DOWN(type, a, _k_, max, comparator, elem_exchanger);\
  }\
  for(_k_=(max)-1; _k_>=0; _k_--) {\
    elem_exchanger(type, a, 0, _k_);\
    SGLIB___ARRAY_HEAP_DOWN(type, a, 0, _k_, comparator, elem_exchanger);\
  }\
}

#define SGLIB___ARRAY_HEAP_DOWN(type, a, ind, max, comparator, elem_exchanger) {\
  type  _t_;\
  int   _m_, _l_, _r_, _i_;\
  _i_ = (ind);\
  _m_ = _i_;\
  do {\
    _i_ = _m_;          \
    _l_ = 2*_i_+1;\
    _r_ = _l_+1;\
    if (_l_ < (max)){\
      if (comparator(((a)[_m_]), ((a)[_l_])) < 0) _m_ = _l_;\
      if (_r_ < (max)) {\
        if (comparator(((a)[_m_]), ((a)[_r_])) < 0) _m_ = _r_;\
      }\
    }\
    if (_m_ != _i_) {\
     elem_exchanger(type, a, _i_, _m_);\
    }\
  } while (_m_ != _i_);\
}


/*             QUICK - SORT   (level 0)          */

#define SGLIB_ARRAY_SINGLE_QUICK_SORT(type, a, max, comparator) {\
  SGLIB_ARRAY_QUICK_SORT(type, a, max, comparator, SGLIB_ARRAY_ELEMENTS_EXCHANGER);\
}

#define SGLIB_ARRAY_QUICK_SORT(type, a, max, comparator, elem_exchanger) {\
  int   _i_, _j_, _p_, _stacki_, _start_, _end_;\
  /* can sort up to 2^64 elements */\
  int   _startStack_[64]; \
  int   _endStack_[64];\
  type  _tmp_;\
  _startStack_[0] = 0;\
  _endStack_[0] = (max);\
  _stacki_ = 1;\
  while (_stacki_ > 0) {\
    _stacki_ --;\
    _start_ = _startStack_[_stacki_];\
    _end_ = _endStack_[_stacki_];\
    while (_end_ - _start_ > 2) {\
      _p_ = _start_;\
      _i_ = _start_ + 1;\
      _j_ = _end_ - 1;\
      while (_i_<_j_) {\
        for(; _i_<=_j_ && comparator(((a)[_i_]),((a)[_p_]))<=0; _i_++) ;\
        if (_i_ > _j_) {\
          /* all remaining elements lesseq than pivot */\
          elem_exchanger(type, a, _j_, _p_);\
          _i_ = _j_;\
        } else {\
          for(; _i_<=_j_ && comparator(((a)[_j_]),((a)[_p_]))>=0; _j_--) ;\
          if (_i_ > _j_) {\
            /* all remaining elements greater than pivot */\
            elem_exchanger(type, a, _j_, _p_);\
            _i_ = _j_;\
          } else if (_i_ < _j_) {\
            elem_exchanger(type, a, _i_, _j_);\
            if (_i_+2 < _j_) {_i_++; _j_--;}\
            else if (_i_+1 < _j_) _i_++;\
          }\
        }\
      }\
      /* O.K. i==j and pivot is on a[i] == a[j] */\
      /* handle recursive calls without recursion */\
      if (_i_-_start_ > 1 && _end_-_j_ > 1) {\
        /* two recursive calls, use array-stack */\
        if (_i_-_start_ < _end_-_j_-1) {\
          _startStack_[_stacki_] = _j_+1;\
          _endStack_[_stacki_] = _end_;\
          _stacki_ ++;\
          _end_ = _i_;\
        } else {\
          _startStack_[_stacki_] = _start_;\
          _endStack_[_stacki_] = _i_;\
          _stacki_ ++;\
          _start_ = _j_+1;\
        }\
      } else {\
        if (_i_-_start_ > 1) {\
          _end_ = _i_;\
        } else {\
          _start_ = _j_+1;\
        }\
      }\
    }\
    if (_end_ - _start_ == 2) {\
      if (comparator(((a)[_start_]),((a)[_end_-1])) > 0) {\
        elem_exchanger(type, a, _start_, _end_-1);\
      }\
    }\
  }\
}

/*             BINARY SEARCH (level 0)          */

#define SGLIB_ARRAY_BINARY_SEARCH(type, a, start_index, end_index, key, comparator, found, result_index) {\
  int _kk_, _cc_, _ii_, _jj_, _ff_;\
  _ii_ = (start_index); \
  _jj_ = (end_index);\
  _ff_ = 0;\
  while (_ii_ <= _jj_ && _ff_==0) {\
    _kk_ = (_jj_+_ii_)/2;\
    _cc_ = comparator(((a)[_kk_]), (key));\
    if (_cc_ == 0) {\
      (result_index) = _kk_;    \
      _ff_ = 1;\
    } else if (_cc_ < 0) {\
      _ii_ = _kk_+1;\
    } else {\
      _jj_ = _kk_-1;\
    }\
  }\
  if (_ff_ == 0) {\
    /* not found, but set its resulting place in the array */\
    (result_index) = _jj_+1;\
  }\
  (found) = _ff_;\
}

/* ------------------------------------ lists (level 0) --------------------- */

#define SGLIB_LIST_ADD(type, list, elem, next) {\
  (elem)->next = (list);\
  (list) = (elem);\
}

#define SGLIB_LIST_CONCAT(type, first, second, next) {\
  if ((first)==NULL) {\
    (first) = (second);\
  } else {\
    type *_p_;\
    for(_p_ = (first); _p_->next!=NULL; _p_=_p_->next) ;\
    _p_->next = (second);\
  }\
}

#define SGLIB_LIST_DELETE(type, list, elem, next) {\
  type **_p_;\
  for(_p_ = &(list); *_p_!=NULL && *_p_!=(elem); _p_= &(*_p_)->next) ;\
  assert(*_p_!=NULL && "elem is not member of the list, use DELETE_IF_MEMBER"!=NULL);\
  *_p_ = (*_p_)->next;\
}

#define SGLIB_LIST_ADD_IF_NOT_MEMBER(type, list, elem, comparator, next, member) {\
  type *_p_;\
  for(_p_ = (list); _p_!=NULL && comparator(_p_, (elem)) != 0; _p_= _p_->next) ;\
  (member) = _p_;\
  if (_p_ == NULL) {\
    SGLIB_LIST_ADD(type, list, elem, next);\
  }\
}

#define SGLIB_LIST_DELETE_IF_MEMBER(type, list, elem, comparator, next, member) {\
  type **_p_;\
  for(_p_ = &(list); *_p_!=NULL && comparator((*_p_), (elem)) != 0; _p_= &(*_p_)->next) ;\
  (member) = *_p_;\
  if (*_p_ != NULL) {\
    *_p_ = (*_p_)->next;\
  }\
}

#define SGLIB_LIST_IS_MEMBER(type, list, elem, next, result) {\
  type *_p_;\
  for(_p_ = (list); _p_!=NULL && _p_ != (elem); _p_= _p_->next) ;\
  (result) = (_p_!=NULL);\
}

#define SGLIB_LIST_FIND_MEMBER(type, list, elem, comparator, next, member) {\
  type *_p_;\
  for(_p_ = (list); _p_!=NULL && comparator(_p_, (elem)) != 0; _p_= _p_->next) ;\
  (member) = _p_;\
}

#define SGLIB_LIST_MAP_ON_ELEMENTS(type, list, next, command) {\
  type *_current_element_, *_ne_;\
  _current_element_=(list); \
  while (_current_element_!=NULL) {\
    _ne_ = _current_element_->next;\
    {command;};\
    _current_element_ = _ne_;\
  }\
}

#define SGLIB_LIST_LEN(type, list, next, result) {\
  (result) = 0;\
  SGLIB_LIST_MAP_ON_ELEMENTS(type, list, next, (result)++);\
}

#define SGLIB_LIST_REVERSE(type, list, next) {\
  type *_list_,*_tmp_,*_res_;\
  _list_ = list;\
  _res_ = NULL;\
  while (_list_!=NULL) {\
    _tmp_ = _list_->next; _list_->next = _res_;\
    _res_ = _list_;   _list_ = _tmp_;\
  }\
  list = _res_;\
}

#define SGLIB_LIST_SORT(type, list, comparator, next) {\
  /* a merge sort on lists */\
  type *_r_;\
  type *_a_, *_b_, *_todo_, *_t_, **_restail_;\
  int _i_, _n_, _contFlag_;\
  _r_ = (list);\
  _contFlag_ = 1;\
  for(_n_ = 1; _contFlag_; _n_ = _n_+_n_) {\
    _todo_ = _r_; _r_ = NULL; _restail_ = &_r_; _contFlag_ =0;\
    while (_todo_!=NULL) {\
      _a_ = _todo_;\
      for(_i_ = 1, _t_ = _a_;  _i_ < _n_ && _t_!=NULL;  _i_++, _t_ = _t_->next) ;\
      if (_t_ ==NULL) {\
        *_restail_ = _a_;\
        break;\
      }\
      _b_ = _t_->next; _t_->next=NULL;\
      for(_i_ =1, _t_ = _b_;  _i_<_n_ && _t_!=NULL;  _i_++, _t_ = _t_->next) ;\
      if (_t_ ==NULL) _todo_ =NULL;\
      else {\
        _todo_ = _t_->next; _t_->next=NULL;\
      }\
      /* merge */\
      while (_a_!=NULL && _b_!=NULL) {\
        if (comparator(_a_, _b_) < 0) {\
          *_restail_ = _a_;  _restail_ = &(_a_->next); _a_ = _a_->next;\
        } else {\
          *_restail_ = _b_;  _restail_ = &(_b_->next); _b_ = _b_->next;\
        }\
      }\
      if (_a_!=NULL) *_restail_ = _a_;\
      else *_restail_ = _b_;\
      while (*_restail_!=NULL) _restail_ = &((*_restail_)->next);\
      _contFlag_ =1;\
    }\
  }\
  (list) = _r_;\
}

/* --------------------------------- sorted list (level 0) --------------------- */

#define SGLIB_SORTED_LIST_ADD(type, list, elem, comparator, next) {\
  type **_e_;\
  int  _cmpres_;\
  SGLIB_SORTED_LIST_FIND_MEMBER_OR_PLACE(type, list, elem, comparator, next, _cmpres_, _e_);\
  (elem)->next = *_e_;\
  *_e_ = (elem);\
}

#define SGLIB_SORTED_LIST_DELETE(type, list, elem, next) {\
  SGLIB_LIST_DELETE(type, list, elem, next);\
}

#define SGLIB_SORTED_LIST_DELETE_IF_MEMBER(type, list, elem, comparator, next, member) {\
  type **_e_;\
  int _cmp_res_;\
  SGLIB_SORTED_LIST_FIND_MEMBER_OR_PLACE(type, list, elem, comparator, next, _cmp_res_, _e_);\
  if (_cmp_res_ == 0) {\
    (member) = *_e_;\
    *_e_ = (*_e_)->next;\
  } else {\
    (member) = NULL;\
  }\
}

#define SGLIB_SORTED_LIST_ADD_IF_NOT_MEMBER(type, list, elem, comparator, next, member) {\
  type **_e_;\
  int _cmp_res_;\
  SGLIB_SORTED_LIST_FIND_MEMBER_OR_PLACE(type, list, elem, comparator, next, _cmp_res_, _e_);\
  if (_cmp_res_ != 0) {\
    (elem)->next = *_e_;\
    *_e_ = (elem);\
    (member) = NULL;\
  } else {\
    (member) = *_e_;\
  }\
}

#define SGLIB_SORTED_LIST_FIND_MEMBER(type, list, elem, comparator, next, member) {\
  type *_p_;\
  int _cmpres_;\
  for(_p_ = (list); _p_!=NULL && (_cmpres_=comparator(_p_, (elem))) < 0; _p_=_p_->next) ;\
  if (_cmpres_ != 0) (member) = NULL;\
  else (member) = _p_;\
}

#define SGLIB_SORTED_LIST_IS_MEMBER(type, list, elem, comparator, next, result) {\
  type *_p_;\
  int _cmpres_;\
  for(_p_ = (list); _p_!=NULL && (_cmpres_=comparator(_p_, (elem))) < 0; _p_=_p_->next) ;\
  while (_p_ != NULL && _p_ != (elem) && (_cmpres_ = comparator(_p_, (elem))) == 0) _p_=_p_->next;\
  (result) = (_p_ == (elem));\
}

#define SGLIB_SORTED_LIST_FIND_MEMBER_OR_PLACE(type, list, elem, comparator, next, comparator_result, member_ptr) {\
  for((member_ptr) = &(list); \
      *(member_ptr)!=NULL && ((comparator_result)=comparator((*member_ptr), (elem))) < 0; \
      (member_ptr) = &(*(member_ptr))->next) ;\
  if (*(member_ptr) == NULL) (comparator_result) = -1;\
}

#define SGLIB_SORTED_LIST_LEN(type, list, next, result) {\
  SGLIB_LIST_LEN(type, list, next, result);\
}

#define SGLIB_SORTED_LIST_MAP_ON_ELEMENTS(type, list, next, command) {\
  SGLIB_LIST_MAP_ON_ELEMENTS(type, list, next, command);\
}

/* ------------------------------- double linked list (draft) (level 0) ------------ */


#define SGLIB_DL_LIST_ADD_AT_BEGINNING(type, list, elem, previous, next) {\
  (elem)->next = (list);\
  (elem)->previous = NULL;\
  (list) = (elem);\
  if ((elem)->next != NULL) (elem)->next->previous = (elem);\
}

#define SGLIB_DL_LIST_ADD_AFTER(type, place, elem, previous, next) {\
  (elem)->next = (place)->next;\
  (elem)->previous = (place);\
  (place)->next = (elem);\
  if ((elem)->next!=NULL) (elem)->next->previous = (elem);\
}

#define SGLIB_DL_LIST_DELETE(type, list, elem, previous, next) {\
  if ((elem)->next != NULL) (elem)->next->previous = (elem)->previous;\
  if ((elem)->previous!=NULL) (elem)->previous->next = (elem)->next;\
  else (list) = (elem)->next;\
}

#define SGLIB_DL_LIST_SORT(type, list, comparator, previous, next) {\
  type *_p_, *_t_;\
  SGLIB_LIST_SORT(type, list, comparator, next);\
  /* remake 'previous' links */\
  _p_ = NULL;\
  for(_t_ = (list); _t_!=NULL; _t_ = _t_->next) {\
    _t_->previous = _p_;\
    _p_ = _t_;\
  }\
}


/* ----------------------------- sorted double linked list (draft) (level 0) ------------ */


#define SGLIB_SORTED_DL_LIST_ADD(type, list, elem, comparator, previous, next) {\
  type *_p_;\
  int  _i_;\
  SGLIB_SORTED_DL_LIST_FIND_PLACE(type, list, elem, comparator, next, _i_, _p_);\
  if (_p_ == NULL) {\
    SGLIB_DL_LIST_ADD_AT_BEGINNING(type, list, elem, previous, next);\
  } else {\
    SGLIB_DL_LIST_ADD_AFTER(type, _p_, elem, previous, next);\
  }\
}

#define SGLIB_SORTED_DL_LIST_ADD_IF_NOT_MEMBER(type, list, elem, comparator, previous, next) {\
  type *_p_;\
  int  _i_;\
  SGLIB_SORTED_DL_LIST_FIND_PLACE(type, list, elem, comparator, next, _i_, _p_);\
  if (_i_) {  \
    if (_p_ == NULL) {\
      SGLIB_DL_LIST_ADD_AT_BEGINNING(type, list, elem, previous, next);\
    } else {\
      SGLIB_DL_LIST_ADD_AFTER(type, _p_, elem, previous, next);\
    }\
  }\
}

#define SGLIB_SORTED_DL_LIST_FIND_PLACE(type, list, elem, comparator, next, comparator_result, member_ptr) {\
  if ((list) == NULL || ((comparator_result)=comparator(((list)->next), (elem))) >= 0) {\
    (member_ptr) = NULL;\
    (comparator_result) = -1;\
  } else {\
    for( (member_ptr) = list; \
         (member_ptr)->next != NULL && ((comparator_result)=comparator(((member_ptr)->next), (elem))) < 0; \
         (member_ptr) = (member_ptr)->next) ;\
    if ((member_ptr)->next == NULL) (comparator_result) = -1;\
  }\
}

/* ----------------------------------- hash table (draft) (level 0) -------------------- */

#ifndef SGLIB_HASH_TAB_SHIFT_CONSTANT
#define SGLIB_HASH_TAB_SHIFT_CONSTANT 211   /* should be a prime */
#endif

#define SGLIB_HASH_TAB_INIT(type, table, size) {\
    memset((table), 0, sizeof(type *) * (size));\
}

#define SGLIB_HASH_TAB_IS_MEMBER(type, table, size, hashing_function, elem, comparator, position, result) {\
    unsigned _posid_;\
    int      _count_, _res_; \
    _count = 0;\
    _posid_ = hashing_function(elem);\
    _posid_ %= (size);\
    while ((_res_ = ((table)[_posid_] != NULL)) && comparator(((table)[_posid_]), (elem)) != 0 && _count_<(size)) {\
        _count_ ++;\
        _posid_ = (_posid_ + SGLIB_HASH_TAB_SHIFT_CONSTANT) % (size);\
    }\
    (position) = _posid_;\
    (result) = _res_;\
}

#define SGLIB_HASH_TAB_ADD_IF_NOT_MEMBER(type, table, size, hashing_function, elem, comparator, position, added) {\
  int      _ismem_;\
  unsigned _pos_;\
  SGLIB_HASH_TAB_IS_MEMBER(type, table, size, hashing_function, elem, comparator, _pos_, _ismem_);\
  (added) = ! _ismem_;\
  (position) = _pos_;\
  if (! _ismem_) {\
    if ((table)[_pos_] != NULL) {\
      /* table is full */\
      (added) = 0;\
      (position) = -1;\
    } else {\
      (table)[_pos_] = (elem);\
    }\
  }\
}

#define SGLIB_HASH_TAB_MAP(type, table, size, command) {\
  unsigned  _current_index_;\
  type     *_current_element_;\
  for(_current_index_=0; _current_index_ < (size); _current_index_++) {\
    _current_element_ = (table)[_current_index_];\
    if (_current_element_ != NULL) {\
      command;\
    }\
  }\
}

/* ------------------------------- binary tree traversal (level 0) -------------------- */

#define SGLIB_BIN_TREE_MAP_ON_ELEMENTS(type, tree, left, right, command) {\
  type *_path_[SGLIB_MAX_TREE_DEEP];\
  /* this is non-recursive implementation of tree traversal */\
  /* it maintains the path to the current node in the array '_path_' */\
  /* the _path_[0] contains the root of the tree; */\
  /* the _path_[_pathi_-1] contains the parent of _current_element_ */\
  type *_current_element_, *_upn_;\
  int _pathi_;\
  int _state_;  /* 0 - goto left; 1 - inspect && goto right; 2 - goto up */\
  if (tree != NULL) {\
    _current_element_ = tree;\
    _pathi_ = 0;\
    _path_[_pathi_++] = _current_element_;\
    _state_ = 0;\
    while (_pathi_>1 || _state_!=2) {\
      assert(_pathi_<SGLIB_MAX_TREE_DEEP && "The tree is too deep"!=NULL);\
      if (_state_==0 && _current_element_->left!=NULL) {\
        _current_element_ = _current_element_->left;\
        _path_[_pathi_++] = _current_element_;\
      } else {\
        if (_state_!=2) {command;}\
        if (_state_!=2 && _current_element_->right!=NULL) {\
          _current_element_ = _current_element_->right;\
          _path_[_pathi_++] = _current_element_;\
          _state_ = 0;\
        } else {\
          _pathi_ --;\
          if (_pathi_ == 0) {\
            _state_ = 2;\
          } else {\
            _upn_ = _path_[_pathi_-1];\
            _state_ = 1 + (_current_element_ != _upn_->left);\
            _current_element_ = _upn_;\
          }\
        }\
      }\
    }\
  }\
}



/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */
/* -                           LEVEL - 1  IMPLEMENTATION                      - */
/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */



/* ----------------------------- array sorting (level 1) ------------ */

#define SGLIB_DEFINE_ARRAY_SORTING_PROTOTYPES(type, comparator) \
 extern void sglib_##type##_array_quick_sort(type *a, int max);\
 extern void sglib_##type##_array_heap_sort(type *a, int max);\


#define SGLIB_DEFINE_ARRAY_SORTING_FUNCTIONS(type, comparator) \
 void sglib_##type##_array_quick_sort(type *a, int max) {\
   SGLIB_ARRAY_SINGLE_QUICK_SORT(type, a, max, comparator);\
 }\
 void sglib_##type##_array_heap_sort(type *a, int max) {\
   SGLIB_ARRAY_SINGLE_HEAP_SORT(type, a, max, comparator);\
 }\


/* ----------------------------- list (level 1) ------------ */

#define SGLIB_DEFINE_LIST_PROTOTYPES(type, comparator, next) \
 extern void sglib_##type##_add(type **list, type *elem);\
 extern void sglib_##type##_add_if_not_member(type **list, type *elem);\
 extern void sglib_##type##_concat(type **first, type *second);\
 extern void sglib_##type##_delete(type **list, type *elem);\
 extern int sglib_##type##_delete_if_member(type **list, type *elem, type **member);\
 extern int sglib_##type##_is_member(type *list, type *elem);\
 extern type *sglib_##type##_find_member(type *list, type *elem);\
 extern void sglib_##type##_sort(type **list);\
 extern int sglib_##type##_len(type *list);\
 extern void sglib_##type##_reverse(type **list);

#define SGLIB_DEFINE_LIST_FUNCTIONS(type, comparator, next) \
 int sglib_##type##_is_member(type *list, type *elem) {\
   int result;\
   SGLIB_LIST_IS_MEMBER(type, list, elem, next, result);\
   return(result);\
 }\
 type *sglib_##type##_find_member(type *list, type *elem) {\
   type *result;\
   SGLIB_LIST_FIND_MEMBER(type, list, elem, comparator, next, result);\
   return(result);\
 }\
 int sglib_##type##_add_if_not_member(type **list, type *elem, type **member) {\
   SGLIB_LIST_ADD_IF_NOT_MEMBER(type, *list, elem, comparator, next, *member);\
   return(*member==NULL);\
 }\
 void sglib_##type##_add(type **list, type *elem) {\
   SGLIB_LIST_ADD(type, *list, elem, next);\
 }\
 void sglib_##type##_concat(type **first, type *second) {\
   SGLIB_LIST_CONCAT(type, *first, second, next);\
 }\
 void sglib_##type##_delete(type **list, type *elem) {\
   SGLIB_LIST_DELETE(type, *list, elem, next);\
 }\
 int sglib_##type##_delete_if_member(type **list, type *elem, type **member) {\
   SGLIB_LIST_DELETE_IF_MEMBER(type, *list, elem, comparator, next, *member);\
   return(*member!=NULL);\
 }\
 void sglib_##type##_sort(type **list) { \
   SGLIB_LIST_SORT(type, *list, comparator, next);\
 }\
 int sglib_##type##_len(type *list) {\
   int res;\
   SGLIB_LIST_LEN(type, list, next, res);\
   return(res);\
 }\
 void sglib_##type##_reverse(type **list) {\
   SGLIB_LIST_REVERSE(type, *list, next);\
 }

/* ----------------------------- sorted list (level 1) ------------ */


#define SGLIB_DEFINE_SORTED_LIST_PROTOTYPES(type, comparator, next) \
 extern void sglib_##type##_add(type **list, type *elem);\
 extern int sglib_##type##_add_if_not_member(type **list, type *elem, type **member);\
 extern void sglib_##type##_delete(type **list, type *elem);\
 extern int sglib_##type##_delete_if_member(type **list, type *elem, type **member);\
 extern int sglib_##type##_is_member(type *list, type *elem);\
 extern type *sglib_##type##_find_member(type *list, type *elem);\
 extern int sglib_##type##_len(type *list);\
 extern void sglib_##type##_sort(type **list);\


#define SGLIB_DEFINE_SORTED_LIST_FUNCTIONS(type, comparator, next) \
 int sglib_##type##_is_member(type *list, type *elem) {\
   int result;\
   SGLIB_SORTED_LIST_IS_MEMBER(type, list, elem, comparator, next, result);\
   return(result);\
 }\
 type *sglib_##type##_find_member(type *list, type *elem) {\
   type *result;\
   SGLIB_SORTED_LIST_FIND_MEMBER(type, list, elem, comparator, next, result);\
   return(result);\
 }\
 int sglib_##type##_add_if_not_member(type **list, type *elem, type **member) {\
   SGLIB_SORTED_LIST_ADD_IF_NOT_MEMBER(type, *list, elem, comparator, next, *member);\
   return(*member==NULL);\
 }\
 void sglib_##type##_add(type **list, type *elem) {\
   SGLIB_SORTED_LIST_ADD(type, *list, elem, comparator, next);\
 }\
 void sglib_##type##_delete(type **list, type *elem) {\
   SGLIB_SORTED_LIST_DELETE(type, *list, elem, next);\
 }\
 int sglib_##type##_delete_if_member(type **list, type *elem, type **member) {\
   SGLIB_SORTED_LIST_DELETE_IF_MEMBER(type, *list, elem, comparator, next, *member);\
   return(*member!=NULL);\
 }\
 int sglib_##type##_len(type *list) {\
   int res;\
   SGLIB_SORTED_LIST_LEN(type, list, next, res);\
   return(res);\
 }\
 void sglib_##type##_sort(type **list) { \
   SGLIB_LIST_SORT(type, *list, comparator, next);\
 }\


/* ----------------------------- double linked list (draft) (level 1) ------------------ */


#define SGLIB_DEFINE_DL_LIST_PROTOTYPES(type, previous, next) \
 extern void sglib_##type##_add(type **list, type *elem);\
 extern void sglib_##type##_delete(type **list, type *elem);


#define SGLIB_DEFINE_DL_LIST_FUNCTIONS(type, previous, next) \
 void sglib_##type##_add(type **list, type *elem) {\
   SGLIB_DL_LIST_ADD_AT_BEGINNING(type, *list, elem, previous, next);\
 }\
 void sglib_##type##_delete(type **list, type *elem) {\
   SGLIB_DL_LIST_DELETE(type, *list, elem, previous, next);\
 }


/* ----------------------------- sorted double linked list (draft) (level 1) ------------ */


#define SGLIB_DEFINE_SORTED_DL_LIST_PROTOTYPES(type, previous, next, comparator) \
 extern void sglib_##type##_add(type **list, type *elem);\
 extern void sglib_##type##_delete(type **list, type *elem);\
 extern void sglib_##type##_sort(type **list, type *elem);


#define SGLIB_DEFINE_SORTED_DL_LIST_FUNCTIONS(type, previous, next, comparator) \
 void sglib_##type##_add(type **list, type *elem) {\
   SGLIB_SORTED_DL_LIST_ADD(type, *list, elem, comparator, previous, next);\
 }\
 void sglib_##type##_delete(type **list, type *elem) {\
   SGLIB_DL_LIST_DELETE(type, *list, elem, previous, next);\
 }\
 void sglib_##type##_sort(type **list, type *elem) {\
   SGLIB_DL_LIST_SORT(type, *list, comparator, previous, next);\
 }


/* ---------------------------- red-black trees (level 1) ------------------------ 

This implementation requires pointers to left and right sons (no
parent pointer is needed) and one bit of additional information
storing the color of the node. The implementation follows discrepancy
fixing rules from:
http://www.cis.ohio-state.edu/~gurari/course/cis680/cis680Ch11.html

*/

#define SGLIB___RBTREE_FIX_INSERTION_DISCREPANCY(type, tree, leftt, rightt, bits, get_color_bit, set_color_bit, RED, BLACK) {\
  type *t, *tl, *a, *b, *c, *ar, *bl, *br, *cl, *cr;\
  t = *tree;\
  tl = t->leftt;\
  if (t->rightt!=NULL && get_color_bit(t->rightt->bits)==RED) {\
    if (get_color_bit(tl->bits)==RED) {\
      if ((tl->leftt!=NULL && get_color_bit(tl->leftt->bits)==RED) \
          || (tl->rightt!=NULL && get_color_bit(tl->rightt->bits)==RED)) {\
        set_color_bit(t->leftt->bits,BLACK);\
        set_color_bit(t->rightt->bits,BLACK);\
        set_color_bit(t->bits,RED);\
      }\
    }\
  } else {\
    if (get_color_bit(tl->bits)==RED) {\
      if (tl->leftt!=NULL && get_color_bit(tl->leftt->bits)==RED) {\
        a = t; b = tl; c = tl->leftt;\
        br = b->rightt;\
        a->leftt = br;\
        b->leftt = c; b->rightt = a;\
        set_color_bit(a->bits,RED);\
        set_color_bit(b->bits,BLACK);\
        *tree = b;\
      } else if (tl->rightt!=NULL && get_color_bit(tl->rightt->bits)==RED) {\
        a = t; b = tl; ar=a->rightt;\
        bl=b->leftt; c=b->rightt;\
        cl=c->leftt; cr=c->rightt;\
        b->rightt = cl;\
        a->leftt = cr;\
        c->leftt = b;\
        c->rightt = a;\
        set_color_bit(c->bits,BLACK);\
        set_color_bit(a->bits,RED);\
        *tree = c;\
      }\
    }\
  }\
}

#define SGLIB___RBTREE_FIX_DELETION_DISCREPANCY(type, tree, leftt, rightt, bits, get_color_bit, set_color_bit, RED, BLACK, res) {\
  type  *t, *a, *b, *c, *d, *ar, *bl, *br, *cl, *cr, *dl, *dr;\
  t = a = *tree;\
  assert(t!=NULL);\
  ar = a->rightt;\
  b = t->leftt;\
  if (b==NULL) {\
    assert(get_color_bit(t->bits)==RED);\
    set_color_bit(t->bits,BLACK);\
    res = 0;\
  } else {\
    bl = b->leftt;\
    br = b->rightt;\
    if (get_color_bit(b->bits)==RED) {\
      if (br==NULL) {\
        *tree = b;\
        set_color_bit(b->bits,BLACK);\
        b->rightt = a;\
        a->leftt = br;\
      } else {\
        c = br;\
        assert(c!=NULL && get_color_bit(c->bits)==BLACK);\
        cl = c->leftt;\
        cr = c->rightt;\
        if ((cl==NULL||get_color_bit(cl->bits)==BLACK) && (cr==NULL||get_color_bit(cr->bits)==BLACK)) {\
          *tree = b;\
          b->rightt = a;\
          set_color_bit(b->bits,BLACK);\
          a->leftt = c;\
          set_color_bit(c->bits,RED);\
          res = 0;\
        } else if (cl!=NULL && get_color_bit(cl->bits)==RED) {\
          if (cr!=NULL && get_color_bit(cr->bits)==RED) {\
            d = cr;\
            dl = d->leftt;\
            dr = d->rightt;\
            *tree = d;\
            set_color_bit(d->bits,BLACK);\
            d->leftt = b;\
            c->rightt = dl;\
            d->rightt = a;\
            a->leftt = dr;\
            res = 0;\
          } else {\
            *tree = c;\
            c->leftt = b;\
            c->rightt = a;\
            b->leftt = bl;\
            b->rightt = cl;\
            a->leftt = cr;\
            set_color_bit(cl->bits,BLACK);\
            res = 0;\
          }\
        } else if (cr!=NULL && get_color_bit(cr->bits)==RED) {\
          assert(cl==NULL || get_color_bit(cl->bits)==BLACK);\
          d = cr;\
          dl = d->leftt;\
          dr = d->rightt;\
          *tree = d;\
          set_color_bit(d->bits,BLACK);\
          d->leftt = b;\
          c->rightt = dl;\
          d->rightt = a;\
          a->leftt = dr;\
          res = 0;\
        } else {\
          assert(0);\
          res = 0;\
        }\
      }\
    } else {\
      if ((bl==NULL || get_color_bit(bl->bits)==BLACK) && (br==NULL || get_color_bit(br->bits)==BLACK)) {\
        res = (get_color_bit(a->bits)==BLACK);\
        set_color_bit(a->bits,BLACK);\
        set_color_bit(b->bits,RED);\
      } else if (bl!=NULL && get_color_bit(bl->bits)==RED) {\
        if (br==NULL || get_color_bit(br->bits)==BLACK) {\
          *tree = b;\
          set_color_bit(b->bits,get_color_bit(a->bits));\
          set_color_bit(a->bits,BLACK);\
          b->rightt = a;\
          a->leftt = br;\
          set_color_bit(bl->bits,BLACK);\
          res = 0;\
        } else {\
          assert(bl!=NULL);\
          assert(br!=NULL);\
          assert(get_color_bit(bl->bits)==RED);\
          assert(get_color_bit(br->bits)==RED);\
          c = br;\
          cl = c->leftt;\
          cr = c->rightt;\
          *tree = c;\
          set_color_bit(c->bits,get_color_bit(a->bits));\
          set_color_bit(a->bits,BLACK);\
          c->leftt = b;\
          c->rightt = a;\
          b->rightt = cl;\
          a->leftt = cr;\
          res = 0;\
        }\
      } else {\
        assert(br!=NULL && get_color_bit(br->bits)==RED);\
        c = br;\
        cl = c->leftt;\
        cr = c->rightt;\
        *tree = c;\
        set_color_bit(c->bits,get_color_bit(a->bits));\
        set_color_bit(a->bits,BLACK);\
        c->leftt = b;\
        c->rightt = a;\
        b->rightt = cl;\
        a->leftt = cr;\
        res = 0;\
      }\
    }\
  }\
}


#define SGLIB_DEFINE_RBTREE_FUNCTIONS_GENERAL(type, left, right, bits, get_color_bit, set_color_bit, comparator, RED, BLACK) \
static void sglib___##type##_fix_left_insertion_discrepancy(type **tree) {\
  SGLIB___RBTREE_FIX_INSERTION_DISCREPANCY(type, tree, left, right, bits, get_color_bit, set_color_bit, RED, BLACK);\
}\
\
static void sglib___##type##_fix_right_insertion_discrepancy(type **tree) {\
  SGLIB___RBTREE_FIX_INSERTION_DISCREPANCY(type, tree, right, left, bits, get_color_bit, set_color_bit, RED, BLACK);\
}\
\
static int sglib___##type##_fix_left_deletion_discrepancy(type **tree) {\
  int       res;\
  SGLIB___RBTREE_FIX_DELETION_DISCREPANCY(type, tree, right, left, bits, get_color_bit, set_color_bit, RED, BLACK, res);\
  return(res);\
}\
\
static int sglib___##type##_fix_right_deletion_discrepancy(type **tree) {\
  int       res;\
  SGLIB___RBTREE_FIX_DELETION_DISCREPANCY(type, tree, left, right, bits, get_color_bit, set_color_bit, RED, BLACK, res);\
  return(res);\
}\
\
static void sglib___##type##_add_recursive(type **tree, type *elem) {\
  int cmp;\
  type *t;\
  t = *tree;\
  if (t == NULL) {\
    set_color_bit(elem->bits,RED);\
    *tree =elem;\
  } else {\
    cmp = comparator(elem, t);\
    if (cmp < 0 || (cmp==0 && elem<t)) {\
      sglib___##type##_add_recursive(&t->left, elem);\
      if (get_color_bit(t->bits)==BLACK) sglib___##type##_fix_left_insertion_discrepancy(tree);\
    } else {\
      sglib___##type##_add_recursive(&t->right, elem);\
      if (get_color_bit(t->bits)==BLACK) sglib___##type##_fix_right_insertion_discrepancy(tree);\
    }\
  }\
}\
\
static int sglib___##type##_delete_rightmost_leaf(type **tree, type **theLeaf) {\
  type  *t;\
  int       res, deepDecreased;\
  t = *tree;\
  res = 0;\
  assert(t!=NULL);\
  if (t->right == NULL) {\
    *theLeaf = t;\
    if (t->left!=NULL) {\
      if (get_color_bit(t->bits)==BLACK && get_color_bit(t->left->bits)==BLACK) res = 1;\
      set_color_bit(t->left->bits,BLACK);\
      *tree = t->left;\
    } else {\
      *tree = NULL;\
      res = (get_color_bit(t->bits)==BLACK);\
    }\
  } else {\
    deepDecreased = sglib___##type##_delete_rightmost_leaf(&t->right, theLeaf);\
    if (deepDecreased) res = sglib___##type##_fix_right_deletion_discrepancy(tree);\
  }\
  return(res);\
}\
\
int sglib___##type##_delete_recursive(type **tree, type *elem) {\
  type  *t, *theLeaf;\
  int       cmp, res, deepDecreased;\
  t = *tree;\
  res = 0;\
  if (t==NULL) {\
    assert(0 && "The element to delete not found in the tree,  use 'delete_if_member'"!=NULL);\
  } else {\
    cmp = comparator(elem, t);\
    if (cmp < 0 || (cmp==0 && elem<t)) {\
      deepDecreased = sglib___##type##_delete_recursive(&t->left, elem);\
      if (deepDecreased) {\
        res = sglib___##type##_fix_left_deletion_discrepancy(tree);\
      }\
    } else if (cmp > 0  || (cmp==0 && elem>t)) {\
      deepDecreased = sglib___##type##_delete_recursive(&t->right, elem);\
      if (deepDecreased) {\
        res = sglib___##type##_fix_right_deletion_discrepancy(tree);\
      }\
    } else {\
      assert(elem==t && "Deleting an element which is non member of the tree, use 'delete_if_member'"!=NULL);\
      if (t->left == NULL) {\
        if (t->right == NULL) {\
          /* a leaf, delete, it; */\
          *tree = NULL;\
          res = (get_color_bit(t->bits)==BLACK);\
        } else {\
          if (get_color_bit(t->bits)==0 && get_color_bit(t->right->bits)==0) res = 1;\
          set_color_bit(t->right->bits,BLACK);\
          *tree = t->right;\
        }\
      } else {\
        /* propagate deletion until righmost leaf of left subtree */\
        deepDecreased = sglib___##type##_delete_rightmost_leaf(&t->left, &theLeaf);\
        theLeaf->left = t->left;\
        theLeaf->right = t->right;\
        set_color_bit(theLeaf->bits,get_color_bit(t->bits));\
        *tree = theLeaf;\
        if (deepDecreased) res = sglib___##type##_fix_left_deletion_discrepancy(tree);\
      }\
    }\
  }\
  return(res);\
}\
\
void sglib_##type##_add(type **tree, type *elem) {\
  elem->left = elem->right = NULL;\
  sglib___##type##_add_recursive(tree, elem);\
  set_color_bit((*tree)->bits,BLACK);\
}\
\
void sglib_##type##_delete(type **tree, type *elem) {\
  sglib___##type##_delete_recursive(tree, elem);\
  if (*tree!=NULL) set_color_bit((*tree)->bits,BLACK);\
}\
\
type *sglib_##type##_find_member(type *t, type *elem) {\
  int       cmp;\
sglib_##type##_find_member_start_point:\
  if (t==NULL) return(NULL);\
  cmp = comparator(elem, t);\
  if (cmp < 0) {\
    t = t->left;\
    goto sglib_##type##_find_member_start_point;\
  } else if (cmp > 0) {\
    t = t->right;\
    goto sglib_##type##_find_member_start_point;\
  } else {\
    return(t);\
  }\
}\
\
int sglib_##type##_is_member(type *t, type *elem) {\
  int       cmp;\
sglib_##type##_is_member_start_point:\
  if (t==NULL) return(0);\
  cmp = comparator(elem, t);\
  if (cmp < 0 || (cmp==0 && elem<t)) {\
    t = t->left;\
    goto sglib_##type##_is_member_start_point;\
  } else if (cmp > 0 || (cmp==0 && elem>t)) {\
    t = t->right;\
    goto sglib_##type##_is_member_start_point;\
  } else {\
    assert(t == elem);\
    return(1);\
  }\
}\
\
int sglib_##type##_delete_if_member(type **tree, type *elem, type **memb) {\
  if ((*memb=sglib_##type##_find_member(*tree, elem))!=NULL) {\
    sglib_##type##_delete(tree, *memb);\
    return(1);\
  } else {\
    return(0);\
  }\
}\
int sglib_##type##_add_if_not_member(type **tree, type *elem, type **memb) {\
  if ((*memb=sglib_##type##_find_member(*tree, elem))==NULL) {\
    sglib_##type##_add(tree, elem);\
    return(1);\
  } else {\
    return(0);\
  }\
}\
\
static void sglib___##type##_consistency_check_recursive(type *t, int *pathdeep, int cdeep) {\
  if (t==NULL) {\
    if (*pathdeep < 0) *pathdeep = cdeep;\
    else assert(*pathdeep == cdeep);\
  } else {\
    if (t->left!=NULL) assert(comparator(t->left, t) <= 0);\
    if (t->right!=NULL) assert(comparator(t, t->right) <= 0);\
    if (get_color_bit(t->bits) == RED) {\
      assert(t->left == NULL || get_color_bit(t->left->bits)==BLACK);\
      assert(t->right == NULL || get_color_bit(t->right->bits)==BLACK);\
      sglib___##type##_consistency_check_recursive(t->left, pathdeep, cdeep);\
      sglib___##type##_consistency_check_recursive(t->right, pathdeep, cdeep);\
    } else {\
      sglib___##type##_consistency_check_recursive(t->left, pathdeep, cdeep+1);\
      sglib___##type##_consistency_check_recursive(t->right, pathdeep, cdeep+1);      \
    }\
  }\
}\
\
void sglib___##type##_consistency_check(type *t) {\
  int pathDeep;\
  assert(t==NULL || get_color_bit(t->bits) == BLACK);\
  pathDeep = -1;\
  sglib___##type##_consistency_check_recursive(t, &pathDeep, 0);\
}

#define SGLIB_DEFINE_RBTREE_PROTOTYPES(type, left, right, colorbit, comparator, RED, BLACK) \
 extern void sglib___##type##_consistency_check(type *t); \
 extern void sglib_##type##_add(type **tree, type *elem); \
 extern int sglib_##type##_add_if_not_member(type **tree, type *elem, type **memb); \
 extern void sglib_##type##_delete(type **tree, type *elem); \
 extern int sglib_##type##_delete_if_member(type **tree, type *elem, type **memb); \
 extern int sglib_##type##_is_member(type *t, type *elem); \
 extern type *sglib_##type##_find_member(type *t, type *elem); \
 extern void sglib___##type##_consistency_check(type *t); \


#define SGLIB_DEFINE_RBTREE_FUNCTIONS(type, left, right, colorbit, comparator, RED, BLACK) \
  SGLIB_DEFINE_RBTREE_FUNCTIONS_GENERAL(type, left, right, colorbit, SGLIB___GET_VALUE, SGLIB___SET_VALUE, comparator, RED, BLACK)


/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */
/* -                          SUPPLEMENTARY DEFINITIONS                       - */
/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */


#define SGLIB___GET_VALUE(x) (x)
#define SGLIB___SET_VALUE(x, value) {(x) = (value);}
#define SGLIB_ARRAY_ELEMENTS_EXCHANGER(type, a, i, j) {type _ae_tmp_; _ae_tmp_=(a)[(i)]; (a)[(i)]=(a)[(j)]; (a)[(j)]= _ae_tmp_;}


#define SGLIB_NUMERIC_COMPARATOR(x, y) ((int)((x) - (y)))
#define SGLIB_REVERSE_NUMERIC_COMPARATOR(x, y) ((int)((y) - (x)))

#ifndef SGLIB_MAX_TREE_DEEP
#define SGLIB_MAX_TREE_DEEP 128
#endif

#endif /* _SGLIB__H_ */

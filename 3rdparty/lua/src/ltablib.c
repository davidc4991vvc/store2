/*
<<<<<<< HEAD
** $Id: ltablib.c,v 1.79 2014/11/02 19:19:04 roberto Exp $
=======
** $Id: ltablib.c,v 1.93 2016/02/25 19:41:54 roberto Exp $
>>>>>>> upstream/master
** Library for Table Manipulation
** See Copyright Notice in lua.h
*/

#define ltablib_c
#define LUA_LIB

#include "lprefix.h"


#include <limits.h>
#include <stddef.h>
<<<<<<< HEAD
=======
#include <string.h>
>>>>>>> upstream/master

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


<<<<<<< HEAD

/*
** Structure with table-access functions
*/
typedef struct {
  int (*geti) (lua_State *L, int idx, lua_Integer n);
  void (*seti) (lua_State *L, int idx, lua_Integer n);
} TabA;


/*
** Check that 'arg' has a table and set access functions in 'ta' to raw
** or non-raw according to the presence of corresponding metamethods.
*/
static void checktab (lua_State *L, int arg, TabA *ta) {
  ta->geti = NULL; ta->seti = NULL;
  if (lua_getmetatable(L, arg)) {
    lua_pushliteral(L, "__index");  /* 'index' metamethod */
    if (lua_rawget(L, -2) != LUA_TNIL)
      ta->geti = lua_geti;
    lua_pushliteral(L, "__newindex");  /* 'newindex' metamethod */
    if (lua_rawget(L, -3) != LUA_TNIL)
      ta->seti = lua_seti;
    lua_pop(L, 3);  /* pop metatable plus both metamethods */
  }
  if (ta->geti == NULL || ta->seti == NULL) {
    luaL_checktype(L, arg, LUA_TTABLE);  /* must be table for raw methods */
    if (ta->geti == NULL) ta->geti = lua_rawgeti;
    if (ta->seti == NULL) ta->seti = lua_rawseti;
=======
/*
** Operations that an object must define to mimic a table
** (some functions only need some of them)
*/
#define TAB_R	1			/* read */
#define TAB_W	2			/* write */
#define TAB_L	4			/* length */
#define TAB_RW	(TAB_R | TAB_W)		/* read/write */


#define aux_getn(L,n,w)	(checktab(L, n, (w) | TAB_L), luaL_len(L, n))


static int checkfield (lua_State *L, const char *key, int n) {
  lua_pushstring(L, key);
  return (lua_rawget(L, -n) != LUA_TNIL);
}


/*
** Check that 'arg' either is a table or can behave like one (that is,
** has a metatable with the required metamethods)
*/
static void checktab (lua_State *L, int arg, int what) {
  if (lua_type(L, arg) != LUA_TTABLE) {  /* is it not a table? */
    int n = 1;  /* number of elements to pop */
    if (lua_getmetatable(L, arg) &&  /* must have metatable */
        (!(what & TAB_R) || checkfield(L, "__index", ++n)) &&
        (!(what & TAB_W) || checkfield(L, "__newindex", ++n)) &&
        (!(what & TAB_L) || checkfield(L, "__len", ++n))) {
      lua_pop(L, n);  /* pop metatable and tested metamethods */
    }
    else
      luaL_checktype(L, arg, LUA_TTABLE);  /* force an error */
>>>>>>> upstream/master
  }
}


<<<<<<< HEAD
#define aux_getn(L,n,ta)	(checktab(L, n, ta), luaL_len(L, n))


=======
>>>>>>> upstream/master
#if defined(LUA_COMPAT_MAXN)
static int maxn (lua_State *L) {
  lua_Number max = 0;
  luaL_checktype(L, 1, LUA_TTABLE);
  lua_pushnil(L);  /* first key */
  while (lua_next(L, 1)) {
    lua_pop(L, 1);  /* remove value */
    if (lua_type(L, -1) == LUA_TNUMBER) {
      lua_Number v = lua_tonumber(L, -1);
      if (v > max) max = v;
    }
  }
  lua_pushnumber(L, max);
  return 1;
}
#endif


static int tinsert (lua_State *L) {
<<<<<<< HEAD
  TabA ta;
  lua_Integer e = aux_getn(L, 1, &ta) + 1;  /* first empty element */
=======
  lua_Integer e = aux_getn(L, 1, TAB_RW) + 1;  /* first empty element */
>>>>>>> upstream/master
  lua_Integer pos;  /* where to insert new element */
  switch (lua_gettop(L)) {
    case 2: {  /* called with only 2 arguments */
      pos = e;  /* insert new element at the end */
      break;
    }
    case 3: {
      lua_Integer i;
      pos = luaL_checkinteger(L, 2);  /* 2nd argument is the position */
      luaL_argcheck(L, 1 <= pos && pos <= e, 2, "position out of bounds");
      for (i = e; i > pos; i--) {  /* move up elements */
<<<<<<< HEAD
        (*ta.geti)(L, 1, i - 1);
        (*ta.seti)(L, 1, i);  /* t[i] = t[i - 1] */
=======
        lua_geti(L, 1, i - 1);
        lua_seti(L, 1, i);  /* t[i] = t[i - 1] */
>>>>>>> upstream/master
      }
      break;
    }
    default: {
      return luaL_error(L, "wrong number of arguments to 'insert'");
    }
  }
<<<<<<< HEAD
  (*ta.seti)(L, 1, pos);  /* t[pos] = v */
=======
  lua_seti(L, 1, pos);  /* t[pos] = v */
>>>>>>> upstream/master
  return 0;
}


static int tremove (lua_State *L) {
<<<<<<< HEAD
  TabA ta;
  lua_Integer size = aux_getn(L, 1, &ta);
  lua_Integer pos = luaL_optinteger(L, 2, size);
  if (pos != size)  /* validate 'pos' if given */
    luaL_argcheck(L, 1 <= pos && pos <= size + 1, 1, "position out of bounds");
  (*ta.geti)(L, 1, pos);  /* result = t[pos] */
  for ( ; pos < size; pos++) {
    (*ta.geti)(L, 1, pos + 1);
    (*ta.seti)(L, 1, pos);  /* t[pos] = t[pos + 1] */
  }
  lua_pushnil(L);
  (*ta.seti)(L, 1, pos);  /* t[pos] = nil */
=======
  lua_Integer size = aux_getn(L, 1, TAB_RW);
  lua_Integer pos = luaL_optinteger(L, 2, size);
  if (pos != size)  /* validate 'pos' if given */
    luaL_argcheck(L, 1 <= pos && pos <= size + 1, 1, "position out of bounds");
  lua_geti(L, 1, pos);  /* result = t[pos] */
  for ( ; pos < size; pos++) {
    lua_geti(L, 1, pos + 1);
    lua_seti(L, 1, pos);  /* t[pos] = t[pos + 1] */
  }
  lua_pushnil(L);
  lua_seti(L, 1, pos);  /* t[pos] = nil */
>>>>>>> upstream/master
  return 1;
}


<<<<<<< HEAD
static int tmove (lua_State *L) {
  TabA ta;
=======
/*
** Copy elements (1[f], ..., 1[e]) into (tt[t], tt[t+1], ...). Whenever
** possible, copy in increasing order, which is better for rehashing.
** "possible" means destination after original range, or smaller
** than origin, or copying to another table.
*/
static int tmove (lua_State *L) {
>>>>>>> upstream/master
  lua_Integer f = luaL_checkinteger(L, 2);
  lua_Integer e = luaL_checkinteger(L, 3);
  lua_Integer t = luaL_checkinteger(L, 4);
  int tt = !lua_isnoneornil(L, 5) ? 5 : 1;  /* destination table */
<<<<<<< HEAD
  /* the following restriction avoids several problems with overflows */
  luaL_argcheck(L, f > 0, 2, "initial position must be positive");
  if (e >= f) {  /* otherwise, nothing to move */
    lua_Integer n, i;
    ta.geti = (luaL_getmetafield(L, 1, "__index") == LUA_TNIL)
      ? (luaL_checktype(L, 1, LUA_TTABLE), lua_rawgeti)
      : lua_geti;
    ta.seti = (luaL_getmetafield(L, tt, "__newindex") == LUA_TNIL)
      ? (luaL_checktype(L, tt, LUA_TTABLE), lua_rawseti)
      : lua_seti;
    n = e - f + 1;  /* number of elements to move */
    if (t > f) {
      for (i = n - 1; i >= 0; i--) {
        (*ta.geti)(L, 1, f + i);
        (*ta.seti)(L, tt, t + i);
      }
    }
    else {
      for (i = 0; i < n; i++) {
        (*ta.geti)(L, 1, f + i);
        (*ta.seti)(L, tt, t + i);
      }
    }
  }
  lua_pushvalue(L, tt);  /* return "to table" */
=======
  checktab(L, 1, TAB_R);
  checktab(L, tt, TAB_W);
  if (e >= f) {  /* otherwise, nothing to move */
    lua_Integer n, i;
    luaL_argcheck(L, f > 0 || e < LUA_MAXINTEGER + f, 3,
                  "too many elements to move");
    n = e - f + 1;  /* number of elements to move */
    luaL_argcheck(L, t <= LUA_MAXINTEGER - n + 1, 4,
                  "destination wrap around");
    if (t > e || t <= f || (tt != 1 && !lua_compare(L, 1, tt, LUA_OPEQ))) {
      for (i = 0; i < n; i++) {
        lua_geti(L, 1, f + i);
        lua_seti(L, tt, t + i);
      }
    }
    else {
      for (i = n - 1; i >= 0; i--) {
        lua_geti(L, 1, f + i);
        lua_seti(L, tt, t + i);
      }
    }
  }
  lua_pushvalue(L, tt);  /* return destination table */
>>>>>>> upstream/master
  return 1;
}


<<<<<<< HEAD
static void addfield (lua_State *L, luaL_Buffer *b, TabA *ta, lua_Integer i) {
  (*ta->geti)(L, 1, i);
=======
static void addfield (lua_State *L, luaL_Buffer *b, lua_Integer i) {
  lua_geti(L, 1, i);
>>>>>>> upstream/master
  if (!lua_isstring(L, -1))
    luaL_error(L, "invalid value (%s) at index %d in table for 'concat'",
                  luaL_typename(L, -1), i);
  luaL_addvalue(b);
}


static int tconcat (lua_State *L) {
<<<<<<< HEAD
  TabA ta;
  luaL_Buffer b;
  size_t lsep;
  lua_Integer i, last;
  const char *sep = luaL_optlstring(L, 2, "", &lsep);
  checktab(L, 1, &ta);
  i = luaL_optinteger(L, 3, 1);
  last = luaL_opt(L, luaL_checkinteger, 4, luaL_len(L, 1));
  luaL_buffinit(L, &b);
  for (; i < last; i++) {
    addfield(L, &b, &ta, i);
    luaL_addlstring(&b, sep, lsep);
  }
  if (i == last)  /* add last value (if interval was not empty) */
    addfield(L, &b, &ta, i);
=======
  luaL_Buffer b;
  lua_Integer last = aux_getn(L, 1, TAB_R);
  size_t lsep;
  const char *sep = luaL_optlstring(L, 2, "", &lsep);
  lua_Integer i = luaL_optinteger(L, 3, 1);
  last = luaL_optinteger(L, 4, last);
  luaL_buffinit(L, &b);
  for (; i < last; i++) {
    addfield(L, &b, i);
    luaL_addlstring(&b, sep, lsep);
  }
  if (i == last)  /* add last value (if interval was not empty) */
    addfield(L, &b, i);
>>>>>>> upstream/master
  luaL_pushresult(&b);
  return 1;
}


/*
** {======================================================
** Pack/unpack
** =======================================================
*/

static int pack (lua_State *L) {
  int i;
  int n = lua_gettop(L);  /* number of elements to pack */
  lua_createtable(L, n, 1);  /* create result table */
  lua_insert(L, 1);  /* put it at index 1 */
  for (i = n; i >= 1; i--)  /* assign elements */
<<<<<<< HEAD
    lua_rawseti(L, 1, i);
=======
    lua_seti(L, 1, i);
>>>>>>> upstream/master
  lua_pushinteger(L, n);
  lua_setfield(L, 1, "n");  /* t.n = number of elements */
  return 1;  /* return table */
}


static int unpack (lua_State *L) {
<<<<<<< HEAD
  TabA ta;
  lua_Integer i, e;
  lua_Unsigned n;
  checktab(L, 1, &ta);
  i = luaL_optinteger(L, 2, 1);
  e = luaL_opt(L, luaL_checkinteger, 3, luaL_len(L, 1));
=======
  lua_Unsigned n;
  lua_Integer i = luaL_optinteger(L, 2, 1);
  lua_Integer e = luaL_opt(L, luaL_checkinteger, 3, luaL_len(L, 1));
>>>>>>> upstream/master
  if (i > e) return 0;  /* empty range */
  n = (lua_Unsigned)e - i;  /* number of elements minus 1 (avoid overflows) */
  if (n >= (unsigned int)INT_MAX  || !lua_checkstack(L, (int)(++n)))
    return luaL_error(L, "too many results to unpack");
<<<<<<< HEAD
  do {  /* must have at least one element */
    (*ta.geti)(L, 1, i);  /* push arg[i..e] */
  } while (i++ < e); 

=======
  for (; i < e; i++) {  /* push arg[i..e - 1] (to avoid overflows) */
    lua_geti(L, 1, i);
  }
  lua_geti(L, 1, e);  /* push last element */
>>>>>>> upstream/master
  return (int)n;
}

/* }====================================================== */



/*
** {======================================================
** Quicksort
** (based on 'Algorithms in MODULA-3', Robert Sedgewick;
**  Addison-Wesley, 1993.)
** =======================================================
*/


<<<<<<< HEAD
static void set2 (lua_State *L, TabA *ta, int i, int j) {
  (*ta->seti)(L, 1, i);
  (*ta->seti)(L, 1, j);
}

static int sort_comp (lua_State *L, int a, int b) {
  if (!lua_isnil(L, 2)) {  /* function? */
    int res;
    lua_pushvalue(L, 2);
    lua_pushvalue(L, a-1);  /* -1 to compensate function */
    lua_pushvalue(L, b-2);  /* -2 to compensate function and 'a' */
    lua_call(L, 2, 1);
    res = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return res;
  }
  else  /* a < b? */
    return lua_compare(L, a, b, LUA_OPLT);
}

static void auxsort (lua_State *L, TabA *ta, int l, int u) {
  while (l < u) {  /* for tail recursion */
    int i, j;
    /* sort elements a[l], a[(l+u)/2] and a[u] */
    (*ta->geti)(L, 1, l);
    (*ta->geti)(L, 1, u);
    if (sort_comp(L, -1, -2))  /* a[u] < a[l]? */
      set2(L, ta, l, u);  /* swap a[l] - a[u] */
    else
      lua_pop(L, 2);
    if (u-l == 1) break;  /* only 2 elements */
    i = (l+u)/2;
    (*ta->geti)(L, 1, i);
    (*ta->geti)(L, 1, l);
    if (sort_comp(L, -2, -1))  /* a[i]<a[l]? */
      set2(L, ta, i, l);
    else {
      lua_pop(L, 1);  /* remove a[l] */
      (*ta->geti)(L, 1, u);
      if (sort_comp(L, -1, -2))  /* a[u]<a[i]? */
        set2(L, ta, i, u);
      else
        lua_pop(L, 2);
    }
    if (u-l == 2) break;  /* only 3 elements */
    (*ta->geti)(L, 1, i);  /* Pivot */
    lua_pushvalue(L, -1);
    (*ta->geti)(L, 1, u-1);
    set2(L, ta, i, u-1);
    /* a[l] <= P == a[u-1] <= a[u], only need to sort from l+1 to u-2 */
    i = l; j = u-1;
    for (;;) {  /* invariant: a[l..i] <= P <= a[j..u] */
      /* repeat ++i until a[i] >= P */
      while ((*ta->geti)(L, 1, ++i), sort_comp(L, -1, -2)) {
        if (i>=u) luaL_error(L, "invalid order function for sorting");
        lua_pop(L, 1);  /* remove a[i] */
      }
      /* repeat --j until a[j] <= P */
      while ((*ta->geti)(L, 1, --j), sort_comp(L, -3, -1)) {
        if (j<=l) luaL_error(L, "invalid order function for sorting");
        lua_pop(L, 1);  /* remove a[j] */
      }
      if (j<i) {
        lua_pop(L, 3);  /* pop pivot, a[i], a[j] */
        break;
      }
      set2(L, ta, i, j);
    }
    (*ta->geti)(L, 1, u-1);
    (*ta->geti)(L, 1, i);
    set2(L, ta, u-1, i);  /* swap pivot (a[u-1]) with a[i] */
    /* a[l..i-1] <= a[i] == P <= a[i+1..u] */
    /* adjust so that smaller half is in [j..i] and larger one in [l..u] */
    if (i-l < u-i) {
      j=l; i=i-1; l=i+2;
    }
    else {
      j=i+1; i=u; u=j-2;
    }
    auxsort(L, ta, j, i);  /* call recursively the smaller one */
  }  /* repeat the routine for the larger one */
}

static int sort (lua_State *L) {
  TabA ta;
  int n = (int)aux_getn(L, 1, &ta);
  luaL_checkstack(L, 50, "");  /* assume array is smaller than 2^50 */
  if (!lua_isnoneornil(L, 2))  /* is there a 2nd argument? */
    luaL_checktype(L, 2, LUA_TFUNCTION);
  lua_settop(L, 2);  /* make sure there are two arguments */
  auxsort(L, &ta, 1, n);
=======
/* type for array indices */
typedef unsigned int IdxT;


/*
** Produce a "random" 'unsigned int' to randomize pivot choice. This
** macro is used only when 'sort' detects a big imbalance in the result
** of a partition. (If you don't want/need this "randomness", ~0 is a
** good choice.)
*/
#if !defined(l_randomizePivot)		/* { */

#include <time.h>

/* size of 'e' measured in number of 'unsigned int's */
#define sof(e)		(sizeof(e) / sizeof(unsigned int))

/*
** Use 'time' and 'clock' as sources of "randomness". Because we don't
** know the types 'clock_t' and 'time_t', we cannot cast them to
** anything without risking overflows. A safe way to use their values
** is to copy them to an array of a known type and use the array values.
*/
static unsigned int l_randomizePivot (void) {
  clock_t c = clock();
  time_t t = time(NULL);
  unsigned int buff[sof(c) + sof(t)];
  unsigned int i, rnd = 0;
  memcpy(buff, &c, sof(c) * sizeof(unsigned int));
  memcpy(buff + sof(c), &t, sof(t) * sizeof(unsigned int));
  for (i = 0; i < sof(buff); i++)
    rnd += buff[i];
  return rnd;
}

#endif					/* } */


/* arrays larger than 'RANLIMIT' may use randomized pivots */
#define RANLIMIT	100u


static void set2 (lua_State *L, IdxT i, IdxT j) {
  lua_seti(L, 1, i);
  lua_seti(L, 1, j);
}


/*
** Return true iff value at stack index 'a' is less than the value at
** index 'b' (according to the order of the sort).
*/
static int sort_comp (lua_State *L, int a, int b) {
  if (lua_isnil(L, 2))  /* no function? */
    return lua_compare(L, a, b, LUA_OPLT);  /* a < b */
  else {  /* function */
    int res;
    lua_pushvalue(L, 2);    /* push function */
    lua_pushvalue(L, a-1);  /* -1 to compensate function */
    lua_pushvalue(L, b-2);  /* -2 to compensate function and 'a' */
    lua_call(L, 2, 1);      /* call function */
    res = lua_toboolean(L, -1);  /* get result */
    lua_pop(L, 1);          /* pop result */
    return res;
  }
}


/*
** Does the partition: Pivot P is at the top of the stack.
** precondition: a[lo] <= P == a[up-1] <= a[up],
** so it only needs to do the partition from lo + 1 to up - 2.
** Pos-condition: a[lo .. i - 1] <= a[i] == P <= a[i + 1 .. up]
** returns 'i'.
*/
static IdxT partition (lua_State *L, IdxT lo, IdxT up) {
  IdxT i = lo;  /* will be incremented before first use */
  IdxT j = up - 1;  /* will be decremented before first use */
  /* loop invariant: a[lo .. i] <= P <= a[j .. up] */
  for (;;) {
    /* next loop: repeat ++i while a[i] < P */
    while (lua_geti(L, 1, ++i), sort_comp(L, -1, -2)) {
      if (i == up - 1)  /* a[i] < P  but a[up - 1] == P  ?? */
        luaL_error(L, "invalid order function for sorting");
      lua_pop(L, 1);  /* remove a[i] */
    }
    /* after the loop, a[i] >= P and a[lo .. i - 1] < P */
    /* next loop: repeat --j while P < a[j] */
    while (lua_geti(L, 1, --j), sort_comp(L, -3, -1)) {
      if (j < i)  /* j < i  but  a[j] > P ?? */
        luaL_error(L, "invalid order function for sorting");
      lua_pop(L, 1);  /* remove a[j] */
    }
    /* after the loop, a[j] <= P and a[j + 1 .. up] >= P */
    if (j < i) {  /* no elements out of place? */
      /* a[lo .. i - 1] <= P <= a[j + 1 .. i .. up] */
      lua_pop(L, 1);  /* pop a[j] */
      /* swap pivot (a[up - 1]) with a[i] to satisfy pos-condition */
      set2(L, up - 1, i);
      return i;
    }
    /* otherwise, swap a[i] - a[j] to restore invariant and repeat */
    set2(L, i, j);
  }
}


/*
** Choose an element in the middle (2nd-3th quarters) of [lo,up]
** "randomized" by 'rnd'
*/
static IdxT choosePivot (IdxT lo, IdxT up, unsigned int rnd) {
  IdxT r4 = (up - lo) / 4;  /* range/4 */
  IdxT p = rnd % (r4 * 2) + (lo + r4);
  lua_assert(lo + r4 <= p && p <= up - r4);
  return p;
}


/*
** QuickSort algorithm (recursive function)
*/
static void auxsort (lua_State *L, IdxT lo, IdxT up,
                                   unsigned int rnd) {
  while (lo < up) {  /* loop for tail recursion */
    IdxT p;  /* Pivot index */
    IdxT n;  /* to be used later */
    /* sort elements 'lo', 'p', and 'up' */
    lua_geti(L, 1, lo);
    lua_geti(L, 1, up);
    if (sort_comp(L, -1, -2))  /* a[up] < a[lo]? */
      set2(L, lo, up);  /* swap a[lo] - a[up] */
    else
      lua_pop(L, 2);  /* remove both values */
    if (up - lo == 1)  /* only 2 elements? */
      return;  /* already sorted */
    if (up - lo < RANLIMIT || rnd == 0)  /* small interval or no randomize? */
      p = (lo + up)/2;  /* middle element is a good pivot */
    else  /* for larger intervals, it is worth a random pivot */
      p = choosePivot(lo, up, rnd);
    lua_geti(L, 1, p);
    lua_geti(L, 1, lo);
    if (sort_comp(L, -2, -1))  /* a[p] < a[lo]? */
      set2(L, p, lo);  /* swap a[p] - a[lo] */
    else {
      lua_pop(L, 1);  /* remove a[lo] */
      lua_geti(L, 1, up);
      if (sort_comp(L, -1, -2))  /* a[up] < a[p]? */
        set2(L, p, up);  /* swap a[up] - a[p] */
      else
        lua_pop(L, 2);
    }
    if (up - lo == 2)  /* only 3 elements? */
      return;  /* already sorted */
    lua_geti(L, 1, p);  /* get middle element (Pivot) */
    lua_pushvalue(L, -1);  /* push Pivot */
    lua_geti(L, 1, up - 1);  /* push a[up - 1] */
    set2(L, p, up - 1);  /* swap Pivot (a[p]) with a[up - 1] */
    p = partition(L, lo, up);
    /* a[lo .. p - 1] <= a[p] == P <= a[p + 1 .. up] */
    if (p - lo < up - p) {  /* lower interval is smaller? */
      auxsort(L, lo, p - 1, rnd);  /* call recursively for lower interval */
      n = p - lo;  /* size of smaller interval */
      lo = p + 1;  /* tail call for [p + 1 .. up] (upper interval) */
    }
    else {
      auxsort(L, p + 1, up, rnd);  /* call recursively for upper interval */
      n = up - p;  /* size of smaller interval */
      up = p - 1;  /* tail call for [lo .. p - 1]  (lower interval) */
    }
    if ((up - lo) / 128 > n) /* partition too imbalanced? */
      rnd = l_randomizePivot();  /* try a new randomization */
  }  /* tail call auxsort(L, lo, up, rnd) */
}


static int sort (lua_State *L) {
  lua_Integer n = aux_getn(L, 1, TAB_RW);
  if (n > 1) {  /* non-trivial interval? */
    luaL_argcheck(L, n < INT_MAX, 1, "array too big");
    if (!lua_isnoneornil(L, 2))  /* is there a 2nd argument? */
      luaL_checktype(L, 2, LUA_TFUNCTION);  /* must be a function */
    lua_settop(L, 2);  /* make sure there are two arguments */
    auxsort(L, 1, (IdxT)n, 0);
  }
>>>>>>> upstream/master
  return 0;
}

/* }====================================================== */


static const luaL_Reg tab_funcs[] = {
  {"concat", tconcat},
#if defined(LUA_COMPAT_MAXN)
  {"maxn", maxn},
#endif
  {"insert", tinsert},
  {"pack", pack},
  {"unpack", unpack},
  {"remove", tremove},
  {"move", tmove},
  {"sort", sort},
  {NULL, NULL}
};


LUAMOD_API int luaopen_table (lua_State *L) {
  luaL_newlib(L, tab_funcs);
#if defined(LUA_COMPAT_UNPACK)
  /* _G.unpack = table.unpack */
  lua_getfield(L, -1, "unpack");
  lua_setglobal(L, "unpack");
#endif
  return 1;
}


/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * tail.h - trie tail for keeping suffixes
 * Created: 2006-08-12
 * Author:  Theppitak Karoonboonyanan <thep@linux.thai.net>
 */

#ifndef __TAIL_H
#define __TAIL_H

#include "triedefs.h"

/**
 * @file tail.h
 * @brief trie tail for keeping suffixes
 */

/**
 * @brief Double-array structure type
 */
typedef struct _Tail  Tail;

/**
 * @brief Open tail data from file
 *
 * @param path : the path that stores the tail files
 * @param name : the name of the tail data (not actual file name)
 * @param mode : openning mode, read or write
 *
 * @return a pointer to the openned tail data, NULL on failure
 *
 * Open a tail data of given name. Note that @a name here does not mean the 
 * actual file name. Rather, the file name will be inferred by the name.
 */
Tail *   tail_open (const char *path, const char *name, TrieIOMode mode);

/**
 * @brief Close tail data
 *
 * @param t : the tail data
 *
 * @return 0 on success, non-zero on failure
 *
 * Close the given tail data. If @a d was openned for writing, all pending 
 * changes will be saved to file.
 */
int      tail_close (Tail *t);

/**
 * @brief Save tail data
 *
 * @param t : the tail data
 *
 * @return 0 on success, non-zero on failure
 *
 * If @a t data was openned for writing, save all pending changes to file.
 */
int      tail_save (Tail *t);


/**
 * @brief Get suffix
 *
 * @param t     : the tail data
 * @param index : the index of the suffix
 *
 * @return an allocated string of the indexed suffix.
 *
 * Get suffix from tail with given @a index. The returned string is allocated.
 * The caller should free it with free().
 */
const TrieChar *    tail_get_suffix (const Tail *t, TrieIndex index);

/**
 * @brief Set suffix of existing entry
 *
 * @param t      : the tail data
 * @param index  : the index of the suffix
 * @param suffix : the new suffix
 *
 * Set suffix of existing entry of given @a index in tail.
 */
Bool     tail_set_suffix (Tail *t, TrieIndex index, const TrieChar *suffix);

/**
 * @brief Add a new suffix
 *
 * @param t      : the tail data
 * @param suffix : the new suffix
 *
 * @return the index of the newly added suffix.
 *
 * Add a new suffix entry to tail.
 */
TrieIndex tail_add_suffix (Tail *t, const TrieChar *suffix);

/**
 * @brief Get data associated to suffix entry
 *
 * @param t      : the tail data
 * @param index  : the index of the suffix
 *
 * @return the data associated to the suffix entry
 *
 * Get data associated to suffix entry @a index in tail data.
 */
TrieData tail_get_data (Tail *t, TrieIndex index);

/**
 * @brief Set data associated to suffix entry
 *
 * @param t      : the tail data
 * @param index  : the index of the suffix
 * @param data   : the data to set
 *
 * @return boolean indicating success
 *
 * Set data associated to suffix entry @a index in tail data.
 */
Bool     tail_set_data (Tail *t, TrieIndex index, TrieData data);

/**
 * @brief Delete suffix entry
 *
 * @param t      : the tail data
 * @param index  : the index of the suffix to delete
 *
 * Delete suffix entry from the tail data.
 */
void     tail_delete (Tail *t, TrieIndex index);

/**
 * @brief Walk in tail with a string
 *
 * @param t          : the tail data
 * @param s          : the tail data index
 * @param suffix_idx : pointer to current character index in suffix
 * @param str        : the string to use in walking
 * @param len        : total characters in @a str to walk
 *
 * @return total number of characters successfully walked
 *
 * Walk in the tail data @a t at entry @a s, from given character position
 * @a *suffix_idx, using @a len characters of given string @a str. On return,
 * @a *suffix_idx is updated to the position after the last successful walk,
 * and the function returns the total number of character succesfully walked.
 */
int      tail_walk_str  (Tail            *t,
                         TrieIndex        s,
                         short           *suffix_idx,
                         const TrieChar  *str,
                         int              len);

/**
 * @brief Walk in tail with a character
 *
 * @param t          : the tail data
 * @param s          : the tail data index
 * @param suffix_idx : pointer to current character index in suffix
 * @param c          : the character to use in walking
 *
 * @return boolean indicating success
 *
 * Walk in the tail data @a t at entry @a s, from given character position
 * @a *suffix_idx, using given character @a c. If the walk is successful,
 * it returns TRUE, and @a *suffix_idx is updated to the next character.
 * Otherwise, it returns FALSE, and @a *suffix_idx is left unchanged.
 */
Bool     tail_walk_char (Tail            *t,
                         TrieIndex        s,
                         short           *suffix_idx,
                         const TrieChar   c);


#endif  /* __TAIL_H */

/*
vi:ts=4:ai:expandtab
*/

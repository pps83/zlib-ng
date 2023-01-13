// inflate.c
#undef PULLBYTE

// adler32.c
#undef partial_hsum
#undef adler32_fold_copy_impl

// insert_string_tpl.h
#undef HASH_SLIDE
#undef HASH_CALC
#undef HASH_CALC_VAR
#undef HASH_CALC_VAR_INIT
#undef HASH_CALC_READ
#undef HASH_CALC_MASK
#undef HASH_CALC_OFFSET
#undef UPDATE_HASH
#undef INSERT_STRING
#undef QUICK_INSERT_STRING
#undef INSERT_STRING_H_

// chunkset_tpl.h
#undef perm_idx_lut
#undef chunk_t
#undef chunkmemset_2
#undef chunkmemset_4
#undef chunkmemset_8
#undef chunkmemset_16
#undef loadchunk
#undef storechunk
#undef loadhalfchunk
#undef storehalfchunk
#undef halfchunk2whole
#undef CHUNKCOPY
#undef CHUNKCOPY_SAFE
#undef CHUNKMEMSET
#undef CHUNKMEMSET_SAFE
#undef CHUNKSIZE
#undef CHUNKUNROLL
#undef CHUNK_SIZE
#undef GET_CHUNK_MAG
#undef GET_HALFCHUNK_MAG
#undef HALFCHUNKCOPY
#undef INFLATE_FAST

#undef HAVE_CHUNKCOPY
#undef HAVE_CHUNKMEMSET_1
#undef HAVE_CHUNKMEMSET_16
#undef HAVE_CHUNKMEMSET_2
#undef HAVE_CHUNKMEMSET_4
#undef HAVE_CHUNKMEMSET_8
#undef HAVE_CHUNKUNROLL
#undef HAVE_CHUNK_MAG
#undef HAVE_HALFCHUNKCOPY
#undef HAVE_HALF_CHUNK
#undef HAVE_MASKED_READWRITE

#undef COPY
#undef XOR_INITIAL

#undef CRC32_FOLD_COPY
#undef CRC32_FOLD
#undef CRC32_FOLD_RESET
#undef CRC32_FOLD_FINAL
#undef CRC32

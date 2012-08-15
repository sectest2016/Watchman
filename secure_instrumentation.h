//-----------------------------
//-----------------------------
//function instrumentation?
//-----------------------------
//-----------------------------
#ifdef INSTRUMENTATION
//turn on "-finstrument-functions" to use these
//XXX turn off if this isn't the gnu compiler?
//TODO can these be inlined?
//TODO make an option to turn these off

void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));
void __cyg_profile_func_enter(void *this_fn, void *call_site) {
  printf("ENTER: %p, from %p\n", this_fn, call_site);
} /* __cyg_profile_func_enter */

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *this_fn, void *call_site) {
  printf("EXIT:  %p, from %p\n", this_fn, call_site);
} /* __cyg_profile_func_enter */
#endif /*INSTRUMENTATION*/


//-----------------------------
//-----------------------------
//help protected objects in C++
//-----------------------------
//-----------------------------
//XXX I think this block belongs somewhere else
#ifdef __GNUG__
	//put C++ specific stuff here
#endif /*__GNUG__*/

//XXX see http://www.gnu.org/software/libc/manual/html_node/Heap-Consistency-Checking.html#Heap-Consistency-Checking

bool ___mcheck_flag = false;

//TODO can these be inlined?
void __cyg_profile_func_enter(void *this_fn, void *call_site)
                              __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	//printf("ENTER: %p, from %p\n", this_fn, call_site);
	//TODO optimize this branch as unlikely (only happens once)
	if(___mcheck_flag == false){
			
		___mcheck_flag = true;
	}
}

void __cyg_profile_func_exit(void *this_fn, void *call_site)
                             __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	//printf("EXIT:  %p, from %p\n", this_fn, call_site);
}

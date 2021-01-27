#include <utmpx.h>
#include <paths.h>
#include <unistd.h>
#include "ruby.h"

#ifndef _PATH_UTMP
#define _PATH_UTMP "/var/log/wtmp"
#endif

#ifndef _PATH_UTMP
#define _PATH_UTMP "/var/run/utmp"
#endif

#ifndef _PATH_BTMP
#define _PATH_BTMP "/var/log/btmp"
#endif

#ifndef R_OK
#define R_OK 4
#endif

#ifndef F_OK
#define F_OK 0
#endif

void read_log(VALUE ary, char *log_path) {
	if(access(log_path, R_OK)) {
		char message[256] ;

		if(access(log_path, F_OK) == 0) {
			sprintf(message, "Permission denied while reading %s", log_path) ;
			rb_raise(rb_eRuntimeError, message, 0) ;
		} else {
			sprintf(message, "No such file or directory %s", log_path) ;
			rb_raise(rb_eRuntimeError, message, 0) ;
		}

		return ;
	}

	struct utmpx data ;

	FILE *log = fopen(log_path, "rb") ;
	unsigned int sizeof_data = sizeof(data) ;

	char *line, *id, *user, *host ;
	short type ;
	unsigned int pid, session ;
	unsigned long long sec, usec ;

	VALUE hash ;

	while(fread(&data, sizeof_data, 1, log) == 1) {
		hash = rb_hash_new() ;

		type = data.ut_type ;
		pid = data.ut_pid ;
		line = data.ut_line ;
		id = data.ut_id ;
		user = data.ut_user ;
		host = data.ut_host ;
		session = data.ut_session ;

		sec = data.ut_tv.tv_sec ;
		usec = data.ut_tv.tv_usec ;

		rb_hash_aset(hash, ID2SYM(rb_intern("type")), INT2FIX(type)) ;
		rb_hash_aset(hash, ID2SYM(rb_intern("pid")), UINT2NUM(pid)) ;
		rb_hash_aset(hash, ID2SYM(rb_intern("line")), rb_str_new_cstr(line)) ;
		rb_hash_aset(hash, ID2SYM(rb_intern("id")), rb_str_new_cstr(id)) ;
		rb_hash_aset(hash, ID2SYM(rb_intern("user")), rb_str_new_cstr(user)) ;
		rb_hash_aset(hash, ID2SYM(rb_intern("host")), rb_str_new_cstr(host)) ;
		rb_hash_aset(hash, ID2SYM(rb_intern("session")), UINT2NUM(session)) ;
		rb_hash_aset(hash, ID2SYM(rb_intern("time")), rb_time_new(sec, usec)) ;

		rb_ary_push(ary, hash) ;
	}

	fclose(log) ;
}

VALUE wtmp(VALUE obj) {
	VALUE ary = rb_ary_new() ;
	read_log(ary, _PATH_WTMP) ;
	return ary ;
}

VALUE utmp(VALUE obj) {
	VALUE ary = rb_ary_new() ;
	read_log(ary, _PATH_UTMP) ;
	return ary ;
}

VALUE btmp(VALUE obj) {
	VALUE ary = rb_ary_new() ;
	read_log(ary, _PATH_BTMP) ;
	return ary ;
}

VALUE parse(VALUE obj, VALUE file) {
	VALUE ary = rb_ary_new() ;
	char *c_f = StringValuePtr(file) ;
	read_log(ary, c_f) ;
	return ary ;
}

void Init_login_records() {
	VALUE _login_records = rb_define_module("LoginRecords") ;
	rb_define_const(_login_records, "PATH_WTMP", rb_str_new_cstr(_PATH_WTMP)) ;
	rb_define_const(_login_records, "PATH_UTMP", rb_str_new_cstr(_PATH_UTMP)) ;
	rb_define_const(_login_records, "PATH_BTMP", rb_str_new_cstr(_PATH_BTMP)) ;

	rb_define_module_function(_login_records, "wtmp", wtmp, 0) ;
	rb_define_module_function(_login_records, "utmp", utmp, 0) ;
	rb_define_module_function(_login_records, "btmp", btmp, 0) ;
	rb_define_module_function(_login_records, "parse", parse, 1) ;
}

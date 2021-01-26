require 'mkmf'

$CFLAGS << ' -O3'

unless have_const('linux') || RbConfig::CONFIG['arch'].to_s[/linux/]
	abort('Platform is not linux')
end

unless have_header('utmpx.h') && have_header('ruby.h')
	abort("Your system doesn't have utmpx.h.")
end

create_makefile 'login_records/login_records'

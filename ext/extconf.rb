require 'mkmf'

abort('Platform is not linux') unless have_const('linux') || RbConfig::CONFIG['arch'].to_s[/linux/]
abort("Your system doesn't have utmpx.h.") unless have_header('utmpx.h') && have_header('ruby.h')
create_makefile 'login_records/login_records'

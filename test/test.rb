begin
	require 'login_records'
rescue LoadError
	abort "You must install login_records before you can run this test"
end

puts "\e[1;4;38;2;255;200;0mUTMP:\e[0m"
puts LoginRecords.utmp

puts "\e[1;4;38;2;255;200;0mWTMP:\e[0m"
puts LoginRecords.wtmp

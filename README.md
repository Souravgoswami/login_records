# LoginRecords
LoginRecords Allows you to read Login Records, well utmp and wmtp files.
The return type is an Array of Hashes.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'login_records'
```

And then execute:

```
$ bundle install
```

Or install it yourself as:

```
$ gem install login_records
```

## Usage

```
>> require 'login_records'
=> true

>> puts LoginRecords.utmp
{:type=>2, :pid=>0, :line=>"~", :id=>"~~", :user=>"reboot", :host=>"5.9.9-xanmod1-1", :session=>0, :time=>2021-01-26 11:15:30.529738 +0530}
=> nil

>> puts LoginRecords.wtmp
{:type=>1, :pid=>0, :line=>"~", :id=>"~~", :user=>"shutdown", :host=>"5.5.10-arch1-1", :session=>0, :time=>2020-03-26 01:30:18.450387 +0530}
{:type=>2, :pid=>0, :line=>"~", :id=>"~~", :user=>"reboot", :host=>"5.5.12-arch1-1", :session=>0, :time=>2020-03-26 01:40:35.355035 +0530}
{:type=>1, :pid=>0, :line=>"~", :id=>"~~", :user=>"shutdown", :host=>"5.5.12-arch1-1", :session=>0, :time=>2020-03-26 04:49:31.611724 +0530}
{:type=>2, :pid=>0, :line=>"~", :id=>"~~", :user=>"reboot", :host=>"5.5.13-arch1-1", :session=>0, :time=>2020-03-26 04:49:59.406445 +0530}
...
...
{:type=>1, :pid=>0, :line=>"~", :id=>"~~", :user=>"shutdown", :host=>"5.9.9-xanmod1-1", :session=>0, :time=>2021-01-26 04:24:02.025406 +0530}
{:type=>2, :pid=>0, :line=>"~", :id=>"~~", :user=>"reboot", :host=>"5.9.9-xanmod1-1", :session=>0, :time=>2021-01-26 11:15:30.529738 +0530}


>> puts LoginRecords.btmp
[{:type=>6, :pid=>49479, :line=>"pts/0", :id=>"0", :user=>"root", :host=>"", :session=>0, :time=>2021-01-27 02:25:10.312062 +0530}]
```

Parsing files:
You can parse utmp files easily:

```
>> LoginRecords.parse('path/to/file')
```

Everything but the timezone is trusted. UTMP or WTMP files don't store timezone.
The timezone returned by the time is local to the system and can be modified by setting the TZ environment variable.

## Constants

There are 3 constants:
1. LoginRecords::PATH_UTMP
2. LoginRecords::PATH_WTMP
3. LoginRecords::PATH_BTMP

These can be used to get the path. Even if you reassign them, they will just reassign on the Ruby level.
The code will not read the reassigned file in other words. It will continue using the older ones.

If you want to read a custom file instead, just use `LoginRecords.parse()` method.

## Errors

On error, RuntimeError is raised for the following problems:
1. ReadError: Any of WTMP, UTMP, BTMP files can't be read when the method is called.
2. No File: If the file doesn't exist.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Souravgoswami/login_records.

## License

The gem is available as open-source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

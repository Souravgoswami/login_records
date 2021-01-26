# frozen_string_literal: true
require_relative "lib/login_records/version"

Gem::Specification.new do |s|
	s.name = "login_records"
	s.version = LoginRecords::VERSION
	s.authors = ["Sourav Goswami"]
	s.email = ["souravgoswami@protonmail.com"]
	s.summary = "LoginRecords Allows you to read UTML and WMTP files on Linux"
	s.description = s.summary
	s.homepage = "https://github.com/Souravgoswami/login_records"
	s.license= "MIT"
	s.required_ruby_version = Gem::Requirement.new(">= 2.1")
	s.files = Dir.glob(%w(lib/**/*rb ext/**/*{rb,c} LICENCE))
	s.require_paths = ["lib"]
	s.extensions = Dir.glob(%w(ext/**/extconf.rb))
end

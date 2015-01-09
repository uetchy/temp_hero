#!/usr/bin/env ruby

DELIMITER = "<:br:>"

if ARGV.size < 1
  puts "Usage: aa_converter.rb aa.txt"
  exit
end

filepath = File.expand_path(ARGV.first)

aa = open(filepath).read
result = ""
aa.each_line do |line|
  result += line.strip
  result += DELIMITER
end
open("#{File.basename(filepath)}-converted", "w") do |f|
  f.print [result].pack('m').gsub(/\n/, "")
end

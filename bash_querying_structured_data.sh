
# Location Count AverageSalary
awk  -F ',' 'BEGIN {print "Location\tCount\tAverageSalary(K)"};NR>1{loc[$7]++; sum[$7] = sum[$7] + $8}; END{ for(l in loc){ print l "\t" loc[l] "\t" sum[l]/(loc[l]*1000)}; }' content_structured_comma_employees.txt



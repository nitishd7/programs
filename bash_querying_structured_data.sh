
echo " -------------Print count of employees and average salary by location------------- "
awk  -F ',' 'BEGIN {print "Location\tCount\tAverageSalary(K)"};NR>1{loc[$7]++; sum[$7] = sum[$7] + $8}; END{ for(l in loc){ print l "\t" loc[l] "\t" sum[l]/(loc[l]*1000)}; }' content_structured_comma_employees.txt

echo 
echo " -------------Print all rows without header--------------- "
tail -n +2 content_structured_comma_employees.txt

echo
echo " -------------Print top 2 lines---------------- "
tail -n +2 content_structured_comma_employees.txt | head -n 2

echo
echo " -------------Print bottom 2 lines--------------- "
tail -n 2 content_structured_comma_employees.txt

echo
echo " -------------Print distinct result sorted by salary-------------- "
tail -n +2 content_structured_comma_play_employees.txt | uniq | sort -t ',' -k 8 -n --reverse

echo
echo " -------------Match phone numbers with area code ----------------- "
grep -o '[[:digit:]]\{,3\}-[[:digit:]]*' content_structured_space_play_employees.txt

echo
echo " -------------Match phone numbers without area code ----------------- "
grep -v '[[:digit:]]\{,3\}-' content_structured_space_play_employees.txt

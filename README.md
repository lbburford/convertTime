# convertTime
sensorgnome/find_tags_unifile processes pulse data recorded by each sensorgnome. It is a component of the sensorgnome software in both V1 and V2. If can be fed a file containing all of the data recorded and it outputs a comma-separated value file with detection information (along with a header). The time field is in seconds since 1970-01-01 and needs conversion to a human-readable format.

There are many ways in which it can be converted (I've done it with Excel, Javascript, and python) but I had fun writing and compiling this program to do the conversion with C++.

I suggest the following usage:

$convert-time input_file.csv > output_time_readable.csv

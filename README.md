A utility to query and update Apples SMC on intel mac's

smc_util [-c] [-q] [-d] [-D] [-p] [-f] [-v] [-t] [-s] [-x] [-n] [-r <key> ] [ -w <key> ] [-l]   [ <value>|keys... ]
-c          suppress newline
-q          be quiet as a mouse
-d          increase debug output
-D          Display known descriptions
-p          Private/Paranoide, blank out the System Serial#
-f          display FAN specific data
-v          display values
-t          display [type](s)
-s          display :size
-x          dump values in (hexbytes)
-n          when normally a single line output line breaks between variables
-w <key>    write value to key
-l          list all keys to stdout
with out options -w or -l the default is to read args[] as a series of keys to display

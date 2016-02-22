~/work/active/sw/BUILD/2016-data-formats-tests-latest/2016-data-formats-tests/benchmark 1 2>&1     | sed -e 's|:.*|,|'  | tr \\n \  | sed -e 's/,[ ]*$//;s/^/N,/'
# Actual data CSV
for N in 1 10 50 100 250 500 1000 2500 5000; do
  ~/work/active/sw/BUILD/2016-data-formats-tests-latest/2016-data-formats-tests/benchmark $N 2>&1    | sed -e 's|.*:[ ]*|,|'  | tr \\n \  | sed -e "s/,$//;s/^,/$N,/"
done

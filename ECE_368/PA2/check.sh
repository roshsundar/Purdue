#!/bin/bash
PROG=pa2
COUNT=pa2_examples/count
INPUT=pa2_examples/encoded
DECODED=pa2_examples/decoded
EVAL=pa2_examples/eval
TREE=pa2_examples/tree

LIST="binary1 gophers lorum stone woods"
set `echo ${LIST}`
for category
do
  

./${PROG} ${INPUT}/${category}_huff.hbt tree decoded freq huff eval_
diff tree ${TREE}/${category}_huff.tree
diff decoded ${DECODED}/${category}
diff freq ${COUNT}/${category}.count
diff huff ${TREE}/${category}_huff.tree
diff eval_ ${EVAL}/${category}_huff.eval

./${PROG} ${INPUT}/${category}_nonhuff.hbt tree decoded freq huff eval_
diff tree ${TREE}/${category}_nonhuff.tree
diff decoded ${DECODED}/${category}
diff freq ${COUNT}/${category}.count
diff huff ${TREE}/${category}_huff.tree
diff eval_ ${EVAL}/${category}_nonhuff.eval

done
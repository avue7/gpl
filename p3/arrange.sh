#!/bin/bash

# The %20s, specifies the spaces followed by -n says space to the right
cat tokens.txt | awk '{printf("%-20s",$3); printf("return %-20s",$2); printf("\n")}' > arranged_tokens.txt

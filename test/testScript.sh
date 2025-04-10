#!/bin/bash



# Move to root directory 
PROJECT_ROOT="$(dirname "$0")/.."
cd "$PROJECT_ROOT" || exit 1



# Build 
if make; then
    echo -e "Build succeeded\n"

else
    echo "Build failed. Exiting."
    exit 1
fi




#########################        Part 1       ###########################

# Loop through the 6 test files 
for i in {1..6}; do
    TEST_FILE="programming_assignment_1-test_file_${i}"
    
    if [[ $i -le 4 ]]; then
        INPUT_FILE="test/testFiles/${TEST_FILE}.c"
        EXPECTED_OUTPUT="test/solutionFiles/output-${TEST_FILE}.c"
        ACTUAL_OUTPUT="test/output-${i}.txt"

        echo "* Running test $i (normal case)..."

        ./parser "$INPUT_FILE" "$ACTUAL_OUTPUT" 1

        if diff -q "$ACTUAL_OUTPUT" "$EXPECTED_OUTPUT" > /dev/null; then
            echo "  Test $i passed!"
        else
            echo "  Test $i failed. Differences:"
            diff "$ACTUAL_OUTPUT" "$EXPECTED_OUTPUT"
        fi


    else
        INPUT_FILE="test/testFiles/${TEST_FILE}.c"
        EXPECTED_ERROR="test/solutionFiles/output-${TEST_FILE}.txt"
        ACTUAL_ERROR="test/error-${i}.txt"

        echo "* Running test $i (error case)..."

        ./parser "$INPUT_FILE" dummy_output.txt 2> "$ACTUAL_ERROR" 1

        if diff -q "$ACTUAL_ERROR" "$EXPECTED_ERROR" > /dev/null; then
            echo "  Test $i passed (error message matched)"
        else
            echo "  Test $i failed. Differences in error message:"
            diff "$ACTUAL_ERROR" "$EXPECTED_ERROR"
        fi
    fi

    echo "-------------------------------------- "
done

# Cleanup generated output files
echo "Cleaning up test outputs..."
rm -f test/output-*.txt test/error-*.txt dummy_output.txt



#########################        Part 2       ###########################
#########################        Part 3       ###########################
#########################        Part 4       ###########################

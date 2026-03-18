#!/bin/bash

# Initialize Git submodules
git submodule update --init --recursive

# Build the Docker image
sudo docker build -t c2rustify .

# Define the list of commands
COMMANDS=("preprocess" "refactor" "analyze" "decompose" "generate")

# Get the list of subjects
SUBJECTS=$(ls artifacts/)

# Iterate over each subject
for SUBJECT in $SUBJECTS; do
    # Iterate over each command
    for COMMAND in "${COMMANDS[@]}"; do
        # Run the Docker container with the current subject and command
        sudo docker run -v $(pwd)/artifacts:/app/artifacts c2rustify $COMMAND subjects/$SUBJECT artifacts/$SUBJECT/$COMMAND
    done
done

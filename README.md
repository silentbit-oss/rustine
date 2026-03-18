# :warning: 
> This repository currently contains only the tool artifacts. The source code has been temporarily removed and **will be released upon acceptance of the associated paper**.
# Rustine Overview
Rustine uses static and dynamic analysis and large language models to translate C repositories to safe Rust. 

# Translating C Projects to Safe Rust with Rustine
Please follow the instructions below to install and use the Rustine tool. If you face any issues, we recommend you open an issue under the issue tracker. 

## 1- Cloning the Repo
Proceed to the location you want to download the Rustine. Then, run the command below:
```
git clone https://github.com/silentbit-oss/rustine.git
```
When successful, this command creates a folder called rustine.

## 2- Installation
Rustine is dockerized to accommodate different running environments. We do not support running Rustine out of the provided container. Please follow the steps below to use the docker.

```bash
cd rustine

git submodule update --init --recursive

sudo docker build -t rustine .
```

The tool provides several commands for handling different aspects of C to Rust translation:

- `run`: Execute the complete translation pipeline end-to-end
- `preprocess`: Preprocess the given C code.
- `refactor`: Refactor C code for optimal translation
- `analyze`: Extract metadata and analyze C code structure
- `decompose`: Break down C code into manageable segments
- `evaluate`: Compare translated Rust code with C source
- `generate`: Create Rust project template structure
- `translate`: Perform LLM-based C to Rust translation
- `validate`: Verify semantic equivalence between C and Rust code

To get help with these commands, you can run the help commands as below:

```bash
sudo docker run rustine --help 

sudo docker run rustine 'command-name' --help
```

### 3- Running Rustine

Use the following commands for each specific action:

```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine $COMMAND [OPTIONS]

# Examples

## Preprocess:
### one file:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine preprocess subjects/genann/genann.c artifacts/genann/preprocess
### repository:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine preprocess subjects/genann/ artifacts/genann/preprocess

### Refactor:
### one file:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine refactor subjects/genann/genann.c artifacts/genann/refactored_genann.c
### repository:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine refactor subjects/genann/ artifacts/genann/refactor/

### Analyze:
### one file:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine analyze subjects/genann/genann.c artifacts/genann/analyze
### repository:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine analyze subjects/genann/ artifacts/genann/analyze

### Decompose:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine decompose subjects/genann artifacts/genann/decompose

### Generate:
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine generate subjects/genann/compile_commands.json artifacts/genann/genannrs -e example1.c -e example2.c -e example3.c -e example4.c -t test.c

### Translate:
sudo docker run -e OPENAI_API_KEY="KEY" -v $(pwd)/artifacts:/app/artifacts rustine translate subjects/genann/compile_commands.json artifacts/genann/genann.translate
```

### 4- Command Details

#### Preprocess
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine preprocess [...SOURCE_CODES...] OUTPUT_DIR
```
This stage resolve C preprocessors in code and generate clean code plus list of included headers

For example you can find result of this command in [here](./artifacts/genann/preprocess)

```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine preprocess subjects/genann/genann.c artifacts/genann/preprocess
```

#### Refactor
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine refactor [...SOURCE_CODES...] REFACTORED_CODE.c
```
Refactors the input C codes to prepare it for smooth translation.

list of refactors are:
- Extract uniary operators like [++ / --] from statement specifically from pointer aritmetic
- Convert uniary operators like [++ / --] to [+= / -=]
- Convert C switch-case statements to if-else chains using AST transformations to improve C-to-Rust translation.

For example you can find result of this command in [here](./artifacts/genann/refactor)
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine refactor subjects/genann/genann.c artifacts/genann/refactored_genann.c

sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine refactor subjects/libcsv/libcsv.c artifacts/refactored_csv.c
``` 

#### Analyze
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine analyze [OPTIONS] [...SOURCE_CODES...] OUTPUT_FOLDER
```
Analyzes C code and extracts relevant metadata.
- callgraph
- list of structs
- list of functions
    - list of function input/output parameters and their types
    - list of local variables in function
    - list of function calls in the function
- global variables and their types
- list of typedefs

For example you can find result of this command in [here](./artifacts/genann/analyze)
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine analyze subjects/genann/genann.c artifacts/genann/analyze
```

#### Decompose
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine decompose COMPILE_COMMAND.JSON OUTPUT
```
Breaks down C code into smaller, meaningful segments for translation with their dependencies

For example you can find result of this command in [here](./artifacts/genann/decompose)
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine decompose subjects/genann/compile_commands.json artifacts/genann/decompose -e example1.c -e example2.c -e example3.c -e example4.c -t test.c
``` 

#### Evaluate
```bash
pipeline evaluate C_SOURCE RUST_OUTPUT
```
Evaluates the quality of the Rust translation compared to the C source.

#### Generate
```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine generate COMPILE_COMMAND.json OUTPUT_FOLDER -e [...EXAMPLES...] -t [...TESTS...]
```
Generates a new Rust project template structure in this format

```bash
sudo docker run -v $(pwd)/artifacts:/app/artifacts rustine generate subjects/genann/compile_commands.json artifacts/genann/genannrs -e example1.c -e example2.c -e example3.c -e example4.c -t test.c

.
├── Cargo.toml
├── examples
│   ├── example1
│   │   └── example1.rs
│   ├── example2
│   │   └── example2.rs
│   ├── example3
│   │   └── example3.rs
│   └── example4
│       └── example4.rs
├── src
└── tests
    └── test.rs
```

#### Translate
```bash
sudo docker run -e OPENAI_API_KEY="YOUR_DEEPSEEK_KEY" -v $(pwd)/artifacts:/app/artifacts rustine decompose COMPILE_COMMAND.JSON OUTPUT
```
Translate C to Rust segment by segment using an LLM.

For example you can find result of this command in [here](./artifacts/genann/genann.translate)

```bash
sudo docker run -e OPENAI_API_KEY="KEY" -v $(pwd)/artifacts:/app/artifacts rustine translate subjects/genann/compile_commands.json artifacts/genann/genann.translate
```

#### Validate
```bash
pipeline validate C_SOURCE RUST_OUTPUT
```
Validates semantic equivalence between C and Rust implementations.

#### Run
```bash
pipeline run
```
Executes the complete translation pipeline with default settings.





<!--
## Installation

```bash
// Go to rustine project directory

git submodule update --init --recursive

pip install -r requirements.txt
```
-->
